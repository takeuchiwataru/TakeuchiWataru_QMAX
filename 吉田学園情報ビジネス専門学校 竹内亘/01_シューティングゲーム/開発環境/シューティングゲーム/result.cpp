//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
//#include "player.h"
//#include "enemy.h"
//#include "boss.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_TEXTURENAME		"data/TEXTURE/result000.png"	//�e�N�X�`����
//#define RESULT_TEXTURENAME_1	"data/TEXTURE/CLEAR.jpg"		//�Q�[���N���A�e�N�X�`��
//#define RESULT_TEXTURENAME_2	"data/TEXTURE/OVER.jpg"			//�Q�[���I�[�o�[�e�N�X�`��
#define RESULT_POS_X			(0)								//�w�i�̍���X���W
#define RESULT_POS_Y			(0)								//�w�i�̍���Y���W
#define RESULT_WIDTH			(SCREEN_WIDTH)					//�w�i�̕�
#define RESULT_HEIGHT			(SCREEN_HEIGHT)					//�w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// ���U���g����������
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	////�v���C���[�̎擾
	//Player * pPlayer;
	//pPlayer = GetPlayer();

	////�G�̎擾
	//Enemy * pEnemy;
	//pEnemy = GetEnemy();

	////�{�X�̎擾
	//Boss * pBoss;
	//pBoss = GetBoss();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME, &g_pTextureResult);

	//if (pPlayer->bDisp == false)
	//{//�v���C���[�����񂾂�
	//	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME_2, &g_pTextureResult);
	//	StopSound(SOUND_LABEL_BGM003);
	//}

	//else if (pEnemy->bUse == false)
	//{//�G���S�ł�����
	//	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME_1, &g_pTextureResult);
	//	StopSound(SOUND_LABEL_BGM003);
	//}

	//else if (pBoss->bUse == true)
	//{//�{�X���S�ł�����
	//	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME_2, &g_pTextureResult);
	//	StopSound(SOUND_LABEL_BGM003);
	//}


	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

	// rhw�̐ݒ�
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

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffResult->Unlock();

	//PlaySound(SOUND_LABEL_BGM000);
}

//=============================================================================
// ���U���g�I������
//=============================================================================
void UninitResult(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=============================================================================
// ���U���g�X�V����
//=============================================================================
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		FADE *pFade;
		pFade = GetFade();
		//PlaySound(SOUND_LABEL_SE_DECIDE);

		if (*pFade != FADE_OUT)
		{
			StopSound(SOUND_LABEL_BGM000);
			SetFade(MODE_TITLE);
		}
	}
}

//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}