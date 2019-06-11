//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : �|���j
//
//=============================================================================
#include "tutorial.h"
#include "fade.h"
#include "pressenter.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIAL_TEXTURE_NAME  "data/TEXTURE/3Dtutorial.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define TUTORIAL_POS_X         (0)									// �w�i�̍���w���W
#define TUTORIAL_POS_Y         (0)									// �w�i�̍���x���W
#define TUTORIAL_WIDTH         (SCREEN_WIDTH)						// �w�i�̕�
#define TUTORIAL_HEIGHT        (SCREEN_HEIGHT)						// �w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureTutorial = NULL;       // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;   // ���_�o�b�t�@�ւ̃|�C���^      

//=============================================================================
// ����������
//=============================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURE_NAME,
		&g_pTextureTutorial);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

    // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);


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
	g_pVtxBuffTutorial->Unlock();

	SetPressEnter(D3DXVECTOR3(1150, 680, 0.0f),120,40);
	DispPressEnter();
}
//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	FADE *pFade;
	bool *disp;

	pFade = GetFade();
	disp = GetDispPressEnter();

	if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{// ENTER�L�[�������ꂽ
		SetFade(MODE_GAME);
		PlaySound(SOUND_LABEL_SE_ENTER000);  // ���艹�𗬂�
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	// �^�C�g����ʂ̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}