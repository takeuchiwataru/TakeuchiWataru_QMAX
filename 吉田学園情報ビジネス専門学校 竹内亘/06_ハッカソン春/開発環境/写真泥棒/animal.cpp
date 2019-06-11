//=============================================================================
//
// �����̏��� [Animal.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "animal.h"
#include "particle.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ANIMAL_NAME0	"data/MODEL/Animal/neko.x"			// �L�̃��f����
#define ANIMAL_NAME1	"data/MODEL/Animal/inu.x"			// ���̃��f����
#define ANIMAL_NAME2	"data/MODEL/Animal/karasu.x"        // �J���X�̃��f����
#define MAX_ANIMAL		(200)
#define MAX_ANIMAL_TYPE   (ANIMALTYPE_MAX)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH		    g_pMeshAnimal[MAX_ANIMAL_TYPE];	         // ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER	    g_pBuffMatAnimal[MAX_ANIMAL_TYPE];	     // �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9* g_pTextureAnimal[MAX_ANIMAL_TYPE];         // �e�N�X�`�����ւ̃|�C���^
DWORD			    g_nNumMatAnimal[MAX_ANIMAL_TYPE] = {};     // �}�e���A�����̐�
ANIMAL	            g_aAnimal[MAX_ANIMAL_TYPE][MAX_ANIMAL];  // �����̏��

//=============================================================================
// ����������
//=============================================================================
void InitAnimal(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char aXFileName[MAX_ANIMAL_TYPE][64] = { ANIMAL_NAME0,
		ANIMAL_NAME1,
		ANIMAL_NAME2,
	};

	for (int nCntType = 0; nCntType < MAX_ANIMAL_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
	 // X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatAnimal[nCntType],
			NULL,
			&g_nNumMatAnimal[nCntType],
			&g_pMeshAnimal[nCntType]);

		// �}�e���A����񂩂�e�N�X�`���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatAnimal[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatAnimal[nCntType]];
		g_pTextureAnimal[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatAnimal[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatAnimal[nCntType]; nCntMat++)
		{// ���_���̐������J��Ԃ� 
		 // �}�e���A������ǂݍ���
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// ����������������
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// �e�N�X�`������������
			g_pTextureAnimal[nCntType][nCntMat] = NULL;

			// �e�N�X�`���̏���ǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// �e�N�X�`���̃t�@�C����������
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureAnimal[nCntType][nCntMat]);
			}
		}

		for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
		{// ��Q���̐������J��Ԃ�
		 // ��Q�����̏�����
			g_aAnimal[nCntType][nCntAnimal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ���W��������
			g_aAnimal[nCntType][nCntAnimal].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ��������������
			g_aAnimal[nCntType][nCntAnimal].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړ��ʂ���������
			g_aAnimal[nCntType][nCntAnimal].Type = (ANIMALTYPE)nCntType;             // ��ނ���������
			g_aAnimal[nCntType][nCntAnimal].bUse = false;                            // �g�p���Ă��Ȃ���Ԃɂ���

			if (nCntAnimal == 0)
			{// 1��ڂ�������
				int nNumVtx;	 // ���_��
				DWORD sizeFVF;	 // ���_�t�H�[�}�b�g�̃T�C�Y
				BYTE *pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

								 // �ŏ��l�̐ݒ�
				g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// ���_�����擾
				nNumVtx = g_pMeshAnimal[nCntType]->GetNumVertices();

				// ���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshAnimal[nCntType]->GetFVF());

				// ���_�o�b�t�@�����b�N
				g_pMeshAnimal[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// ���f���̒��_�������J��Ԃ�
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

					if (vtx.x < g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.x)
					{// X���W����菬����
						g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.x = vtx.x;
					}
					if (vtx.y < g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.y)
					{// Y���W����菬����
						g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.y = vtx.y;
					}
					if (vtx.z < g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.z)
					{// Z���W����菬����
						g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.z = vtx.z;
					}

					if (vtx.x > g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.x)
					{// X���W�����傫��
						g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.x = vtx.x;
					}
					if (vtx.y > g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.y)
					{// Y���W�����傫��
						g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.y = vtx.y;
					}
					if (vtx.z > g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.z)
					{// Z���W�����傫��
						g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
				}

				// ���_�o�b�t�@���A�����b�N
				g_pMeshAnimal[nCntType]->UnlockVertexBuffer();
			}
			else
			{// ����ȍ~
				g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle = g_aAnimal[nCntType][nCntAnimal - 1].vtxMaxObstacle;
				g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle = g_aAnimal[nCntType][nCntAnimal - 1].vtxMinObstacle;
			}
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitAnimal(void)
{
	for (int nCntType = 0; nCntType < MAX_ANIMAL_TYPE; nCntType++)
	{
		// ���b�V���̊J��
		if (g_pMeshAnimal[nCntType] != NULL)
		{
			g_pMeshAnimal[nCntType]->Release();
			g_pMeshAnimal[nCntType] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatAnimal[nCntType] != NULL)
		{
			g_pBuffMatAnimal[nCntType]->Release();
			g_pBuffMatAnimal[nCntType] = NULL;
		}
		// �e�N�X�`���̊J��
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatAnimal[nCntType]; nCntMat++)
		{
			if (g_pTextureAnimal[nCntType][nCntMat] != NULL)
			{
				g_pTextureAnimal[nCntType][nCntMat]->Release();
				g_pTextureAnimal[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateAnimal(void)
{
	for (int nCntType = 0; nCntType < MAX_ANIMAL_TYPE; nCntType++)
	{// �����̎�ނ̐������J��Ԃ�
		for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
		{// �����̐������J��Ԃ�
			if (g_aAnimal[nCntType][nCntAnimal].bUse == true)
			{// �������g�p����Ă���
				// �ʒu���ړ�
				g_aAnimal[nCntType][nCntAnimal].pos += g_aAnimal[nCntType][nCntAnimal].move;

				// �J�E���^�[�����Z
				g_aAnimal[nCntType][nCntAnimal].nMoveCounter++;

				if (g_aAnimal[nCntType][nCntAnimal].nMoveCounter >= 120)
				{// �J�E���^�[��������x������
					g_aAnimal[nCntType][nCntAnimal].move *= -1;
					g_aAnimal[nCntType][nCntAnimal].DestRot *= -1;
					g_aAnimal[nCntType][nCntAnimal].nMoveCounter = 0;
				}

				// �p�x�̏C��
				g_aAnimal[nCntType][nCntAnimal].DiffRot.y = g_aAnimal[nCntType][nCntAnimal].DestRot.y - g_aAnimal[nCntType][nCntAnimal].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

				if (g_aAnimal[nCntType][nCntAnimal].DiffRot.y > D3DX_PI)
				{// ������D3DX_PI�𒴂���
					g_aAnimal[nCntType][nCntAnimal].DiffRot.y -= D3DX_PI * 2.0f;
				}
				if (g_aAnimal[nCntType][nCntAnimal].DiffRot.y < -D3DX_PI)
				{// ������-D3DX_PI�𒴂���
					g_aAnimal[nCntType][nCntAnimal].DiffRot.y += D3DX_PI * 2.0f;
				}

				g_aAnimal[nCntType][nCntAnimal].rot.y += g_aAnimal[nCntType][nCntAnimal].DiffRot.y * 0.1f;

				if (g_aAnimal[nCntType][nCntAnimal].rot.y > D3DX_PI)
				{// ���݂̌�����D3DX_PI�𒴂���
					g_aAnimal[nCntType][nCntAnimal].rot.y -= D3DX_PI * 2.0f;
				}
				if (g_aAnimal[nCntType][nCntAnimal].rot.y < -D3DX_PI)
				{// ���݂̌�����-D3DX_PI�𒴂���
					g_aAnimal[nCntType][nCntAnimal].rot.y += D3DX_PI * 2.0f;
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawAnimal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntType = 0; nCntType< MAX_ANIMAL_TYPE; nCntType++)
	{// �����̎�ނ̐������J��Ԃ�
		for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
		{// �����̐������J��Ԃ�
			if (g_aAnimal[nCntType][nCntAnimal].bUse == true)
			{// �������g�p����Ă���
			    // ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aAnimal[nCntType][nCntAnimal].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aAnimal[nCntType][nCntAnimal].rot.y, g_aAnimal[nCntType][nCntAnimal].rot.x, g_aAnimal[nCntType][nCntAnimal].rot.z);
				D3DXMatrixMultiply(&g_aAnimal[nCntType][nCntAnimal].mtxWorld, &g_aAnimal[nCntType][nCntAnimal].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aAnimal[nCntType][nCntAnimal].pos.x, g_aAnimal[nCntType][nCntAnimal].pos.y, g_aAnimal[nCntType][nCntAnimal].pos.z);
				D3DXMatrixMultiply(&g_aAnimal[nCntType][nCntAnimal].mtxWorld, &g_aAnimal[nCntType][nCntAnimal].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aAnimal[nCntType][nCntAnimal].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatAnimal[nCntType]->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_nNumMatAnimal[nCntType]; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureAnimal[nCntType][nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_pMeshAnimal[nCntType]->DrawSubset(nCntMat);
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetAnimal(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, ANIMALTYPE Type)
{
	for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
	{// ��Q���̐������J��Ԃ�
		if (g_aAnimal[Type][nCntAnimal].bUse == false)
		{// ��Q�����g�p����Ă��Ȃ�
		 // �ʒu�E�����̏����ݒ�
			g_aAnimal[Type][nCntAnimal].pos = pos;
			g_aAnimal[Type][nCntAnimal].rot = rot;
			g_aAnimal[Type][nCntAnimal].DestRot = rot;
			g_aAnimal[Type][nCntAnimal].move = move;
			//�@�e�̃Z�b�g
			//g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);

			g_aAnimal[Type][nCntAnimal].bUse = true;
			break;
		}
	}

}
//=============================================================================
// �����ƃV���b�^�[����ꂽ���̓����蔻��
//=============================================================================
void CollisionShutterAnimal(D3DXVECTOR3 pos, D3DXVECTOR3 radius)
{
	for (int nCntType = 0; nCntType < MAX_ANIMAL_TYPE; nCntType++)
	{// �����̎�ނ̐������J��Ԃ�
		for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
		{// �����̐������J��Ԃ�
			if (g_aAnimal[nCntType][nCntAnimal].bUse == true)
			{// �������g�p����Ă���
				if (g_aAnimal[nCntType][nCntAnimal].pos.x + g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.x >= pos.x - radius.x && g_aAnimal[nCntType][nCntAnimal].pos.x + g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.x <= pos.x + radius.x
					&& g_aAnimal[nCntType][nCntAnimal].pos.z + g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.z >= pos.z - radius.z && g_aAnimal[nCntType][nCntAnimal].pos.z + g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.z <= pos.z + radius.z)
				{// �V���b�^�[�̘g�̒��ɂ���
					if (g_aAnimal[nCntType][nCntAnimal].Type == ANIMALTYPE_CROW)
					{// �������Ă���̂��J���X��������
						AddScore(-10);
						for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
						{
							SetParticle(D3DXVECTOR3(g_aAnimal[nCntType][nCntAnimal].pos.x, g_aAnimal[nCntType][nCntAnimal].pos.y + 20.0f, g_aAnimal[nCntType][nCntAnimal].pos.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f, 1.4f, cosf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f), 60.0f, 180);
						}
					}
					else
					{// ����ȊO�̓�����������
						AddScore(10);
						for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
						{
							SetParticle(D3DXVECTOR3(g_aAnimal[nCntType][nCntAnimal].pos.x, g_aAnimal[nCntType][nCntAnimal].pos.y + 20.0f, g_aAnimal[nCntType][nCntAnimal].pos.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f, 1.4f, cosf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f), 60.0f, 180);
						}
					}
				}
			}
		}
	}
}