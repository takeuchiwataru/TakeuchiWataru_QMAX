//=============================================================================
//
// �w�i�`�揈�� [bg01.cpp]
// Author : �|���j
//
//=============================================================================
#include "bg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEXTURE_NAME  "data/TEXTURE/sky000.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define BG_POS_X         (0)								// �w�i�̍���w���W
#define BG_POS_Y         (0)								// �w�i�̍���x���W
#define BG_WIDTH         (SCREEN_WIDTH)						// �w�i�̕�
#define BG_HEIGHT        (SCREEN_HEIGHT)					// �w�i�̍���
#define ANIMATIONPATTERN (0.00020f * g_PatternAnimBG01)		// �w�i�e�N�X�`�����W��؂�ւ���v�Z��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureBG01 = NULL;       // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG01 = NULL;   // ���_�o�b�t�@�ւ̃|�C���^
int g_CounterAnimBG01;                           // �A�j���[�V�����J�E���^�[ 
int g_PatternAnimBG01;                           // �A�j���[�V�����p�^�[��No.

//=============================================================================
// ����������
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		                      BG_TEXTURE_NAME,
		                      &g_pTextureBG01);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBG01,
		                        NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG01->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);


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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG01->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureBG01 != NULL)
	{
		g_pTextureBG01->Release();
		g_pTextureBG01 = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG01 != NULL)
	{
		g_pVtxBuffBG01->Release();
		g_pVtxBuffBG01 = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{
	g_PatternAnimBG01++; // �p�^�[��NO.��i�߂�

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG01->Lock(0, 0, (void**)&pVtx, 0);
	// �e�N�X�`�����W�̍X�V
	pVtx[0].tex.x = ANIMATIONPATTERN + 0.0f;
	pVtx[1].tex.x = ANIMATIONPATTERN + 0.25f;
	pVtx[2].tex.x = ANIMATIONPATTERN + 0.0f;
	pVtx[3].tex.x = ANIMATIONPATTERN + 0.25f;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG01->Unlock();

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG01, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBG01);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		                   0,
		                   2);
}