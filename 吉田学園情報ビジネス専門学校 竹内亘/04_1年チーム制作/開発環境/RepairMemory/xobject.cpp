//=========================================================================================================================
//
// �I�u�W�F�N�g���� [xobject.cpp]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS		// scanf�G���[����
#include <stdio.h>					// stdio
#include "xobject.h"
#include "shadow.h"
#include "meshfield.h"
#include "camera.h"
#include "questfade.h"
#include "time.h"
#include "input.h"
#include "flontpolygon.h"
#include "sound.h"
#include "game.h"
#include "effect.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_XOBJECT				(32)						// �I�u�W�F�N�g�̍ő吔
#define MAX_XOBJECT_NUM			(64)						// �e�I�u�W�F�N�g�̍ő吔
#define XOBJECT_UPSPPED			(0.7f)						// �I�u�W�F�N�g�������x
#define XOBJECT_DOWNSPPED		(0.2f)						// �I�u�W�F�N�g�������x

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef struct
{
	char cLoadName[XOBJECT_TEXT_NAME];
	int nCntXObject;
	int nCntXObjectModel;
	bool bLoad;
}LOADMODEL;

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
XOBJECTINI						g_XObjectIni[MAX_XOBJECT];
XOBJECT							g_XObject[MAX_XOBJECT][MAX_XOBJECT_NUM];
LOADMODEL						g_LoadModel[MAX_XOBJECT_NUM];
int								g_nLoadNum;
PAZZLENUM						g_PazzleNum;
int								g_MaxXObject;
int								g_PuzzleSetingNum;
int								g_PuzzleSetingTimer;
bool							g_bPuzzleSeting;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void CountPazzlemodel(int nType, int nCntXObject, int nCntXObjectModel);

//=========================================================================================================================
// �I�u�W�F�N�g�̏���������
//=========================================================================================================================
void InitXObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FILE *pFile;
	int nCntXObject, nCntXObjectModel;

	g_MaxXObject = 0;
	g_nLoadNum = 0;
	g_PuzzleSetingNum = 0;
	g_PuzzleSetingTimer = 0;
	g_bPuzzleSeting = false;

	for (int nCnt = 0; nCnt < MAX_XOBJECT_NUM; nCnt++)
	{
		g_LoadModel[nCnt].cLoadName[0] = NULL;
		g_LoadModel[nCnt].nCntXObject = 0;
		g_LoadModel[nCnt].nCntXObjectModel = 0;
		g_LoadModel[nCnt].bLoad = false;
	}

	// �t�@�C���ݒ�
	pFile = fopen(XOBJECT_TEXT_INFO, "r");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		fscanf(pFile, "%d", &g_MaxXObject);	// �ǂݍ���

		for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
		{
			fscanf(pFile, "%s", &g_XObjectIni[nCntXObject].FileName[0]);	// �ǂݍ���
		}

		fclose(pFile);	// �t�@�C�������
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		MessageBox(0, "�ݒ�t�@�C���̃`�F�b�N�Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}

	// �I�u�W�F�N�g�e�L�X�g�f�[�^�ǂݍ���
	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{
		// �t�@�C���ݒ�
		pFile = fopen(&g_XObjectIni[nCntXObject].FileName[0], "r");

		if (pFile != NULL)
		{// �t�@�C�����J�����ꍇ
			fscanf(pFile, "%d", &g_XObject[nCntXObject][0].nMaxModel);	// �ǂݍ���

			for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
			{
				fscanf(pFile, "%s", &g_XObject[nCntXObject][nCntXObjectModel].FileName[0]);	// �ǂݍ���
			}

			for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
			{
				fscanf(pFile, "%d", &g_XObject[nCntXObject][nCntXObjectModel].nOya);		// �ǂݍ���
				fscanf(pFile, "%f", &g_XObject[nCntXObject][nCntXObjectModel].Initpos.x);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XObject[nCntXObject][nCntXObjectModel].Initpos.y);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XObject[nCntXObject][nCntXObjectModel].Initpos.z);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XObject[nCntXObject][nCntXObjectModel].Initrot.x);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XObject[nCntXObject][nCntXObjectModel].Initrot.y);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XObject[nCntXObject][nCntXObjectModel].Initrot.z);	// �ǂݍ���
			}

			fclose(pFile);	// �t�@�C�������
		}
		else
		{// �t�@�C�����J���Ȃ��ꍇ
			MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s�I", "�x���I", MB_ICONWARNING);
		}
	}

	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�̃|�C���^

						// X�t�@�C���̓ǂݍ���
	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{
		for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
		{
			g_XObject[nCntXObject][nCntXObjectModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_XObject[nCntXObject][nCntXObjectModel].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_XObject[nCntXObject][nCntXObjectModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_XObject[nCntXObject][nCntXObjectModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_XObject[nCntXObject][nCntXObjectModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_XObject[nCntXObject][nCntXObjectModel].vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
			g_XObject[nCntXObject][nCntXObjectModel].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
			g_XObject[nCntXObject][nCntXObjectModel].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_XObject[nCntXObject][nCntXObjectModel].nIdxShadow = 0;
			g_XObject[nCntXObject][nCntXObjectModel].bUse = false;

			for (int nCnt = 0; nCnt < MAX_XOBJECT_NUM; nCnt++)
			{
				if (g_LoadModel[nCnt].bLoad == true && strcmp(g_LoadModel[nCnt].cLoadName, g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
				{
					strcpy(g_XObject[nCntXObject][nCntXObjectModel].FileName, g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].FileName);
					g_XObject[nCntXObject][nCntXObjectModel].pMesh = g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pMesh;
					g_XObject[nCntXObject][nCntXObjectModel].pBuffMat = g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pBuffMat;
					g_XObject[nCntXObject][nCntXObjectModel].nNumMat = g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].nNumMat;
					g_XObject[nCntXObject][nCntXObjectModel].pTexture = g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pTexture;
					g_XObject[nCntXObject][nCntXObjectModel].vtxMax = g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].vtxMax;
					g_XObject[nCntXObject][nCntXObjectModel].vtxMin = g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].vtxMin;
					break;
				}
				
				if (nCnt == MAX_XOBJECT_NUM - 1)
				{
					//if (g_XObject[nCntXObject][nCntXObjectModel].Initrot.y == 0.0f)
					{
						g_LoadModel[g_nLoadNum].bLoad = true;
						strcpy(g_LoadModel[g_nLoadNum].cLoadName, &g_XObject[nCntXObject][nCntXObjectModel].FileName[0]);
						g_LoadModel[g_nLoadNum].nCntXObject = nCntXObject;
						g_LoadModel[g_nLoadNum].nCntXObjectModel = nCntXObjectModel;
						g_nLoadNum++;
					}

					D3DXLoadMeshFromX
					(
						&g_XObject[nCntXObject][nCntXObjectModel].FileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_XObject[nCntXObject][nCntXObjectModel].pBuffMat,
						NULL,
						&g_XObject[nCntXObject][nCntXObjectModel].nNumMat,
						&g_XObject[nCntXObject][nCntXObjectModel].pMesh
					);

					D3DXMATERIAL *pmat;							// �}�e���A���f�[�^�ւ̃|�C���^
					D3DMATERIAL9 *matDef;						// ���݂̃}�e���A���ۑ��p
					pmat = (D3DXMATERIAL*)g_XObject[nCntXObject][nCntXObjectModel].pBuffMat->GetBufferPointer();
					matDef = new D3DMATERIAL9[g_XObject[nCntXObject][nCntXObjectModel].nNumMat];
					g_XObject[nCntXObject][nCntXObjectModel].pTexture = new LPDIRECT3DTEXTURE9[g_XObject[nCntXObject][nCntXObjectModel].nNumMat];

					for (DWORD tex = 0; tex < g_XObject[nCntXObject][nCntXObjectModel].nNumMat; tex++)
					{
						matDef[tex] = pmat[tex].MatD3D;
						matDef[tex].Ambient = matDef[tex].Diffuse;
						g_XObject[nCntXObject][nCntXObjectModel].pTexture[tex] = NULL;
						if (pmat[tex].pTextureFilename != NULL &&
							lstrlen(pmat[tex].pTextureFilename) > 0)
						{
							if (FAILED(D3DXCreateTextureFromFile(pDevice,
								pmat[tex].pTextureFilename,
								&g_XObject[nCntXObject][nCntXObjectModel].pTexture[tex])))
							{
								MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
							}
						}
					}

					// ���_���̎擾
					nNumVtx = g_XObject[nCntXObject][nCntXObjectModel].pMesh->GetNumVertices();

					// ���_�t�H�[�}�b�g�̃T�C�Y���擾
					sizeFVF = D3DXGetFVFVertexSize(g_XObject[nCntXObject][nCntXObjectModel].pMesh->GetFVF());

					// ���_�o�b�t�@�����b�N
					g_XObject[nCntXObject][nCntXObjectModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

					for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
					{
						D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��

						if (vtx.x > g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x)
						{
							g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x = vtx.x;
						}
						if (vtx.y > g_XObject[nCntXObject][nCntXObjectModel].vtxMax.y)
						{
							g_XObject[nCntXObject][nCntXObjectModel].vtxMax.y = vtx.y;
						}
						if (vtx.z > g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z)
						{
							g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z = vtx.z;
						}

						if (vtx.x < g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x)
						{
							g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x = vtx.x;
						}
						if (vtx.y < g_XObject[nCntXObject][nCntXObjectModel].vtxMin.y)
						{
							g_XObject[nCntXObject][nCntXObjectModel].vtxMin.y = vtx.y;
						}
						if (vtx.z < g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z)
						{
							g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z = vtx.z;
						}

						pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
					}

					// ���_�o�b�t�@���A�����b�N
					g_XObject[nCntXObject][nCntXObjectModel].pMesh->UnlockVertexBuffer();

					break;
				}
			}
		}
	}

	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{
		for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
		{
			if (strcmp("data\\MODEL\\Map\\ki.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
			{
				g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x = 15;
				g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x = -15;

				g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z = 15;
				g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z = -15;
			}
			else
			{
				if (g_XObject[nCntXObject][nCntXObjectModel].Initrot.y > 1.56f && g_XObject[nCntXObject][nCntXObjectModel].Initrot.y < 1.58f)
				{
					float frot1, frot2;

					frot1 = g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x;
					frot2 = g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x;

					g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x = g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z;
					g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x = g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z;

					g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z = -frot2;
					g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z = -frot1;
				}
				else if (g_XObject[nCntXObject][nCntXObjectModel].Initrot.y < -1.56f && g_XObject[nCntXObject][nCntXObjectModel].Initrot.y > -1.58f)
				{
					float frot1, frot2;

					frot1 = g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x;
					frot2 = g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x;

					g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x = -g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z;
					g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x = -g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z;

					g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z = frot1;
					g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z = frot2;
				}
			}
		}
	}

	for (nCntXObject = 0; nCntXObject < 8; nCntXObject++)
	{
		g_PazzleNum.modelNum[nCntXObject] = 0;
	}
}

//=========================================================================================================================
// �I�u�W�F�N�g�̏I������
//=========================================================================================================================
void UninitXObject(void)
{
	// �ϐ��錾
	//	int nCntXObject, nCntXObjectModel;

	// ���b�V���̊J��
	for (int nCnt = 0; nCnt < g_nLoadNum; nCnt++)
	{// ���f�����J�E���g
		if (g_LoadModel[nCnt].bLoad == true)
		{
			if (g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pMesh != NULL)
			{// NULL�ȊO�̏ꍇ
				g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pMesh->Release();
				g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pMesh = NULL;
			}
		}
	}

	// �}�e���A���̊J��
	for (int nCnt = 0; nCnt < g_nLoadNum; nCnt++)
	{// ���f�����J�E���g
		if (g_LoadModel[nCnt].bLoad == true)
		{
			if (g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pBuffMat != NULL)
			{// NULL�ȊO�̏ꍇ
				g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pBuffMat->Release();
				g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pBuffMat = NULL;
			}
		}
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < g_nLoadNum; nCnt++)
	{// ���f�����J�E���g
		if (g_LoadModel[nCnt].bLoad == true)
		{
			for (DWORD tex = 0; tex < g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].nNumMat; tex++)
			{// �}�e���A�����J�E���g
				if (g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pTexture[tex] != NULL)
				{// NULL�ȊO�̏ꍇ
					g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pTexture[tex]->Release();
					g_XObject[g_LoadModel[nCnt].nCntXObject][g_LoadModel[nCnt].nCntXObjectModel].pTexture[tex] = NULL;
				}
			}
		}
	}
}

//=========================================================================================================================
// �I�u�W�F�N�g�̍X�V����
//=========================================================================================================================
void UpdateXObject(void)
{
	// �ϐ��錾
	int nCntXObject, nCntXObjectModel;

	QUESTTYPE pQuestType = GetQuestType();

	Time *pTime = GetTime();

	DIMOUSESTATE2 pMouse = GetMousePointer();
	DIJOYSTATE pStick = GetStick();

	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{// �I�u�W�F�N�g���J�E���g
		for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
		{// ���f�����J�E���g

			if (g_XObject[nCntXObject][nCntXObjectModel].bUse == true)
			{// �g�p���Ă���ꍇ

				g_XObject[nCntXObject][nCntXObjectModel].posOld = g_XObject[nCntXObject][nCntXObjectModel].pos;

				if ((nCntXObject == TEXTTYPE_PUZZLE_1 || nCntXObject == TEXTTYPE_PUZZLE_2 || nCntXObject == TEXTTYPE_PUZZLE_3) && g_bPuzzleSeting == false && pTime->TimeState == TIMESTATE_NORMAL)
				{// ����p�Y���̂�
					if (g_XObject[nCntXObject][nCntXObjectModel].move.y == 0.0f)
					{
						/*if (GetKeyboardTrigger(DIK_RSHIFT) == true || pMouse.lZ != 0)
						{// ����p�Y���؂�ւ�
						g_XObject[nCntXObject][nCntXObjectModel].bUse = false;
						g_XObject[nCntXObject][(nCntXObjectModel + 1) % g_XObject[nCntXObject][0].nMaxModel].pos.x = g_XObject[nCntXObject][nCntXObjectModel].pos.x;
						g_XObject[nCntXObject][(nCntXObjectModel + 1) % g_XObject[nCntXObject][0].nMaxModel].pos.z = g_XObject[nCntXObject][nCntXObjectModel].pos.z;
						g_XObject[nCntXObject][(nCntXObjectModel + 1) % g_XObject[nCntXObject][0].nMaxModel].bUse = true;

						break;
						}*/

						// �ړ�����
						/*if (GetMousePress(0) == true)
						{
						if (pMouse.lX > 0)
						{
						g_XObject[nCntXObject][nCntXObjectModel].pos.x += (pMouse.lX / 1.0f);
						}
						if (pMouse.lX < 0)
						{
						g_XObject[nCntXObject][nCntXObjectModel].pos.x += (pMouse.lX / 1.0f);
						}
						if (pMouse.lY > 0)
						{
						g_XObject[nCntXObject][nCntXObjectModel].pos.z -= (pMouse.lY / 1.0f);
						}
						if (pMouse.lY < 0)
						{
						g_XObject[nCntXObject][nCntXObjectModel].pos.z -= (pMouse.lY / 1.0f);
						}
						}*/

						// �ړ�����
						if ((GetKeyboardPress(DIK_UP) == true || pStick.rgdwPOV[0] == 0) || pStick.lY < -300)
						{// �C�ӂ̃L�[�i���j���������ꍇ
							g_XObject[nCntXObject][nCntXObjectModel].pos.z += 5.0f;
						}
						if ((GetKeyboardPress(DIK_DOWN) == true || pStick.rgdwPOV[0] == 18000) || pStick.lY > 300)
						{// �C�ӂ̃L�[�i���j���������ꍇ
							g_XObject[nCntXObject][nCntXObjectModel].pos.z -= 5.0f;
						}
						if ((GetKeyboardPress(DIK_LEFT) == true || pStick.rgdwPOV[0] == 27000) || pStick.lX < -300)
						{// �C�ӂ̃L�[�i���j���������ꍇ
							g_XObject[nCntXObject][nCntXObjectModel].pos.x -= 5.0f;
						}
						if ((GetKeyboardPress(DIK_RIGHT) == true || pStick.rgdwPOV[0] == 9000) || pStick.lX > 300)
						{// �C�ӂ̃L�[�i���j���������ꍇ
							g_XObject[nCntXObject][nCntXObjectModel].pos.x += 5.0f;
						}

						if (pQuestType == QUESTTYPE_FIRST)
						{
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.x > 195.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.x = 195.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.x < -455.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.x = -455.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.z > 125.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.z = 125.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.z < -315.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.z = -315.0f;
							}
						}
						else if (pQuestType == QUESTTYPE_SECOND)
						{
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.x > 295.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.x = 295.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.x < -455.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.x = -455.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.z > 190.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.z = 190.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.z < -315.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.z = -315.0f;
							}
						}
						else if (pQuestType == QUESTTYPE_THIRD)
						{
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.x > 200.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.x = 200.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.x < -455.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.x = -455.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.z > 190.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.z = 190.0f;
							}
							if (g_XObject[nCntXObject][nCntXObjectModel].pos.z < -315.0f)
							{
								g_XObject[nCntXObject][nCntXObjectModel].pos.z = -315.0f;
							}
						}

						// �p�Y�����͂߂�
						if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_LCONTROL) == true || GetKeyboardTrigger(DIK_RCONTROL) == true || GetButtonTrigger(2) == true/* || GetMouseTrigger(1) == true*/)
						{// �C�ӂ̃L�[�i�ECTRL�j���������ꍇ
							g_XObject[nCntXObject][nCntXObjectModel].move.y -= 8.0f;
						}
					}

					if (g_XObject[nCntXObject][nCntXObjectModel].vtxMax.y > g_XObject[nCntXObject][nCntXObjectModel].pos.y)
					{
						g_XObject[nCntXObject][nCntXObjectModel].move.y = 0.0f;
						g_XObject[nCntXObject][nCntXObjectModel].pos.y = g_XObject[nCntXObject][0].Initpos.y;

						if (PuzzleSeting(&g_XObject[nCntXObject][nCntXObjectModel].FileName[0], &g_XObject[nCntXObject][nCntXObjectModel].pos, &g_XObject[nCntXObject][nCntXObjectModel].vtxMin, &g_XObject[nCntXObject][nCntXObjectModel].vtxMax) == true)
						{// �S�Ă͂߂��ꍇ
						 //SetFadeMode(MODE_RESULT);
							g_XObject[nCntXObject][nCntXObjectModel].move.y = 5.0f;
							g_bPuzzleSeting = true;

							SetTimeState(TIMESTATE_ADD);
						}
					}

					g_XObject[nCntXObject][nCntXObjectModel].pos += g_XObject[nCntXObject][nCntXObjectModel].move;
				}
				else if ((nCntXObject == TEXTTYPE_PUZZLE_1 || nCntXObject == TEXTTYPE_PUZZLE_2 || nCntXObject == TEXTTYPE_PUZZLE_3) && g_bPuzzleSeting == true)
				{
					if (g_XObject[nCntXObject][nCntXObjectModel].pos.y < 1000.0f)
					{
						g_XObject[nCntXObject][nCntXObjectModel].pos += g_XObject[nCntXObject][nCntXObjectModel].move;
					}
				}

				if ((nCntXObject == TEXTTYPE_PUZZLE_1_A || nCntXObject == TEXTTYPE_PUZZLE_2_A || nCntXObject == TEXTTYPE_PUZZLE_3_A) && g_bPuzzleSeting == true)
				{
					g_PuzzleSetingTimer++;

					if (g_PuzzleSetingTimer > 600)
					{
						if (strcmp("data\\MODEL\\Pazzle\\zenmai.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
						{
							g_XObject[nCntXObject][nCntXObjectModel].rot.z -= 0.01f;
						}
						else if (strcmp("data\\MODEL\\Pazzle\\MBSPIN.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
						{
							g_XObject[nCntXObject][nCntXObjectModel].rot.x += 0.05f;
						}
						else if (strcmp("data\\MODEL\\Pazzle\\MBDown.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
						{

						}
						else
						{
							if (nCntXObjectModel % 2 == 0)
							{
								if (strcmp("data\\MODEL\\Pazzle\\gear0001.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
									strcmp("data\\MODEL\\Pazzle\\gear0101.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
									strcmp("data\\MODEL\\Pazzle\\gear0201.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
									strcmp("data\\MODEL\\Pazzle\\gear0301.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
								{
									g_XObject[nCntXObject][nCntXObjectModel].rot.y -= 0.0334f;
								}
								else
								{
									g_XObject[nCntXObject][nCntXObjectModel].rot.y -= 0.05f;
								}
							}
							else
							{
								if (strcmp("data\\MODEL\\Pazzle\\gear0001.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
									strcmp("data\\MODEL\\Pazzle\\gear0101.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
									strcmp("data\\MODEL\\Pazzle\\gear0201.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
									strcmp("data\\MODEL\\Pazzle\\gear0301.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
								{
									g_XObject[nCntXObject][nCntXObjectModel].rot.y += 0.0334f;
								}
								else
								{
									g_XObject[nCntXObject][nCntXObjectModel].rot.y += 0.05f;
								}
							}
						}
					}

					if (g_PuzzleSetingTimer == 3000)
					{
						SetQuestFade(QUESTSTATE_REPORT);
					}
				}

				if (nCntXObject == TEXTTYPE_PUZZLE_1 || nCntXObject == TEXTTYPE_PUZZLE_2 || nCntXObject == TEXTTYPE_PUZZLE_3)
				{// ����p�Y���̂�
					SetPostionShadow(g_XObject[nCntXObject][0].nIdxShadow, g_XObject[nCntXObject][nCntXObjectModel].pos, g_XObject[nCntXObject][nCntXObjectModel].posOld);
				}
			}
		}
	}
}

//=========================================================================================================================
// �I�u�W�F�N�g�̕`�揈��
//=========================================================================================================================
void DrawXObject(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pmat;							// �}�e���A���f�[�^�ւ̃|�C���^
	int nCntXObject, nCntXObjectModel;

	MeshField *pMeshField = GetMeshField();

	// �A���t�@�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{// �I�u�W�F�N�g���J�E���g
		for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
		{// ���f�����J�E���g
			if (g_XObject[nCntXObject][nCntXObjectModel].bUse == true)
			{// �g�p���Ă���ꍇ
				if (g_XObject[nCntXObject][nCntXObjectModel].nOya < 0)
				{
					// ���[���h�}�g���b�N�X�̏�����
					D3DXMatrixIdentity(&g_XObject[nCntXObject][nCntXObjectModel].mtxWorld);
				}
				else
				{
					g_XObject[nCntXObject][nCntXObjectModel].mtxWorld = g_XObject[nCntXObject][g_XObject[nCntXObject][nCntXObjectModel].nOya].mtxWorld;
				}

				if (nCntXObject == TEXTTYPE_SEARCH_HOUSE_0 || nCntXObject == TEXTTYPE_SEARCH_HOUSE_1 || nCntXObject == TEXTTYPE_SEARCH_HOUSE_2 ||
					nCntXObject == TEXTTYPE_SEARCH_HOUSE_3 || nCntXObject == TEXTTYPE_SEARCH_HOUSE_4 || nCntXObject == TEXTTYPE_SEARCH_HOUSE_5 ||
					nCntXObject == TEXTTYPE_SEARCH_HOUSE_6 || nCntXObject == TEXTTYPE_SEARCH_HOUSE_7 || nCntXObject == TEXTTYPE_SEARCH_HOUSE_8)
				{
					//g_XObject[nCntXObject][nCntXObjectModel].mtxWorld = pMeshField[8].mtxWorld;
				}

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll
				(
					&mtxRot,
					g_XObject[nCntXObject][nCntXObjectModel].rot.y,
					g_XObject[nCntXObject][nCntXObjectModel].rot.x,
					g_XObject[nCntXObject][nCntXObjectModel].rot.z
				);

				D3DXMatrixMultiply
				(
					&g_XObject[nCntXObject][nCntXObjectModel].mtxWorld,
					&g_XObject[nCntXObject][nCntXObjectModel].mtxWorld,
					&mtxRot
				);

				// �ʒu�𔽉f
				D3DXMatrixTranslation
				(
					&mtxTrans,
					g_XObject[nCntXObject][nCntXObjectModel].pos.x,
					g_XObject[nCntXObject][nCntXObjectModel].pos.y,
					g_XObject[nCntXObject][nCntXObjectModel].pos.z
				);

				D3DXMatrixMultiply
				(
					&g_XObject[nCntXObject][nCntXObjectModel].mtxWorld,
					&g_XObject[nCntXObject][nCntXObjectModel].mtxWorld,
					&mtxTrans
				);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_XObject[nCntXObject][nCntXObjectModel].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pmat = (D3DXMATERIAL*)g_XObject[nCntXObject][nCntXObjectModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_XObject[nCntXObject][nCntXObjectModel].nNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					//if (nCntXObject == TEXTTYPE_PUZZLE_A)
					{// �𓚃p�Y���̂�
						pmat[nCntMat].MatD3D.Diffuse.a = g_XObject[nCntXObject][nCntXObjectModel].col.a;
					}
					pDevice->SetMaterial(&pmat[nCntMat].MatD3D);

					// �e�N�X�`���ݒ�
					pDevice->SetTexture(0, g_XObject[nCntXObject][nCntXObjectModel].pTexture[nCntMat]);

					// �I�u�W�F�N�g(�p�[�c)�̕`��
					g_XObject[nCntXObject][nCntXObjectModel].pMesh->DrawSubset(nCntMat);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}

	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=========================================================================================================================
// �I�u�W�F�N�g�̐ݒ菈��
//=========================================================================================================================
void SetXObject(TEXTTYPE type)
{
	// �ϐ��錾
	int nCntXObjectModel;
	MeshField *pMeshField = GetMeshField();

	for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[type][0].nMaxModel; nCntXObjectModel++)
	{// ���f�����J�E���g
		if (g_XObject[type][nCntXObjectModel].bUse == false)
		{// �g�p���Ă���ꍇ
			g_XObject[type][nCntXObjectModel].pos = g_XObject[type][nCntXObjectModel].Initpos;
			g_XObject[type][nCntXObjectModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_XObject[type][nCntXObjectModel].rot = g_XObject[type][nCntXObjectModel].Initrot;

			if (type == TEXTTYPE_SEARCH_HOUSE_0 || type == TEXTTYPE_SEARCH_HOUSE_1 || type == TEXTTYPE_SEARCH_HOUSE_2 ||
				type == TEXTTYPE_SEARCH_HOUSE_3 || type == TEXTTYPE_SEARCH_HOUSE_4 || type == TEXTTYPE_SEARCH_HOUSE_5 ||
				type == TEXTTYPE_SEARCH_HOUSE_6 || type == TEXTTYPE_SEARCH_HOUSE_7 || type == TEXTTYPE_SEARCH_HOUSE_8)
			{
				g_XObject[type][nCntXObjectModel].pos += pMeshField[type].pos;
			}

			if (type == TEXTTYPE_PUZZLE_1 || type == TEXTTYPE_PUZZLE_2 || type == TEXTTYPE_PUZZLE_3)
			{// ����p�Y���̂�
				if (nCntXObjectModel == 0)
				{// 1�ڂ����f���̂�
					g_XObject[type][nCntXObjectModel].nIdxShadow = SetShadow(g_XObject[type][nCntXObjectModel].pos, g_XObject[type][nCntXObjectModel].rot, 50, 50);
				}
			}
			//else if (type != TEXTTYPE_PUZZLE_1_A || type != TEXTTYPE_PUZZLE_2_A || type != TEXTTYPE_PUZZLE_3_A)
			{// �𓚃p�Y���ȊO
			 //g_XObject[type][nCntXObjectModel].nIdxShadow = SetShadow(g_XObject[type][nCntXObjectModel].pos, g_XObject[type][nCntXObjectModel].rot, g_XObject[type][nCntXObjectModel].vtxMax);
			}

			if (type == TEXTTYPE_PUZZLE_1_A || type == TEXTTYPE_PUZZLE_2_A || type == TEXTTYPE_PUZZLE_3_A)
			{// �𓚃p�Y���̂�
				g_XObject[type][nCntXObjectModel].col.a = 0.5f;

				CountPazzlemodel(0, type, nCntXObjectModel);
			}
			else
			{
				g_XObject[type][nCntXObjectModel].col.a = 1.0f;
			}

			if (type == TEXTTYPE_PUZZLE_1 || type == TEXTTYPE_PUZZLE_2 || type == TEXTTYPE_PUZZLE_3)
			{// ����p�Y���̂�
				if (nCntXObjectModel == 0)
				{// 1�ڂ̃��f���̂�
					g_XObject[type][nCntXObjectModel].bUse = true;
				}
				else
				{// ���̑�
					g_XObject[type][nCntXObjectModel].bUse = false;
				}
			}
			else
			{// ���̑�
				g_XObject[type][nCntXObjectModel].bUse = true;
			}
		}
	}
}

//=========================================================================================================================
// �I�u�W�F�N�g�̎擾����
//=========================================================================================================================
XOBJECT *GetXObject(void)
{
	return &g_XObject[0][0];
}

//=========================================================================================================================
// �I�u�W�F�N�g�̏Փˏ���
//=========================================================================================================================
bool CollisionXObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax)
{
	// �ϐ��錾
	int nCntXObject, nCntXObjectModel;
	bool bLand = false;

	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{// �I�u�W�F�N�g���J�E���g
		for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
		{// ���f�����J�E���g
			if (g_XObject[nCntXObject][nCntXObjectModel].bUse == true)
			{// �g�p����Ă���
			 //if (pPos->y + vtxMax->y > g_XObject[nCntXObject][nCntXObjectModel].pos.y + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.y && pPos->y + vtxMin->y < g_XObject[nCntXObject][nCntXObjectModel].pos.y + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.y)
				{// X�͈͊m�F
					if (pPos->x + vtxMax->x > g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x && pPos->x + vtxMin->x < g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x)
					{// X�͈͊m�F
						if (pPosOld->z + vtxMin->z >= g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z && g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z >= pPos->z + vtxMin->z)
						{// Z��ꔻ��
							pPos->z = g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z - vtxMin->z;
							//pMove->x = 0.0f;
							//pMove->z = 0.0f;
						}
						else if (pPosOld->z + vtxMax->z <= g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z && g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z <= pPos->z + vtxMax->z)
						{// Z���ꔻ��
							pPos->z = g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z - vtxMax->z;
							//pMove->x = 0.0f;
							//pMove->z = 0.0f;
						}
					}

					if (pPos->z + vtxMax->z > g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z && pPos->z + vtxMin->z < g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z)
					{// Z�͈͊m�F
						if (pPosOld->x + vtxMin->x >= g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x && g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x >= pPos->x + vtxMin->x)
						{// X�E�Ӕ���
							pPos->x = g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x - vtxMin->x;
							//pMove->x = 0.0f;
							//pMove->z = 0.0f;
						}
						else if (pPosOld->x + vtxMax->x <= g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x && g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x <= pPos->x + vtxMax->x)
						{// X���Ӕ���
							pPos->x = g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x - vtxMax->x;
							//pMove->x = 0.0f;
							//pMove->z = 0.0f;
						}
					}
				}

				/*if (pPos->x + vtxMax->x > g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x && pPos->x + vtxMin->x < g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x)
				{// X�͈͊m�F
				if (pPos->z + vtxMax->z > g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z && pPos->z + vtxMin->z < g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z)
				{// Z�͈͊m�F
				if (pPosOld->y + vtxMin->y >= g_XObject[nCntXObject][nCntXObjectModel].pos.y + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.y && g_XObject[nCntXObject][nCntXObjectModel].pos.y + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.y > pPos->y + vtxMin->y)
				{// X�E�Ӕ���
				pPos->y = g_XObject[nCntXObject][nCntXObjectModel].pos.y + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.y - vtxMin->y;
				//pMove->x = 0.0f;
				//pMove->z = 0.0f;
				}
				else if (pPosOld->y + vtxMax->y <= g_XObject[nCntXObject][nCntXObjectModel].pos.y + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.y && g_XObject[nCntXObject][nCntXObjectModel].pos.y + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.y < pPos->x + vtxMax->y)
				{// X���Ӕ���
				pPos->y = g_XObject[nCntXObject][nCntXObjectModel].pos.y + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.y - vtxMax->y;
				//pMove->x = 0.0f;
				//pMove->z = 0.0f;
				}
				}
				}*/
			}
		}
	}

	return bLand;
}

//=========================================================================================================================
// �p�Y���ݒ菈��
//=========================================================================================================================
bool PuzzleSeting(char *pName, D3DXVECTOR3 *pPos, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax)
{
	// �ϐ��錾
	int nCntXObject, nCntXObjectModel;
	bool bLand = false;

	int nCountPazzleNum = g_PuzzleSetingNum;

	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{// �I�u�W�F�N�g���J�E���g
		for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
		{// ���f�����J�E���g
			if (g_XObject[nCntXObject][nCntXObjectModel].bUse == true && (nCntXObject == TEXTTYPE_PUZZLE_1_A || nCntXObject == TEXTTYPE_PUZZLE_2_A || nCntXObject == TEXTTYPE_PUZZLE_3_A) &&
				strcmp(pName, g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 && g_XObject[nCntXObject][nCntXObjectModel].col.a != 1.0f)
			{// �g�p����Ă���A�𓚃p�Y���ł���A�f�[�^�p�X������A���l��1.0f�łȂ��ꍇ
				if (g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.x < pPos->x + (vtxMin->x / 2.0f) &&
					g_XObject[nCntXObject][nCntXObjectModel].pos.x + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.x > pPos->x + (vtxMax->x / 2.0f) &&
					g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMin.z < pPos->z + (vtxMin->z / 2.0f) &&
					g_XObject[nCntXObject][nCntXObjectModel].pos.z + g_XObject[nCntXObject][nCntXObjectModel].vtxMax.z > pPos->z + (vtxMax->z / 2.0f))
				{
					PlaySound(SOUND_LABEL_SE_GEAR);

					g_PuzzleSetingNum++;	//
					CountPazzlemodel(1, nCntXObject, nCntXObjectModel);

					//SetParticleEffect(g_XObject[nCntXObject][nCntXObjectModel].pos, EFFECTTYPE_EXPLOSION, 30, 30, 30, 0);
					SetRainEffect(g_XObject[nCntXObject][nCntXObjectModel].pos, EFFECTTYPE_RESURRECTIONWATER_1, 30, 30, 0, 0);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ�	/����

					g_XObject[nCntXObject][nCntXObjectModel].col.a = 1.0f;

					if (g_PuzzleSetingNum == g_XObject[nCntXObject][0].nMaxModel)
					{
						SetFlontPolygon(FLONTPOLYGONTEXTURE_PAZZLE_END, D3DXVECTOR3(SCREEN_WIDTH + 400, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 700, 300);

						PlaySound(SOUND_LABEL_SE_PAZZLEEND);

						bLand = true;
					}
					break;
				}
			}
		}
	}

	if (nCountPazzleNum == g_PuzzleSetingNum)
	{
		PlaySound(SOUND_LABEL_SE_MISS);
	}

	return bLand;
}

//=========================================================================================================================
// �ړ��p�Y���ݒ菈��
//=========================================================================================================================
void SetMovePazzelObj(int nNum)
{
	// �ϐ��錾
	int nCntXObject, nCntXObjectModel;

	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{// �I�u�W�F�N�g���J�E���g
		for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
		{// ���f�����J�E���g
			if (g_XObject[nCntXObject][nCntXObjectModel].bUse == true)
			{// �g�p���Ă���ꍇ
				if ((nCntXObject == TEXTTYPE_PUZZLE_1 || nCntXObject == TEXTTYPE_PUZZLE_2 || nCntXObject == TEXTTYPE_PUZZLE_3) && g_bPuzzleSeting == false)
				{// ����p�Y���̂�
					g_XObject[nCntXObject][nCntXObjectModel].bUse = false;
					g_XObject[nCntXObject][(nNum)].pos.x = g_XObject[nCntXObject][nCntXObjectModel].pos.x;
					g_XObject[nCntXObject][(nNum)].pos.z = g_XObject[nCntXObject][nCntXObjectModel].pos.z;
					g_XObject[nCntXObject][(nNum)].bUse = true;
				}
			}
		}
	}
}

//=========================================================================================================================
// �p�Y�����擾����
//=========================================================================================================================
PAZZLENUM *GetPazzleNum(void)
{
	return &g_PazzleNum;
}

//=========================================================================================================================
// �p�Y�����m�F����
//=========================================================================================================================
void CountPazzlemodel(int nType, int nCntXObject, int nCntXObjectModel)
{
	switch (nType)
	{
	case 0:

		if (strcmp("data\\MODEL\\Pazzle\\gear0000.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[0]++;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0100.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[1]++;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0200.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[2]++;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0300.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[3]++;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0001.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[4]++;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0101.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[5]++;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0201.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
			strcmp("data\\MODEL\\Pazzle\\MBSPIN.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[6]++;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0301.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
			strcmp("data\\MODEL\\Pazzle\\MBDown.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
			strcmp("data\\MODEL\\Pazzle\\zenmai.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[7]++;
		}

		break;
	case 1:

		if (strcmp("data\\MODEL\\Pazzle\\gear0000.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[0]--;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0100.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[1]--;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0200.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[2]--;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0300.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[3]--;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0001.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[4]--;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0101.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[5]--;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0201.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
			strcmp("data\\MODEL\\Pazzle\\MBSPIN.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[6]--;
		}
		else if (strcmp("data\\MODEL\\Pazzle\\gear0301.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
			strcmp("data\\MODEL\\Pazzle\\MBDown.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0 ||
			strcmp("data\\MODEL\\Pazzle\\zenmai.x", g_XObject[nCntXObject][nCntXObjectModel].FileName) == 0)
		{
			g_PazzleNum.modelNum[7]--;
		}

		break;
	}
}

//=========================================================================================================================
// �I�u�W�F�N�g������
//=========================================================================================================================
void DeleteXObject(void)
{
	// �ϐ��錾
	int nCntXObject, nCntXObjectModel;

	for (nCntXObject = 0; nCntXObject < g_MaxXObject; nCntXObject++)
	{// �I�u�W�F�N�g���J�E���g
		for (nCntXObjectModel = 0; nCntXObjectModel < g_XObject[nCntXObject][0].nMaxModel; nCntXObjectModel++)
		{// ���f�����J�E���g
			if (g_XObject[nCntXObject][nCntXObjectModel].bUse == true)
			{
				g_XObject[nCntXObject][nCntXObjectModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_XObject[nCntXObject][nCntXObjectModel].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_XObject[nCntXObject][nCntXObjectModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_XObject[nCntXObject][nCntXObjectModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_XObject[nCntXObject][nCntXObjectModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_XObject[nCntXObject][nCntXObjectModel].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				g_XObject[nCntXObject][nCntXObjectModel].nIdxShadow = 0;
				g_XObject[nCntXObject][nCntXObjectModel].bUse = false;

				DeleteShadow(g_XObject[nCntXObject][nCntXObjectModel].nIdxShadow);
			}
		}
	}
	g_PuzzleSetingNum = 0;
	g_PuzzleSetingTimer = 0;
	g_bPuzzleSeting = false;
}
void DeleteXObject(int nCntXObject, int nCntXObjectModel)
{
	if (g_XObject[nCntXObject][nCntXObjectModel].bUse == true)
	{
		g_XObject[nCntXObject][nCntXObjectModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XObject[nCntXObject][nCntXObjectModel].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XObject[nCntXObject][nCntXObjectModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XObject[nCntXObject][nCntXObjectModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XObject[nCntXObject][nCntXObjectModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XObject[nCntXObject][nCntXObjectModel].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_XObject[nCntXObject][nCntXObjectModel].nIdxShadow = 0;
		g_XObject[nCntXObject][nCntXObjectModel].bUse = false;

		DeleteShadow(g_XObject[nCntXObject][nCntXObjectModel].nIdxShadow);
	}
}