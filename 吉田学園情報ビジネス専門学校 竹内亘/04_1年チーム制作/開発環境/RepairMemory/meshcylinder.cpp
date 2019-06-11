//=========================================================================================================================
//
// �~������ [meshcylinder.cpp]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS		// scanf�G���[����
#include <stdio.h>					// stdio
#include "meshcylinder.h"
#include "input.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MESHCYLINDER_TEXT_INFO			"data\\TEXT\\meshcylinderdata.txt"		// �ǂݍ��ރf�[�^�t�@�C��
#define MAX_MESHCYLINDER				(32)									// �~���̍ő吔
#define MESHCYLINDER_TEXTURE_NAME1		"data\\TEXTURE\\sky001.jpg"				// �ǂݍ��ރe�N�X�`���t�@�C��1
#define MESHCYLINDER_TEXTURE_UV_U		(1.0f)									// �e�N�X�`���A�j���[�V����U�͈�
#define MESHCYLINDER_TEXTURE_UV_V		(1.0f)									// �e�N�X�`���A�j���[�V����V�͈�
#define MESHCYLINDER_MOVE_ROT			(0.0002f)								// ��]��

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice);							// ���_���̐ݒ�

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9				g_pTextureMeshCylinder = NULL;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffMeshCylinder = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9			g_pIdxBuffMeshCylinder = NULL;					// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshCylinder					g_MeshCylinder[MAX_MESHCYLINDER];				// �~���̏��
int								g_MaxMeshCylinder;								// �ǂݍ��ރ��f���̍ő吔
int								g_MaxVtxMeshCylinder;							// ���_�̍ő吔
int								g_MaxIdxMeshCylinder;							// �C���f�b�N�X�̍ő吔
int								g_MaxPolygonMeshCylinder;						// �|���S���̍ő吔

//=========================================================================================================================
// �~���̏���������
//=========================================================================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCntMeshCylinder;
	FILE *pFile;

	g_MaxMeshCylinder = 0;
	g_MaxPolygonMeshCylinder = 0;
	g_MaxVtxMeshCylinder = 0;

	// �t�@�C���ݒ�
	pFile = fopen(MESHCYLINDER_TEXT_INFO, "r");

	// �~���e�L�X�g�f�[�^�ǂݍ���
	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		fscanf(pFile, "%d", &g_MaxMeshCylinder);	// �ǂݍ���

		for (nCntMeshCylinder = 0; nCntMeshCylinder < g_MaxMeshCylinder; nCntMeshCylinder++)
		{
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].pos.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].pos.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].pos.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].rot.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].rot.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].rot.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].num.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].num.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].num.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].fRadius.x);	// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].fRadius.y);	// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshCylinder[nCntMeshCylinder].fRadius.z);	// �ǂݍ���
		}

		fclose(pFile);	// �t�@�C�������
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}

	for (nCntMeshCylinder = 0; nCntMeshCylinder < g_MaxMeshCylinder; nCntMeshCylinder++)
	{
		// ���_�A�C���f�b�N�X�A�|���S�������v�Z
		g_MeshCylinder[nCntMeshCylinder].MaxVtx = ((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1) * ((int)g_MeshCylinder[nCntMeshCylinder].num.y + 1);
		g_MeshCylinder[nCntMeshCylinder].MaxIdx = (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1) * 2) * (int)g_MeshCylinder[nCntMeshCylinder].num.y + (((int)g_MeshCylinder[nCntMeshCylinder].num.y - 1) * 2);
		g_MeshCylinder[nCntMeshCylinder].MaxPolygon = ((int)g_MeshCylinder[nCntMeshCylinder].num.x * (int)g_MeshCylinder[nCntMeshCylinder].num.y * 2) + (((int)g_MeshCylinder[nCntMeshCylinder].num.y - 1) * 4);
		g_MeshCylinder[nCntMeshCylinder].bUse = false;

		// ���_�A�C���f�b�N�X�A�|���S���������Z
		g_MaxVtxMeshCylinder += g_MeshCylinder[nCntMeshCylinder].MaxVtx;
		g_MaxIdxMeshCylinder += g_MeshCylinder[nCntMeshCylinder].MaxIdx;
		g_MaxPolygonMeshCylinder += g_MeshCylinder[nCntMeshCylinder].MaxPolygon;
	}

	// ���_���̍쐬
	MakeVertexMeshCylinder(pDevice);
}

//=========================================================================================================================
// �~���̏I������
//=========================================================================================================================
void UninitMeshCylinder(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//=========================================================================================================================
// �~���̍X�V����
//=========================================================================================================================
void UpdateMeshCylinder(void)
{
	int nCntMeshCylinder;

	for (nCntMeshCylinder = 0; nCntMeshCylinder < g_MaxMeshCylinder; nCntMeshCylinder++)
	{
		if (g_MeshCylinder[nCntMeshCylinder].bUse == true)
		{
			g_MeshCylinder[nCntMeshCylinder].rot.y += MESHCYLINDER_MOVE_ROT;
		}
	}
}

//=========================================================================================================================
// �~���̕`�揈��
//=========================================================================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	int nCntMeshCylinder, nNumVtx = 0, nNumIdx = 0;;

	for (nCntMeshCylinder = 0; nCntMeshCylinder < g_MaxMeshCylinder; nCntMeshCylinder++)
	{
		if (g_MeshCylinder[nCntMeshCylinder].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshCylinder[nCntMeshCylinder].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_MeshCylinder[nCntMeshCylinder].rot.y,
				g_MeshCylinder[nCntMeshCylinder].rot.x,
				g_MeshCylinder[nCntMeshCylinder].rot.z
			);

			D3DXMatrixMultiply
			(
				&g_MeshCylinder[nCntMeshCylinder].mtxWorld,
				&g_MeshCylinder[nCntMeshCylinder].mtxWorld,
				&mtxRot
			);

			// �ʒu�𔽉f
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_MeshCylinder[nCntMeshCylinder].pos.x,
				g_MeshCylinder[nCntMeshCylinder].pos.y,
				g_MeshCylinder[nCntMeshCylinder].pos.z
			);

			D3DXMatrixMultiply
			(
				&g_MeshCylinder[nCntMeshCylinder].mtxWorld,
				&g_MeshCylinder[nCntMeshCylinder].mtxWorld,
				&mtxTrans
			);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshCylinder[nCntMeshCylinder].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource
			(
				0,
				g_pVtxBuffMeshCylinder,
				0,
				sizeof(VERTEX_3D)
			);

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshCylinder);

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureMeshCylinder);
			//pDevice->SetTexture(0, NULL);

			// �~���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, nNumIdx, g_MeshCylinder[nCntMeshCylinder].MaxIdx + nNumIdx, nNumIdx, g_MeshCylinder[nCntMeshCylinder].MaxPolygon);
		}

		nNumVtx += g_MeshCylinder[nCntMeshCylinder].MaxVtx;
		nNumIdx += g_MeshCylinder[nCntMeshCylinder].MaxIdx;
	}
}

//=========================================================================================================================
// �~���̐ݒ菈��
//=========================================================================================================================
void SetMeshCylinder(void)
{
	int nCntMeshCylinder, nNumVtx = 0, nNumIdx = 0;
	int nCount_x, nCount_y, nCount_mesh = 0;

	D3DXVECTOR3 vecNor = D3DXVECTOR3(0.0f, 0.0f, 0.0);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	WORD *pIdx;			// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshCylinder = 0; nCntMeshCylinder < g_MaxMeshCylinder; nCntMeshCylinder++)
	{// �|���S�����J�E���g
		if (g_MeshCylinder[nCntMeshCylinder].bUse == false)
		{// �g�p���Ă��Ȃ��ꍇ
			g_MeshCylinder[nCntMeshCylinder].bUse = true;				// �g�p����

			// ���_���̐ݒ�
			for (nCount_y = 0; nCount_y < g_MeshCylinder[nCntMeshCylinder].num.y + 1; nCount_y++)
			{// y���J�E���g
				for (nCount_x = 0; nCount_x < g_MeshCylinder[nCntMeshCylinder].num.x + 1; nCount_x++)
				{// x���J�E���g
					pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.x = sinf(D3DX_PI + (D3DX_PI * (1.0f / (g_MeshCylinder[nCntMeshCylinder].num.x / 2))) * nCount_x) * g_MeshCylinder[nCntMeshCylinder].fRadius.x;
					pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.y = ((g_MeshCylinder[nCntMeshCylinder].fRadius.y) * g_MeshCylinder[nCntMeshCylinder].num.y) - (g_MeshCylinder[nCntMeshCylinder].fRadius.y * (nCount_y));
					pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.z = cosf(D3DX_PI + (D3DX_PI * (1.0f / (g_MeshCylinder[nCntMeshCylinder].num.x / 2))) * nCount_x) * g_MeshCylinder[nCntMeshCylinder].fRadius.x;

					vecNor.x = g_MeshCylinder[nCntMeshCylinder].pos.x - (pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.x / pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.x);
					//vecNor.y = g_MeshCylinder[nCntMeshCylinder].pos.y - (pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.y / pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.y);
					vecNor.z = g_MeshCylinder[nCntMeshCylinder].pos.z - (pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.z / pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].pos.z);
					D3DXVec3Normalize(&vecNor, &vecNor);		// ���K������
					pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].nor = vecNor;

					pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1))) + (nCount_x)].tex =
						D3DXVECTOR2((MESHCYLINDER_TEXTURE_UV_U / (g_MeshCylinder[nCntMeshCylinder].num.x)) * (nCount_x % ((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1)), (MESHCYLINDER_TEXTURE_UV_V / (g_MeshCylinder[nCntMeshCylinder].num.y)) * (nCount_y));
						//D3DXVECTOR2(MESHCYLINDER_TEXTURE_UV_U * (nCount_x % ((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1)), MESHCYLINDER_TEXTURE_UV_V * (nCount_y));
				}
			}

			// �C���f�b�N�X�̐ݒ�
			for (nCount_y = 0; nCount_y < g_MeshCylinder[nCntMeshCylinder].num.y; nCount_y++)
			{
				for (nCount_x = 0; nCount_x < g_MeshCylinder[nCntMeshCylinder].num.x + 1; nCount_x++)
				{
					// pIdx[(���b�V���J�E���^ * ���_��) + (y�J�E���^ * (x�̐ݒu�� + 1)) + (x�J�E���^ * 2) + �~���Ɏg�p�������_��]

					// ��F	(		nCntxxx	  *	  4	  )	+ (	  0		 * (    2  	  + 1)) + (    0	 * 2) + 0
					//	=	((y�J�E���^ + 1) * (x�̐ݒu�� + 1)) + (x�J�E���^)
					// pIdx��	x�J�E���^ * 2	��2���_���ݒ肷�邽�ߍs���i2���_�ڂ�	+ 1	�ōs��)
					// y�J�E���^ + 1	�ɂ�艺�����߁A����	y�J�E���^�@�݂̂ŏ�����߂�	

					pIdx[(nNumIdx) + (nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh] =
						(WORD)(((nCount_y + 1) * (g_MeshCylinder[nCntMeshCylinder].num.x + 1)) + nCount_x);
					
					pIdx[(nNumIdx) + (nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1] =
						(WORD)(((nCount_y) * (g_MeshCylinder[nCntMeshCylinder].num.x + 1)) + nCount_x);

					if (g_MeshCylinder[nCntMeshCylinder].num.y > 1 && nCount_y != g_MeshCylinder[nCntMeshCylinder].num.y - 1 && nCount_x == g_MeshCylinder[nCntMeshCylinder].num.x)
					{
						pIdx[(nNumIdx) + (nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1 + 1] =
							(WORD)(((nCount_y) * (g_MeshCylinder[nCntMeshCylinder].num.x + 1)) + nCount_x);
					
						pIdx[(nNumIdx) + (nCount_y * (((int)g_MeshCylinder[nCntMeshCylinder].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1 + 2] =
							(WORD)(((nCount_y + 2) * (g_MeshCylinder[nCntMeshCylinder].num.x + 1)));

						nCount_mesh += 2;		// �~���̒��_���Z
					}
				}
			}
		}
		
		nCount_mesh = 0;
		nNumVtx += g_MeshCylinder[nCntMeshCylinder].MaxVtx;		// ���_�o�b�t�@�𒲐�
		nNumIdx += g_MeshCylinder[nCntMeshCylinder].MaxIdx;		// �C���f�b�N�X�𒲐�
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshCylinder->Unlock();
}

//=========================================================================================================================
// �~���̔j������
//=========================================================================================================================
void DeleteMeshCylinder(void)
{
	int nCntMeshCylinder;

	for (nCntMeshCylinder = 0; nCntMeshCylinder < g_MaxMeshCylinder; nCntMeshCylinder++)
	{// �|���S�����J�E���g
		if (g_MeshCylinder[nCntMeshCylinder].bUse == true)
		{// �g�p���Ă��Ȃ��ꍇ
			g_MeshCylinder[nCntMeshCylinder].bUse = false;
		}
	}
}

//=========================================================================================================================
// ���_���̍쐬
//=========================================================================================================================
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntMeshCylinder;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_TEXTURE_NAME1, &g_pTextureMeshCylinder);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * g_MaxVtxMeshCylinder,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL
	);

	// �C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * g_MaxIdxMeshCylinder,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL
	);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshCylinder = 0; nCntMeshCylinder < g_MaxVtxMeshCylinder; nCntMeshCylinder++)
	{
		// ���_���̐ݒ�
		pVtx[nCntMeshCylinder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �@���̐ݒ�
		pVtx[nCntMeshCylinder].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// ���_�J���[�̐ݒ�
		pVtx[nCntMeshCylinder].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`���̐ݒ�
		pVtx[nCntMeshCylinder].tex = D3DXVECTOR2(0.0f, 0.0f);	
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshCylinder->Unlock();

	WORD *pIdx;			// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshCylinder = 0; nCntMeshCylinder < g_MaxIdxMeshCylinder; nCntMeshCylinder++)
	{
		// �C���f�b�N�X�̐ݒ�
		pIdx[nCntMeshCylinder] = nCntMeshCylinder;
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();
}

