//=============================================================================
//
// �e�̏��� [shadow.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "shadow.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SHADOW_TEXTURE_NAME   "data/TEXTURE/shadow000.jpg"          // �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureShadow = NULL;   // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;   // ���_�o�b�t�@�ւ̃|�C���^
Shadow                  g_aShadow[MAX_SHADOW];     // �e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_���̍쐬
	MakeVertexShadow(pDevice);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{// �e�̑������J��Ԃ�
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);
		g_aShadow[nCntShadow].width = 0.0f;
		g_aShadow[nCntShadow].depth = 0.0f;
		g_aShadow[nCntShadow].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{ 
	// �e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
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
	D3DXMATRIX mtxRot, mtxTrans;                // �v�Z�p�}�g���b�N�X

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{// �e�̑������J��Ԃ�
		if (g_aShadow[nCntShadow].bUse == true)
		{// �e���g�p����Ă���
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

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, NUM_POLYGON);
		}
	}

	// �����̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		SHADOW_TEXTURE_NAME,
		&g_pTextureShadow);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{// �e�̑������J��Ԃ�
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].width, 0.0f, g_aShadow[nCntShadow].depth);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].width, 0.0f, g_aShadow[nCntShadow].depth);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].width, 0.0f, -g_aShadow[nCntShadow].depth);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].width, 0.0f, -g_aShadow[nCntShadow].depth);

		// �@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[
		pVtx[0].col = g_aShadow[nCntShadow].col;
		pVtx[1].col = g_aShadow[nCntShadow].col;
		pVtx[2].col = g_aShadow[nCntShadow].col;
		pVtx[3].col = g_aShadow[nCntShadow].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}
//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float width, float depth)
{
	VERTEX_3D *pVtx;
	int nCntShadow;  // �e�̔ԍ�

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{// �e�̑������J��Ԃ�
		if (g_aShadow[nCntShadow].bUse == false)
		{// �e���g�p����Ă��Ȃ�
			g_aShadow[nCntShadow].pos = pos;       // �ʒu��ݒ�
			g_aShadow[nCntShadow].rot = rot;       // ������ݒ�
			g_aShadow[nCntShadow].width = width;   // ����ݒ�
			g_aShadow[nCntShadow].depth = depth;   // ���s��ݒ�
			g_aShadow[nCntShadow].col = col;       // �F��ݒ�

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].width, 0.0f, g_aShadow[nCntShadow].depth);
			pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].width, 0.0f, g_aShadow[nCntShadow].depth);
			pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].width, 0.0f, -g_aShadow[nCntShadow].depth);
			pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].width, 0.0f, -g_aShadow[nCntShadow].depth);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aShadow[nCntShadow].col;
			pVtx[1].col = g_aShadow[nCntShadow].col;
			pVtx[2].col = g_aShadow[nCntShadow].col;
			pVtx[3].col = g_aShadow[nCntShadow].col;

			g_aShadow[nCntShadow].bUse = true;     // �g�p���Ă����Ԃɂ���
			break;
		}
		pVtx += 4;   // �|�C���^��i�߂Ă���
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}
//=============================================================================
// �e�̍��W�ݒ�
//=============================================================================
void SetPositionShadow(int IdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[IdxShadow].pos = pos;  // ���W��ݒ肵�Ȃ���
}
//=============================================================================
// �e�̐F�ݒ�
//=============================================================================
void SetColShadow(int IdxShadow, D3DXCOLOR col)
{
	g_aShadow[IdxShadow].col = col;  // �F��ݒ肵�Ȃ���

	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += IdxShadow * 4;  // �|�C���^��ԍ��̐擪�ɂ����Ă���

	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_aShadow[IdxShadow].col;
	pVtx[1].col = g_aShadow[IdxShadow].col;
	pVtx[2].col = g_aShadow[IdxShadow].col;
	pVtx[3].col = g_aShadow[IdxShadow].col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}
//=============================================================================
// �e�̑傫���ݒ�
//=============================================================================
void SetSizeShadow(int IdxShadow, float width, float depth)
{
	g_aShadow[IdxShadow].width = width;  // ����ݒ肵�Ȃ���
	g_aShadow[IdxShadow].depth = depth;  // ���s��ݒ肵�Ȃ���

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += IdxShadow * 4;    // �|�C���^��ԍ��̐擪�ɂ����Ă���

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-g_aShadow[IdxShadow].width, 0.0f, g_aShadow[IdxShadow].depth);
	pVtx[1].pos = D3DXVECTOR3(g_aShadow[IdxShadow].width, 0.0f, g_aShadow[IdxShadow].depth);
	pVtx[2].pos = D3DXVECTOR3(-g_aShadow[IdxShadow].width, 0.0f, -g_aShadow[IdxShadow].depth);
	pVtx[3].pos = D3DXVECTOR3(g_aShadow[IdxShadow].width, 0.0f, -g_aShadow[IdxShadow].depth);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}
//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteShadow(int IdxShadow)
{
	g_aShadow[IdxShadow].bUse = false;  // �g�p���Ă��Ȃ���Ԃɂ���
}