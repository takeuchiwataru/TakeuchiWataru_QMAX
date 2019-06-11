//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �|���j
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define SCORE_SIZE (30.0f)									//�X�R�A�T�C�Y
//#define SCORE_WIDE (25)									//�X�R�A�̕�
//#define SCORE_POS (30)									//�X�R�A�̏ꏊ
#define MAX_NUMBER (8)										//�X�R�A�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_ScorePos(1200, 60, 0.0f);	// �X�R�A�̒��_���W
int						g_nScore;					// �X�R�A
int						g_TexturePos;				// �e�N�X�`��X���W

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nScore = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile	(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,			// �t�@�C���̖��O
								&g_pTextureScore);		// �e�N�X�`���ւ̃|�C���^
		
	// ���_���̍쐬
	MakeVertexScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntScore;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUMBER,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	int nCntScore;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(g_ScorePos.x - SCORE_SIZE, g_ScorePos.y - SCORE_SIZE, g_ScorePos.z);
		pVtx[1].pos = D3DXVECTOR3(g_ScorePos.x + SCORE_SIZE, g_ScorePos.y - SCORE_SIZE, g_ScorePos.z);
		pVtx[2].pos = D3DXVECTOR3(g_ScorePos.x - SCORE_SIZE, g_ScorePos.y + SCORE_SIZE, g_ScorePos.z);
		pVtx[3].pos = D3DXVECTOR3(g_ScorePos.x + SCORE_SIZE, g_ScorePos.y + SCORE_SIZE, g_ScorePos.z);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
		g_ScorePos.x -= 55;
	}
	g_ScorePos.x = 1220;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	int nAnswer = 1;
	int nScore;
	int nCntScore;

	g_nScore += nValue;

	if (g_nScore < 0)
	{
		g_nScore = 0;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		nScore = g_nScore % (nAnswer * 10) / nAnswer;

		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 1.0f);

		nAnswer *= 10;
		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}
