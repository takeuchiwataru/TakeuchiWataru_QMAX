//=============================================================================
//
// �����L���O�����N���� [rankingrank.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "rankingrank.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME       "data/TEXTURE/ranking_rank.png"   // �ǂݍ��ރe�N�X�`���t�@�C����
#define RANNKINGRANK_POS_X    (100)                          // �����L���O�����N�̍���w���W
#define RANNKINGRANK_POS_Y    (40)                           // �����L���O�����N����x���W
#define RANNKINGRANK_WIDTH    (800)                          // �����L���O�����N�̕�
#define RANNKINGRANK_HEIGHT   (680)                          // �����L���O�����N�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRankingRank(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRankingRank = NULL; // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingRank = NULL; // ���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR				g_colorRankingRank;		      // �����L���O�����N�F.

//=============================================================================
// ����������
//=============================================================================
void InitRankingRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_colorRankingRank = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexRankingRank(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRankingRank(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRankingRank != NULL)
	{
		g_pTextureRankingRank->Release();
		g_pTextureRankingRank = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRankingRank != NULL)
	{
		g_pVtxBuffRankingRank->Release();
		g_pVtxBuffRankingRank = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankingRank(void)
{
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawRankingRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffRankingRank, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingRank);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRankingRank(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureRankingRank);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingRank,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

					   // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingRank->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(RANNKINGRANK_POS_X, RANNKINGRANK_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RANNKINGRANK_WIDTH, RANNKINGRANK_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RANNKINGRANK_POS_X, RANNKINGRANK_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RANNKINGRANK_WIDTH, RANNKINGRANK_HEIGHT, 0.0f);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorRankingRank;
	pVtx[1].col = g_colorRankingRank;
	pVtx[2].col = g_colorRankingRank;
	pVtx[3].col = g_colorRankingRank;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingRank->Unlock();
}