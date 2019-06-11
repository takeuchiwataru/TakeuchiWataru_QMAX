//=============================================================================
//
// ���f������ [model.cpp]
// Author : �|���j
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "game.h"
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME		"data/MODEL/benti000.x"		// ���f����
#define MODEL_NAME0		"data/MODEL/benti001.x"		// ���f����
#define MODEL_NAME1		"data/MODEL/buranko.x"		// ���f����
#define MODEL_NAME2		"data/MODEL/slide.x"		// ���f����
#define MODEL_NAME3		"data/MODEL/taiya.x"		// ���f����
#define MODEL_NAME4		"data/MODEL/JG.x"			// ���f����
#define MODEL_NAME5		"data/MODEL/seesaw.x"		// ���f����
#define MODEL_NAME6		"data/MODEL/taiya002.x"		// ���f����
#define MAX_MODEL		(256)						// ���f���z�u�̍ő吔
#define MAX_MODEL_TYPE	(5)							// ���f����ނ̍ő吔
#define TEXTURE_NAME	"data/TEXTURE/mokume.png"	// �e�N�X�`����
//#define MAX_TEXTURE		(1)							// �ǂݍ��ރe�N�X�`����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshModel[MODELTYPE_MAX];							// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel[MODELTYPE_MAX];					// �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureModel = NULL;			// �e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatModel[MODELTYPE_MAX];						// �}�e���A�����̐�
MODEL g_aModel[MODELTYPE_MAX][MAX_MODEL];						// ���f���̏��
//VTXMODEL g_aModelVtx[MAX_MODEL_TYPE];							

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char cFN[MODELTYPE_MAX][256] = { MODEL_NAME ,MODEL_NAME0,MODEL_NAME1, MODEL_NAME2,MODEL_NAME3,MODEL_NAME4,MODEL_NAME5,MODEL_NAME6 };

	for (int nCntModelType = 0; nCntModelType < MODELTYPE_MAX; nCntModelType++)
	{// ���f���̎�ތJ��Ԃ�

	 // X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(cFN[nCntModelType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatModel[nCntModelType],
			NULL,
			&g_nNumMatModel[nCntModelType],
			&g_pMeshModel[nCntModelType]);

		////�e�N�X�`���̓ǂݍ���
		//D3DXCreateTextureFromFile(pDevice,
		//	TEXTURE_NAME,
		//	&g_pTextureModel[0]);

		int nNumVtex;					// ���_��
		DWORD sizeFvF;					// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

		// ���f��������
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// ���f���̐��J��Ԃ�
			g_aModel[nCntModelType][nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModel[nCntModelType][nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModel[nCntModelType][nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModel[nCntModelType][nCntModel].VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
			g_aModel[nCntModelType][nCntModel].VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
			g_aModel[nCntModelType][nCntModel].nType = MODELTYPE_BENCH;
			g_aModel[nCntModelType][nCntModel].bUse = false;

			// ���_�����擾
			nNumVtex = g_pMeshModel[nCntModelType]->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nCntModelType]->GetFVF());

			// ���_�o�b�t�@�����b�N
			g_pMeshModel[nCntModelType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				if (g_aModel[nCntModelType][nCntModel].VtxMinModel.x >= vtx.x)
				{
					g_aModel[nCntModelType][nCntModel].VtxMinModel.x = vtx.x;
				}
				if (g_aModel[nCntModelType][nCntModel].VtxMinModel.y >= vtx.y)
				{
					g_aModel[nCntModelType][nCntModel].VtxMinModel.y = vtx.y;
				}
				if (g_aModel[nCntModelType][nCntModel].VtxMinModel.z >= vtx.z)
				{
					g_aModel[nCntModelType][nCntModel].VtxMinModel.z = vtx.z;
				}

				if (g_aModel[nCntModelType][nCntModel].VtxMaxModel.x <= vtx.x)
				{
					g_aModel[nCntModelType][nCntModel].VtxMaxModel.x = vtx.x;
				}
				if (g_aModel[nCntModelType][nCntModel].VtxMaxModel.y <= vtx.y)
				{
					g_aModel[nCntModelType][nCntModel].VtxMaxModel.y = vtx.y;
				}
				if (g_aModel[nCntModelType][nCntModel].VtxMaxModel.z <= vtx.z)
				{
					g_aModel[nCntModelType][nCntModel].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff += sizeFvF;
			}
			// ���_�o�b�t�@���A�����b�N
			g_pMeshModel[nCntModelType]->UnlockVertexBuffer();
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	for (int nCntModelType = 0; nCntModelType < MODELTYPE_MAX; nCntModelType++)
	{
	 // ���b�V���̊J��
		if (g_pMeshModel[nCntModelType] != NULL)
		{
			g_pMeshModel[nCntModelType]->Release();
			g_pMeshModel[nCntModelType] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatModel[nCntModelType] != NULL)
		{
			g_pBuffMatModel[nCntModelType]->Release();
			g_pBuffMatModel[nCntModelType] = NULL;
		}
	}

	// �e�N�X�`���̔j��
	if (g_pTextureModel != NULL)
	{
		g_pTextureModel->Release();
		g_pTextureModel = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntModelType = 0; nCntModelType < MODELTYPE_MAX; nCntModelType++)
	{// ���f���̎�ތJ��Ԃ�
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// ���f���̐��J��Ԃ�
			if (g_aModel[nCntModelType][nCntModel].bUse == true)	
			{// ���f�����g�p����Ă���

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aModel[nCntModelType][nCntModel].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModelType][nCntModel].rot.y, g_aModel[nCntModelType][nCntModel].rot.x, g_aModel[nCntModelType][nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aModel[nCntModelType][nCntModel].mtxWorld, &g_aModel[nCntModelType][nCntModel].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModelType][nCntModel].pos.x, g_aModel[nCntModelType][nCntModel].pos.y, g_aModel[nCntModelType][nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aModel[nCntModelType][nCntModel].mtxWorld, &g_aModel[nCntModelType][nCntModel].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModelType][nCntModel].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModelType][nCntModel].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[g_aModel[nCntModelType][nCntModel].nType]; nCntMat++)
				{// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`��
					pDevice->SetTexture(0, g_pTextureModel);

					// ���f��(�p�[�c)�̕`��
					g_pMeshModel[g_aModel[nCntModelType][nCntModel].nType]->DrawSubset(nCntMat);

				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// ���f���̐ݒ�
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nType][nCntModel].bUse == false)
		{
			g_aModel[nType][nCntModel].pos = pos;
			g_aModel[nType][nCntModel].rot = D3DXVECTOR3(0, 0, 0);
			g_aModel[nType][nCntModel].nType = nType;
			g_aModel[nType][nCntModel].bUse = true;
			break;
		}
	}
}

//=============================================================================
// ���f���Ƃ̓����蔻�菈��
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	bool bHit = false;		// �����������ǂ���

	for (int nCntModelType = 0; nCntModelType < MODELTYPE_MAX; nCntModelType++)
	{// ���f���̎�ތJ��Ԃ�
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// ���f���̐��J��Ԃ�
			if (g_aModel[nCntModelType][nCntModel].bUse == true)
			{// ���f�����g���Ă���

				if (pPos->x >= g_aModel[nCntModelType][nCntModel].pos.x + g_aModel[nCntModelType][nCntModel].VtxMinModel.x &&
					pPos->x <= g_aModel[nCntModelType][nCntModel].pos.x + g_aModel[nCntModelType][nCntModel].VtxMaxModel.x)
				{// Z�ʂ̔���
					if (pPosold->z <= g_aModel[nCntModelType][nCntModel].pos.z + g_aModel[nCntModelType][nCntModel].VtxMinModel.z &&
						pPos->z >= g_aModel[nCntModelType][nCntModel].pos.z + g_aModel[nCntModelType][nCntModel].VtxMinModel.z)
					{// ��O�̔���
						pPos->z = pPosold->z;
					}
					else if (pPosold->z >= g_aModel[nCntModelType][nCntModel].pos.z + (g_aModel[nCntModelType][nCntModel].VtxMaxModel.z) &&
						pPos->z <= g_aModel[nCntModelType][nCntModel].pos.z + (g_aModel[nCntModelType][nCntModel].VtxMaxModel.z))
					{// ���̔���
						pPos->z = pPosold->z;
					}
				}
				if (pPos->z >= g_aModel[nCntModelType][nCntModel].pos.z + g_aModel[nCntModelType][nCntModel].VtxMinModel.z &&
					pPos->z <= g_aModel[nCntModelType][nCntModel].pos.z + g_aModel[nCntModelType][nCntModel].VtxMaxModel.z)
				{// X�ʂ̔���
					if (pPosold->x >= g_aModel[nCntModelType][nCntModel].pos.x + g_aModel[nCntModelType][nCntModel].VtxMaxModel.x &&
						pPos->x <= g_aModel[nCntModelType][nCntModel].pos.x + g_aModel[nCntModelType][nCntModel].VtxMaxModel.x)
					{// �E�ʂ̔���
						pPos->x = pPosold->x;
					}
					else if (pPosold->x <= g_aModel[nCntModelType][nCntModel].pos.x + (g_aModel[nCntModelType][nCntModel].VtxMinModel.x) &&
						pPos->x >= g_aModel[nCntModelType][nCntModel].pos.x + (g_aModel[nCntModelType][nCntModel].VtxMinModel.x))
					{// ���ʂ̔���
						pPos->x = pPosold->x;
					}
				}
			}
		}
	}
	return bHit;
}

////=============================================================================
//// ���f���Ƃ̓����蔻�菈��
////=============================================================================
//bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin)
//{
//	bool bHit = false;		// �����������ǂ���
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		if (g_aModel[nCntModel].bUse == true)
//		{// ���f�����g���Ă���
//			if (pPos->y < g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y
//				&& pPos->y > g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y)
//			{// ���f����Y���̒�
//				if (pPos->z + VtxMin.z < g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z
//					&& pPos->z + VtxMax.z > g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z)
//				{// ���f����Z���̒�
//					if (pPos->x + VtxMin.x < g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x
//						&& pPos->x + VtxMax.x > g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x)
//					{// ���f����X���̒�
//						if (pPosold->x + 1 > g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x)
//						{// X���̓����蔻��
//							pPos->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x + VtxMax.x;
//							pPosold->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x + VtxMax.x;
//							//pPos->x = pPosold->x;
//						}
//						else if (pPosold->x - 1 < g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x)
//						{
//							pPos->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x + VtxMin.x;
//							pPosold->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x + VtxMin.x;
//							//pPos->x = pPosold->x;
//						}
//
//						else if (pPosold->z + 1 > g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z)
//						{// Z���̓����蔻��
//							pPos->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z + VtxMax.z;
//							pPosold->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z + VtxMax.z;
//							//pPos->z = pPosold->z;
//						}
//						else if (pPosold->z - 1 < g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z)
//						{
//							pPos->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z + VtxMin.z;
//							pPosold->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z + VtxMin.z;
//							//pPos->z = pPosold->z;
//						}
//
//						else if (pPosold->y >= g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y)
//						{// Y���̓����蔻��
//							pPos->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y;
//							pPosold->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y;
//							//pPos->y = pPosold->y;
//						}
//						else if (pPosold->y <= g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y)
//						{
//							pPos->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y;
//							pPosold->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y;
//							//pPos->y = pPosold->y;
//						}
//					}
//				}
//			}
//		}
//	}
//	return bHit;
//}


//=============================================================================
// ���f���̎擾
//=============================================================================
MODEL *GetModel(void)
{
	return &g_aModel[0][0];
}
