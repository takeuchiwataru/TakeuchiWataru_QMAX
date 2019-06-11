//=============================================================================
//
// �G2���� [enemy2.cpp]
// Author : �|���j
//
//=============================================================================
#include "enemy2.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "player2.h"
#include "game.h"
#include "explosion.h"
#include "meshWall.h"
#include "life.h"
#include "model.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME		"data/MODEL/karasu.x"			// ���f����karasu002.x
#define MODEL_NAME1		"data/MODEL/karasu002.x"		// ���f����
#define MAX_MODEL		(256)							// ���f���z�u�̍ő吔
#define MAX_MODEL_TYPE	(1)								// ���f����ނ̍ő吔

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshEnemy2[ENEMYTYPE2_MAX];							// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatEnemy2[ENEMYTYPE2_MAX];						// �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureEnemy2 = NULL;						// �e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatEnemy2[ENEMYTYPE2_MAX];								// �}�e���A�����̐�
ENEMY2 g_aEnemy2[ENEMYTYPE2_MAX][MAX_MODEL];						// ���f���̏��

//=============================================================================
// ����������
//=============================================================================
void InitEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char cFN[ENEMYTYPE2_MAX][256] = { MODEL_NAME };

	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{// �G�̎�ތJ��Ԃ�

	 // X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(cFN[nCntEnemyType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatEnemy2[nCntEnemyType],
			NULL,
			&g_nNumMatEnemy2[nCntEnemyType],
			&g_pMeshEnemy2[nCntEnemyType]);

		int nNumVtex;					// ���_��
		DWORD sizeFvF;					// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^

		// �G�̏�����
		for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
		{// �G�̐��J��Ԃ�
			g_aEnemy2[nCntEnemyType][nCntEnemy2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].nType = ENEMYTYPE2_NORMAL;
			g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = false;

			// ���_�����擾
			nNumVtex = g_pMeshEnemy2[nCntEnemyType]->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFvF = D3DXGetFVFVertexSize(g_pMeshEnemy2[nCntEnemyType]->GetFVF());

			// ���_�o�b�t�@�����b�N
			g_pMeshEnemy2[nCntEnemyType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x >= vtx.x)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x = vtx.x;
				}
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.y >= vtx.y)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.y = vtx.y;
				}
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z >= vtx.z)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z = vtx.z;
				}

				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x <= vtx.x)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x = vtx.x;
				}
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.y <= vtx.y)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.y = vtx.y;
				}
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z <= vtx.z)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff += sizeFvF;
			}
			// ���_�o�b�t�@���A�����b�N
			g_pMeshEnemy2[nCntEnemyType]->UnlockVertexBuffer();
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy2(void)
{
	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{
		// ���b�V���̊J��
		if (g_pMeshEnemy2[nCntEnemyType] != NULL)
		{
			g_pMeshEnemy2[nCntEnemyType]->Release();
			g_pMeshEnemy2[nCntEnemyType] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatEnemy2[nCntEnemyType] != NULL)
		{
			g_pBuffMatEnemy2[nCntEnemyType]->Release();
			g_pBuffMatEnemy2[nCntEnemyType] = NULL;
		}
	}

	// �e�N�X�`���̔j��
	if (g_pTextureEnemy2 != NULL)
	{
		g_pTextureEnemy2->Release();
		g_pTextureEnemy2 = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy2(void)
{
	// �J�����̎擾
	Camera *pCamera;
	pCamera = GetCamera();

	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{// �G�̎�ތJ��Ԃ�
		for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
		{// �G�̐��J��Ԃ�
			if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == true)
			{// �G���g���Ă���
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].nType == ENEMYTYPE2_NORMAL)
				{
					{
						if (rand() % 2)
						{
							g_aEnemy2[nCntEnemyType][nCntEnemy2].move.x -= sinf((rand() % 314 * 2) + pCamera->rot.y) * 2;
							g_aEnemy2[nCntEnemyType][nCntEnemy2].move.z -= cosf((rand() % 314 * 2) + pCamera->rot.y) * 2;
						}
					}
				}

				// ���b�V���E�H�[���̎擾
				MeshWall *pMeshWall;
				pMeshWall = GetMeshWall();

				// �ǂƂ̓����蔻��
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z > 725)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z = 725;
				}
				else if (g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z < -25)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z = -25;
				}
				else if (g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x > 725)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x = 725;
				}
				else if (g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x < -25)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x = -25;
				}
				else
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].move;
				}

				// �ߋ��̈ʒu���擾
				g_aEnemy2[nCntEnemyType][nCntEnemy2].posOld = g_aEnemy2[nCntEnemyType][nCntEnemy2].pos;

				g_aEnemy2[nCntEnemyType][nCntEnemy2].pos += g_aEnemy2[nCntEnemyType][nCntEnemy2].move;
				g_aEnemy2[nCntEnemyType][nCntEnemy2].move.x += (0.0f - g_aEnemy2[nCntEnemyType][nCntEnemy2].move.x) * 0.2f;
				g_aEnemy2[nCntEnemyType][nCntEnemy2].move.z += (0.0f - g_aEnemy2[nCntEnemyType][nCntEnemy2].move.z) * 0.2f;

				// ���f���Ƃ̓����蔻��
				if (CollisionModel(&g_aEnemy2[nCntEnemyType][nCntEnemy2].pos, &g_aEnemy2[nCntEnemyType][nCntEnemy2].posOld, &g_aEnemy2[nCntEnemyType][nCntEnemy2].move) == true)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = false;			//�g�p���ĂȂ�
				}
				else
				{
					if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == false)
					{
						g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = true;		//�g�p���Ă�
					}
				}

				SetPositionShadow(g_aEnemy2[nCntEnemyType][nCntEnemy2].nIdexShadow, g_aEnemy2[nCntEnemyType][nCntEnemy2].pos);

				//// �v���C���[�Ƃ̓����蔻��
				//if (CollisionPlayer(&g_aEnemy2[nCntEnemyType][nCntEnemy2].pos, &g_aEnemy2[nCntEnemyType][nCntEnemy2].posOld, &g_aEnemy2[nCntEnemyType][nCntEnemy2].move) == true)
				//{
				//	g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = false;			//�g�p���ĂȂ�
				//}
				//else
				//{
				//	if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == false)
				//	{
				//		g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = true;		//�g�p���Ă�
				//	}
				//}

			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{// �G�̎�ތJ��Ԃ�
		for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
		{// �G�̐��J��Ԃ�
			if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == true)
			{// �G���g�p����Ă���
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy2[nCntEnemyType][nCntEnemy2].rot.y, g_aEnemy2[nCntEnemyType][nCntEnemy2].rot.x, g_aEnemy2[nCntEnemyType][nCntEnemy2].rot.z);
				D3DXMatrixMultiply(&g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld, &g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x, g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.y, g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z);
				D3DXMatrixMultiply(&g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld, &g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatEnemy2[g_aEnemy2[nCntEnemyType][nCntEnemy2].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy2[g_aEnemy2[nCntEnemyType][nCntEnemy2].nType]; nCntMat++)
				{// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`��
					pDevice->SetTexture(0, g_pTextureEnemy2);

					// ���f��(�p�[�c)�̕`��
					g_pMeshEnemy2[g_aEnemy2[nCntEnemyType][nCntEnemy2].nType]->DrawSubset(nCntMat);

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
void SetEnemy2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE2 nType)
{
	for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
	{
		if (g_aEnemy2[nType][nCntEnemy2].bDisp == false)
		{
			g_aEnemy2[nType][nCntEnemy2].pos = pos;
			g_aEnemy2[nType][nCntEnemy2].rot = D3DXVECTOR3(0, 0, 0);
			g_aEnemy2[nType][nCntEnemy2].nType = nType;
			g_aEnemy2[nType][nCntEnemy2].nIdexShadow = SetShadow(g_aEnemy2[nType][nCntEnemy2].pos, g_aEnemy2[nType][nCntEnemy2].rot);
			g_aEnemy2[nType][nCntEnemy2].bDisp = true;
			break;
		}
	}
}

//=============================================================================
// �G�̓����蔻�菈��
//=============================================================================
bool CollisionEnemy2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	bool bHit = false;		// �����������ǂ���

	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{// �G�̎�ތJ��Ԃ�
		for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
		{// �G�̐��J��Ԃ�
			if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == true)
			{// �G���g���Ă���
				if (pPos->x >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x &&
					pPos->x <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x)
				{// Z�ʂ̔���
					if (pPosold->z <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z &&
						pPos->z >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z)
					{// ��O�̔���
						pPos->z = pPosold->z;
						pMove->z = -20.0f;
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_KARASU);
					}
					else if (pPosold->z >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z) &&
						pPos->z <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z))
					{// ���̔���
						pPos->z = pPosold->z;
						pMove->z = 20.0f;
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_KARASU);
					}
				}
				if (pPos->z >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z &&
					pPos->z <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z)
				{// X�ʂ̔���
					if (pPosold->x >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x &&
						pPos->x <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x)
					{// �E�ʂ̔���
						pPos->x = pPosold->x;
						pMove->x = 20.0f;
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_KARASU);

					}
					else if (pPosold->x <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x) &&
						pPos->x >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x))
					{// ���ʂ̔���
						pPos->x = pPosold->x;
						pMove->x = -20.0f;
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_KARASU);
					}
				}
			}		
		}
	}
	return bHit;
}

//=============================================================================
// �G�̎擾
//=============================================================================
ENEMY2 *GetEnemy2(void)
{
	return &g_aEnemy2[0][0];
}

