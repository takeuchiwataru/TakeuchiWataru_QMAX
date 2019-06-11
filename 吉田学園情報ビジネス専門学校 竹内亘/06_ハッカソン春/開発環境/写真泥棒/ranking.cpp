//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "ranking.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "input.h"

#include "field.h"
#include "model.h"
#include "sky.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//---------------
//   ���S�p
//---------------
#define RANKINGLOGO_TEXTURE_NAME      "data/TEXTURE/ranking.png"  // �ǂݍ��ރe�N�X�`���t�@�C����
#define RANKINGLOGO_TEXTURE_SIZEX     (260)                            // �e�N�X�`���𒣂�t���镝
#define RANKINGLOGO_TEXTURE_SIZEY     (70)                             // �e�N�X�`���𒣂�t���鍂��

//---------------
//   ���ʗp
//---------------
#define RANNKINGRANK_TEXTURE_NAME     "data/TEXTURE/ranking_rank.png"  // �ǂݍ��ރe�N�X�`���t�@�C����
#define RANNKINGRANK_POS_X           (200)                             // �����L���O�����N�̍���w���W
#define RANNKINGRANK_POS_Y           (150)                             // �����L���O�����N����x���W
#define RANNKINGRANK_WIDTH           (450)                             // �����L���O�����N�̕�
#define RANNKINGRANK_HEIGHT          (640)                             // �����L���O�����N�̍���

//---------------
//  �X�R�A�p
//---------------
#define	RANKINGSCORE_TEXTURE_SCORE    "data/TEXTURE/number000.png"       // �ǂݍ��ރe�N�X�`���t�@�C����
#define RANKINGSCORE_TEXTURE_SIZE     (40)                               // �e�N�X�`���̃T�C�Y
#define MAX_RANKINGSCORENUMBER        (3)                                // �����L���O�X�R�A�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRankingLogo(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexRankingRank(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int        g_nCounterRanking;                // �^�C�g����ʂɑJ�ڂ���^�C�~���O
RANKINGOLD g_RankingOld = RANKINGOLD_TITLE;  // �ǂ̉�ʂ���J�ڂ��Ă�����

//------------
//  ���S�p
//------------
LPDIRECT3DTEXTURE9		g_pTextureRankingLogo = NULL; // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingLogo = NULL; // ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_PosRankingLogo;             // �����L���O���S���W
D3DXCOLOR				g_colorRankingLogo;		      // �����L���O���S�F

//------------
//  ���ʗp
//------------
LPDIRECT3DTEXTURE9		g_pTextureRankingRank = NULL; // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingRank = NULL; // ���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR				g_colorRankingRank;		      // �����L���O�����N�F

//---------------
//  �X�R�A�p
//---------------
LPDIRECT3DTEXTURE9		g_pTextureRankingScore = NULL;     // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;	   // ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_RankingScorePos;                 // ���_���W
int                     g_TextureRankingScorePos;          // �e�N�X�`��X���W
RANKINGSCORE            g_aRankingScore[MAX_RANKINGSCORE]; // �����L���O�X�R�A

//=============================================================================
// ����������
//=============================================================================
void InitRanking(void)
{
	// ���ʏ���������
	InitRankingRank();

	// ���S����������
	InitRankingLogo();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �t�B�[���h�̏���������
	InitField();

	// ���f���̏���������
	InitModel();

	// ��̏���������
	InitSky();

	g_nCounterRanking = 0;            // �J�E���^�[��0��
}
//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// ���ʏI������
	UninitRankingRank();

	// ���S�I������
	UninitRankingLogo();

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// �t�B�[���h�̏I������
	UninitField();

	// ���f���̏I������
	UninitModel();

	// ��̏I������
	UninitSky();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	// ���ʂ̍X�V����
	UpdateRankingRank();

	// ���S�̍X�V����
	UpdateRankingLogo();

	// �X�R�A�̍X�V����
	UpdateRankingScore();

	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	// �t�B�[���h�̍X�V����
	UpdateField();

	// ���f���̍X�V����
	UpdateModel();

	// ��̍X�V����
	UpdateSky();

	g_nCounterRanking++;
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE ||
		GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE && GetFade() == FADE_NONE ||
		g_nCounterRanking % 340 == 0 && GetFade() == FADE_NONE)
	{// ����{�^���������ꂽ����莞�Ԃ��o�߂���
		// �����L���O�X�R�A�̎擾
		RANKINGSCORE *rankingscore;
		rankingscore = GetRankingScore();

		for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++, rankingscore++)
		{// �����L���O�X�R�A�̐������J��Ԃ�
			if (rankingscore->state == RANKINGSCORESTATE_UPDATE)
			{// �X�V��ԂɂȂ��Ă�����
				rankingscore->state = RANKINGSCORESTATE_NONE;
				rankingscore->col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
		}
		SetFade(MODE_TITLE);   // �^�C�g����ʂ�
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	// �J�����̐ݒ菈��
	SetCamera();

	// �t�B�[���h�̕`�揈��
	DrawField();

	// ���f���̕`�揈��
	DrawModel();

	// ��̕`�揈��
	DrawSky();

	// ���ʕ`�揈��
	DrawRankingRank();

	// ���S�`�揈��
	DrawRankingLogo();

	// �X�R�A�`�揈��
	DrawRankingScore();
}
//=============================================================================
// �ǂ̉�ʂ���J�ڂ��Ă�������ݒ�
//=============================================================================
void SetRankingOld(RANKINGOLD rankold)
{
	g_RankingOld = rankold;    
}

//=============================================================================
// �����L���O���S�̏���������
//=============================================================================
void InitRankingLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_PosRankingLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, 80, 0.0f);
	g_colorRankingLogo = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexRankingLogo(pDevice);
}

//=============================================================================
// �����L���O���S�̏I������
//=============================================================================
void UninitRankingLogo(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureRankingLogo != NULL)
	{
		g_pTextureRankingLogo->Release();
		g_pTextureRankingLogo = NULL;
	}


	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRankingLogo != NULL)
	{
		g_pVtxBuffRankingLogo->Release();
		g_pVtxBuffRankingLogo = NULL;
	}
}

//=============================================================================
// �����L���O���S�̍X�V����
//=============================================================================
void UpdateRankingLogo(void)
{
}
//=============================================================================
// �����L���O���S�̕`�揈��
//=============================================================================
void DrawRankingLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffRankingLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �����L���O���S�̒��_���̍쐬
//=============================================================================
void MakeVertexRankingLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RANKINGLOGO_TEXTURE_NAME,
		&g_pTextureRankingLogo);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingLogo,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_PosRankingLogo.x - RANKINGLOGO_TEXTURE_SIZEX, g_PosRankingLogo.y - RANKINGLOGO_TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosRankingLogo.x + RANKINGLOGO_TEXTURE_SIZEX, g_PosRankingLogo.y - RANKINGLOGO_TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosRankingLogo.x - RANKINGLOGO_TEXTURE_SIZEX, g_PosRankingLogo.y + RANKINGLOGO_TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosRankingLogo.x + RANKINGLOGO_TEXTURE_SIZEX, g_PosRankingLogo.y + RANKINGLOGO_TEXTURE_SIZEY, g_PosRankingLogo.z);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorRankingLogo;
	pVtx[1].col = g_colorRankingLogo;
	pVtx[2].col = g_colorRankingLogo;
	pVtx[3].col = g_colorRankingLogo;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingLogo->Unlock();
}

//=============================================================================
// ���ʂ̏���������
//=============================================================================
void InitRankingRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_colorRankingRank = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexRankingRank(pDevice);
}

//=============================================================================
// ���ʂ̏I������
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
// ���ʂ̍X�V����
//=============================================================================
void UpdateRankingRank(void)
{
}
//=============================================================================
// ���ʂ̕`�揈��
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
// ���ʂ̒��_���̍쐬
//=============================================================================
void MakeVertexRankingRank(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RANNKINGRANK_TEXTURE_NAME,
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

//=============================================================================
// �����L���O�X�R�A�̏���������
//=============================================================================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nRankingScore = 30;
	g_RankingScorePos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 165, 0.0f);  // ���W�̏�����
	g_aRankingScore[0].col = D3DXCOLOR(1.0f, 0.9f, 0.0f, 1.0f);
	g_aRankingScore[1].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	g_aRankingScore[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
	g_aRankingScore[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_aRankingScore[4].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++)
	{// �����L���O�X�R�A�̐������J��Ԃ�
		g_aRankingScore[nCntRankingScore].pos = g_RankingScorePos;                 // �����L���O�X�R�A���W��������
		g_aRankingScore[nCntRankingScore].colStd = g_aRankingScore[nCntRankingScore].col; // �����L���O�X�R�A�̒ʏ�̐F��������
		g_aRankingScore[nCntRankingScore].score = nRankingScore;                   // �����L���O�X�R�A��������
		g_aRankingScore[nCntRankingScore].nCounterCol = 0;                         // �J�E���^�[�͏�����
		g_aRankingScore[nCntRankingScore].state = RANKINGSCORESTATE_NONE;          // �X�V����Ă��Ȃ���Ԃ�
		nRankingScore -= 5;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		RANKINGSCORE_TEXTURE_SCORE,		    // �t�@�C���̖��O
		&g_pTextureRankingScore);	        // �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexRankingScore(pDevice);
}
//=============================================================================
// �����L���O�X�R�A�̏I������
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
// �����L���O�X�R�A�̍X�V����
//=============================================================================
void UpdateRankingScore(void)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++)
	{// �����L���O�X�R�A�̐������J��Ԃ�
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
		else
		{// �ʏ�̏�ԂȂ�
			g_aRankingScore[nCntRankingScore].col = g_aRankingScore[nCntRankingScore].colStd;
		}
		for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORENUMBER; nCntRankingScore1++)
		{// �X�R�A�̌��������J��Ԃ�
		 // ���_�J���[
			pVtx[0].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[1].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[2].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[3].col = g_aRankingScore[nCntRankingScore].col;
			pVtx += 4;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingScore->Unlock();
}
//=============================================================================
// �����L���O�X�R�A�̕`�揈��
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
	for (int nCntRankingScore2 = 0; nCntRankingScore2 < MAX_RANKINGSCORENUMBER * MAX_RANKINGSCORE; nCntRankingScore2++)
	{// �\�����郉���L���O�X�R�A�̌��������J��Ԃ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			(nCntRankingScore2 * 4),
			2);
	}
}
//=============================================================================
// �����L���O�X�R�A�̒��_���̍쐬
//=============================================================================
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKINGSCORENUMBER * MAX_RANKINGSCORE,
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
	{// �����L���O�X�R�A�̐������J��Ԃ�
		int RankingScore = 1;
		for (int nCntRankingScore2 = 0; nCntRankingScore2 < MAX_RANKINGSCORENUMBER; nCntRankingScore2++)
		{// �����L���O�X�R�A�̌��������J��Ԃ�
			g_TextureRankingScorePos = g_aRankingScore[nCntRankingScore1].score % (RankingScore * 10) / RankingScore;
			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_RankingScorePos.x - RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.y - RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[1].pos = D3DXVECTOR3(g_RankingScorePos.x + RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.y - RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[2].pos = D3DXVECTOR3(g_RankingScorePos.x - RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.y + RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[3].pos = D3DXVECTOR3(g_RankingScorePos.x + RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.y + RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.z);

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
			g_RankingScorePos.x -= 70;
			RankingScore *= 10;
		}
		g_RankingScorePos.y += 100;
		g_RankingScorePos.x = SCREEN_WIDTH / 2 + 100;
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

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++)
	{// �����L���O�X�R�A�̐������J��Ԃ�
		if (g_aRankingScore[nCntRankingScore].score < nScore)
		{// �n�C�X�R�A���X�V���ꂽ
			g_aRankingScore[nCntRankingScore].score = nScore;

			int RankingScore = 1;
			// ���_����ݒ�
			for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORENUMBER; nCntRankingScore1++)
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
			break;
		}
		pVtx += 4 * MAX_RANKINGSCORENUMBER; // �����L���O�X�R�A�̌����������i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingScore->Unlock();
}
//=============================================================================
// �����L���O�X�R�A�̎擾
//=============================================================================
RANKINGSCORE *GetRankingScore(void)
{
	return &g_aRankingScore[0];
}