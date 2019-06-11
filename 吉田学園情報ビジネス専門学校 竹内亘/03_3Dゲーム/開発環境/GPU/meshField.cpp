//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.cpp]
// Author : �|���j
//
//=============================================================================
#include "meshField.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURENAME	"data/TEXTURE/field005.jpg"						// �e�N�X�`����
#define MESHFIELD_POS (50.0f)													// �|���S���̈ʒu
#define MAX_MESHFIELD (14)
#define MAX_MF_X (15)															// X(���̐�)
#define MAX_MF_Z (15)															// Z(�c�̐�)
#define VERTEX_KAZU ((MAX_MF_X + 1) * (MAX_MF_Z + 1))							// ���_��
#define INDEX_KAZU ((((MAX_MF_X + 1) * 2) * (MAX_MF_Z)) + ((MAX_MF_Z - 1) * 2))	// �C���f�b�N�X��
#define POLYGON_KAZU (((MAX_MF_X * MAX_MF_Z) * 2) + ((MAX_MF_Z - 1) * 4))		// �|���S����											// �|���S����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexmeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffmeshField = NULL;			// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturemeshField = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;			// �C���f�b�N�X�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posmeshField;									// �ʒu
D3DXVECTOR3 g_rotmeshField;									// ����
D3DXMATRIX g_mtxWorldmeshField;								// ���[���h�}�g���b�N�X
int g_nNumVertexMeshField;									// ���_��
int g_nNumIndexMeshField;									// �C���f�b�N�X��
int g_nNumPolygonMeshField;									// �|���S����

//=============================================================================
// ����������
//=============================================================================
void InitmeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	int nCntMFdepth;
	int nCntMFwidth;

	// �e�������̐ݒ�
	g_nNumVertexMeshField = VERTEX_KAZU;		// ���_��
	g_nNumIndexMeshField = INDEX_KAZU;			// �C���f�b�N�X��
	g_nNumPolygonMeshField = POLYGON_KAZU;		// �|���S����

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_KAZU,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffmeshField,
		NULL);

	// �C���f�b�N�X�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_KAZU,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,			// 2�o�C�g�̃f�[�^
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURENAME, &g_pTexturemeshField);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffmeshField->Lock(0, 0, (void**)&pVtx, 0);

	 //���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	//pVtx[4].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[6].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[7].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[8].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[9].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	//pVtx[10].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[11].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[12].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	//pVtx[13].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);

	//���_���W�̐ݒ�
	for (nCntMFdepth = 0; nCntMFdepth < MAX_MF_Z + 1; nCntMFdepth++)
	{// �c�̖ʂ̐������J��Ԃ�
		for (nCntMFwidth = 0; nCntMFwidth < MAX_MF_X + 1; nCntMFwidth++)
		{// ���̖ʂ̐������J��Ԃ�
			pVtx[nCntMFdepth * (MAX_MF_X + 1) + nCntMFwidth].pos = D3DXVECTOR3((-MESHFIELD_POS / 2) + nCntMFdepth * MESHFIELD_POS , 0.0f, (-MESHFIELD_POS / 2 )+ nCntMFwidth * MESHFIELD_POS);
			pVtx[nCntMFdepth * (MAX_MF_X + 1) + nCntMFwidth].nor = D3DXVECTOR3(0.0f, 1.0f , 0.0f);
			pVtx[nCntMFdepth * (MAX_MF_X + 1) + nCntMFwidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntMFdepth * (MAX_MF_X + 1) + nCntMFwidth].tex = D3DXVECTOR2(1.0f * (nCntMFdepth % (MAX_MF_X + 1)), 1.0f * (nCntMFwidth));
		}
	}

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-MESHFIELD_POS, 0.0f, MESHFIELD_POS);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, MESHFIELD_POS);
	//pVtx[2].pos = D3DXVECTOR3(MESHFIELD_POS, 0.0f, MESHFIELD_POS);
	//pVtx[3].pos = D3DXVECTOR3(-MESHFIELD_POS, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(MESHFIELD_POS, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-MESHFIELD_POS, 0.0f, -MESHFIELD_POS);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -MESHFIELD_POS);
	//pVtx[8].pos = D3DXVECTOR3(MESHFIELD_POS, 0.0f, -MESHFIELD_POS);

	// // �@���̐ݒ�
	//pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//// ���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);

	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	//pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffmeshField->Unlock();

	WORD * pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntMesh = 0;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMFdepth = 0; nCntMFdepth < MAX_MF_Z ; nCntMFdepth++)
	{
		for (nCntMFwidth = 0; nCntMFwidth < MAX_MF_X + 1; nCntMFwidth++)
		{
			pIdx[(nCntMFdepth * (MAX_MF_X + 1) * 2) + (nCntMFwidth * 2) + nCntMesh] = ((nCntMFdepth + 1) * (MAX_MF_X + 1)) + nCntMFwidth;
			pIdx[(nCntMFdepth * (MAX_MF_X + 1) * 2) + (nCntMFwidth * 2) + 1 + nCntMesh] = (nCntMFdepth * (MAX_MF_X + 1)) + nCntMFwidth;

			if (MAX_MF_Z > 1 && nCntMFdepth != MAX_MF_Z - 1 && nCntMFwidth == MAX_MF_X)
			{
				pIdx[(nCntMFdepth * (MAX_MF_X + 1) * 2) + (nCntMFwidth * 2) + 1 + nCntMesh + 1] = (nCntMFdepth * (MAX_MF_X + 1)) + nCntMFwidth;
				pIdx[(nCntMFdepth * (MAX_MF_X + 1) * 2) + (nCntMFwidth * 2) + 1 + nCntMesh + 2] = ((nCntMFdepth + 2) * (MAX_MF_X + 1));

				nCntMesh += 2;
			}
		}
	}

	// �C���f�b�N�X�̐ݒ�
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitmeshField(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffmeshField != NULL)
	{
		g_pVtxBuffmeshField->Release();
		g_pVtxBuffmeshField = NULL;
	}
	// �e�N�X�`���̉��
	if (g_pTexturemeshField != NULL)
	{
		g_pTexturemeshField->Release();
		g_pTexturemeshField = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatemeshField(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawmeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldmeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotmeshField.y, g_rotmeshField.x, g_rotmeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldmeshField, &g_mtxWorldmeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posmeshField.x, g_posmeshField.y, g_posmeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldmeshField, &g_mtxWorldmeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldmeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffmeshField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturemeshField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VERTEX_KAZU, 0, POLYGON_KAZU);		// ���_��,0,�`�悷��v���~�e�B�u��(�|���S����)
}

////=============================================================================
//// ���_���̍쐬
////=============================================================================
//void MakeVertexmeshField(LPDIRECT3DDEVICE9 pDevice)
//{

//}

