//=============================================================================
//
// �w�i�̏��� [Result.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "resultlogo.h"
//#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Result_WIDTH	(SCREEN_WIDTH)
#define Result_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//VERTEX_2D g_aVertex[4];								//���_�����i�[����
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//�e�N�X�`���̃|�C���^

//=============================================================================
// ����������(�|���S��)
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//�f�o�C�X�̃|�C���^
													//�f�o�C�X�̎擾
	pDevise = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\movie.png",
		&g_pTextureResult);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);
	//���[�J���ϐ�
	VERTEX_2D*pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^�̎擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResult->Unlock();

	InitResultlogo();
}

//=============================================================================
// �I������(�|���S��)
//=============================================================================
void UninitResult(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	UninitResultlogo();
}
//=============================================================================
// �X�V����(�|���S��)
//=============================================================================
void UpdateResult(void)
{
	D3DXVECTOR3 Resultrogo;

	FADE Fade;
	Fade = GetFade();

	//if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
	//{
	//	Resultrogo = *GetResultrogo();
	//	SetResultrogo(D3DXVECTOR3(1000.0f, SCREEN_WIDTH - 48, 0.0f));

	//	if (Resultrogo == D3DXVECTOR3(1000.0f, SCREEN_WIDTH - 48, 0.0f))
	//	{
	//		//PlaySound(SOUND_LABEL_SE_DECIDE);
	//		SetFade(MODE_RANKING);
	//		//StopSound(SOUND_LABEL_BGM_TITLE);
	//	}
	//}

	if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
	{
		SetFade(MODE_RANKING);
		//PlaySound(SOUND_LABEL_SE_DECIDE);
	}

	UpdateResultlogo();
}

//=============================================================================
// �`�揈��(�|���S��)
//=============================================================================
void DrawResult(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//�f���@�C�X���擾
	pDevice = GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	DrawResultlogo();

}