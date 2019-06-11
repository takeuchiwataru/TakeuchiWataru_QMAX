//=============================================================================
//
// �|�[�Y���ڏ��� [pauseselect.cpp]
// Author : �|���j
//
//=============================================================================
#include "pauseselect.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME1        "data/TEXTURE/pause000.png" // �ǂݍ��ރe�N�X�`����(CONTINUE)
#define TEXTURE_NAME2        "data/TEXTURE/pause001.png" // �ǂݍ��ރe�N�X�`����(RETRY)
#define TEXTURE_NAME3        "data/TEXTURE/pause002.png" // �ǂݍ��ރe�N�X�`����(QUIT)
#define MAX_PAUSE_SELECT     (RESTART_MAX)               // �|�[�Y�I���ł��鍀�ڂ̐�
#define PAUSESELECT_POS_X    (470)                       // �|�[�Y���ڂ̍���w���W
#define PAUSESELECT_POS_Y    (220)                       // �|�[�Y���ڍ���x���W
#define PAUSESELECT_WIDTH    (800)                       // �|�[�Y���ڂ̕�
#define PAUSESELECT_HEIGHT   (280)                       // �|�[�Y���ڂ̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePauseSelect[MAX_PAUSE_SELECT] = {}; // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseSelect = NULL;                 // ���_�o�b�t�@�ւ̃|�C���^
PAUSE                   g_aPause[MAX_PAUSE_SELECT];                   // �|�[�Y����
RESTART                 g_restart;                                    // �J�ڂ����
float                   g_col;                                        // �F�̕ω��Ɏg�p
int                     g_Select;                                     // �I���Ɏg�p

//=============================================================================
// ����������
//=============================================================================
void InitPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_aPause[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);  // �F��������
	g_aPause[0].select = PAUSESELECT_SELECT;              // �X�^�[�g��CONTINUE����
	// �l�̏�����
	for (int nCntPauseSelect = 1; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// ���ڂ̐������J��Ԃ�
		g_aPause[nCntPauseSelect].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);  // �F��������
		g_aPause[nCntPauseSelect].select = PAUSESELECT_NONE;                // �I������Ă��Ȃ���Ԃɂ���
	}
	g_col = 0.01f;                // �F�̕ω���������
	g_restart = RESTART_CONTINUE; // �Q�[���ĊJ��Ԃɂ��Ă���
	g_Select = 0;                 // �I������Ă���ԍ���CONTINUE��

	// ���_���̐ݒ�
	MakeVertexPauseSelect(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseSelect(void)
{
	// �e�N�X�`���̊J��
	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// �ǂݍ��񂾃e�N�X�`���̐������J��Ԃ�
		if (g_pTexturePauseSelect[nCntPauseSelect] != NULL)
		{
			g_pTexturePauseSelect[nCntPauseSelect]->Release();
			g_pTexturePauseSelect[nCntPauseSelect] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseSelect != NULL)
	{
		g_pVtxBuffPauseSelect->Release();
		g_pVtxBuffPauseSelect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseSelect(void)
{
	// �I�����ڈړ�����
	if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true)
	{// S�L�[�������ꂽ
		g_aPause[g_Select].select = PAUSESELECT_NONE;
		g_aPause[(g_Select + 1) % MAX_PAUSE_SELECT].select = PAUSESELECT_SELECT;
		g_Select = (g_Select + 1) % MAX_PAUSE_SELECT;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_UP) == true)
	{// W�L�[�������ꂽ
		g_aPause[g_Select].select = PAUSESELECT_NONE;
		g_aPause[(g_Select + (MAX_PAUSE_SELECT - 1)) % MAX_PAUSE_SELECT].select = PAUSESELECT_SELECT;
		g_Select = (g_Select + (MAX_PAUSE_SELECT - 1)) % MAX_PAUSE_SELECT;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// ���ڂ̐������J��Ԃ�
		if (g_aPause[nCntPauseSelect].select == PAUSESELECT_SELECT)
		{// �I������Ă�����
			g_aPause[nCntPauseSelect].col.r += g_col;
			g_aPause[nCntPauseSelect].col.g += g_col;
			g_aPause[nCntPauseSelect].col.b += g_col;

			if (g_aPause[nCntPauseSelect].col.r < 0.2f || g_aPause[nCntPauseSelect].col.r >= 1.0f)
			{// �F������̒l�ɒB����
				g_col *= -1;
			}
		}
		else if (g_aPause[nCntPauseSelect].select == PAUSESELECT_NONE)
		{// �I������Ă��Ȃ�������
			g_aPause[nCntPauseSelect].col.r = 0.2f;
			g_aPause[nCntPauseSelect].col.g = 0.2f;
			g_aPause[nCntPauseSelect].col.b = 0.2f;
		}
		// ���_�J���[�̍X�V
		pVtx[0].col = g_aPause[nCntPauseSelect].col;
		pVtx[1].col = g_aPause[nCntPauseSelect].col;
		pVtx[2].col = g_aPause[nCntPauseSelect].col;
		pVtx[3].col = g_aPause[nCntPauseSelect].col;

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseSelect->Unlock();

	// ��ʑJ��
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{// ENTER�L�[�������ꂽ
		switch (g_Select)
		{
		case RESTART_CONTINUE:
			g_restart = RESTART_CONTINUE; // �Q�[���ĊJ��Ԃ�
			break;
		case RESTART_RETRY:
			g_restart = RESTART_RETRY;    // �Q�[����蒼����Ԃ�
			break;
		case RESTART_QUIT:
			g_restart = RESTART_QUIT;     // �^�C�g���J�ڏ�Ԃ�
			StopSound(SOUND_LABEL_BGM_GAME);
			break;
		}
		//PlaySound(SOUND_LABEL_SE_DECIDE);
	}
	if (GetKeyboardTrigger(DIK_P))
	{// �|�[�Y���������ꂽ
		g_aPause[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);  // �F��������
		g_aPause[0].select = PAUSESELECT_SELECT;              // �X�^�[�g��CONTINUE����
		for (int nCntPauseSelect = 1; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
		{// ���ڂ̐������J��Ԃ�
			g_aPause[nCntPauseSelect].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);  // �F��������
			g_aPause[nCntPauseSelect].select = PAUSESELECT_NONE;                // �I������Ă��Ȃ���Ԃɂ���
		}
		g_Select = 0;      // �I������Ă���ԍ���CONTINUE��
		VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
		{
			pVtx[0].col = g_aPause[nCntPauseSelect].col;
			pVtx[1].col = g_aPause[nCntPauseSelect].col;
			pVtx[2].col = g_aPause[nCntPauseSelect].col;
			pVtx[3].col = g_aPause[nCntPauseSelect].col;
			pVtx += 4;
		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPauseSelect->Unlock();
	}
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPauseSelect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// ���ڂ̐������J��Ԃ�
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePauseSelect[nCntPauseSelect]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseSelect * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���(CONTINUE)
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME1,
		&g_pTexturePauseSelect[0]);

	// �e�N�X�`���̓ǂݍ���(RETRY)
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME2,
		&g_pTexturePauseSelect[1]);

	// �e�N�X�`���̓ǂݍ���(QUIT)
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME3,
		&g_pTexturePauseSelect[2]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE_SELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseSelect,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	float Pos = 0.0f;

	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// ���ڂ̐������J��Ԃ�
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(PAUSESELECT_POS_X, PAUSESELECT_POS_Y  + Pos, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PAUSESELECT_WIDTH, PAUSESELECT_POS_Y  + Pos, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PAUSESELECT_POS_X, PAUSESELECT_HEIGHT + Pos, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PAUSESELECT_WIDTH, PAUSESELECT_HEIGHT + Pos, 0.0f);

		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = g_aPause[nCntPauseSelect].col;
		pVtx[1].col = g_aPause[nCntPauseSelect].col;
		pVtx[2].col = g_aPause[nCntPauseSelect].col;
		pVtx[3].col = g_aPause[nCntPauseSelect].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		Pos += 110;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseSelect->Unlock();
}
//=============================================================================
// ���ڂ̎擾
//=============================================================================
RESTART GetRestart(void)
{
	return g_restart;
}