//=============================================================================
//
// �Q�[���N���A���� [clear.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "clear.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "boss.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLEAR_TEXTURENAME	"data/TEXTURE/CLEAR.jpg"		//�Q�[���I�[�o�[�e�N�X�`��
#define CLEAR_POS_X			(0)								//�w�i�̍���X���W
#define CLEAR_POS_Y			(0)								//�w�i�̍���Y���W
#define CLEAR_WIDTH			(SCREEN_WIDTH)					//�w�i�̕�
#define CLEAR_HEIGHT		(SCREEN_HEIGHT)					//�w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureClear = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// �Q�[���N���A����������
//=============================================================================
void InitClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CLEAR_TEXTURENAME, &g_pTextureClear);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffClear,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(CLEAR_POS_X, CLEAR_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(CLEAR_WIDTH, CLEAR_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(CLEAR_POS_X, CLEAR_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CLEAR_WIDTH, CLEAR_HEIGHT, 0.0f);

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
	g_pVtxBuffClear->Unlock();

	PlaySound(SOUND_LABEL_SE_GAMECLEAR);
}

//=============================================================================
// �Q�[���N���A�I������
//=============================================================================
void UninitClear(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureClear != NULL)
	{
		g_pTextureClear->Release();
		g_pTextureClear = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}
}

//=============================================================================
// �Q�[���N���A�X�V����
//=============================================================================
void UpdateClear(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		FADE *pFade;
		pFade = GetFade();
		//PlaySound(SOUND_LABEL_SE_DECIDE);

		if (*pFade != FADE_OUT)
		{
			StopSound(SOUND_LABEL_SE_GAMECLEAR);
			SetFade(MODE_RANKING);
		}
	}
}

//=============================================================================
// �Q�[���N���A�`�揈��
//=============================================================================
void DrawClear(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureClear);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}