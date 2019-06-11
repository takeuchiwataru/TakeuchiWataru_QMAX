//=============================================================================
//
// �|�[�Y���S���� [pauselogo.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "pauselogo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME       "data/TEXTURE/pause100.png"    // �ǂݍ��ރe�N�X�`���t�@�C����
#define PAUSELOGO_POS_X    (460)                          // �|�[�Y���S�̍���w���W
#define PAUSELOGO_POS_Y    (180)                          // �|�[�Y���S����x���W
#define PAUSELOGO_WIDTH    (820)                          // �|�[�Y���S�̕�
#define PAUSELOGO_HEIGHT   (540)                          // �|�[�Y���S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPauseLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePauseLogo = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseLogo = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR				g_colorPauseLogo;		    // �|�[�Y���S�F

//=============================================================================
// ����������
//=============================================================================
void InitPauseLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_colorPauseLogo = D3DXCOLOR(0.5f, 0.25f, 0.112f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexPauseLogo(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseLogo(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePauseLogo != NULL)
	{
		g_pTexturePauseLogo->Release();
		g_pTexturePauseLogo = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseLogo != NULL)
	{
		g_pVtxBuffPauseLogo->Release();
		g_pVtxBuffPauseLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseLogo(void)
{
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawPauseLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPauseLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPauseLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTexturePauseLogo);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseLogo,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(PAUSELOGO_POS_X, PAUSELOGO_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSELOGO_WIDTH, PAUSELOGO_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSELOGO_POS_X, PAUSELOGO_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSELOGO_WIDTH, PAUSELOGO_HEIGHT, 0.0f);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorPauseLogo;
	pVtx[1].col = g_colorPauseLogo;
	pVtx[2].col = g_colorPauseLogo;
	pVtx[3].col = g_colorPauseLogo;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseLogo->Unlock();
}