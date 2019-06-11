//=============================================================================
//
//	�`���[�g���A�����S���� [tutoriallogo.cpp]
// Author : �|���j
//
//=============================================================================
#include "tutoriallogo.h"
#include "pressenter.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME       "data/TEXTURE/tutorial.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZEX      (200)							// �e�N�X�`���𒣂�t���镝
#define TEXTURE_SIZEY      (100)							// �e�N�X�`���𒣂�t���鍂��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTutorialLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTutorialLogo = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialLogo = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_PosTutorialLogo;             // �`���[�g���A�����S���W
//D3DXVECTOR3             g_MoveTutorialLogo;            // �`���[�g���A�����S�ړ���
D3DXCOLOR				g_colorTutorialLogo;		    // �`���[�g���A�����S�F

//=============================================================================
// ����������
//=============================================================================
void InitTutorialLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_PosTutorialLogo = D3DXVECTOR3(200.0f, 60.0f, 0.0f);
	//g_MoveTutorialLogo = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	g_colorTutorialLogo = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexTutorialLogo(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorialLogo(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTutorialLogo != NULL)
	{
		g_pTextureTutorialLogo->Release();
		g_pTextureTutorialLogo = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorialLogo != NULL)
	{
		g_pVtxBuffTutorialLogo->Release();
		g_pVtxBuffTutorialLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialLogo(void)
{
	//if (g_PosTutorialLogo.y <= SCREEN_HEIGHT / 2)
	//{// �^�񒆂ɗ���܂�
	//	if (GetKeyboardTrigger(DIK_RETURN))
	//	{// ENTER�L�[�������ꂽ
	//		g_PosTutorialLogo.y = SCREEN_HEIGHT / 2;
	//	}
	//	else
	//	{
	//		g_PosTutorialLogo += g_MoveTutorialLogo;
	//		bool *disp;
	//		disp = GetDispPressEnter();
	//		disp = false;
	//	}

	//	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	//	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	//	g_pVtxBuffTutorialLogo->Lock(0, 0, (void**)&pVtx, 0);

	//	// ���_���W
	//	pVtx[0].pos = D3DXVECTOR3(g_PosTutorialLogo.x - TEXTURE_SIZEX, g_PosTutorialLogo.y - TEXTURE_SIZEY, g_PosTutorialLogo.z);
	//	pVtx[1].pos = D3DXVECTOR3(g_PosTutorialLogo.x + TEXTURE_SIZEX, g_PosTutorialLogo.y - TEXTURE_SIZEY, g_PosTutorialLogo.z);
	//	pVtx[2].pos = D3DXVECTOR3(g_PosTutorialLogo.x - TEXTURE_SIZEX, g_PosTutorialLogo.y + TEXTURE_SIZEY, g_PosTutorialLogo.z);
	//	pVtx[3].pos = D3DXVECTOR3(g_PosTutorialLogo.x + TEXTURE_SIZEX, g_PosTutorialLogo.y + TEXTURE_SIZEY, g_PosTutorialLogo.z);

	//	// ���_�o�b�t�@���A�����b�N����
	//	g_pVtxBuffTutorialLogo->Unlock();
	//}
	//else
	//{
	//	SetPressEnter(D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0.0f),300,50);
	//}

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawTutorialLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorialLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTutorialLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureTutorialLogo);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialLogo,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorialLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_PosTutorialLogo.x - TEXTURE_SIZEX, g_PosTutorialLogo.y - TEXTURE_SIZEY, g_PosTutorialLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosTutorialLogo.x + TEXTURE_SIZEX, g_PosTutorialLogo.y - TEXTURE_SIZEY, g_PosTutorialLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosTutorialLogo.x - TEXTURE_SIZEX, g_PosTutorialLogo.y + TEXTURE_SIZEY, g_PosTutorialLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosTutorialLogo.x + TEXTURE_SIZEX, g_PosTutorialLogo.y + TEXTURE_SIZEY, g_PosTutorialLogo.z);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorTutorialLogo;
	pVtx[1].col = g_colorTutorialLogo;
	pVtx[2].col = g_colorTutorialLogo;
	pVtx[3].col = g_colorTutorialLogo;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialLogo->Unlock();
}