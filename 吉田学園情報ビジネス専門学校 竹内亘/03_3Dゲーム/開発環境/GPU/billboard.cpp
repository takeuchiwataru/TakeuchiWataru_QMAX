//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : �|���j
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BB_TEXTURENAME	"data/TEXTURE/grass.png"				// �e�N�X�`����
#define MAX_BB (256)											// �r���{�[�h�̍ő吔
#define BB_POS (20.0f)											// ���_

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;			// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;				// �e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3 g_posWall;									// �ʒu
//D3DXVECTOR3 g_rotWall;									// ����
//D3DXMATRIX g_mtxWorldBillboard;								// ���[���h�}�g���b�N�X
Billboard g_aBillboard[MAX_BB];								// �ǂ̏�� 
int g_nIdexShadowBillboard;							// �e�̎擾�����邽��

//=============================================================================
// ����������
//=============================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCntBillboard;

	// �r���{�[�h�̏���������
	for (nCntBillboard = 0; nCntBillboard < MAX_BB; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].bUse = false;
	}


	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BB,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BB_TEXTURENAME, &g_pTextureBillboard);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BB; nCntBillboard++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BB_POS, BB_POS, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BB_POS, BB_POS, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BB_POS, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BB_POS, 0.0f, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
	// �e�N�X�`���̉��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard(void)
{
	int nCntBillboard;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (nCntBillboard = 0; nCntBillboard < MAX_BB; nCntBillboard++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
		g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
		g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
		g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
		g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
		g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
		g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
		g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
		g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBillboard);

		// �A���t�@�e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBillboard[nCntBillboard].bUse == true)	// �r���{�[�h���g�p����Ă���
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBillboard,
				2);
		}

		// �A���t�@�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
//// ���_���̍쐬
////=============================================================================
//void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
//{
//	// ���_�o�b�t�@�𐶐�
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffWall,
//		NULL);
//
//	// ���_���̐ݒ�
//	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
//
//	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
//	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
//
//	// ���_���W�̐ݒ�
//	pVtx[0].pos = D3DXVECTOR3(-50.0f, 50.0f, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
//
//	// �@���̐ݒ�
//	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//
//	// ���_�J���[�̐ݒ�
//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// �e�N�X�`�����W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	// ���_�o�b�t�@���A�����b�N
//	g_pVtxBuffWall->Unlock();
//}

//=============================================================================
// �r���{�[�h�̐ݒ�
//=============================================================================
int SetBillboard(D3DXVECTOR3 pos)
{
	int nCntBillboard;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BB; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = pos;


			//// ���_���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(-BB_POS, BB_POS, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(BB_POS, BB_POS, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(-BB_POS, 0.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(BB_POS, 0.0f, 0.0f);

			//g_aBillboard[nCntBillboard].rot = rot;
			g_aBillboard[nCntBillboard].bUse = true;			// �g�p���Ă���

			//g_aBillboard[nCntBillboard].nIdexShadow = SetShadow(g_aBillboard[nCntBillboard].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillboard->Unlock();

	return nCntBillboard;
}

