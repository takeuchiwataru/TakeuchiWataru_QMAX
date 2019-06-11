//=============================================================================
//
// �^�C�g�����S���� [titlelogo.cpp]
// Author : �|���j
//
//=============================================================================
#include "titlelogo.h"
#include "pressenter.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME       "data/TEXTURE/title000.png"      // �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZEX      (900)							// �e�N�X�`���𒣂�t���镝
#define TEXTURE_SIZEY      (300)							// �e�N�X�`���𒣂�t���鍂��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTitleLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTitleLogo = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_PosTitleLogo;             // �^�C�g�����S���W
D3DXVECTOR3             g_MoveTitleLogo;            // �^�C�g�����S�ړ���
D3DXCOLOR				g_colorTitleLogo;		    // �^�C�g�����S�F

//=============================================================================
// ����������
//=============================================================================
void InitTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_PosTitleLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, -200, 0.0f);
	g_MoveTitleLogo = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	g_colorTitleLogo = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexTitleLogo(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitleLogo(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();
		g_pTextureTitleLogo = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();
		g_pVtxBuffTitleLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitleLogo(void)
{
	if (g_PosTitleLogo.y <= SCREEN_HEIGHT / 2 - 60.0f)
	{// �^�񒆂ɗ���܂�
		if (GetKeyboardTrigger(DIK_RETURN))
		{// ENTER�L�[�������ꂽ
			g_PosTitleLogo.y = SCREEN_HEIGHT / 2 - 60.0f;
		}
		else
		{
			g_PosTitleLogo += g_MoveTitleLogo;
			bool *disp;
			disp = GetDispPressEnter();
			disp = false;
		}
		for (int nCntPad = 0; nCntPad < 8; nCntPad++)
		{
			if (GetJoyPadTrigger(nCntPad, 0) == TRUE)
			{
				g_PosTitleLogo.y = SCREEN_HEIGHT / 2 - 60.0f;
			}
		}

		VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_PosTitleLogo.x - TEXTURE_SIZEX, g_PosTitleLogo.y - TEXTURE_SIZEY, g_PosTitleLogo.z);
		pVtx[1].pos = D3DXVECTOR3(g_PosTitleLogo.x + TEXTURE_SIZEX, g_PosTitleLogo.y - TEXTURE_SIZEY, g_PosTitleLogo.z);
		pVtx[2].pos = D3DXVECTOR3(g_PosTitleLogo.x - TEXTURE_SIZEX, g_PosTitleLogo.y + TEXTURE_SIZEY, g_PosTitleLogo.z);
		pVtx[3].pos = D3DXVECTOR3(g_PosTitleLogo.x + TEXTURE_SIZEX, g_PosTitleLogo.y + TEXTURE_SIZEY, g_PosTitleLogo.z);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTitleLogo->Unlock();
	}
	else
	{
		SetPressEnter(D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0.0f),450,100);
	}

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTitleLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureTitleLogo);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleLogo,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_PosTitleLogo.x - TEXTURE_SIZEX, g_PosTitleLogo.y - TEXTURE_SIZEY, g_PosTitleLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosTitleLogo.x + TEXTURE_SIZEX, g_PosTitleLogo.y - TEXTURE_SIZEY, g_PosTitleLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosTitleLogo.x - TEXTURE_SIZEX, g_PosTitleLogo.y + TEXTURE_SIZEY, g_PosTitleLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosTitleLogo.x + TEXTURE_SIZEX, g_PosTitleLogo.y + TEXTURE_SIZEY, g_PosTitleLogo.z);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorTitleLogo;
	pVtx[1].col = g_colorTitleLogo;
	pVtx[2].col = g_colorTitleLogo;
	pVtx[3].col = g_colorTitleLogo;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleLogo->Unlock();
}