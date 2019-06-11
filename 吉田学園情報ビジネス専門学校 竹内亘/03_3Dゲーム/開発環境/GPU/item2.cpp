//=============================================================================
//
// �A�C�e��(���f��ver)���� [item2.cpp]
// Author : �|���j
//
//=============================================================================
#include "item2.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "score.h"
#include "fade.h"
#include "timer.h"
#include "game.h"
#include "particle.h"
//#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME "data/MODEL/gomi.x"		// ���f����
#define MODEL_NAME2 "data/MODEL/PB.x"		// ���f����
#define MODEL_NAME3 "data/MODEL/kan.x"		// ���f����
#define MODEL_NAME4 "data/MODEL/book.x"		// ���f����
#define MOVE_SPEED (2.0f)					// �A�C�e���̓����X�s�[�h
#define MAX_ITEM (256)						// �A�C�e���̍ő吔
#define MAX_ITEMTYPE (4)					// �A�C�e���̎�ސ�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshItem2[ITEMTYPE2_MAX] = {};		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatItem2[ITEMTYPE2_MAX] = {};	// �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureItem2 = NULL;			// �e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatItem2[ITEMTYPE2_MAX];				// �}�e���A�����̐�
//D3DXVECTOR3 g_VtxMinModel, g_VtxMaxModel;			// �A�C�e���̍ŏ��l,�ő�l
//D3DXVECTOR3 g_posModel;							// �ʒu
//D3DXVECTOR3 g_rotModel;							// ����
//D3DXMATRIX g_mtxWorldModel;						// ���[���h�}�g���b�N�X
ITEM2 g_aItem2[ITEMTYPE2_MAX][MAX_ITEM];							// �A�C�e���̏��
//int g_nIdexShadow;								// �e�̎擾�����邽��
int g_nNumItem;										// �A�C�e���̑���

//=============================================================================
// ����������
//=============================================================================
void InitItem2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	char cFN[ITEMTYPE2_MAX][256] = { MODEL_NAME , MODEL_NAME2, MODEL_NAME3,MODEL_NAME4};

	for (int nCntItemType = 0; nCntItemType < ITEMTYPE2_MAX; nCntItemType++)
	{// �A�C�e���̎�ތJ��Ԃ�

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(cFN[nCntItemType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatItem2[nCntItemType],
			NULL,
			&g_nNumMatItem2[nCntItemType],
			&g_pMeshItem2[nCntItemType]);

		// �����蔻��ɕK�v
		int nNumVtx;		// ���_��
		DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE * pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

		//�A�C�e���̏�����
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{// �A�C�e���̐��J��Ԃ�
			g_aItem2[nCntItemType][nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem2[nCntItemType][nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem2[nCntItemType][nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem2[nCntItemType][nCntItem].VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
			g_aItem2[nCntItemType][nCntItem].VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
			g_aItem2[nCntItemType][nCntItem].nType = ITEMTYPE2_GOMI;
			//g_aItem2[nCntItemType][nCntItem].nNumItem = MAX_ITEM;
			g_aItem2[nCntItemType][nCntItem].bUse = false;
			g_nNumItem = 0;

			// ���_�����擾
			nNumVtx = g_pMeshItem2[nCntItemType]->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem2[nCntItemType]->GetFVF());

			// ���_�o�b�t�@�����b�N
			g_pMeshItem2[nCntItemType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				if (g_aItem2[nCntItemType][nCntItem].VtxMinModel.x >= vtx.x)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMinModel.x = vtx.x;
				}
				if (g_aItem2[nCntItemType][nCntItem].VtxMinModel.y >= vtx.y)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMinModel.y = vtx.y;
				}
				if (g_aItem2[nCntItemType][nCntItem].VtxMinModel.z >= vtx.z)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMinModel.z = vtx.z;
				}

				if (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x <= vtx.x)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x = vtx.x;
				}
				if (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.y <= vtx.y)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMaxModel.y = vtx.y;
				}
				if (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z <= vtx.z)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff += sizeFVF;
			}

			// ���_�o�b�t�@�����b�N
			g_pMeshItem2[nCntItemType]->UnlockVertexBuffer();
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem2(void)
{
	for (int nCntItemType = 0; nCntItemType < ITEMTYPE2_MAX; nCntItemType++)
	{
		// ���b�V���̊J��
		if (g_pMeshItem2[nCntItemType] != NULL)
		{
			g_pMeshItem2[nCntItemType]->Release();
			g_pMeshItem2[nCntItemType] = NULL;
		}

		// �}�e���A���̊J��
		if (g_pBuffMatItem2[nCntItemType] != NULL)
		{
			g_pBuffMatItem2[nCntItemType]->Release();
			g_pBuffMatItem2[nCntItemType] = NULL;
		}

		// �e�N�X�`���̉��
		if (g_pTextureItem2 != NULL)
		{
			g_pTextureItem2->Release();
			g_pTextureItem2 = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem2(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntItemType = 0; nCntItemType < ITEMTYPE2_MAX; nCntItemType++)
	{// �A�C�e���̎�ތJ��Ԃ�
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{// �A�C�e���̐��J��Ԃ�
			if (g_aItem2[nCntItemType][nCntItem].bUse == true)
			{// �A�C�e�����g���Ă���

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aItem2[nCntItemType][nCntItem].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aItem2[nCntItemType][nCntItem].rot.y, g_aItem2[nCntItemType][nCntItem].rot.x, g_aItem2[nCntItemType][nCntItem].rot.z);
				D3DXMatrixMultiply(&g_aItem2[nCntItemType][nCntItem].mtxWorld, &g_aItem2[nCntItemType][nCntItem].mtxWorld, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aItem2[nCntItemType][nCntItem].pos.x, g_aItem2[nCntItemType][nCntItem].pos.y, g_aItem2[nCntItemType][nCntItem].pos.z);
				D3DXMatrixMultiply(&g_aItem2[nCntItemType][nCntItem].mtxWorld, &g_aItem2[nCntItemType][nCntItem].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aItem2[nCntItemType][nCntItem].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatItem2[g_aItem2[nCntItemType][nCntItem].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_nNumMatItem2[g_aItem2[nCntItemType][nCntItem].nType]; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					pDevice->SetTexture(0, NULL);

					// ���f��(�p�[�c)�̕`��
					g_pMeshItem2[g_aItem2[nCntItemType][nCntItem].nType]->DrawSubset(nCntMat);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================
void SetItem2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, ITEMTYPE2 nType)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem2[nType][nCntItem].bUse == false)
		{
			g_aItem2[nType][nCntItem].pos = pos;
			g_aItem2[nType][nCntItem].rot = rot;
			g_aItem2[nType][nCntItem].move = move;
			g_aItem2[nType][nCntItem].nType = nType;
			g_aItem2[nType][nCntItem].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �A�C�e���̓����蔻��
//=============================================================================
bool CollisionItem2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	bool bGet = false;		//�Q�b�g�������ǂ���

	for (int nCntItemType = 0; nCntItemType < ITEMTYPE2_MAX; nCntItemType++)
	{// �A�C�e���̎�ތJ��Ԃ�
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{
			if (g_aItem2[nCntItemType][nCntItem].bUse == true)
			{// �A�C�e�����g���Ă���
				if (pPos->x >= g_aItem2[nCntItemType][nCntItem].pos.x + g_aItem2[nCntItemType][nCntItem].VtxMinModel.x &&
					pPos->x <= g_aItem2[nCntItemType][nCntItem].pos.x + g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x)
				{// Z�ʂ̔���
					if (pPosold->z <= g_aItem2[nCntItemType][nCntItem].pos.z + g_aItem2[nCntItemType][nCntItem].VtxMinModel.z &&
						pPos->z >= g_aItem2[nCntItemType][nCntItem].pos.z + g_aItem2[nCntItemType][nCntItem].VtxMinModel.z)
					{// ��O�̔���
						bGet = true;
						g_aItem2[nCntItemType][nCntItem].bUse = false;
						SetParticle(g_aItem2[nCntItemType][nCntItem].pos, g_aItem2[nCntItemType][nCntItem].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);

						// �A�C�e���ʂ̃X�R�A
						if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_GOMI)
						{// �A�C�e��1
							AddScore(1000);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_BOOK)
						{// �{
							AddScore(600);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_PB)
						{// PB
							AddScore(100);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_KAN)
						{// ��
							AddScore(200);
						}
						pPos->z = pPosold->z;
					}
					else if (pPosold->z >= g_aItem2[nCntItemType][nCntItem].pos.z + (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z) &&
						pPos->z <= g_aItem2[nCntItemType][nCntItem].pos.z + (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z))
					{// ���̔���
						bGet = true;
						g_aItem2[nCntItemType][nCntItem].bUse = false;
						SetParticle(g_aItem2[nCntItemType][nCntItem].pos, g_aItem2[nCntItemType][nCntItem].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);

						// �A�C�e���ʂ̃X�R�A
						if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_GOMI)
						{// �A�C�e��1
							AddScore(1000);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_BOOK)
						{// �{
							AddScore(600);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_PB)
						{// PB
							AddScore(100);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_KAN)
						{// ��
							AddScore(200);
						}
						pPos->z = pPosold->z;
					}
				}
				if (pPos->z >= g_aItem2[nCntItemType][nCntItem].pos.z + g_aItem2[nCntItemType][nCntItem].VtxMinModel.z &&
					pPos->z <= g_aItem2[nCntItemType][nCntItem].pos.z + g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z)
				{// X�ʂ̔���
					if (pPosold->x >= g_aItem2[nCntItemType][nCntItem].pos.x + g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x &&
						pPos->x <= g_aItem2[nCntItemType][nCntItem].pos.x + g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x)
					{// �E�ʂ̔���
						bGet = true;
						g_aItem2[nCntItemType][nCntItem].bUse = false;
						SetParticle(g_aItem2[nCntItemType][nCntItem].pos, g_aItem2[nCntItemType][nCntItem].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);

						// �A�C�e���ʂ̃X�R�A
						if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_GOMI)
						{// �A�C�e��1
							AddScore(1000);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_BOOK)
						{// �{
							AddScore(600);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_PB)
						{// PB
							AddScore(100);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_KAN)
						{// ��
							AddScore(200);
						}
						pPos->x = pPosold->x;
					}
					else if (pPosold->x <= g_aItem2[nCntItemType][nCntItem].pos.x + (g_aItem2[nCntItemType][nCntItem].VtxMinModel.x) &&
						pPos->x >= g_aItem2[nCntItemType][nCntItem].pos.x + (g_aItem2[nCntItemType][nCntItem].VtxMinModel.x))
					{// ���ʂ̔���
						bGet = true;
						g_aItem2[nCntItemType][nCntItem].bUse = false;
						SetParticle(g_aItem2[nCntItemType][nCntItem].pos, g_aItem2[nCntItemType][nCntItem].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);

						// �A�C�e���ʂ̃X�R�A
						if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_GOMI)
						{// �A�C�e��1
							AddScore(1000);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_BOOK)
						{// �{
							AddScore(600);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_PB)
						{// PB
							AddScore(100);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_KAN)
						{// ��
							AddScore(200);
						}
						pPos->x = pPosold->x;
					}
				}
				g_nNumItem--;	// �A�C�e���̐������炷
				if (g_nNumItem <= 0)
				{// �A�C�e���̐���0�ɂȂ�����
					SetGameState(GAMESTATE_GAMECLEAR);
					//SetFade(MODE_GAMECLEAR);
				}
			}
		}
	}
	return bGet;
}

//=============================================================================
// �A�C�e���̎擾
//=============================================================================
ITEM2 *GetItem2(void)
{
	return &g_aItem2[0][0];
}

//=============================================================================
// �A�C�e���̑������擾
//=============================================================================
int GetITEM(void)
{
	return g_nNumItem;
}


