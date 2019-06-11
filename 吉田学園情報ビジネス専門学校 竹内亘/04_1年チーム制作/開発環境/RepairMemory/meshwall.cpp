//=========================================================================================================================
//
// �Ǐ��� [meshwall.cpp]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS		// scanf�G���[����
#include <stdio.h>					// stdio
#include "meshwall.h"
#include "input.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MESHWALL_TEXT_INFO			"data\\TEXT\\meshwalldata.txt"			// �ǂݍ��ރf�[�^�t�@�C��
#define MAX_MESHWALL				(32)									// �ǂ̍ő吔
#define MESHWALL_TEXTURE_NAME1		"data\\TEXTURE\\field101.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C��1
#define MESHWALL_TEXTURE_UV_U		(1.0f)									// �e�N�X�`���A�j���[�V����U�͈�
#define MESHWALL_TEXTURE_UV_V		(1.0f)									// �e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);						// ���_���̐ݒ�

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9				g_pTextureMeshWall = NULL;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffMeshWall = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9			g_pIdxBuffMeshWall = NULL;					// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshWall						g_MeshWall[MAX_MESHWALL];					// �ǂ̏��
int								g_MaxMeshWall;								// �ǂݍ��ރ��f���̍ő吔
int								g_MaxVtxMeshWall;							// ���_�̍ő吔
int								g_MaxIdxMeshWall;							// �C���f�b�N�X�̍ő吔
int								g_MaxPolygonMeshWall;						// �|���S���̍ő吔

//=========================================================================================================================
// �ǂ̏���������
//=========================================================================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCntMeshWall;
	FILE *pFile;

	g_MaxMeshWall = 0;
	g_MaxPolygonMeshWall = 0;
	g_MaxVtxMeshWall = 0;

	// �t�@�C���ݒ�
	pFile = fopen(MESHWALL_TEXT_INFO, "r");

	// �ǃe�L�X�g�f�[�^�ǂݍ���
	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		fscanf(pFile, "%d", &g_MaxMeshWall);	// �ǂݍ���

		for (nCntMeshWall = 0; nCntMeshWall < g_MaxMeshWall; nCntMeshWall++)
		{
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].pos.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].pos.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].pos.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].rot.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].rot.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].rot.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].num.x);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].num.y);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].num.z);		// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].fRadius.x);	// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].fRadius.y);	// �ǂݍ���
			fscanf(pFile, "%f", &g_MeshWall[nCntMeshWall].fRadius.z);	// �ǂݍ���
		}

		fclose(pFile);	// �t�@�C�������
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}

	for (nCntMeshWall = 0; nCntMeshWall < g_MaxMeshWall; nCntMeshWall++)
	{
		// ���_�A�C���f�b�N�X�A�|���S�������v�Z
		g_MeshWall[nCntMeshWall].MaxVtx = ((int)g_MeshWall[nCntMeshWall].num.x + 1) * ((int)g_MeshWall[nCntMeshWall].num.y + 1);
		g_MeshWall[nCntMeshWall].MaxIdx = (((int)g_MeshWall[nCntMeshWall].num.x + 1) * 2) * (int)g_MeshWall[nCntMeshWall].num.y + (((int)g_MeshWall[nCntMeshWall].num.y - 1) * 2);
		g_MeshWall[nCntMeshWall].MaxPolygon = ((int)g_MeshWall[nCntMeshWall].num.x * (int)g_MeshWall[nCntMeshWall].num.y * 2) + (((int)g_MeshWall[nCntMeshWall].num.y - 1) * 4);
		g_MeshWall[nCntMeshWall].nTexNum = 0;
		g_MeshWall[nCntMeshWall].bUse = false;

		// ���_�A�C���f�b�N�X�A�|���S���������Z
		g_MaxVtxMeshWall += g_MeshWall[nCntMeshWall].MaxVtx;
		g_MaxIdxMeshWall += g_MeshWall[nCntMeshWall].MaxIdx;
		g_MaxPolygonMeshWall += g_MeshWall[nCntMeshWall].MaxPolygon;
	}

	// ���_���̍쐬
	MakeVertexMeshWall(pDevice);
}

//=========================================================================================================================
// �ǂ̏I������
//=========================================================================================================================
void UninitMeshWall(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//=========================================================================================================================
// �ǂ̍X�V����
//=========================================================================================================================
void UpdateMeshWall(void)
{

}

//=========================================================================================================================
// �ǂ̕`�揈��
//=========================================================================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	int nCntMeshWall, nNumVtx = 0, nNumIdx = 0;

	for (nCntMeshWall = 0; nCntMeshWall < g_MaxMeshWall; nCntMeshWall++)
	{
		if (g_MeshWall[nCntMeshWall].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshWall[nCntMeshWall].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_MeshWall[nCntMeshWall].rot.y,
				g_MeshWall[nCntMeshWall].rot.x,
				g_MeshWall[nCntMeshWall].rot.z
			);

			D3DXMatrixMultiply
			(
				&g_MeshWall[nCntMeshWall].mtxWorld,
				&g_MeshWall[nCntMeshWall].mtxWorld,
				&mtxRot
			);

			// �ʒu�𔽉f
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_MeshWall[nCntMeshWall].pos.x,
				g_MeshWall[nCntMeshWall].pos.y,
				g_MeshWall[nCntMeshWall].pos.z
			);

			D3DXMatrixMultiply
			(
				&g_MeshWall[nCntMeshWall].mtxWorld,
				&g_MeshWall[nCntMeshWall].mtxWorld,
				&mtxTrans
			);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntMeshWall].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource
			(
				0,
				g_pVtxBuffMeshWall,
				0,
				sizeof(VERTEX_3D)
			);

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���ݒ�
			if (g_MeshWall[nCntMeshWall].nTexNum == 1)
			{
				pDevice->SetTexture(0, NULL);
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureMeshWall);
			}

			// �ǂ̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, nNumIdx, g_MeshWall[nCntMeshWall].MaxIdx + nNumIdx, nNumIdx, g_MeshWall[nCntMeshWall].MaxPolygon);
		}

		nNumVtx += g_MeshWall[nCntMeshWall].MaxVtx;		// ���_�o�b�t�@�𒲐�
		nNumIdx += g_MeshWall[nCntMeshWall].MaxIdx;		// ���_�o�b�t�@�𒲐�
	}
}

//=========================================================================================================================
// �ǂ̐ݒ菈��
//=========================================================================================================================
void SetMeshWall(int nTexNum, D3DXCOLOR col)
{
	int nCntMeshWall, nNumVtx = 0, nNumIdx = 0;
	int nCount_x, nCount_y, nCount_mesh = 0;
	
	int ip = 0;
	float fx = 0.0f, fy = 0.0f;

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshWall->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	WORD *pIdx;			// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < g_MaxMeshWall; nCntMeshWall++)
	{// �|���S�����J�E���g
		if (g_MeshWall[nCntMeshWall].bUse == false)
		{// �g�p���Ă��Ȃ��ꍇ
			g_MeshWall[nCntMeshWall].nTexNum = nTexNum;
			g_MeshWall[nCntMeshWall].bUse = true;				// �g�p����

			// ���_���̐ݒ�
			for (nCount_y = 0; nCount_y < g_MeshWall[nCntMeshWall].num.y + 1; nCount_y++)
			{// y���J�E���g
				for (nCount_x = 0; nCount_x < g_MeshWall[nCntMeshWall].num.x + 1; nCount_x++)
				{// x���J�E���g

					// pVtx[(���b�V���J�E���^ * ���_��) + (y�J�E���^ * (x�̐ݒu�� + 1)) + (x�J�E���^)]
					// ��F	(		nCntxxx	  *	  4	  )	+ (	  0		 * (    2  	  + 1)) + (    0	)
					// .pos.x = -((x�̑傫�� / 2) * x�̐ݒu��) + (x�̑傫�� * x�J�E���^)
					//		y =  ((y�̑傫�� / 2) * y�̐ݒu��) - (y�̑傫�� * y�J�E���^)
					// ���S�ɕ`�悷�邽�߂Ɋ��Q���s���B
					// �ł����Ɖ��̒l�����߁A���Z���Z�ɂ�葼���_�����߂�

					pVtx[(nNumVtx) + (nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1))) + (nCount_x)].pos = D3DXVECTOR3(
						-((g_MeshWall[nCntMeshWall].fRadius.x / 2) * g_MeshWall[nCntMeshWall].num.x) + (g_MeshWall[nCntMeshWall].fRadius.x * nCount_x),
						((g_MeshWall[nCntMeshWall].fRadius.y) * g_MeshWall[nCntMeshWall].num.y) - (g_MeshWall[nCntMeshWall].fRadius.y * (nCount_y)), 0.0f);

					ip = (nNumVtx) + (nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1))) + (nCount_x);
	
					fx = -((g_MeshWall[nCntMeshWall].fRadius.x / 2) * g_MeshWall[nCntMeshWall].num.x) + (g_MeshWall[nCntMeshWall].fRadius.x * nCount_x);
					fy = ((g_MeshWall[nCntMeshWall].fRadius.y) * g_MeshWall[nCntMeshWall].num.y) - (g_MeshWall[nCntMeshWall].fRadius.y * (nCount_y));

					// pVtx[(���b�V���J�E���^ * ���_��) + (y�J�E���^ * (x�̐ݒu�� + 1)) + (x�J�E���^)]
					// ��F	(		nCntxxx	  *	  4	  )	+ (	  0		 * (    2  	  + 1)) + (    0	)
					// .pos.x = -((x�̑傫�� / 2) * x�̐ݒu��) + (x�̑傫�� * x�J�E���^)
					//		y =  ((y�̑傫�� / 2) * y�̐ݒu��) - (y�̑傫�� * y�J�E���^)
					// ���S�ɕ`�悷�邽�߂Ɋ��Q���s���B
					// �ł����Ɖ��̒l�����߁A���Z���Z�ɂ�葼���_�����߂�

					// �܂��Ȃ����ĂȂ���
					pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1))) + (nCount_x)].col = col;

					pVtx[(nNumVtx)+(nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1))) + (nCount_x)].tex =
						D3DXVECTOR2(MESHWALL_TEXTURE_UV_U * (nCount_x % ((int)g_MeshWall[nCntMeshWall].num.x + 1)), MESHWALL_TEXTURE_UV_V * (nCount_y));
				}
			}

			// �C���f�b�N�X�̐ݒ�
			for (nCount_y = 0; nCount_y < g_MeshWall[nCntMeshWall].num.y; nCount_y++)
			{
				for (nCount_x = 0; nCount_x < g_MeshWall[nCntMeshWall].num.x + 1; nCount_x++)
				{
					// pIdx[(���b�V���J�E���^ * ���_��) + (y�J�E���^ * (x�̐ݒu�� + 1)) + (x�J�E���^ * 2) + �ǂɎg�p�������_��]
					// ��F	(		nCntxxx	  *	  4	  )	+ (	  0		 * (    2  	  + 1)) + (    0	 * 2) + 0
					//	=	((y�J�E���^ + 1) * (x�̐ݒu�� + 1)) + (x�J�E���^)
					// pIdx��	x�J�E���^ * 2	��2���_���ݒ肷�邽�ߍs���i2���_�ڂ�	+ 1	�ōs��)
					// y�J�E���^ + 1	�ɂ�艺�����߁A����	y�J�E���^�@�݂̂ŏ�����߂�	

					pIdx[(nNumIdx) + (nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh] =
						(WORD)((nNumVtx) + ((nCount_y + 1) * (g_MeshWall[nCntMeshWall].num.x + 1)) + nCount_x);
					
					pIdx[(nNumIdx) + (nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1] =
						(WORD)((nNumVtx)+((nCount_y) * (g_MeshWall[nCntMeshWall].num.x + 1)) + nCount_x);
					
					ip = (nNumIdx) + (nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh;
					fx = ((nNumVtx) + ((nCount_y + 1) * (g_MeshWall[nCntMeshWall].num.x + 1)) + nCount_x);
					fy = ((nNumVtx) + ((nCount_y) * (g_MeshWall[nCntMeshWall].num.x + 1)) + nCount_x);


					if (g_MeshWall[nCntMeshWall].num.y > 1 && nCount_y != g_MeshWall[nCntMeshWall].num.y - 1 && nCount_x == g_MeshWall[nCntMeshWall].num.x)
					{
						pIdx[(nNumIdx) + (nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1 + 1] =
							(WORD)((nNumVtx) + ((nCount_y) * (g_MeshWall[nCntMeshWall].num.x + 1)) + nCount_x);
					
						pIdx[(nNumIdx) + (nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1 + 2] =
							(WORD)((nNumVtx) + ((nCount_y + 2) * (g_MeshWall[nCntMeshWall].num.x + 1)));

						ip = (nNumIdx) + (nCount_y * (((int)g_MeshWall[nCntMeshWall].num.x + 1) * 2)) + (nCount_x * 2) + nCount_mesh + 1 + 1;
						fx = ((nNumVtx) + ((nCount_y) * (g_MeshWall[nCntMeshWall].num.x + 1)) + nCount_x);
						fy = ((nNumVtx) + ((nCount_y + 2) * (g_MeshWall[nCntMeshWall].num.x + 1)));

						nCount_mesh += 2;		// �ǂ̒��_���Z
					}
				}
			}

			break;
		}
		nCount_mesh = 0;
		nNumVtx += g_MeshWall[nCntMeshWall].MaxVtx;		// ���_�o�b�t�@�𒲐�
		nNumIdx += g_MeshWall[nCntMeshWall].MaxIdx;
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshWall->Unlock();

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshWall->Unlock();
}

//=========================================================================================================================
// �ǂ̏Փˏ���
//=========================================================================================================================
bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pRot, D3DXVECTOR3 fRadius)
{
	int nCntMeshWall, nCount = 0;
	bool bLand = false;
	float vecA_x, vecA_z, vecC_x, vecC_z;
	float fx1, fx2, fz1, fz2;
	D3DXVECTOR3 Radius;

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < g_MaxMeshWall; nCntMeshWall++)
	{
		if (g_MeshWall[nCntMeshWall].bUse == true)
		{// �g�p����Ă���
			fx1 = (g_MeshWall[nCntMeshWall].pos.x + sinf(g_MeshWall[nCntMeshWall].rot.y) + pVtx[nCount + 1].pos.x);
			fx2 = (g_MeshWall[nCntMeshWall].pos.x + sinf(g_MeshWall[nCntMeshWall].rot.y) + pVtx[nCount].pos.x);
			fz1 = (g_MeshWall[nCntMeshWall].pos.z + cosf(g_MeshWall[nCntMeshWall].rot.y) + pVtx[nCount + 1].pos.z);
			fz2 = (g_MeshWall[nCntMeshWall].pos.z + cosf(g_MeshWall[nCntMeshWall].rot.y) + pVtx[nCount].pos.z);

			Radius = g_MeshWall[nCntMeshWall].fRadius;
			Radius.x = g_MeshWall[nCntMeshWall].pos.x + sinf(g_MeshWall[nCntMeshWall].rot.y) * pVtx[nCount + 1].pos.x;
			Radius.z = g_MeshWall[nCntMeshWall].pos.x + cosf(g_MeshWall[nCntMeshWall].rot.y) * pVtx[nCount + 1].pos.z;

			vecA_x = (g_MeshWall[nCntMeshWall].pos.x + Radius.x) - (g_MeshWall[nCntMeshWall].pos.x + Radius.x);
			vecA_z = (g_MeshWall[nCntMeshWall].pos.z + Radius.z) - (g_MeshWall[nCntMeshWall].pos.z + Radius.z);
			vecC_x = (pPos->x) - (g_MeshWall[nCntMeshWall].pos.x + Radius.x);
			vecC_z = (pPos->z) - (g_MeshWall[nCntMeshWall].pos.z + Radius.z);

			if (((vecA_z * vecC_x) - (vecA_x * vecC_z)) < 0)
			{
				bLand = true;
			}
			
			nCount += 4;
			

			/*if (pPos->x + fRadius.x > g_MeshWall[nCntMeshWall].pos.x - g_MeshWall[nCntMeshWall].fRadius.x && pPos->x - fRadius.x < g_MeshWall[nCntMeshWall].pos.x + g_MeshWall[nCntMeshWall].fRadius.x)
			{// X�͈͊m�F
				if (pPosOld->z + fRadius.z >= g_MeshWall[nCntMeshWall].pos.z && g_MeshWall[nCntMeshWall].pos.z > pPos->z + fRadius.z)
				{// Z��ꔻ��
					pPos->z = g_MeshWall[nCntMeshWall].pos.z - fRadius.z;
					//pMove->x = 0.0f;
					//pMove->z = 0.0f;
				}
				else if (pPosOld->z + fRadius.z <= g_MeshWall[nCntMeshWall].pos.z && g_MeshWall[nCntMeshWall].pos.z < pPos->z + fRadius.z)
				{// Z���ꔻ��
					pPos->z = g_MeshWall[nCntMeshWall].pos.z - fRadius.z;
					//pMove->x = 0.0f;
					//pMove->z = 0.0f;
				}
			}

			if (pPos->z + fRadius.z > g_MeshWall[nCntMeshWall].pos.z && pPos->z + fRadius.z < g_MeshWall[nCntMeshWall].pos.z)
			{// Z�͈͊m�F
				if (pPosOld->x + fRadius.x >= g_MeshWall[nCntMeshWall].pos.x && g_MeshWall[nCntMeshWall].pos.x > pPos->x + fRadius.x)
				{// X�E�Ӕ���
					pPos->x = g_MeshWall[nCntMeshWall].pos.x - fRadius.x;
					//pMove->x = 0.0f;
					//pMove->z = 0.0f;
				}
				else if (pPosOld->x + fRadius.x <= g_MeshWall[nCntMeshWall].pos.x && g_MeshWall[nCntMeshWall].pos.x < pPos->x + fRadius.x)
				{// X���Ӕ���
					pPos->x = g_MeshWall[nCntMeshWall].pos.x - fRadius.x;
					//pMove->x = 0.0f;
					//pMove->z = 0.0f;
				}
			}*/
		}
	}
	
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	return bLand;
}

//=========================================================================================================================
// �ǂ̔j������
//=========================================================================================================================
void DeleteMeshWall(void)
{
	int nCntMeshWall;

	for (nCntMeshWall = 0; nCntMeshWall < g_MaxMeshWall; nCntMeshWall++)
	{
		if (g_MeshWall[nCntMeshWall].bUse == true)
		{// �g�p����Ă���
			g_MeshWall[nCntMeshWall].bUse = false;
		}
	}
}

//=========================================================================================================================
// ���_���̍쐬
//=========================================================================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntMeshWall;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHWALL_TEXTURE_NAME1, &g_pTextureMeshWall);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * g_MaxVtxMeshWall,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL
	);

	// �C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * g_MaxIdxMeshWall,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL
	);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < g_MaxVtxMeshWall; nCntMeshWall++)
	{
		// ���_���̐ݒ�
		pVtx[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �@���̐ݒ�
		pVtx[nCntMeshWall].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// ���_�J���[�̐ݒ�
		pVtx[nCntMeshWall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`���̐ݒ�
		pVtx[nCntMeshWall].tex = D3DXVECTOR2(0.0f, 0.0f);	
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	WORD *pIdx;			// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshWall = 0; nCntMeshWall < g_MaxIdxMeshWall; nCntMeshWall++)
	{
		// �C���f�b�N�X�̐ݒ�
		pIdx[nCntMeshWall] = nCntMeshWall;
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshWall->Unlock();
}

