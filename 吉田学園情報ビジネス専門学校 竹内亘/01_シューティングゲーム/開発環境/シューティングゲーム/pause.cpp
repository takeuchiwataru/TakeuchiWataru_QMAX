//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "pause.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEXTURENAME		"data/TEXTURE/pause100.png"		//�e�N�X�`����
#define BG_POS_X			(0)								//�w�i�̍���X���W
#define BG_POS_Y			(0)								//�w�i�̍���Y���W
#define BG_WIDTH			(SCREEN_WIDTH)					//�w�i�̕�
#define BG_HEIGHT			(SCREEN_HEIGHT)					//�w�i�̍���
#define BG_MOVESPEED		(10)							//�w�i�̓�������

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// �|�[�Y����������
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTexturePause);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
// �|�[�Y�I������
//=============================================================================
void UninitPause(void)
{
	// �e�N�X�`���̔j��
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================================================
// �|�[�Y�X�V����
//=============================================================================
void UpdatePause(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//pVtx[0].pos = D3DXVECTOR3(BG_POS_X + 200, BG_POS_Y + 100 , 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(400, BG_POS_Y + 100 , 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(BG_POS_X + 200, 300, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(400, 300, 0.0f);

	pVtx += 4;	//���_�f�[�^���S���i�߂�

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
// �|�[�Y�`�揈��
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}