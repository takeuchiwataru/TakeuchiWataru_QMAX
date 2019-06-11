//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "ranking.h"
#include "rankingscore.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_TEXTURE_NAME  "data/TEXTURE/ranking001.jpg" // �ǂݍ��ރe�N�X�`���t�@�C����
#define RANKING_POS_X         (0)                           // �����L���O��ʂ̍���w���W
#define RANKING_POS_Y         (0)                           // �����L���O��ʂ̍���x���W
#define RANKING_WIDTH         (SCREEN_WIDTH)                // �����L���O��ʂ̕�
#define RANKING_HEIGHT        (SCREEN_HEIGHT)               // �����L���O��ʂ̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureRanking = NULL;   // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;   // ���_�o�b�t�@�ւ̃|�C���^
int                     g_nCounterRanking;          // �^�C�g����ʂɑJ�ڂ���^�C�~���O

//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_nCounterRanking = 0;  // �J�E���^�[��������

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RANKING_TEXTURE_NAME,
		&g_pTextureRanking);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);


	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	FADE fade;
	fade = GetFade();

	g_nCounterRanking++;

	if (GetKeyboardTrigger(DIK_RETURN) && fade == FADE_NONE || g_nCounterRanking % 300 == 0 && fade == FADE_NONE)
	{// ENTER�L�[��������邩��莞�Ԃ��o�߂���
		SetFade(MODE_TITLE);
		// �����L���O�X�R�A�̎擾
		RANKINGSCORE *rankingscore;
		rankingscore = GetRankingScore();

		for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++, rankingscore++)
		{// �����L���O�X�R�A�̐������J��Ԃ�
			if (rankingscore->state == RANKINGSCORESTATE_UPDATE)
			{// �X�V��ԂɂȂ��Ă�����
				rankingscore->state = RANKINGSCORESTATE_NONE;
				rankingscore->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}