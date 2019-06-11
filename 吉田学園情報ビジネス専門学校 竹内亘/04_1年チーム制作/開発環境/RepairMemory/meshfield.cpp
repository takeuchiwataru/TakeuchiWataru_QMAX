//=========================================================================================================================
//
// �t�B�[���h���� [meshfield.cpp]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS		// scanf�G���[����
#include <stdio.h>					// stdio
#include "meshfield.h"
#include "input.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MESHFIELD_TEXT_INFO			"data\\TEXT\\meshfielddata.txt"			// �ǂݍ��ރf�[�^�t�@�C��
#define MAX_MESHFIELD				(32)									// �t�B�[���h�̍ő吔
#define MESHFIELD_TEXTURE_UV_U		(1.0f)									// �e�N�X�`���A�j���[�V����U�͈�
#define MESHFIELD_TEXTURE_UV_V		(1.0f)									// �e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);						// ���_���̐ݒ�

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9				g_pTextureMeshField[FIELDTEXTURE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffMeshField = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9			g_pIdxBuffMeshField = NULL;					// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshField						g_MeshField[MAX_MESHFIELD];					// �t�B�[���h�̏��
int								g_MaxMeshField;								// �ǂݍ��ރ��f���̍ő吔
int								g_MaxVtxMeshField;							// ���_�̍ő吔
int								g_MaxIdxMeshField;							// �C���f�b�N�X�̍ő吔
int								g_MaxPolygonMeshField;						// �|���S���̍ő吔

//=========================================================================================================================
// �t�B�[���h�̏���������
//=========================================================================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCntMeshField;
	FILE *pFile;

	g_MaxMeshField = 0;
	g_MaxPolygonMeshField = 0;
	g_MaxVtxMeshField = 0;

	// �t�@�C���ݒ�
	pFile = fopen(MESHFIELD_TEXT_INFO, "r");

	// �t�B�[���h�e�L�X�g�f�[�^�ǂݍ���
	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		fscanf(pFile, "%d", &g_MaxMeshField);	// �ǂݍ���

		for (nCntMeshField = 0; nCntMeshField < g_MaxMeshField; nCntMeshField++)
		{
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].pos.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].pos.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].pos.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].rot.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].rot.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].rot.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].num.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].num.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].num.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].fRadius.x);	// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].fRadius.y);	// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshField[nCntMeshField].fRadius.z);	// �ǂݍ���
		}

		fclose(pFile);	// �t�@�C�������
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}

	for (nCntMeshField = 0; nCntMeshField < g_MaxMeshField; nCntMeshField++)
	{
		// ���_�A�C���f�b�N�X�A�|���S�������v�Z
		g_MeshField[nCntMeshField].MaxVtx = ((int)g_MeshField[nCntMeshField].num.x + 1) * ((int)g_MeshField[nCntMeshField].num.z + 1);
		g_MeshField[nCntMeshField].MaxIdx = (((int)g_MeshField[nCntMeshField].num.x + 1) * 2) * (int)g_MeshField[nCntMeshField].num.z + (((int)g_MeshField[nCntMeshField].num.z - 1) * 2);
		g_MeshField[nCntMeshField].MaxPolygon = ((int)g_MeshField[nCntMeshField].num.x * (int)g_MeshField[nCntMeshField].num.z * 2) + (((int)g_MeshField[nCntMeshField].num.z - 1) * 4);
		g_MeshField[nCntMeshField].nTexNum = 0;
		g_MeshField[nCntMeshField].bUse = false;

		// ���_�A�C���f�b�N�X�A�|���S���������Z
		g_MaxVtxMeshField += g_MeshField[nCntMeshField].MaxVtx;
		g_MaxIdxMeshField += g_MeshField[nCntMeshField].MaxIdx;
		g_MaxPolygonMeshField += g_MeshField[nCntMeshField].MaxPolygon;
	}

	// ���_���̍쐬
	MakeVertexMeshField(pDevice);
}

//=========================================================================================================================
// �t�B�[���h�̏I������
//=========================================================================================================================
void UninitMeshField(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < FIELDTEXTURE_MAX; nCntTex++)
	{
		if (g_pTextureMeshField[nCntTex] != NULL)
		{
			g_pTextureMeshField[nCntTex]->Release();
			g_pTextureMeshField[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=========================================================================================================================
// �t�B�[���h�̍X�V����
//=========================================================================================================================
void UpdateMeshField(void)
{

}

//=========================================================================================================================
// �t�B�[���h�̕`�揈��
//=========================================================================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	int nCntMeshField, nNumVtx = 0, nNumIdx = 0;

	for (nCntMeshField = 0; nCntMeshField < g_MaxMeshField; nCntMeshField++)
	{
		if (g_MeshField[nCntMeshField].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshField[nCntMeshField].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_MeshField[nCntMeshField].rot.y,
				g_MeshField[nCntMeshField].rot.x,
				g_MeshField[nCntMeshField].rot.z
			);

			D3DXMatrixMultiply
			(
				&g_MeshField[nCntMeshField].mtxWorld,
				&g_MeshField[nCntMeshField].mtxWorld,
				&mtxRot
			);

			// �ʒu�𔽉f
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_MeshField[nCntMeshField].pos.x,
				g_MeshField[nCntMeshField].pos.y,
				g_MeshField[nCntMeshField].pos.z
			);

			D3DXMatrixMultiply
			(
				&g_MeshField[nCntMeshField].mtxWorld,
				&g_MeshField[nCntMeshField].mtxWorld,
				&mtxTrans
			);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshField[nCntMeshField].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource
			(
				0,
				g_pVtxBuffMeshField,
				0,
				sizeof(VERTEX_3D)
			);

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshField);

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���ݒ�
			if (g_MeshField[nCntMeshField].nTexNum >= FIELDTEXTURE_MAX)
			{
				pDevice->SetTexture(0, NULL);
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureMeshField[g_MeshField[nCntMeshField].nTexNum]);
			}

			// �t�B�[���h�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, nNumIdx, g_MeshField[nCntMeshField].MaxIdx + nNumIdx, nNumIdx, g_MeshField[nCntMeshField].MaxPolygon);
		}

		nNumVtx += g_MeshField[nCntMeshField].MaxVtx;
		nNumIdx += g_MeshField[nCntMeshField].MaxIdx;
	}
}

//=========================================================================================================================
// �t�B�[���h�̐ݒ菈��
//=========================================================================================================================
void SetMeshField(int SetNum, int nTexNum)
{
	int nCntMeshField, nNumVtx = 0, nNumIdx = 0;
	int nCount_x, nCount_z, nCount_mesh = 0;

	int ip = 0;
	float fx = 0, fz = 0;

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshField->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	WORD *pIdx;			// �C���f�b�N�X�f�[�^�ւ̃|�C���^

						// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshField = 0; nCntMeshField < SetNum; nCntMeshField++)
	{// �|���S�����J�E���g
		nCount_mesh = 0;
		nNumVtx += g_MeshField[nCntMeshField].MaxVtx;
		nNumIdx += g_MeshField[nCntMeshField].MaxIdx;
	}

	if (g_MeshField[SetNum].bUse == false)
	{// �g�p���Ă��Ȃ��ꍇ
		g_MeshField[SetNum].nTexNum = nTexNum;
		g_MeshField[SetNum].bUse = true;				// �g�p����

														// ���_���̐ݒ�
		for (nCount_z = 0; nCount_z < g_MeshField[SetNum].num.z + 1; nCount_z++)
		{// z���J�E���g
			for (nCount_x = 0; nCount_x < g_MeshField[SetNum].num.x + 1; nCount_x++)
			{// x���J�E���g

			 // pVtx[(���b�V���J�E���^ * ���_��) + (z�J�E���^ * (x�̐ݒu�� + 1)) + (x�J�E���^)]
			 // ��F	(		nCntxxx	  *	  4	  )	+ (	  0		 * (    2  	  + 1)) + (    0	)
			 // .pos.x = -((x�̑傫�� / 2) * x�̐ݒu��) + (x�̑傫�� * x�J�E���^)
			 //		z =  ((z�̑傫�� / 2) * z�̐ݒu��) - (z�̑傫�� * z�J�E���^)
			 // ���S�ɕ`�悷�邽�߂Ɋ��Q���s���B
			 // �ł����Ɖ��̒l�����߁A���Z���Z�ɂ�葼���_�����߂�

				pVtx[(nNumVtx)+(nCount_z * (((int)g_MeshField[SetNum].num.x + 1))) + (nCount_x)].pos = D3DXVECTOR3(
					-((g_MeshField[SetNum].fRadius.x / 2) * g_MeshField[SetNum].num.x) + (g_MeshField[SetNum].fRadius.x * nCount_x), 0.0f,
					((g_MeshField[SetNum].fRadius.z / 2) * g_MeshField[SetNum].num.z) - (g_MeshField[SetNum].fRadius.z * (nCount_z)));

				ip = (nNumVtx)+(nCount_z * (((int)g_MeshField[SetNum].num.x + 1))) + (nCount_x);
				fx = -((g_MeshField[SetNum].fRadius.x / 2) * g_MeshField[SetNum].num.x) + (g_MeshField[SetNum].fRadius.x * nCount_x);
				fz = ((g_MeshField[SetNum].fRadius.z / 2) * g_MeshField[SetNum].num.z) - (g_MeshField[SetNum].fRadius.z * (nCount_z));

				// pVtx[(���b�V���J�E���^ * ���_��) + (z�J�E���^ * (x�̐ݒu�� + 1)) + (x�J�E���^)]
				// ��F	(		nCntxxx	  *	  4	  )	+ (	  0		 * (    2  	  + 1)) + (    0	)
				// .pos.x = -((x�̑傫�� / 2) * x�̐ݒu��) + (x�̑傫�� * x�J�E���^)
				//		z =  ((z�̑傫�� / 2) * z�̐ݒu��) - (z�̑傫�� * z�J�E���^)
				// ���S�ɕ`�悷�邽�߂Ɋ��Q���s���B
				// �ł����Ɖ��̒l�����߁A���Z���Z�ɂ�葼���_�����߂�

				// �܂��Ȃ����ĂȂ���

				pVtx[(nNumVtx)+(nCount_z * (((int)g_MeshField[SetNum].num.x + 1))) + (nCount_x)].tex =
					//D3DXVECTOR2((MESHFIELD_TEXTURE_UV_U / (g_MeshField[SetNum].num.x)) * (nCount_x % ((int)g_MeshField[SetNum].num.x + 1)), (MESHFIELD_TEXTURE_UV_V / (g_MeshField[SetNum].num.z)) * (nCount_z));
					D3DXVECTOR2(MESHFIELD_TEXTURE_UV_U * (nCount_x % ((int)g_MeshField[SetNum].num.x + 1)), MESHFIELD_TEXTURE_UV_V * (nCount_z));
			}
		}

		// �C���f�b�N�X�̐ݒ�
		for (nCount_z = 0; nCount_z < g_MeshField[SetNum].num.z; nCount_z++)
		{
			for (nCount_x = 0; nCount_x < g_MeshField[SetNum].num.x + 1; nCount_x++)
			{
				// pIdx[(���b�V���J�E���^ * ���_��) + (z�J�E���^ * (x�̐ݒu�� + 1)) + (x�J�E���^ * 2) + �t�B�[���h�Ɏg�p�������_��]
				// ��F	(		nCntxxx	  *	  4	  )	+ (	  0		 * (    2  	  + 1)) + (    0	 * 2) + 0
				//	=	((z�J�E���^ + 1) * (x�̐ݒu�� + 1)) + (x�J�E���^)
				// pIdx��	x�J�E���^ * 2	��2���_���ݒ肷�邽�ߍs���i2���_�ڂ�	+ 1	�ōs��)
				// z�J�E���^ + 1	�ɂ�艺�����߁A����	z�J�E���^�@�݂̂ŏ�����߂�	

				pIdx[(nNumIdx)+(nCount_z * (((int)g_MeshField[SetNum].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh] =
					(WORD)(((nNumVtx)+(nCount_z + 1) * (g_MeshField[SetNum].num.x + 1)) + nCount_x);

				pIdx[(nNumIdx)+(nCount_z * (((int)g_MeshField[SetNum].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1] =
					(WORD)(((nNumVtx)+(nCount_z) * (g_MeshField[SetNum].num.x + 1)) + nCount_x);

				ip = (nNumIdx)+(nCount_z * (((int)g_MeshField[SetNum].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh;
				fx = (((nNumVtx)+(nCount_z + 1) * (g_MeshField[SetNum].num.x + 1)) + nCount_x);
				fz = (((nNumVtx)+(nCount_z) * (g_MeshField[SetNum].num.x + 1)) + nCount_x);

				if (g_MeshField[SetNum].num.z > 1 && nCount_z != g_MeshField[SetNum].num.z - 1 && nCount_x == g_MeshField[SetNum].num.x)
				{
					pIdx[(nNumIdx)+(nCount_z * (((int)g_MeshField[SetNum].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1 + 1] =
						(WORD)(((nNumVtx)+(nCount_z) * (g_MeshField[SetNum].num.x + 1)) + nCount_x);

					pIdx[(nNumIdx)+(nCount_z * (((int)g_MeshField[SetNum].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1 + 2] =
						(WORD)(((nNumVtx)+(nCount_z + 2) * (g_MeshField[SetNum].num.x + 1)));

					nCount_mesh += 2;		// �t�B�[���h�̒��_���Z
				}
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshField->Unlock();

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshField->Unlock();
}

//=========================================================================================================================
// �t�B�[���h�̎擾����
//=========================================================================================================================
MeshField *GetMeshField(void)
{
	return &g_MeshField[0];
}

//=========================================================================================================================
// �t�B�[���h�̏Փˏ���
//=========================================================================================================================
bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax)
{
	int nCntMeshField;
	bool bLand = false;

	for (nCntMeshField = 0; nCntMeshField < g_MaxMeshField; nCntMeshField++)
	{
		if (g_MeshField[nCntMeshField].bUse == true)
		{// �g�p����Ă���
			if (pPos->x + vtxMax->x > g_MeshField[nCntMeshField].pos.x - ((g_MeshField[nCntMeshField].fRadius.x / 2.0f) * g_MeshField[nCntMeshField].num.x) && pPos->x + vtxMin->x < g_MeshField[nCntMeshField].pos.x + ((g_MeshField[nCntMeshField].fRadius.x / 2.0f) * g_MeshField[nCntMeshField].num.x))
			{// X�͈͊m�F
				if (pPos->z + vtxMax->z > g_MeshField[nCntMeshField].pos.z - ((g_MeshField[nCntMeshField].fRadius.z / 2.0f) * g_MeshField[nCntMeshField].num.z) && pPos->z + vtxMin->z < g_MeshField[nCntMeshField].pos.z + ((g_MeshField[nCntMeshField].fRadius.z / 2.0f) * g_MeshField[nCntMeshField].num.z))
				{// Z�͈͊m�F
					if (pPosOld->y >= g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fRadius.y && g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fRadius.y > pPos->y)
					{// Y����
						pPos->y = g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fRadius.y;
						pMove->y = 0.0f;
						//pMove->z = 0.0f;
					}
				}
			}
		}
	}

	return bLand;
}

//=========================================================================================================================
// �t�B�[���h�̔j������
//=========================================================================================================================
void DeleteMeshField(void)
{
	int nCntMeshField;

	for (nCntMeshField = 0; nCntMeshField < g_MaxMeshField; nCntMeshField++)
	{
		if (g_MeshField[nCntMeshField].bUse == true)
		{// �g�p����Ă���
			g_MeshField[nCntMeshField].bUse = false;
		}
	}
}

//=========================================================================================================================
// ���_���̍쐬
//=========================================================================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntMeshField;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME1, &g_pTextureMeshField[0]);
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME2, &g_pTextureMeshField[1]);
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME3, &g_pTextureMeshField[2]);
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME4, &g_pTextureMeshField[3]);
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME5, &g_pTextureMeshField[4]);
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME6, &g_pTextureMeshField[5]);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * g_MaxVtxMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL
	);

	// �C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * g_MaxIdxMeshField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL
	);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshField = 0; nCntMeshField < g_MaxVtxMeshField; nCntMeshField++)
	{
		// ���_���̐ݒ�
		pVtx[nCntMeshField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �@���̐ݒ�
		pVtx[nCntMeshField].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[nCntMeshField].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`���̐ݒ�
		pVtx[nCntMeshField].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshField->Unlock();

	WORD *pIdx;			// �C���f�b�N�X�f�[�^�ւ̃|�C���^

						// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshField = 0; nCntMeshField < g_MaxIdxMeshField; nCntMeshField++)
	{
		// �C���f�b�N�X�̐ݒ�
		pIdx[nCntMeshField] = nCntMeshField;
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshField->Unlock();
}