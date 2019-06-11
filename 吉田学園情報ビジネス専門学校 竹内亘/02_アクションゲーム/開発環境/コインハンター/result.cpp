//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �|���j
//
//=============================================================================
#include "result.h"
#include "fade.h"
#include "input.h"
//#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_TEXTURE_NAME  "data/TEXTURE/ranking_bg000.jpg"  // �ǂݍ��ރe�N�X�`���t�@�C����
#define RESULT_POS_X         (0)                            // �w�i�̍���w���W
#define RESULT_POS_Y         (0)                            // �w�i�̍���x���W
#define RESULT_WIDTH         (SCREEN_WIDTH)                 // �w�i�̕�
#define RESULT_HEIGHT        (SCREEN_HEIGHT)                // �w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureResult = NULL;       // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;   // ���_�o�b�t�@�ւ̃|�C���^
int                     g_nCounterResult;          // �^�C�g����ʂɈڍs����^�C�~���O 

//=============================================================================
// ����������
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_nCounterResult = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RESULT_TEXTURE_NAME,
		&g_pTextureResult);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);


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
	g_pVtxBuffResult->Unlock();
}
//=============================================================================
// �I������
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
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_nCounterResult++;

	//if (*pFade != FADE_OUT)
	//{
	//	SetFade(MODE_TITLE);
	//}

	if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{// ENTER�L�[�������ꂽ
		SetFade(MODE_RANKING);
		//PlaySound(SOUND_LABEL_SE_DECIDE);  // ���艹�𗬂�
	}

	//if (g_nCounterResult % 400 == 0 && *pFade == FADE_NONE)
	//{// ��莞�Ԃ���������
	//	SetFade(MODE_TITLE);
	//}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}