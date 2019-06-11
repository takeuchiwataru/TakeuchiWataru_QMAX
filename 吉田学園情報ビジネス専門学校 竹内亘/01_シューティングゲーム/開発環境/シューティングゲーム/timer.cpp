//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : �|���j
//
//=============================================================================
#include "timer.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIMER		"data/TEXTURE/number000.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define TIMER_SIZE (20.0f)									//�^�C�}�[�T�C�Y
#define TIMER_WIDE (30)										//�^�C�}�[�̕�
#define TIMER_POS (100)										//�^�C�}�[�̏ꏊ
#define MAX_NUMBER (2)										//�^�C�}�[�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_TimerPos(640, 50, 0.0f);	// �^�C�}�[�̒��_���W
int						g_nTimer = 60;				// �^�C�}�[
int						g_nCntTimer = 0;

//=============================================================================
// ����������
//=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �^�C�}�[�̏�����
	g_nTimer = 30;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile	(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TIMER,			// �t�@�C���̖��O
								&g_pTextureTimer);		// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTimer(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{
	int nAnswer = 1;
	int nTimer;
	int nCntTimer;

	// ���_����ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	g_nCntTimer++;
	if (g_nCntTimer >= 60)
	{
		g_nTimer -= 1;
		g_nCntTimer = 0;
	}

	if (g_nTimer >= 0)
	{
		for (nCntTimer = 0; nCntTimer < MAX_NUMBER; nCntTimer++)
		{
			nTimer = g_nTimer % (nAnswer * 10) / nAnswer;

			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nTimer), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nTimer), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nTimer), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nTimer), 1.0f);

			nAnswer *= 10;
			pVtx += 4;	//���_�f�[�^���S���i�߂�
		}
	}

	if (g_nTimer == 0)
	{//�^�C�}�[��0�ɂȂ�����
		SetGameState(GAMESTATE_GAMEOVER);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntTimer;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimer);

	// �|���S���̕`��
	for (nCntTimer = 0; nCntTimer < MAX_NUMBER; nCntTimer++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTimer, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUMBER,		//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	int nCntTimer;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < MAX_NUMBER; nCntTimer++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_TimerPos.x - TIMER_SIZE, g_TimerPos.y - TIMER_SIZE, g_TimerPos.z);
		pVtx[1].pos = D3DXVECTOR3(g_TimerPos.x + TIMER_SIZE, g_TimerPos.y - TIMER_SIZE, g_TimerPos.z);
		pVtx[2].pos = D3DXVECTOR3(g_TimerPos.x - TIMER_SIZE, g_TimerPos.y + TIMER_SIZE, g_TimerPos.z);
		pVtx[3].pos = D3DXVECTOR3(g_TimerPos.x + TIMER_SIZE, g_TimerPos.y + TIMER_SIZE, g_TimerPos.z);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
		g_TimerPos.x -= 40;
	}
	g_TimerPos.x = 640;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();
}