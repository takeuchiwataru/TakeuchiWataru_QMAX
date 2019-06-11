//=============================================================================
//
// �����L���O�X�R�A���� [rankingscore.cpp]
// Author : �|���j
//
//=============================================================================
#include "rankingscore.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		    "data/TEXTURE/number003.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZE            (50)                            // �e�N�X�`���̃T�C�Y
#define MAX_RANKINGSCORE_NUMBER  (8)                            // �����L���O�X�R�A�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRankingScore = NULL;     // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;	   // ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_RankingScorePos;                 // ���_���W
int                     g_TextureRankingScorePos;          // �e�N�X�`��X���W
RANKINGSCORE            g_aRankingScore[MAX_RANKINGSCORE]; // �����L���O�X�R�A

//=============================================================================
// ����������
//=============================================================================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nRankingScore = 8000;
	g_RankingScorePos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 550, SCREEN_HEIGHT / 2 - 250, 0.0f); // ���W�̏�����

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++)
	{
		g_aRankingScore[nCntRankingScore].pos = g_RankingScorePos;                 // �����L���O�X�R�A���W��������
		g_aRankingScore[nCntRankingScore].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); // �����L���O�X�R�A�̐F��������
		g_aRankingScore[nCntRankingScore].score = nRankingScore;                   // �����L���O�X�R�A��������
		g_aRankingScore[nCntRankingScore].nCounterCol = 0;                         // �J�E���^�[�͏�����
		g_aRankingScore[nCntRankingScore].state = RANKINGSCORESTATE_NONE;          // �X�V����Ă��Ȃ���Ԃ�
		nRankingScore -= 500;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE,		                // �t�@�C���̖��O
		&g_pTextureRankingScore);	        // �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexRankingScore(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitRankingScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankingScore(void)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++)
	{
		if (g_aRankingScore[nCntRankingScore].state == RANKINGSCORESTATE_UPDATE)
		{// �X�V���ꂽ��Ԃ�������
			g_aRankingScore[nCntRankingScore].nCounterCol++;
			if (g_aRankingScore[nCntRankingScore].nCounterCol % 2 == 0)
			{// ��莞�Ԃ���������
				if (g_aRankingScore[nCntRankingScore].col.b == 0.0f)
				{// �Ԃ�������
					g_aRankingScore[nCntRankingScore].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{// ����������
					g_aRankingScore[nCntRankingScore].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
		}
		for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORE_NUMBER; nCntRankingScore1++)
		{
		 // ���_�J���[
			pVtx[0].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[1].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[2].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[3].col = g_aRankingScore[nCntRankingScore].col;
			pVtx += 4;
		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRankingScore->Unlock();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingScore);

	// �|���S���̕`��
	for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORE_NUMBER; nCntRankingScore1++)
	{
		for (int nCntRankingScore2 = 0; nCntRankingScore2 < MAX_RANKINGSCORE_NUMBER * MAX_RANKINGSCORE; nCntRankingScore2++)
		{// �\�����郉���L���O�X�R�A�̌��������J��Ԃ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				 (nCntRankingScore2 * 4),
				2);
		}
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKINGSCORE_NUMBER * MAX_RANKINGSCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);
	// ���_����ݒ�
	for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORE; nCntRankingScore1++)
	{
		int RankingScore = 1;
		for (int nCntRankingScore2 = 0; nCntRankingScore2 < MAX_RANKINGSCORE_NUMBER; nCntRankingScore2++)
		{
			g_TextureRankingScorePos = g_aRankingScore[nCntRankingScore1].score % (RankingScore * 10) / RankingScore;
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_RankingScorePos.x - TEXTURE_SIZE, g_RankingScorePos.y - TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[1].pos = D3DXVECTOR3(g_RankingScorePos.x + TEXTURE_SIZE, g_RankingScorePos.y - TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[2].pos = D3DXVECTOR3(g_RankingScorePos.x - TEXTURE_SIZE, g_RankingScorePos.y + TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[3].pos = D3DXVECTOR3(g_RankingScorePos.x + TEXTURE_SIZE, g_RankingScorePos.y + TEXTURE_SIZE, g_RankingScorePos.z);

			// ���_�e�N�X�`��
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// ���_�J���[
			pVtx[0].col = g_aRankingScore[nCntRankingScore1].col;
			pVtx[1].col = g_aRankingScore[nCntRankingScore1].col;
			pVtx[2].col = g_aRankingScore[nCntRankingScore1].col;
			pVtx[3].col = g_aRankingScore[nCntRankingScore1].col;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_TextureRankingScorePos * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_TextureRankingScorePos * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_TextureRankingScorePos * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_TextureRankingScorePos * 0.1f), 1.0f);

			pVtx += 4;
			g_RankingScorePos.x -= 110;
			RankingScore *= 10;
		}
		g_RankingScorePos.y += 123;
		g_RankingScorePos.x = SCREEN_WIDTH / 2 + 550;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingScore->Unlock();
}
//=============================================================================
// �����L���O�X�R�A�ƃQ�[���X�R�A�̔�r
//=============================================================================
void SetRankingScore(int nScore)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntRankingScore = 0;nCntRankingScore < MAX_RANKINGSCORE;nCntRankingScore++)
	{
		if (g_aRankingScore[nCntRankingScore].score <= nScore)
		{// �n�C�X�R�A���X�V���ꂽ
			g_aRankingScore[nCntRankingScore].score = nScore;

			int RankingScore = 1;
			// ���_����ݒ�
			for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORE_NUMBER; nCntRankingScore1++)
			{// �X�R�A�̌��������J��Ԃ�
				g_TextureRankingScorePos = g_aRankingScore[nCntRankingScore].score % (RankingScore * 10) / RankingScore;

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (g_TextureRankingScorePos * 0.1f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (g_TextureRankingScorePos * 0.1f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (g_TextureRankingScorePos * 0.1f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (g_TextureRankingScorePos * 0.1f), 1.0f);

				RankingScore *= 10;        // �������炷����
				pVtx += 4;
			}
			g_aRankingScore[nCntRankingScore].state = RANKINGSCORESTATE_UPDATE;  // �X�V���ꂽ��Ԃ�

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffRankingScore->Unlock();
			break;
		}
		pVtx += 4 * MAX_RANKINGSCORE_NUMBER; // �����L���O�X�R�A�̌����������i�߂�
	}
}
//=============================================================================
// �����L���O�X�R�A�̎擾
//=============================================================================
RANKINGSCORE *GetRankingScore(void)
{
	return &g_aRankingScore[0];
}