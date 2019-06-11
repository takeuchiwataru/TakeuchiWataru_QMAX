//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "item.h"
#include "input.h"
#include "camera.h"
#include "itemCnt.h"
#include "flontpolygon.h"
#include "itemfont.h"
#include "xplayer.h"
#include "storyfont.h"
#include "mark.h"
#include "sound.h"
#include "effect.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_XFAILE		(4)								//�ǂ݂��ނ��t�@�C���̍ő吔
#define MAX_XOBJECT		(10)							//���t�@�C���̍ő�g�p��
#define ITEM_SPEED		(2.0f)							//���f���̈ړ���
#define MAX_ITEM		(5)								//���f���̍ő吔
#define MAX_TEXTURE		(3)								//�e�N�X�`���̍ő吔
#define ITEM_CIRCLE		(60.0f)							//�A�C�e���͈̔͐ݒ�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Item				g_Item[MAX_XFAILE][MAX_XOBJECT];	//���f���̏��
int					g_nGetItem;							//�A�C�e���̑���

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	//�ϐ��錾
	char XFileName[MAX_XFAILE][48];
	int nCntXFile;
	int nCntItem;
	int		nNumVtx = 0;	//���_��
	DWORD	sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *	pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	//�t�@�C�����̓ǂ݂���
//	wsprintf(&XFileName[0][0], "data\\MODEL\\box000.x");	//�A�C�e��
//	wsprintf(&XFileName[1][0], "data\\MODEL\\kanban.x");	//��

	wsprintf(&XFileName[0][0], "data\\MODEL\\kanban.x");	//����1-�Ŕ�
	wsprintf(&XFileName[1][0], "data\\MODEL\\car.x");		//����2-��
	wsprintf(&XFileName[2][0], "data\\MODEL\\ueki_pink.x");	//����3-�A�ؔ�
	wsprintf(&XFileName[3][0], "data\\MODEL\\denwabox.x");	//����4-�d�b�{�b�N�X

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(&XFileName[nCntXFile][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Item[nCntXFile][0].pBuffMatItem,
			NULL,
			&g_Item[nCntXFile][0].nNumMatItem,
			&g_Item[nCntXFile][0].pMeshItem);

		D3DXMATERIAL *pmat;							// �}�e���A���f�[�^�ւ̃|�C���^
		D3DMATERIAL9 *matDef;						// ���݂̃}�e���A���ۑ��p
		pmat = (D3DXMATERIAL*)g_Item[nCntXFile][0].pBuffMatItem->GetBufferPointer();
		matDef = new D3DMATERIAL9[g_Item[nCntXFile][0].nNumMatItem];
		g_Item[nCntXFile][0].pTextureItem = new LPDIRECT3DTEXTURE9[g_Item[nCntXFile][0].nNumMatItem];

		for (DWORD tex = 0; tex < g_Item[nCntXFile][0].nNumMatItem; tex++)
		{
			matDef[tex] = pmat[tex].MatD3D;
			matDef[tex].Ambient = matDef[tex].Diffuse;
			g_Item[nCntXFile][0].pTextureItem[tex] = NULL;
			if (pmat[tex].pTextureFilename != NULL &&
				lstrlen(pmat[tex].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					pmat[tex].pTextureFilename,
					&g_Item[nCntXFile][0].pTextureItem[tex])))
				{
					MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				}
			}
		}
	}

	//�ϐ��̏�����
	g_nGetItem = 0;

	// �\���̂̏����ݒ�
	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		g_Item[nCntXFile][0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntXFile][0].OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntXFile][0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntXFile][0].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntXFile][0].CircleMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntXFile][0].CircleMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntXFile][0].vtxMinItem = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);
		g_Item[nCntXFile][0].vtxMaxItem = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
		g_Item[nCntXFile][0].nIdxMark = 0;
		g_Item[nCntXFile][0].nIdxFlontPolygon[0] = 0;
		g_Item[nCntXFile][0].nIdxFlontPolygon[1] = 0;
		g_Item[nCntXFile][0].type = ITEMTYPE_MAX;
		g_Item[nCntXFile][0].nCntTimer = 0;
		g_Item[nCntXFile][0].bInPlayer = false;
		g_Item[nCntXFile][0].bUse = false;

		//���_�����擾
		nNumVtx = g_Item[nCntXFile][0].pMeshItem->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Item[nCntXFile][0].pMeshItem->GetFVF());

		//���_�o�b�t�@�����b�N
		g_Item[nCntXFile][0].pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

			//�ő�l���r
			if (g_Item[nCntXFile][0].vtxMaxItem.x < vtx.x)
			{
				g_Item[nCntXFile][0].vtxMaxItem.x = vtx.x;
			}
			if (g_Item[nCntXFile][0].vtxMaxItem.z < vtx.z)
			{
				g_Item[nCntXFile][0].vtxMaxItem.z = vtx.z;
			}

			//�ŏ��l���r
			if (g_Item[nCntXFile][0].vtxMinItem.x > vtx.x)
			{
				g_Item[nCntXFile][0].vtxMinItem.x = vtx.x;
			}
			if (g_Item[nCntXFile][0].vtxMinItem.z > vtx.z)
			{
				g_Item[nCntXFile][0].vtxMinItem.z = vtx.z;
			}

			//�T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//�o�b�t�@���A�����b�N
		g_Item[nCntXFile][0].pMeshItem->UnlockVertexBuffer();
	}

	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		for (nCntItem = 1; nCntItem < MAX_XOBJECT; nCntItem++)
		{
			g_Item[nCntXFile][nCntItem] = g_Item[nCntXFile][0];
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	//�ϐ��錾
	int nCntTex;
	int	nCntXFile;
	int nCntItem;

	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		// ���b�V���̊J��
		if (g_Item[nCntXFile][0].pMeshItem != NULL)
		{
			g_Item[nCntXFile][0].pMeshItem->Release();
			g_Item[nCntXFile][0].pMeshItem = NULL;
		}

		// �}�e���A���̊J��
		if (g_Item[nCntXFile][0].pBuffMatItem != NULL)
		{
			g_Item[nCntXFile][0].pBuffMatItem->Release();
			g_Item[nCntXFile][0].pBuffMatItem = NULL;
		}
	}

	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		for (DWORD nTex = 0; nTex < g_Item[nCntXFile][0].nNumMatItem; nTex++)
		{
			//�e�N�X�`���̊J��
			if (g_Item[nCntXFile][0].pTextureItem[nTex] != NULL)
			{
				g_Item[nCntXFile][0].pTextureItem[nTex]->Release();
				g_Item[nCntXFile][0].pTextureItem[nTex] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	//�ϐ��錾
	int	nCntXFile;
	int nCntItem;

	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		for (nCntItem = 0; nCntItem < MAX_XOBJECT; nCntItem++)
		{
			if (g_Item[nCntXFile][nCntItem].bUse == true)
			{
				g_Item[nCntXFile][nCntItem].nCntTimer++;

				if (g_Item[nCntXFile][nCntItem].nCntTimer % 20 == 0)
				{
					SetRainEffect(g_Item[nCntXFile][nCntItem].pos, EFFECTTYPE_RESURRECTIONWATER_1, 2, 30, 0, 0);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ�	/����
				}
			}

			if (g_Item[nCntXFile][nCntItem].bUse == false && g_Item[nCntXFile][nCntItem].nIdxFlontPolygon[0] != g_Item[nCntXFile][nCntItem].nIdxFlontPolygon[1])
			{
				if (GetStoryFont() == false)
				{
					if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
					{
						DeleteFlontPolygon(g_Item[nCntXFile][nCntItem].nIdxFlontPolygon[0]);	//�|���S��������
						DeleteFlontPolygon(g_Item[nCntXFile][nCntItem].nIdxFlontPolygon[1]);
						DeleteItemFont();		//�t�H���g������
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int				nCntXFile;
	int				nCntItem;
	D3DXMATRIX		mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9	matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL	*pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		for (nCntItem = 0; nCntItem < MAX_XOBJECT; nCntItem++)
		{
			if (g_Item[nCntXFile][nCntItem].bUse == true)
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Item[nCntXFile][nCntItem].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nCntXFile][nCntItem].rot.y, g_Item[nCntXFile][nCntItem].rot.x, g_Item[nCntXFile][nCntItem].rot.z);
				D3DXMatrixMultiply(&g_Item[nCntXFile][nCntItem].mtxWorld, &g_Item[nCntXFile][nCntItem].mtxWorld, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Item[nCntXFile][nCntItem].pos.x, g_Item[nCntXFile][nCntItem].pos.y, g_Item[nCntXFile][nCntItem].pos.z);
				D3DXMatrixMultiply(&g_Item[nCntXFile][nCntItem].mtxWorld, &g_Item[nCntXFile][nCntItem].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCntXFile][nCntItem].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_Item[nCntXFile][nCntItem].pBuffMatItem->GetBufferPointer();

				// �e�N�X�`���f�[�^�ւ̃|�C���^���擾
				for (int nCntMat = 0; nCntMat < (int)g_Item[nCntXFile][nCntItem].nNumMatItem; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_Item[nCntXFile][nCntItem].pTextureItem[nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_Item[nCntXFile][nCntItem].pMeshItem->DrawSubset(nCntMat);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}

}

//=============================================================================
// �����蔻��
//=============================================================================
bool CollsionItem(D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 * pPos, D3DXVECTOR3 * pOldPos)
{
	//�ϐ��錾
	int	nCntXFile;
	int nCntItem;
	bool bLand = false;

	XPLAYER *pXPlayer = GetXPlayer();

	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		for (nCntItem = 0; nCntItem < MAX_XOBJECT; nCntItem++)
		{
			if (g_Item[nCntXFile][nCntItem].bUse == true)
			{
				if (pPos->x + vtxMax.x >= g_Item[nCntXFile][nCntItem].pos.x + g_Item[nCntXFile][nCntItem].vtxMinItem.x &&
					pPos->x + vtxMin.x <= g_Item[nCntXFile][nCntItem].pos.x + g_Item[nCntXFile][nCntItem].vtxMaxItem.x &&
					pPos->z + vtxMax.z >= g_Item[nCntXFile][nCntItem].pos.z + g_Item[nCntXFile][nCntItem].vtxMinItem.z &&
					pPos->z + vtxMin.z <= g_Item[nCntXFile][nCntItem].pos.z + g_Item[nCntXFile][nCntItem].vtxMaxItem.z)
				{//���͈͔̔���
						DeleteItem(nCntItem, g_Item[nCntXFile][nCntItem].type);		//�A�C�e��������
						DeleteMark(g_Item[nCntXFile][nCntItem].nIdxMark);			//�}�[�N������

						pXPlayer->nAnimnow = PLAYERANIM_NEUTRAL;
						pXPlayer->nAnimkeynow = 0;

						bLand = true;

						AddScore(1500);

						PlaySound(SOUND_LABEL_SE_PICKUP);
				}

				/*if (pPos->x + vtxMax.x > g_Item[nCntXFile][nCntItem].pos.x + g_Item[nCntXFile][nCntItem].vtxMinItem.x &&
					pPos->x + vtxMin.x < g_Item[nCntXFile][nCntItem].pos.x + g_Item[nCntXFile][nCntItem].vtxMaxItem.x)
				{//���͈͔̔���
					if (pOldPos->z + vtxMin.z >= g_Item[nCntXFile][nCntItem].pos.z + g_Item[nCntXFile][nCntItem].vtxMaxItem.z &&
						g_Item[nCntXFile][nCntItem].pos.z + g_Item[nCntXFile][nCntItem].vtxMaxItem.z >= pPos->z + vtxMin.z)
					{//����
						DeleteItem(nCntItem, g_Item[nCntXFile][nCntItem].type);	//�A�C�e��������
						DeleteMark(g_Item[nCntXFile][nCntItem].nIdxMark);			//�}�[�N������

						pXPlayer->nAnimnow = PLAYERANIM_NEUTRAL;
						pXPlayer->nAnimkeynow = 0;

						bLand = true;
					}
					else if (pOldPos->z + vtxMax.z <= g_Item[nCntXFile][nCntItem].pos.z + g_Item[nCntXFile][nCntItem].vtxMinItem.z &&
						g_Item[nCntXFile][nCntItem].pos.z + g_Item[nCntXFile][nCntItem].vtxMinItem.z <= pPos->z + vtxMax.z)
					{//��O�̖�
						DeleteItem(nCntItem, g_Item[nCntXFile][nCntItem].type);	//�A�C�e��������
						DeleteMark(g_Item[nCntXFile][nCntItem].nIdxMark);			//�}�[�N������

						pXPlayer->nAnimnow = PLAYERANIM_NEUTRAL;
						pXPlayer->nAnimkeynow = 0;

						bLand = true;
					}
				}

				if (pPos->z + vtxMax.z < g_Item[nCntXFile][nCntItem].pos.z + g_Item[nCntXFile][nCntItem].vtxMaxItem.z &&
					pPos->z + vtxMax.z > g_Item[nCntXFile][nCntItem].pos.z + g_Item[nCntXFile][nCntItem].vtxMinItem.z)
				{//z�͈͔̔���
					if (pOldPos->x + vtxMin.x >= g_Item[nCntXFile][nCntItem].pos.x + g_Item[nCntXFile][nCntItem].vtxMaxItem.x &&
						g_Item[nCntXFile][nCntItem].pos.x + g_Item[nCntXFile][nCntItem].vtxMaxItem.x >= pPos->x + vtxMin.x)
					{//�E���̖�
						DeleteItem(nCntItem, g_Item[nCntXFile][nCntItem].type);	//�A�C�e��������
						DeleteMark(g_Item[nCntXFile][nCntItem].nIdxMark);			//�}�[�N������

						pXPlayer->nAnimnow = PLAYERANIM_NEUTRAL;
						pXPlayer->nAnimkeynow = 0;

						bLand = true;
					}
					else if (pOldPos->x + vtxMax.x <= g_Item[nCntXFile][nCntItem].pos.x + g_Item[nCntXFile][nCntItem].vtxMinItem.x &&
						g_Item[nCntXFile][nCntItem].pos.x + g_Item[nCntXFile][nCntItem].vtxMinItem.x <= pPos->x + vtxMax.x)
					{//�����̖�
						DeleteItem(nCntItem, g_Item[nCntXFile][nCntItem].type);		//�A�C�e��������
						DeleteMark(g_Item[nCntXFile][nCntItem].nIdxMark);				//�}�[�N������

						pXPlayer->nAnimnow = PLAYERANIM_NEUTRAL;
						pXPlayer->nAnimkeynow = 0;

						bLand = true;
					}
				}*/

				//�O���͈͔̔���
				if (pPos->x + vtxMax.x > g_Item[nCntXFile][nCntItem].CircleMin.x &&
					pPos->x + vtxMin.x < g_Item[nCntXFile][nCntItem].CircleMax.x &&
					pPos->z + vtxMax.z < g_Item[nCntXFile][nCntItem].CircleMax.z &&
					pPos->z + vtxMax.z > g_Item[nCntXFile][nCntItem].CircleMin.z)
				{//���Ƃ��͈͔̔���
					if (g_Item[nCntXFile][nCntItem].bInPlayer == false)
					{//�A�C�e���͈͓̔��ɓ�������
						g_Item[nCntXFile][nCntItem].nIdxMark = SetMark(D3DXVECTOR3(g_Item[nCntXFile][nCntItem].pos.x, 50.0f, g_Item[nCntXFile][nCntItem].pos.z));	//�}�[�N���o��
						g_Item[nCntXFile][nCntItem].bInPlayer = true;																								//�͈͓��ɓ����Ă����Ԃɂ���
					}
				}
				else
				{
					if (g_Item[nCntXFile][nCntItem].bInPlayer == true)
					{
						DeleteMark(g_Item[nCntXFile][nCntItem].nIdxMark);		//�}�[�N������
						g_Item[nCntXFile][nCntItem].bInPlayer = false;			//�͈͓��ɓ����Ă��Ȃ���Ԃɂ���
					}
				}
			}
		}
	}

	return bLand;
}

//=============================================================================
// ���f���̐ݒ�
//=============================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEMTYPE type)
{
	//�ϐ��錾
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_XOBJECT; nCntItem++)
	{
		if (g_Item[type][nCntItem].bUse == false)
		{
			g_Item[type][nCntItem].pos = pos;								//���S���W
			g_Item[type][nCntItem].OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
			g_Item[type][nCntItem].rot = rot;								//����
			g_Item[type][nCntItem].type = type;								//�A�C�e���̃^�C�v
			g_Item[type][nCntItem].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]��
			g_Item[type][nCntItem].nIdxMark = 0;							//�}�[�N�̔ԍ�
			g_Item[type][nCntItem].nIdxFlontPolygon[0] = 0;					//�t�����g�|���S���̎g�p�ԍ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = 0;					//�t�����g�|���S���̎g�p�ԍ�
			g_Item[type][nCntItem].nCntTimer = 0;					//
			g_Item[type][nCntItem].bInPlayer = false;						//�͈͓��ɓ����Ă��Ȃ���Ԃɂ���
			g_Item[type][nCntItem].bUse = true;								//�g�p���Ă����Ԃɂ���

			//�͈͐ݒ�iMax�j
			g_Item[type][nCntItem].CircleMax = g_Item[type][nCntItem].pos + g_Item[type][nCntItem].vtxMaxItem;
			g_Item[type][nCntItem].CircleMax += D3DXVECTOR3(30.0f, 0.0f, 30.0f);

			//�͈͐ݒ�iMin�j
			g_Item[type][nCntItem].CircleMin = g_Item[type][nCntItem].pos + g_Item[type][nCntItem].vtxMinItem;
			g_Item[type][nCntItem].CircleMin -= D3DXVECTOR3(30.0f, 0.0f, 30.0f);

			//�A�C�e���̑����𑝂₷
			g_nGetItem++;

			//�e�̐ݒ�
			/*g_Item[nCntXFile].nIdxshadow = SetShadow(D3DXVECTOR3(g_Item[nCntXFile].pos.x, 0.0f, g_Item[nCntXFile].pos.z),
																  g_Item[nCntXFile].rot, 15.0f, 15.0f);	*/
			break;
		}
	}
}

//=============================================================================
// �A�C�e���̏���
//=============================================================================
void DeleteItem(int nCntItem, ITEMTYPE type)
{
	if (g_Item[type][nCntItem].bUse == true)
	{
		g_Item[type][nCntItem].bUse = false;	//����
		AddItemCnt(1);
		g_Item[type][nCntItem].nIdxFlontPolygon[0] = SetFlontPolygon(FLONTPOLYGONTEXTURE_FONT_BG, D3DXVECTOR3(640.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH, 180.0f);	//UI�̃Z�b�g

		if (g_Item[type][nCntItem].type == ITEMTYPE_GIAR_00)
		{
			SetItemFont("���i����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);														//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_GEAR_0, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_GIAR_01)
		{
			SetItemFont("���i����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);														//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_GEAR_1, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_GIAR_02)
		{
			SetItemFont("���i����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);														//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_GEAR_2, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_GIAR_03)
		{
			SetItemFont("���i����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);														//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_GEAR_3, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_WATCH_00)
		{
			SetItemFont("���v�̘g����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);													//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_CLOCK_0, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_WATCH_01)
		{
			SetItemFont("�`�F�[������ɓ��ꂽ�I", TYPEITEMFONT_ITEM);													//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_CLOCK_1, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_WATCH_02)
		{
			SetItemFont("��M����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);														//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_CLOCK_2, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_ORUGORU_00)
		{
			SetItemFont("�I���S�[���P����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);														//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_MUSICBOX_0, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_ORUGORU_01)
		{
			SetItemFont("�I���S�[���Q����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);														//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_MUSICBOX_1, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
		else if (g_Item[type][nCntItem].type == ITEMTYPE_ORUGORU_02)
		{
			SetItemFont("�ؔ�����ɓ��ꂽ�I", TYPEITEMFONT_ITEM);														//�����̐ݒ�
			g_Item[type][nCntItem].nIdxFlontPolygon[1] = SetFlontPolygon(FLONTPOLYGONTEXTURE_MUSICBOX_2, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130.0f, 130.0f);	//�A�C�e���̃A�C�R���ݒ�
		}
	}
}

//=============================================================================
// �S�ẴA�C�e��������
//=============================================================================
void AllDeleteItem(void)
{
	//�ϐ��錾
	int nCntXFile;
	int nCntItem;

	for (nCntXFile = 0; nCntXFile < MAX_XFAILE; nCntXFile++)
	{
		for (nCntItem = 0; nCntItem < MAX_XOBJECT; nCntItem++)
		{
			g_Item[nCntXFile][nCntItem].bUse = false;		//�A�C�e��������
		}
	}

	g_nGetItem = 0;

	//�A�C�e���J�E���^�[�����Z�b�g����
	ResetItemCnt();
}

//=============================================================================
// �A�C�e���̑������擾
//=============================================================================
int GetItem(void)
{
	return g_nGetItem;
}