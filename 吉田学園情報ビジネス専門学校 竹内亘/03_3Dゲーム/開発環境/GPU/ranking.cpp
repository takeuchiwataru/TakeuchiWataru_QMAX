//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : �|���j
//
//=============================================================================
#include "ranking.h"
#include "rankingscore.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "meshWall.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_TEXTURE_NAME  "data/TEXTURE/title_bg000.jpg"// �ǂݍ��ރe�N�X�`���t�@�C����
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
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// ���b�V���t�B�[���h�̏���������
	InitmeshField();

	//// ���b�V���t�B�[���h2�̏���������
	//InitMeshField2();

	// ���b�V���E�H�[���̏���������
	InitMeshWall(0, D3DXVECTOR3(-25.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	InitMeshWall(1, D3DXVECTOR3(-25.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	InitMeshWall(2, D3DXVECTOR3(725.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	InitMeshWall(3, D3DXVECTOR3(725.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	//LPDIRECT3DDEVICE9 pDevice;

	//pDevice = GetDevice();

	//g_nCounterRanking = 0;  // �J�E���^�[��������

	//// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	RANKING_TEXTURE_NAME,
	//	&g_pTextureRanking);

	//// ���_�o�b�t�@�̐���
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffRanking,
	//	NULL);

	//VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	//// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	//g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//// ���_���W
	//pVtx[0].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);


	//// ���_�e�N�X�`��
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// ���_�J���[
	//pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

	//// �e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// ���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffRanking->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// ���b�V���t�B�[���h�̏I������
	UninitmeshField();

	//// ���b�V���t�B�[���h2�̏I������
	//UninitMeshField2();

	// ���b�V���E�H�[���̏I������
	UninitMeshWall();

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
	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	// ���b�V���t�B�[���h�̍X�V����
	UpdatemeshField();

	//// ���b�V���t�B�[���h2�̏I������
	//UpdateMeshField2();

	// ���b�V���E�H�[���̍X�V����
	UpdateMeshWall();

	//�t�F�[�h�̎擾
	FADE *pFade;
	pFade = GetFade();

	g_nCounterRanking++;

	if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{// ENTER�L�[�������ꂽ��
		SetFade(MODE_TITLE);

		// �����L���O�X�R�A�̎擾
		RANKINGSCORE *rankingscore;
		rankingscore = GetRankingScore();

		for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++, rankingscore++)
		{
			if (rankingscore->state == RANKINGSCORESTATE_UPDATE)
			{// �X�V��ԂɂȂ��Ă�����
				rankingscore->state = RANKINGSCORESTATE_NONE;
				rankingscore->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}

	if (g_nCounterRanking % 200 == 0 && *pFade == FADE_NONE)
	{//��莞�Ԃ�������
		SetFade(MODE_TITLE);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// ���b�V���t�B�[���h�̕`�揈��
	DrawmeshField();

	//// ���b�V���t�B�[���h�̕`�揈��
	//DrawMeshField2();

	// ���b�V���E�H�[���̕`�揈��
	DrawMeshWall();

	//LPDIRECT3DDEVICE9 pDevice;

	//// �f�o�C�X���擾����
	//pDevice = GetDevice();

	//// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureRanking);

	//// �|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);
}