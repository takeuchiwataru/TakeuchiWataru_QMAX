//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "pause.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//--------------
// ����ʗp
//--------------
#define PAUSE_POS_X        (0)                         // �|�[�Y�̍���w���W
#define PAUSE_POS_Y        (0)                         // �|�[�Y�̍���x���W
#define PAUSE_WIDTH        (SCREEN_WIDTH)              // �|�[�Y�̕�
#define PAUSE_HEIGHT       (SCREEN_HEIGHT)             // �|�[�Y�̍���

//--------------
// ���S�p
//--------------
#define TEXTURE_NAME       "data/TEXTURE/pause100.png"  // �ǂݍ��ރe�N�X�`���t�@�C����
#define PAUSELOGO_POS_X    (350)                              // �|�[�Y���S�̍���w���W
#define PAUSELOGO_POS_Y    (150)                              // �|�[�Y���S����x���W
#define PAUSELOGO_WIDTH    (970)                              // �|�[�Y���S�̕�
#define PAUSELOGO_HEIGHT   (570)                              // �|�[�Y���S�̍���

//--------------
// �I�����ڗp
//--------------
#define PAUSESELECT_TEXTURE_NAME1  "data/TEXTURE/pause000.png" // �ǂݍ��ރe�N�X�`���t�@�C����(�ĊJ)
#define PAUSESELECT_TEXTURE_NAME2  "data/TEXTURE/pause001.png" // �ǂݍ��ރe�N�X�`���t�@�C����(��蒼��)
#define PAUSESELECT_TEXTURE_NAME3  "data/TEXTURE/pause002.png" // �ǂݍ��ރe�N�X�`���t�@�C����(�I��)
#define MAX_PAUSE_SELECT          (RESTART_MAX)                      // �|�[�Y�I���ł��鍀�ڂ̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexPauseLogo(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//--------------
// ����ʗp
//--------------
LPDIRECT3DTEXTURE9		g_pTexturePause = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR				g_colorPause;			// �|�[�Y��ʐF

//--------------
// ���S�p
//--------------
LPDIRECT3DTEXTURE9		g_pTexturePauseLogo = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseLogo = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR				g_colorPauseLogo;		    // �|�[�Y���S�F

//--------------
// �I�����ڗp
//--------------
LPDIRECT3DTEXTURE9		g_pTexturePauseSelect[MAX_PAUSE_SELECT] = {}; // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseSelect = NULL;                 // ���_�o�b�t�@�ւ̃|�C���^
PAUSE                   g_aPause[MAX_PAUSE_SELECT];                   // �|�[�Y����
RESTART                 g_restart;                                    // �J�ڂ����
float                   g_col;                                        // �F�̕ω��Ɏg�p
int                     g_Select;                                     // �I���Ɏg�p

//=============================================================================
// ����������
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_colorPause = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	// ���_���̐ݒ�
	MakeVertexPause(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPause(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePause(void)
{

}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);


	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorPause;
	pVtx[1].col = g_colorPause;
	pVtx[2].col = g_colorPause;
	pVtx[3].col = g_colorPause;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
// �|�[�Y���S�̏���������
//=============================================================================
void InitPauseLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_colorPauseLogo = D3DXCOLOR(0.3f, 0.8f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexPauseLogo(pDevice);
}

//=============================================================================
// �|�[�Y���S�̏I������
//=============================================================================
void UninitPauseLogo(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePauseLogo != NULL)
	{
		g_pTexturePauseLogo->Release();
		g_pTexturePauseLogo = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseLogo != NULL)
	{
		g_pVtxBuffPauseLogo->Release();
		g_pVtxBuffPauseLogo = NULL;
	}
}

//=============================================================================
// �|�[�Y���S�̍X�V����
//=============================================================================
void UpdatePauseLogo(void)
{
}
//=============================================================================
// �|�[�Y���S�̕`�揈��
//=============================================================================
void DrawPauseLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPauseLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �|�[�Y���S�̒��_���̍쐬
//=============================================================================
void MakeVertexPauseLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTexturePauseLogo);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseLogo,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(PAUSELOGO_POS_X, PAUSELOGO_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSELOGO_WIDTH, PAUSELOGO_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSELOGO_POS_X, PAUSELOGO_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSELOGO_WIDTH, PAUSELOGO_HEIGHT, 0.0f);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorPauseLogo;
	pVtx[1].col = g_colorPauseLogo;
	pVtx[2].col = g_colorPauseLogo;
	pVtx[3].col = g_colorPauseLogo;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseLogo->Unlock();
}
//=============================================================================
// �I�����ڂ̏���������
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
		g_aPause[nCntPauseSelect].nCounter = 0;                             // �J�E���^�[�͖߂��Ă���
	}
	g_col = 0.01f;                // �F�̕ω���������
	g_restart = RESTART_CONTINUE; // �Q�[���ĊJ��Ԃɂ��Ă���
	g_Select = 0;                 // �I������Ă���ԍ���CONTINUE��

								  // ���_���̐ݒ�
	MakeVertexPauseSelect(pDevice);
}

//=============================================================================
// �I�����ڂ̏I������
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
// �I�����ڂ̍X�V����
//=============================================================================
void UpdatePauseSelect(void)
{
	if (GetFade() == FADE_NONE)
	{// �t�F�[�h���Ă��Ȃ�
		// �I�����ڈړ�����
		if (GetJoyPadTrigger(DIJS_BUTTON_18,0) == TRUE || GetKeyboardTrigger(DIK_W) == true
			|| GetKeyboardRepeat(DIK_W) == true || GetJoyPadRepeat(DIJS_BUTTON_18,0) == true)
		{// ������̓��͂����ꂽ
			g_aPause[g_Select].select = PAUSESELECT_NONE;
			g_aPause[(g_Select + (MAX_PAUSE_SELECT - 1)) % MAX_PAUSE_SELECT].select = PAUSESELECT_SELECT;
			g_Select = (g_Select + (MAX_PAUSE_SELECT - 1)) % MAX_PAUSE_SELECT;
			g_aPause[g_Select].col.r = 0.8f;
			g_aPause[g_Select].col.g = 0.8f;
			g_aPause[g_Select].col.b = 0.8f;
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetJoyPadTrigger(DIJS_BUTTON_19,0) == TRUE || GetKeyboardTrigger(DIK_S) == true
			|| GetKeyboardRepeat(DIK_S) == true || GetJoyPadRepeat(DIJS_BUTTON_19,0) == true)
		{// �������̓��͂����ꂽ
			g_aPause[g_Select].select = PAUSESELECT_NONE;
			g_aPause[(g_Select + 1) % MAX_PAUSE_SELECT].select = PAUSESELECT_SELECT;
			g_Select = (g_Select + 1) % MAX_PAUSE_SELECT;
			g_aPause[g_Select].col.r = 0.8f;
			g_aPause[g_Select].col.g = 0.8f;
			g_aPause[g_Select].col.b = 0.8f;
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// ����{�^���������ꂽ
			g_aPause[g_Select].select = PAUSESELECT_PUSH;   // ������Ă�����
			g_aPause[g_Select].col.r = 1.0f;
			g_aPause[g_Select].col.g = 1.0f;
			g_aPause[g_Select].col.b = 1.0f;
		}
		if (GetJoyPadTrigger(DIJS_BUTTON_9,0) == TRUE || GetKeyboardTrigger(DIK_P) == true)
		{// �|�[�Y���������ꂽ
			g_aPause[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);  // �F��������
			g_aPause[0].select = PAUSESELECT_SELECT;              // �X�^�[�g��CONTINUE����
			for (int nCntPauseSelect = 1; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
			{// ���ڂ̐������J��Ԃ�
				g_aPause[nCntPauseSelect].col = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);  // �F��������
				g_aPause[nCntPauseSelect].select = PAUSESELECT_NONE;                // �I������Ă��Ȃ���Ԃɂ���
			}
			g_Select = 0;      // �I������Ă���ԍ���CONTINUE��
		}
		// ��ʑJ��
		if (GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// ����{�^���������ꂽ
			switch (g_Select)
			{
			case RESTART_CONTINUE:
				g_restart = RESTART_CONTINUE; // �Q�[���ĊJ��Ԃ�
				break;
			case RESTART_RETRY:
				g_restart = RESTART_RETRY;    // �Q�[����蒼����Ԃ�
				PlaySound(SOUND_LABEL_SE_DECIDE);
				break;
			case RESTART_QUIT:
				g_restart = RESTART_QUIT;     // �^�C�g���J�ڏ�Ԃ�
				PlaySound(SOUND_LABEL_SE_DECIDE);
				break;
			}
		}
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

			if (g_aPause[nCntPauseSelect].col.r < 0.3f || g_aPause[nCntPauseSelect].col.r >= 1.0f)
			{// �F������̒l�ɒB����
				g_col *= -1;
			}
		}
		else if (g_aPause[nCntPauseSelect].select == PAUSESELECT_NONE)
		{// �I������Ă��Ȃ�������
			g_aPause[nCntPauseSelect].col.r = 0.15f;
			g_aPause[nCntPauseSelect].col.g = 0.15f;
			g_aPause[nCntPauseSelect].col.b = 0.15f;
		}
		else if (g_aPause[nCntPauseSelect].select == PAUSESELECT_PUSH)
		{// ������Ă����ԂȂ�
			g_aPause[nCntPauseSelect].nCounter++;
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
}
//=============================================================================
// �I�����ڂ̕`�揈��
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
		if (g_aPause[nCntPauseSelect].select != PAUSESELECT_PUSH || g_aPause[nCntPauseSelect].select == PAUSESELECT_PUSH && g_aPause[nCntPauseSelect].nCounter % 3 == 0)
		{// ����L�[��������Ă��Ȃ���,���łɉ�����Ă��ăJ�E���^�[������̒l��������
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePauseSelect[nCntPauseSelect]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseSelect * 4, NUM_POLYGON);
		}
	}
}

//=============================================================================
// �I�����ڂ̒��_���̍쐬
//=============================================================================
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���(CONTINUE)
	D3DXCreateTextureFromFile(pDevice,
		PAUSESELECT_TEXTURE_NAME1,
		&g_pTexturePauseSelect[0]);

	// �e�N�X�`���̓ǂݍ���(RETRY)
	D3DXCreateTextureFromFile(pDevice,
		PAUSESELECT_TEXTURE_NAME2,
		&g_pTexturePauseSelect[1]);

	// �e�N�X�`���̓ǂݍ���(QUIT)
	D3DXCreateTextureFromFile(pDevice,
		PAUSESELECT_TEXTURE_NAME3,
		&g_pTexturePauseSelect[2]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (4 * MAX_PAUSE_SELECT),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseSelect,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	//-----------
	//  �ĊJ
	//-----------

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(500, 190, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(830, 190, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(500, 280, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(830, 280, 0.0f);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_aPause[0].col;
	pVtx[1].col = g_aPause[0].col;
	pVtx[2].col = g_aPause[0].col;
	pVtx[3].col = g_aPause[0].col;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//-----------
	//  ��蒼��
	//-----------

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(440, 310, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(880, 310, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(440, 400, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(880, 400, 0.0f);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_aPause[0].col;
	pVtx[1].col = g_aPause[0].col;
	pVtx[2].col = g_aPause[0].col;
	pVtx[3].col = g_aPause[0].col;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//-----------
	//  �I��
	//-----------

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(515, 430, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(815, 430, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(515, 520, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(815, 520, 0.0f);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_aPause[0].col;
	pVtx[1].col = g_aPause[0].col;
	pVtx[2].col = g_aPause[0].col;
	pVtx[3].col = g_aPause[0].col;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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