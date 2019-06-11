//=============================================================================
//
// ���f������ [model.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "score.h"
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define  MAX_TYPE           (30)                // ���f���̎�ނ̔z��̈�̍ő吔
#define  MAX_MODEL          (300)               // ���f���̔z��̈�̍ő吔
#define  NUM_MODEL          "NUM_MODEL"
#define  MODEL_FILENAME     "MODEL_FILENAME"
#define  MODELSET           "MODELSET"
#define  END_MODELSET       "END_MODELSET"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH   g_pMeshModel[MAX_TYPE] = {};          // ���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel[MAX_TYPE] = {};       // �}�e���A�����ւ̃|�C���^
DWORD        g_nNumMatModel[MAX_TYPE] = {};        // �}�e���A�����̐�
LPDIRECT3DTEXTURE9* g_pTexturModel[MAX_TYPE] = {}; // �e�N�X�`���̃|�C���^
Model  g_model[MAX_TYPE][MAX_MODEL];               // ���f�����
int   g_NumModelType = 0;                          // ���f���̎�ނ̑���
int   g_NumModel[MAX_TYPE] = {};                   // ���f���̔z�u��

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	FILE *pFile;         // �e�L�X�g�t�@�C���ւ̃|�C���^
	char str0[128];      // ����Ȃ�����
	char xFileName[64];  // x�t�@�C���̖��O
	D3DXVECTOR3 pos;     // ���f���̍��W
	D3DXVECTOR3 rot;     // ���f���̌���
	int nCntType = 0;    // ���f���̎�ނ𐔂���
	for (nCntType = 0; nCntType < MAX_TYPE; nCntType++)
	{
		g_NumModel[nCntType] = 0;
	}
	nCntType = 0;
	g_NumModelType = 0;

	// �e�L�X�g�t�@�C�����J��
	pFile = fopen("data/TEXT/model.txt", "r");

	if (pFile != NULL)
	{// �e�L�X�g�t�@�C��������
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// �e�L�X�g�t�@�C���̖��[�܂ŕ���������s���󔒂�����܂œǂݎ��
			if (strcmp(&str0[0], NUM_MODEL) == 0)
			{// ���f���̑�����ǂݎ��ꏊ��������
				// ���f���̑�����ǂݎ��
				fscanf(pFile, "%s %d", &str0[0], &g_NumModelType);
			}
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// x�t�@�C���̊g���q��������Ă�����
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// ���f���̃t�@�C������ǂݎ������
					// x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatModel[nCntType],
						NULL,
						&g_nNumMatModel[nCntType],
						&g_pMeshModel[nCntType]);

					// �}�e���A����񂩂�e�N�X�`���������o��
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCntType]->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatModel[nCntType]];
					g_pTexturModel[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatModel[nCntType]];

					for (DWORD nCntMat = 0; nCntMat < g_nNumMatModel[nCntType]; nCntMat++)
					{// ���_���̐������J��Ԃ�
					 // �}�e���A������ǂݍ���
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// ����������������
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// �e�N�X�`������������
						g_pTexturModel[nCntType][nCntMat] = NULL;

						// �e�N�X�`���̏���ǂݍ���
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// �e�N�X�`���̃t�@�C����������
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_pTexturModel[nCntType][nCntMat]);
						}

					}
				}
				nCntType++;  // ��ނ��ς��̂Ői�߂Ă���
			}
			if (strcmp(&str0[0], MODELSET) == 0)
			{// ���f����񂪏�����Ă���Ƃ��낪����
				int nCntSet = 0;  // ����ݒ肵����
				fscanf(pFile, "%s %s %d", &str0[0], &str0[0], &nCntType);
				while (strcmp(&str0[0], END_MODELSET) != 0)
				{// ���f���̐ݒ肪�I���܂ŌJ��Ԃ�
					if (nCntSet == MODELSET_POS)
					{// �P��ڂ�������
						if (fscanf(pFile, "%s %s %f %f %f", &str0[0], &str0[0],&pos.x, &pos.y, &pos.z) == 5)
						{// ���W����ǂݎ������
							g_model[nCntType][g_NumModel[nCntType]].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);  // �ʒu��ݒ�
						}
					}
					else if (nCntSet == MODELSET_ROT)
					{// �Q��ڂ�������
						if (fscanf(pFile, "%s %f %f %f", &str0[0], &rot.x, &rot.y, &rot.z) == 4)
						{// ��������ǂݎ������
							g_model[nCntType][g_NumModel[nCntType]].rot = D3DXVECTOR3(rot.x, rot.y, rot.z);  // ������ݒ�
						}
					}
					fscanf(pFile, "%s", &str0[0]);
					nCntSet++;                     // �Z�b�g�����񐔂𑝂₷
				}
				g_NumModel[nCntType]++;  // ���f���̔z�u���𐔂���
			}
		}
	}

	// �t�@�C������đ��̃v���O�������炢�����悤�ɂ���
	fclose(pFile);

	for (int nCntType = 0; nCntType < g_NumModelType; nCntType++)
	{// ���f���̎�ނ̐������J��Ԃ�
		for (int nCntModel = 0; nCntModel < g_NumModel[nCntType]; nCntModel++)
		{// ���f���̐������J��Ԃ�
			if (nCntModel == 0)
			{// 1��ڂ�������
				int nNumVtx;	 // ���_��
				DWORD sizeFVF;	 // ���_�t�H�[�}�b�g�̃T�C�Y
				BYTE *pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

				// �ŏ��l�̐ݒ�
				g_model[nCntType][nCntModel].vtxMinObstacle = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_model[nCntType][nCntModel].vtxMaxObstacle = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// ���_�����擾
				nNumVtx = g_pMeshModel[nCntType]->GetNumVertices();

				// ���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel[nCntType]->GetFVF());

				// ���_�o�b�t�@�����b�N
				g_pMeshModel[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// ���f���̒��_�������J��Ԃ�
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

					if (vtx.x < g_model[nCntType][nCntModel].vtxMinObstacle.x)
					{// X���W����菬����
						g_model[nCntType][nCntModel].vtxMinObstacle.x = vtx.x;
					}
					if (vtx.y < g_model[nCntType][nCntModel].vtxMinObstacle.y)
					{// Y���W����菬����
						g_model[nCntType][nCntModel].vtxMinObstacle.y = vtx.y;
					}
					if (vtx.z < g_model[nCntType][nCntModel].vtxMinObstacle.z)
					{// Z���W����菬����
						g_model[nCntType][nCntModel].vtxMinObstacle.z = vtx.z;
					}

					if (vtx.x > g_model[nCntType][nCntModel].vtxMaxObstacle.x)
					{// X���W�����傫��
						g_model[nCntType][nCntModel].vtxMaxObstacle.x = vtx.x;
					}
					if (vtx.y > g_model[nCntType][nCntModel].vtxMaxObstacle.y)
					{// Y���W�����傫��
						g_model[nCntType][nCntModel].vtxMaxObstacle.y = vtx.y;
					}
					if (vtx.z > g_model[nCntType][nCntModel].vtxMaxObstacle.z)
					{// Z���W�����傫��
						g_model[nCntType][nCntModel].vtxMaxObstacle.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
				}

				// ���_�o�b�t�@���A�����b�N
				g_pMeshModel[nCntType]->UnlockVertexBuffer();
			}
			else
			{// ����ȍ~
				g_model[nCntType][nCntModel].vtxMaxObstacle = g_model[nCntType][nCntModel - 1].vtxMaxObstacle;
				g_model[nCntType][nCntModel].vtxMinObstacle = g_model[nCntType][nCntModel - 1].vtxMinObstacle;
			}
			g_model[nCntType][nCntModel].Vertex[0].pos = D3DXVECTOR3(g_model[nCntType][nCntModel].vtxMinObstacle.x - 8.0f, 0.0f, g_model[nCntType][nCntModel].vtxMaxObstacle.z + 8.0f);
			g_model[nCntType][nCntModel].Vertex[1].pos = D3DXVECTOR3(g_model[nCntType][nCntModel].vtxMaxObstacle.x + 8.0f, 0.0f, g_model[nCntType][nCntModel].vtxMaxObstacle.z + 8.0f);
			g_model[nCntType][nCntModel].Vertex[2].pos = D3DXVECTOR3(g_model[nCntType][nCntModel].vtxMaxObstacle.x + 8.0f, 0.0f, g_model[nCntType][nCntModel].vtxMinObstacle.z - 8.0f);
			g_model[nCntType][nCntModel].Vertex[3].pos = D3DXVECTOR3(g_model[nCntType][nCntModel].vtxMinObstacle.x - 8.0f, 0.0f, g_model[nCntType][nCntModel].vtxMinObstacle.z - 8.0f);
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	for (int nCntType = 0; nCntType < MAX_TYPE; nCntType++)
	{// ���f���̎�ނ̐������J��Ԃ�
			// ���b�V���̔j��
		if (g_pMeshModel[nCntType] != NULL)
		{
			g_pMeshModel[nCntType]->Release();
			g_pMeshModel[nCntType] = NULL;
		}

		// �}�e���A���̔j��
		if (g_pBuffMatModel[nCntType] != NULL)
		{
			g_pBuffMatModel[nCntType]->Release();
			g_pBuffMatModel[nCntType] = NULL;
		}

		// �e�N�X�`���̔j��
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatModel[nCntType]; nCntMat++)
		{
			if (g_pTexturModel[nCntType][nCntMat] != NULL)
			{
				g_pTexturModel[nCntType][nCntMat]->Release();
				g_pTexturModel[nCntType][nCntMat] = NULL;
			}
		}
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;                // �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;                        // ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;                         // �}�e���A���f�[�^�ւ̃|�C���^
	for (int nCntType = 0; nCntType < g_NumModelType; nCntType++)
	{// ���f���̎�ނ̐������J��Ԃ�
		for (int nCntModel = 0; nCntModel < g_NumModel[nCntType]; nCntModel++)
		{// ���f���̐������J��Ԃ�
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_model[nCntType][nCntModel].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model[nCntType][nCntModel].rot.y, g_model[nCntType][nCntModel].rot.x, g_model[nCntType][nCntModel].rot.z);
			D3DXMatrixMultiply(&g_model[nCntType][nCntModel].mtxWorld, &g_model[nCntType][nCntModel].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_model[nCntType][nCntModel].pos.x, g_model[nCntType][nCntModel].pos.y, g_model[nCntType][nCntModel].pos.z);
			D3DXMatrixMultiply(&g_model[nCntType][nCntModel].mtxWorld, &g_model[nCntType][nCntModel].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_model[nCntType][nCntModel].mtxWorld);

			for (int nCntVer = 0; nCntVer < 4; nCntVer++)
			{// ���_���̐������J��Ԃ�
			 // ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_model[nCntType][nCntModel].Vertex[nCntVer].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model[nCntType][nCntModel].Vertex[nCntVer].rot.y, g_model[nCntType][nCntModel].Vertex[nCntVer].rot.x, g_model[nCntType][nCntModel].Vertex[nCntVer].rot.z);
				D3DXMatrixMultiply(&g_model[nCntType][nCntModel].Vertex[nCntVer].mtxWorld, &g_model[nCntType][nCntModel].Vertex[nCntVer].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_model[nCntType][nCntModel].Vertex[nCntVer].pos.x, g_model[nCntType][nCntModel].Vertex[nCntVer].pos.y, g_model[nCntType][nCntModel].Vertex[nCntVer].pos.z);
				D3DXMatrixMultiply(&g_model[nCntType][nCntModel].Vertex[nCntVer].mtxWorld, &g_model[nCntType][nCntModel].Vertex[nCntVer].mtxWorld, &mtxTrans);

				// �e�̃}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_model[nCntType][nCntModel].Vertex[nCntVer].mtxWorld, &g_model[nCntType][nCntModel].Vertex[nCntVer].mtxWorld, &g_model[nCntType][nCntModel].mtxWorld);
			}

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCntType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[nCntType]; nCntMat++)
			{// �ݒ肳��Ă����}�e���A���̐������J��Ԃ�
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturModel[nCntType][nCntMat]);

				// ���f��(�p�[�c)�̕`��
				g_pMeshModel[nCntType]->DrawSubset(nCntMat);
			}

			// �ۑ����Ă����}�e���A���ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=============================================================================
// ���f���̓����蔻��
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
{
	bool bLand = false;  // ��������ǂ���

	// �O�ς̓����蔻��p
	D3DXVECTOR3 vecA, vecC;
	D3DXVECTOR3 aVerPos[4];
	int nCntVec = 0;

	for (int nCntType = 0; nCntType < g_NumModelType; nCntType++)
	{// ���f���̎�ނ̐������J��Ԃ�
		for (int nCntModel = 0; nCntModel < g_NumModel[nCntType]; nCntModel++)
		{// ���f���̐������J��Ԃ�
			nCntVec = 0;
			// ���̃R�[�X�̒��_���W���擾
			aVerPos[0] = D3DXVECTOR3(g_model[nCntType][nCntModel].Vertex[0].mtxWorld._41, g_model[nCntType][nCntModel].Vertex[0].mtxWorld._42, g_model[nCntType][nCntModel].Vertex[0].mtxWorld._43);
			aVerPos[1] = D3DXVECTOR3(g_model[nCntType][nCntModel].Vertex[1].mtxWorld._41, g_model[nCntType][nCntModel].Vertex[1].mtxWorld._42, g_model[nCntType][nCntModel].Vertex[1].mtxWorld._43);
			aVerPos[2] = D3DXVECTOR3(g_model[nCntType][nCntModel].Vertex[2].mtxWorld._41, g_model[nCntType][nCntModel].Vertex[2].mtxWorld._42, g_model[nCntType][nCntModel].Vertex[2].mtxWorld._43);
			aVerPos[3] = D3DXVECTOR3(g_model[nCntType][nCntModel].Vertex[3].mtxWorld._41, g_model[nCntType][nCntModel].Vertex[3].mtxWorld._42, g_model[nCntType][nCntModel].Vertex[3].mtxWorld._43);

			for (int nCntVer = 0; nCntVer < 4; nCntVer++)
			{// ���_���̐������J��Ԃ�
				vecC = *pPos - aVerPos[nCntVer];
				vecA = aVerPos[(nCntVer + 1) % 4] - aVerPos[nCntVer];

				if ((vecA.z * vecC.x) - (vecA.x * vecC.z) < 0)
				{// ���̃x�N�g���̊O���ɂ���
					nCntVec++;
				}
			}

			if (pPos->y <= g_model[nCntType][nCntModel].pos.y + g_model[nCntType][nCntModel].vtxMaxObstacle.y - 5.0f && pPos->y + radius.y >= g_model[nCntType][nCntModel].pos.y + g_model[nCntType][nCntModel].vtxMaxObstacle.y - 5.0f
				|| pPos->y + radius.y >= g_model[nCntType][nCntModel].pos.y + g_model[nCntType][nCntModel].vtxMinObstacle.y && pPos->y <= g_model[nCntType][nCntModel].pos.y + g_model[nCntType][nCntModel].vtxMinObstacle.y
				|| pPos->y + radius.y <= g_model[nCntType][nCntModel].pos.y + g_model[nCntType][nCntModel].vtxMaxObstacle.y - 5.0f && pPos->y >= g_model[nCntType][nCntModel].pos.y + g_model[nCntType][nCntModel].vtxMinObstacle.y)
			{// ��Q����Y���W�̒��ɂ���
				if (nCntVec == 0)
				{// ��x���x�N�g���̊O���ɂ��Ȃ�����
					pPos->x = pPosOld->x;
					pPos->z = pPosOld->z;
					pPos->x -= pMove->x * 0.001f;
					pPos->z -= pMove->z * 0.001f;
					pPos->x += g_model[nCntType][nCntModel].move.x;
					pPos->z += g_model[nCntType][nCntModel].move.z;
				}
			}
		}
	}

	return bLand;
}
//=============================================================================
// ���f���ƃV���b�^�[����ꂽ���̓����蔻��
//=============================================================================
void CollisionShutterModel(D3DXVECTOR3 pos, D3DXVECTOR3 radius)
{
	for (int nCntType = 0; nCntType < g_NumModelType; nCntType++)
	{// ���f���̎�ނ̐������J��Ԃ�
		for (int nCntModel = 0; nCntModel < g_NumModel[nCntType]; nCntModel++)
		{// ���f���̐������J��Ԃ�
			if (g_model[nCntType][nCntModel].pos.x + g_model[nCntType][nCntModel].vtxMaxObstacle.x >= pos.x - radius.x && g_model[nCntType][nCntModel].pos.x + g_model[nCntType][nCntModel].vtxMinObstacle.x <= pos.x + radius.x
				&& g_model[nCntType][nCntModel].pos.z + g_model[nCntType][nCntModel].vtxMaxObstacle.z >= pos.z - radius.z && g_model[nCntType][nCntModel].pos.z + g_model[nCntType][nCntModel].vtxMinObstacle.z <= pos.z + radius.z)
			{// �V���b�^�[�̘g�̒��ɂ���
				AddScore(10);
				for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
				{
					SetParticle(D3DXVECTOR3(g_model[nCntType][nCntModel].pos.x, g_model[nCntType][nCntModel].pos.y + 20.0f, g_model[nCntType][nCntModel].pos.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f, 1.4f, cosf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f), 60.0f, 180);
				}
			}
		}
	}
}