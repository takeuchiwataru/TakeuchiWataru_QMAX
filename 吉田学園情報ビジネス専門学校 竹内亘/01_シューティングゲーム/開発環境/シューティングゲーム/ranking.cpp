//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : �|���j
//
//=============================================================================
#include "ranking.h"
#include "score.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RANKING		"data/TEXTURE/number000.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define RANKING_SIZE (50.0f)								//�����L���O�T�C�Y
#define RANKING_WIDE (15)									//�����L���O�̕�
#define RANKING_POS (30)									//�����L���O�̏ꏊ
#define MAX_NUMBER (8)										//�����L���O�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_RankingPos(700, 350, 0.0f);	// �����L���O�̒��_���W
int						g_nRankScore;					// �����L���O
int						g_TexturePosRanking;			// �e�N�X�`��X���W
	
//=============================================================================
// �����L���O����������
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nScore;
	nScore = GetScore();

	if (nScore > g_nRankScore)
	{
		g_nRankScore = nScore;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile	(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_RANKING,		// �t�@�C���̖��O
								&g_pTextureRanking);	// �e�N�X�`���ւ̃|�C���^

			
	// ���_���̍쐬
	MakeVertexRanking(pDevice);
}

//=============================================================================
// �����L���O�I������
//=============================================================================
void UninitRanking(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=============================================================================
// �����L���O�X�V����
//=============================================================================
void UpdateRanking(void)
{
	int nAnswer = 1;
	int nScore;
	int nCntScore;

	// ���_����ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		nScore = g_nRankScore % (nAnswer * 10) / nAnswer;

		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 1.0f);

		nAnswer *= 10;
		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();


	// �t�F�[�h�̎擾
	FADE * Fade;
	Fade = GetFade();

	if (GetKeyboardTrigger(DIK_RETURN) == true && *Fade == FADE_NONE)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);

		// ���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}

}

//=============================================================================
// �����L���O�`�揈��
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntScore;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUMBER,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	int nCntScore;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x - RANKING_SIZE, g_RankingPos.y - RANKING_SIZE, g_RankingPos.z);
		pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + RANKING_SIZE, g_RankingPos.y - RANKING_SIZE, g_RankingPos.z);
		pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x - RANKING_SIZE, g_RankingPos.y + RANKING_SIZE, g_RankingPos.z);
		pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + RANKING_SIZE, g_RankingPos.y + RANKING_SIZE, g_RankingPos.z);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
		g_RankingPos.x -= 80;
	}
	g_RankingPos.x = 700;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void SetRank(int nValue)
{
	int nAnswer = 1;
	int nScore;
	int nCntScore;

	g_nRankScore += nValue;

	// ���_����ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		nScore = g_nRankScore % (nAnswer * 10) / nAnswer;

		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 1.0f);

		nAnswer *= 10;
		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();
}
