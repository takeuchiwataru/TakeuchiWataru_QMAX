//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : �|���j
//
//=============================================================================
#include "timer.h"
#include "fade.h"
#include "game.h"
//#include "score.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIMER		"data/TEXTURE/number000.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define TIMER_SIZE (30.0f)									//�^�C�}�[�T�C�Y
//#define TIMER_POS (100)										//�^�C�}�[�̏ꏊ
#define MAX_NUMBER (2)										//�^�C�}�[�̌���
#define TIMER_WIDE (30)										//�^�C�}�[�̕�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_TimerPos(680, 60, 0.0f);	// �^�C�}�[�̒��_���W
int						g_nCntTimer = 0;
bool					g_TimerStop;
Timer g_Timer;										// �^�C�}�[�̏��

//=============================================================================
// ����������
//=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �^�C�}�[�̏�����
	g_Timer.nTimer = 90;
	g_TimerStop = false;

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

	if (g_TimerStop == false)
	{
		g_nCntTimer++;
		if (g_nCntTimer >= 60)
		{
			g_Timer.nTimer -= 1;	//+�ŃJ�E���gUP,//-�ŃJ�E���gDOWN
			g_nCntTimer = 0;
		}

		if (g_Timer.nTimer >= 0)
		{
			for (nCntTimer = 0; nCntTimer < MAX_NUMBER; nCntTimer++)
			{
				nTimer = g_Timer.nTimer % (nAnswer * 10) / nAnswer;

				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nTimer), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nTimer), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nTimer), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nTimer), 1.0f);

				nAnswer *= 10;
				pVtx += 4;	//���_�f�[�^���S���i�߂�
			}
		}
	}

	if (g_Timer.nTimer == 0)
	{//�^�C�}�[��0�ɂȂ�����
		SetGameState(GAMESTATE_END);
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
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
		g_TimerPos.x -= 55;
	}
	g_TimerPos.x = 680;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();
}

//=============================================================================
// �^�C�}�[�X�g�b�v
//=============================================================================
void StopTimer(void)
{
	g_TimerStop = true;
	//AddScore(g_nTimer * 100);
}

//=============================================================================
// �^�C�}�[�̎擾
//=============================================================================
Timer *GetTimer(void)
{
	return &g_Timer;
}
