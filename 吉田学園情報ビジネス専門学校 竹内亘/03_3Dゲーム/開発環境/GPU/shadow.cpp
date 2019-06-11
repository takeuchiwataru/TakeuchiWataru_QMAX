//=============================================================================
//
// �e���� [shadow.cpp]
// Author : �|���j
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SHADOW_TEXTURENAME	"data/TEXTURE/shadow000.jpg"			// �e�N�X�`����
#define MAX_SHADOW (256)											// �e�̍ő吔
#define SHADOW_POS (10.0f)											// �e�̈ʒu

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;					// �e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3 g_posShadow;									// �ʒu
//D3DXVECTOR3 g_rotShadow;									// ����
//D3DXMATRIX g_mtxWorldShadow;								// ���[���h�}�g���b�N�X
Shadow g_aShadow[MAX_SHADOW];								// �e�̏�� 

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�̏�����
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, SHADOW_TEXTURENAME, &g_pTextureShadow);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-SHADOW_POS, 0.0f, SHADOW_POS);
		pVtx[1].pos = D3DXVECTOR3(SHADOW_POS, 0.0f, SHADOW_POS);
		pVtx[2].pos = D3DXVECTOR3(-SHADOW_POS, 0.0f, -SHADOW_POS);
		pVtx[3].pos = D3DXVECTOR3(SHADOW_POS, 0.0f, -SHADOW_POS);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
	// �e�N�X�`���̉��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureShadow);

		if (g_aShadow[nCntShadow].bUse == true)	// �e���g�p����Ă���
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntShadow,
				2);
		}
	}

	// ���̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
//void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
//{
//	// ���_�o�b�t�@�𐶐�
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,	//�m�ۂ���o�b�t�@�̃T�C�Y
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffShadow,
//		NULL);
//
//	// ���_���̐ݒ�
//	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
//
//	int nCntShadow;
//
//	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
//	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
//	{
//		// ���_���W�̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - 10.0f, 0.0f, g_aShadow[nCntShadow].pos.z + 10.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + 10.0f, 0.0f, g_aShadow[nCntShadow].pos.z + 10.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - 10.0f, 0.0f, g_aShadow[nCntShadow].pos.z - 10.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + 10.0f, 0.0f, g_aShadow[nCntShadow].pos.z - 10.0f);
//
//		// �@���̐ݒ�
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		// ���_�J���[�̐ݒ�
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		// �e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//	
//	// ���_�o�b�t�@���A�����b�N
//	g_pVtxBuffShadow->Unlock();
//}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
			pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
			pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
			pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;			// �g�p���Ă���
			break;
		}
		pVtx += 4;

	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//=============================================================================
// �e�̈ʒu��ݒ�
//=============================================================================
void SetPositionShadow(int nIdexShadow, D3DXVECTOR3 pos)
{	
	g_aShadow[nIdexShadow].pos = pos;
}
//=============================================================================
// �e�̈ʒu��ݒ�
//=============================================================================
void DeleteShadow(int nIdexShadow)
{
	g_aShadow[nIdexShadow].bUse = false;
}


