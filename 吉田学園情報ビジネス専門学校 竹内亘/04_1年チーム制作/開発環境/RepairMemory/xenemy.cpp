//=========================================================================================================================
//
// �G���� [xenemy.cpp]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS		// scanf�G���[����
#include <stdio.h>					// stdio
#include "xenemy.h"
#include "xobject.h"
#include "xplayer.h"
#include "meshfield.h"
#include "shadow.h"
#include "camera.h"
#include "mark.h"
#include "fade.h"
#include "input.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_XENEMY				(10)						// �G�̍ő吔
#define MAX_XENEMY_NUM			(16)						// �e�G�̍ő吔
#define XENEMY_UPSPPED			(0.3f)						// �G�������x
#define XENEMY_DOWNSPPED		(0.15f)						// �G�������x

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
XENEMYINI						g_XEnemyIni[MAX_XENEMY];
XENEMY							g_XEnemy[MAX_XENEMY][MAX_XENEMY_NUM];		// �G���
int								g_XEnemyNum;

//=========================================================================================================================
// �G�̏���������
//=========================================================================================================================
void InitXEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FILE *pFile;
	int nCntXEnemy, nCntXEnemyParts;

	// �t�@�C���ݒ�
	pFile = fopen(XENEMY_TEXT_INFO, "r");

	// �G�e�L�X�g�f�[�^�ǂݍ���
	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		fscanf(pFile, "%d", &g_XEnemyNum);	// �ǂݍ���

		for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
		{
			fscanf(pFile, "%d", &g_XEnemyIni[nCntXEnemy].nSetNum);		// �ǂݍ���
			fscanf(pFile, "%s", &g_XEnemyIni[nCntXEnemy].FileName[0]);	// �ǂݍ���
		}

		fclose(pFile);	// �t�@�C�������
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		MessageBox(0, "�ݒ�t�@�C���̃`�F�b�N�Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}

	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		// �t�@�C���ݒ�
		pFile = fopen(&g_XEnemyIni[nCntXEnemy].FileName[0], "r");

		// �G�e�L�X�g�f�[�^�ǂݍ���
		if (pFile != NULL)
		{// �t�@�C�����J�����ꍇ
			fscanf(pFile, "%d", &g_XEnemy[nCntXEnemy][0].nMaxPartsNum);	// �ǂݍ���

			for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][0].nMaxPartsNum; nCntXEnemyParts++)
			{
				fscanf(pFile, "%s", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].FileName[0]);	// �ǂݍ���
			}

			for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][0].nMaxPartsNum; nCntXEnemyParts++)
			{
				fscanf(pFile, "%d", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].nIndexParent);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].Initpos.x);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].Initpos.y);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].Initpos.z);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].Initrot.x);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].Initrot.y);	// �ǂݍ���
				fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].Initrot.z);	// �ǂݍ���
			}

			fscanf(pFile, "%d", &g_XEnemy[nCntXEnemy][0].nMaxAnimNum);	// �ǂݍ���

			for (int nCntXEnemyPartsAnim = 0; nCntXEnemyPartsAnim < g_XEnemy[nCntXEnemy][0].nMaxAnimNum; nCntXEnemyPartsAnim++)
			{
				fscanf(pFile, "%d", &g_XEnemy[nCntXEnemy][0].nAnimloop[nCntXEnemyPartsAnim]);				// �ǂݍ���
				fscanf(pFile, "%d", &g_XEnemy[nCntXEnemy][0].nAnimkey[nCntXEnemyPartsAnim]);				// �ǂݍ���

				for (int nCntXEnemyPartsAnimKey = 0; nCntXEnemyPartsAnimKey < g_XEnemy[nCntXEnemy][0].nAnimkey[nCntXEnemyPartsAnim]; nCntXEnemyPartsAnimKey++)
				{
					fscanf(pFile, "%d", &g_XEnemy[nCntXEnemy][0].nAnimfram[nCntXEnemyPartsAnim][nCntXEnemyPartsAnimKey]);			// �ǂݍ���

					for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][0].nMaxPartsNum; nCntXEnemyParts++)
					{
						fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].posAnim[nCntXEnemyPartsAnim][nCntXEnemyPartsAnimKey].x);	// �ǂݍ���
						fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].posAnim[nCntXEnemyPartsAnim][nCntXEnemyPartsAnimKey].y);	// �ǂݍ���
						fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].posAnim[nCntXEnemyPartsAnim][nCntXEnemyPartsAnimKey].z);	// �ǂݍ���
						fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].rotAnim[nCntXEnemyPartsAnim][nCntXEnemyPartsAnimKey].x);	// �ǂݍ���
						fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].rotAnim[nCntXEnemyPartsAnim][nCntXEnemyPartsAnimKey].y);	// �ǂݍ���
						fscanf(pFile, "%f", &g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].rotAnim[nCntXEnemyPartsAnim][nCntXEnemyPartsAnimKey].z);	// �ǂݍ���
					}
				}
			}

			fclose(pFile);	// �t�@�C�������
		}
		else
		{// �t�@�C�����J���Ȃ��ꍇ
			MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s�I", "�x���I", MB_ICONWARNING);
		}
	}

	// X�t�@�C���̓ǂݍ���
	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][0].nMaxPartsNum; nCntXEnemyParts++)
		{
			D3DXLoadMeshFromX
			(
				&g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].FileName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pBuffMat,
				NULL,
				&g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].nNumMat,
				&g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pMesh
			);
		}
	}

	// �ʒu�E�����̏����ݒ�
	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		g_XEnemy[nCntXEnemy][0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XEnemy[nCntXEnemy][0].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XEnemy[nCntXEnemy][0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XEnemy[nCntXEnemy][0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XEnemy[nCntXEnemy][0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XEnemy[nCntXEnemy][0].vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
		g_XEnemy[nCntXEnemy][0].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
		g_XEnemy[nCntXEnemy][0].nCntTimerand = 0;
		g_XEnemy[nCntXEnemy][0].nCntTime = 0;
		g_XEnemy[nCntXEnemy][0].nAnimnow = ENEMYANIM_NEUTRAL;
		g_XEnemy[nCntXEnemy][0].nAnimChange = 0;
		g_XEnemy[nCntXEnemy][0].nAnimkeynow = 0;
		g_XEnemy[nCntXEnemy][0].nIdxShadow = 0;
		g_XEnemy[nCntXEnemy][0].nIdxMark = 0;
		g_XEnemy[nCntXEnemy][0].bIdxMarkUse = false;
		g_XEnemy[nCntXEnemy][0].bAttack = false;
		g_XEnemy[nCntXEnemy][0].bUse = false;

		for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][0].nMaxPartsNum; nCntXEnemyParts++)
		{
			g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pos = g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].Initpos;
			g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].rot = g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].rotAnim[0][0];
			g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
			g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
		}
	}

	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�̃|�C���^

	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][0].nMaxPartsNum; nCntXEnemyParts++)
		{
			// ���_���̎擾
			nNumVtx = g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pMesh->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pMesh->GetFVF());

			// ���_�o�b�t�@�����b�N
			g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��
				{
					if (vtx.x > g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMax.x)
					{
						g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMax.x = vtx.x;
					}
					if (vtx.y > g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMax.y)
					{
						g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMax.y = vtx.y;
					}
					if (vtx.z > g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMax.z)
					{
						g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMax.z = vtx.z;
					}

					if (vtx.x < g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMin.x)
					{
						g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMin.x = vtx.x;
					}
					if (vtx.y < g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMin.y)
					{
						g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMin.y = vtx.y;
					}
					if (vtx.z < g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMin.z)
					{
						g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].vtxMin.z = vtx.z;
					}
				}

				pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
			}

			// ���_�o�b�t�@���A�����b�N
			g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pMesh->UnlockVertexBuffer();
		}
	}

	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		g_XEnemy[nCntXEnemy][0].vtxMin.x = -20.0f;
		g_XEnemy[nCntXEnemy][0].vtxMin.y = 0.0f;
		g_XEnemy[nCntXEnemy][0].vtxMin.z = -20.0f;
		g_XEnemy[nCntXEnemy][0].vtxMax.x = 20.0f;

		if (g_XEnemy[nCntXEnemy][0].nMaxPartsNum == 10)
		{
			g_XEnemy[nCntXEnemy][0].vtxMax.y = g_XEnemy[nCntXEnemy][0].aModel[0].pos.y + g_XEnemy[nCntXEnemy][0].aModel[1].pos.y + g_XEnemy[nCntXEnemy][0].aModel[1].vtxMax.y;
		}
		else if (g_XEnemy[nCntXEnemy][0].nMaxPartsNum == 15)
		{
			g_XEnemy[nCntXEnemy][0].vtxMax.y = g_XEnemy[nCntXEnemy][0].aModel[0].pos.y + g_XEnemy[nCntXEnemy][0].aModel[1].pos.y + g_XEnemy[nCntXEnemy][0].aModel[2].pos.y + g_XEnemy[nCntXEnemy][0].aModel[2].vtxMax.y;
		}
		g_XEnemy[nCntXEnemy][0].vtxMax.z = 20.0f;

		for (int nCntXEnemyNum = 1; nCntXEnemyNum < g_XEnemyIni[nCntXEnemy].nSetNum; nCntXEnemyNum++)
		{
			g_XEnemy[nCntXEnemy][nCntXEnemyNum] = g_XEnemy[nCntXEnemy][0];
		}
	}
}

//=========================================================================================================================
// �G�̏I������
//=========================================================================================================================
void UninitXEnemy(void)
{
	// �ϐ��錾
	int nCntXEnemy;
	int nCntXEnemyParts;

	// ���b�V���̊J��
	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][0].nMaxPartsNum; nCntXEnemyParts++)
		{
			if (g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pMesh != NULL)
			{
				g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pMesh->Release();
				g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pMesh = NULL;
			}
		}
	}

	// �}�e���A���̊J��
	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][0].nMaxPartsNum; nCntXEnemyParts++)
		{
			if (g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pBuffMat != NULL)
			{
				g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pBuffMat->Release();
				g_XEnemy[nCntXEnemy][0].aModel[nCntXEnemyParts].pBuffMat = NULL;
			}
		}
	}
}

//=========================================================================================================================
// �G�̍X�V����
//=========================================================================================================================
void UpdateXEnemy(void)
{
	int nCntXEnemy;
	Camera *pCamera = GetCamera();
	XPLAYER *pXPlayer = GetXPlayer();
	float fDiff = 0.0f;
	float frac = 0.0f;
	int nCntXEnemyParts;

	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		for (int nCntXEnemyNum = 0; nCntXEnemyNum < g_XEnemyIni[nCntXEnemy].nSetNum; nCntXEnemyNum++)
		{
			if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].bUse == true)
			{
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime++;

				g_XEnemy[nCntXEnemy][nCntXEnemyNum].posOld = g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos;

				/*if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTimerand == 0)
				{
					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow != ENEMYANIM_WALK)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow = ENEMYANIM_WALK;
					}

					g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y += D3DX_PI / 200.0f;

					g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.x -= sinf(D3DX_PI * 0.0f + g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y) * XENEMY_UPSPPED;
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.z -= cosf(D3DX_PI * 0.0f + g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y) * XENEMY_UPSPPED;
				}*/

				// �ړ��l���
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos += g_XEnemy[nCntXEnemy][nCntXEnemyNum].move;

				// ��������
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.x += (0.0f - g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.x) * XENEMY_DOWNSPPED;
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.z += (0.0f - g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.z) * XENEMY_DOWNSPPED;

				{
					// �ڕW��������
					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y > D3DX_PI)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y -= D3DX_PI * 2.0f;
					}
					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y < -D3DX_PI)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y += D3DX_PI * 2.0f;
					}
					// �����ݒ�
					fDiff = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y - g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y);

					// ������������
					if (fDiff > D3DX_PI)
					{
						fDiff -= D3DX_PI * 2.0f;
					}
					if (fDiff < -D3DX_PI)
					{
						fDiff += D3DX_PI * 2.0f;
					}
					// ���݌����ݒ�
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y += fDiff * 0.1f;

					// ���݌�������
					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y > D3DX_PI)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y -= D3DX_PI * 2.0f;
					}
					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y < -D3DX_PI)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y += D3DX_PI * 2.0f;
					}
				}

				if (pXPlayer->pos.x + 100 > g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x && pXPlayer->pos.x - 100 < g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x &&
					pXPlayer->pos.z + 100 > g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z && pXPlayer->pos.z - 100 < g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z)
				{
					/*if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].bIdxMarkUse == false)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nIdxMark = SetMark(D3DXVECTOR3(g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x, 80.0f, g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z));	//�}�[�N���o��
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].bIdxMarkUse = true;
					}*/

					g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y = atan2f(pXPlayer->pos.x - g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x, pXPlayer->pos.z - g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z) + D3DX_PI;
				}
				else
				{
					/*if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].bIdxMarkUse == true)
					{
						DeleteMark(g_XEnemy[nCntXEnemy][nCntXEnemyNum].nIdxMark);		//�}�[�N������
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].bIdxMarkUse = false;
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y = g_XEnemy[nCntXEnemy][nCntXEnemyNum].Initrot.y;
					}*/

					g_XEnemy[nCntXEnemy][nCntXEnemyNum].rotDest.y = g_XEnemy[nCntXEnemy][nCntXEnemyNum].Initrot.y;
				}

				// �ړ��l���
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos += g_XEnemy[nCntXEnemy][nCntXEnemyNum].move;

				// ��������
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.x += (0.0f - g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.x) * XENEMY_DOWNSPPED;
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.z += (0.0f - g_XEnemy[nCntXEnemy][nCntXEnemyNum].move.z) * XENEMY_DOWNSPPED;

				// �I�u�W�F�N�g�����蔻��
				CollisionXObject(&g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].posOld, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].move, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax);

				CollisionMeshField(&g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].posOld, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].move, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax);

				/*if (CollisionXPlayer(&g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].posOld, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].move, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax) == true)
				{
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTimerand = 1;

					g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime = 1;
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow = 0;
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimChange = 1;

					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow != ENEMYANIM_NEUTRAL)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow = ENEMYANIM_NEUTRAL;
					}
				}
				else if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTimerand != 0)
				{
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTimerand++;

					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTimerand == 60)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTimerand = 0;

						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow != ENEMYANIM_WALK)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow = ENEMYANIM_WALK;
						}
					}
				}*/

				SetPostionShadow(g_XEnemy[nCntXEnemy][nCntXEnemyNum].nIdxShadow, g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos, g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos);	// �e�ʒu�X�V

				if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimChange == 1)
				{
					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime % 10 == 0)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime = 0;
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow + 1) % g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkey[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow];
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimChange = 0;
					}
				}
				else
				{
					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime % g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimfram[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow][g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow] == 0)
					{
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime = 0;
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow + 1) % g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkey[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow];

						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimloop[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow] != 1 && g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow == g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkey[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow] - 1)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime = 1;
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow = 0;
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimChange = 1;

							if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow == ENEMYANIM_ATTACK)
							{
								g_XEnemy[nCntXEnemy][nCntXEnemyNum].bAttack = false;
							}

							//g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow = ENEMYANIM_NEUTRAL;
						}
					}
				}

				if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimChange == 1)
				{
					frac = (10 - g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime) * 1.0f;
				}
				else
				{
					frac = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimfram[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow][(g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow)] - g_XEnemy[nCntXEnemy][nCntXEnemyNum].nCntTime) * 1.0f;
				}

				g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].posDest = g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].Initpos + g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].posAnim[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow][(g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow + 1) % (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkey[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow])];

				// �����ݒ�
				fDiff = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].posDest.x - g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].pos.x);
				// ���݌����ݒ�
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].pos.x += fDiff / frac;

				// �����ݒ�
				fDiff = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].posDest.y - g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].pos.y);
				// ���݌����ݒ�
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].pos.y += fDiff / frac;

				// �����ݒ�
				fDiff = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].posDest.z - g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].pos.z);
				// ���݌����ݒ�
				g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[0].pos.z += fDiff / frac;

				for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][nCntXEnemyNum].nMaxPartsNum; nCntXEnemyParts++)
				{
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest = g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotAnim[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow][(g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkeynow + 1) % (g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimkey[g_XEnemy[nCntXEnemy][nCntXEnemyNum].nAnimnow])];

					{
						// �ڕW��������
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.x > D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.x -= D3DX_PI * 2.0f;
						}
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.x < -D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.x += D3DX_PI * 2.0f;
						}
						// �����ݒ�
						fDiff = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.x - g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.x);

						// ������������
						if (fDiff > D3DX_PI)
						{
							fDiff -= D3DX_PI * 2.0f;
						}
						if (fDiff < -D3DX_PI)
						{
							fDiff += D3DX_PI * 2.0f;
						}
						// ���݌����ݒ�
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.x += fDiff / frac;

						// ���݌�������
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.x > D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.x -= D3DX_PI * 2.0f;
						}
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.x < -D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.x += D3DX_PI * 2.0f;
						}

						// �ڕW��������
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.y > D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.y -= D3DX_PI * 2.0f;
						}
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.y < -D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.y += D3DX_PI * 2.0f;
						}
						// �����ݒ�
						fDiff = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.y - g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.y);

						// ������������
						if (fDiff > D3DX_PI)
						{
							fDiff -= D3DX_PI * 2.0f;
						}
						if (fDiff < -D3DX_PI)
						{
							fDiff += D3DX_PI * 2.0f;
						}
						// ���݌����ݒ�
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.y += fDiff / frac;

						// ���݌�������
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.y > D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.y -= D3DX_PI * 2.0f;
						}
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.y < -D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.y += D3DX_PI * 2.0f;
						}

						// �ڕW��������
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.z > D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.z -= D3DX_PI * 2.0f;
						}
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.z < -D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.z += D3DX_PI * 2.0f;
						}
						// �����ݒ�
						fDiff = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rotDest.z - g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.z);

						// ������������
						if (fDiff > D3DX_PI)
						{
							fDiff -= D3DX_PI * 2.0f;
						}
						if (fDiff < -D3DX_PI)
						{
							fDiff += D3DX_PI * 2.0f;
						}
						// ���݌����ݒ�
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.z += fDiff / frac;

						// ���݌�������
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.z > D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.z -= D3DX_PI * 2.0f;
						}
						if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.z < -D3DX_PI)
						{
							g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.z += D3DX_PI * 2.0f;
						}
					}
				}
			}
		}
	}
}

//=========================================================================================================================
// �G�̕`�揈��
//=========================================================================================================================
void DrawXEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pmat;							// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;						//
	int nCntXEnemy;
	int nCntXEnemyParts;

	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		for (int nCntXEnemyNum = 0; nCntXEnemyNum < g_XEnemyIni[nCntXEnemy].nSetNum; nCntXEnemyNum++)
		{
			if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].bUse == true)
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_XEnemy[nCntXEnemy][nCntXEnemyNum].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll
				(
					&mtxRot,
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.y,
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.x,
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].rot.z
				);

				D3DXMatrixMultiply
				(
					&g_XEnemy[nCntXEnemy][nCntXEnemyNum].mtxWorld,
					&g_XEnemy[nCntXEnemy][nCntXEnemyNum].mtxWorld,
					&mtxRot
				);

				// �ʒu�𔽉f
				D3DXMatrixTranslation
				(
					&mtxTrans,
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x,
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y,
					g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z
				);

				D3DXMatrixMultiply
				(
					&g_XEnemy[nCntXEnemy][nCntXEnemyNum].mtxWorld,
					&g_XEnemy[nCntXEnemy][nCntXEnemyNum].mtxWorld,
					&mtxTrans
				);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].mtxWorld);

				for (nCntXEnemyParts = 0; nCntXEnemyParts < g_XEnemy[nCntXEnemy][nCntXEnemyNum].nMaxPartsNum; nCntXEnemyParts++)
				{
					if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].nIndexParent < 0)
					{
						mtxParent = g_XEnemy[nCntXEnemy][nCntXEnemyNum].mtxWorld;
					}
					else
					{
						mtxParent = g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].nIndexParent].mtxWorld;
					}

					// ���[���h�}�g���b�N�X�̏�����
					D3DXMatrixIdentity(&g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].mtxWorld);

					// ��]�𔽉f
					D3DXMatrixRotationYawPitchRoll
					(
						&mtxRot,
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.y,
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.x,
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].rot.z
					);

					D3DXMatrixMultiply
					(
						&g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].mtxWorld,
						&g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].mtxWorld,
						&mtxRot
					);

					// �ʒu�𔽉f
					D3DXMatrixTranslation
					(
						&mtxTrans,
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].pos.x,
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].pos.y,
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].pos.z
					);

					D3DXMatrixMultiply
					(
						&g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].mtxWorld,
						&g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].mtxWorld,
						&mtxTrans
					);

					D3DXMatrixMultiply
					(
						&g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].mtxWorld,
						&g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].mtxWorld,
						&mtxParent
					);

					// ���[���h�}�g���b�N�X�̐ݒ�
					pDevice->SetTransform(D3DTS_WORLD, &g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].mtxWorld);

					// ���݂̃}�e���A�����擾
					pDevice->GetMaterial(&matDef);

					// �}�e���A���f�[�^�ւ̃|�C���^���擾
					pmat = (D3DXMATERIAL*)g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].nNumMat; nCntMat++)
					{
						// �}�e���A���̐ݒ�
						pDevice->SetMaterial(&pmat[nCntMat].MatD3D);

						// �e�N�X�`���ݒ�
						pDevice->SetTexture(0, NULL);

						// �G(�p�[�c)�̕`��
						g_XEnemy[nCntXEnemy][nCntXEnemyNum].aModel[nCntXEnemyParts].pMesh->DrawSubset(nCntMat);
					}

					// �}�e���A�����f�t�H���g�ɖ߂�
					pDevice->SetMaterial(&matDef);
				}
			}
		}
	}
}

//=========================================================================================================================
// �G�̐ݒ菈��
//=========================================================================================================================
void SetXEnemy(ENEMYTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 Initrot, D3DXVECTOR3 rot)
{
	for (int nCntXEnemyNum = 0; nCntXEnemyNum < g_XEnemyIni[type].nSetNum; nCntXEnemyNum++)
	{
		if (g_XEnemy[type][nCntXEnemyNum].bUse == false)
		{
			g_XEnemy[type][nCntXEnemyNum].pos = pos;
			g_XEnemy[type][nCntXEnemyNum].Initpos = pos;
			g_XEnemy[type][nCntXEnemyNum].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_XEnemy[type][nCntXEnemyNum].rot = rot;
			g_XEnemy[type][nCntXEnemyNum].rotDest = rot;
			g_XEnemy[type][nCntXEnemyNum].Initrot = Initrot;
			g_XEnemy[type][nCntXEnemyNum].nIdxShadow = SetShadow(g_XEnemy[type][nCntXEnemyNum].pos, g_XEnemy[type][nCntXEnemyNum].rot, 30.0f, 30.0f);
			g_XEnemy[type][nCntXEnemyNum].bUse = true;

			break;
		}
	}
}

//=========================================================================================================================
// �G�̎擾����
//=========================================================================================================================
XENEMY *GetXEnemy(void)
{
	return &g_XEnemy[0][0];
}

//=========================================================================================================================
// �G�̏Փˏ���
//=========================================================================================================================
bool CollisionXEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax)
{
	int nCntXEnemy;
	bool bLand = false;

	//float vecA_x, vecA_z, vecC_x, vecC_z;

	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		for (int nCntXEnemyNum = 0; nCntXEnemyNum < g_XEnemyIni[nCntXEnemy].nSetNum; nCntXEnemyNum++)
		{
			if (g_XEnemy[nCntXEnemy][nCntXEnemyNum].bUse == true)
			{// �g�p����Ă���

				/*if (pPos->x + vtxMax->x > g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.x && pPos->x + vtxMin->x < g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.x)
				{// X�͈͊m�F
					vecA_x = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.x) - (g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.x);
					vecA_z = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.z) - (g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.z);
					vecC_x = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.x) - (pPos->x);
					vecC_z = (g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.z) - (pPos->z);

					if (((vecA_z * vecC_x) - (vecA_x * vecC_z)) < 0)
					{
						pPos->z = g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.z;
						pMove->z = 0.0f;

						bLand = true;
					}
				}*/

			//	if (pPos->y + vtxMax->y > g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.y && pPos->y + vtxMin->y < g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.y)
				{// X�͈͊m�F
					if (pPos->x + vtxMax->x > g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.x && pPos->x + vtxMin->x < g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.x)
					{// X�͈͊m�F
						if (pPosOld->z + vtxMin->z >= g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.z && g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.z >= pPos->z + vtxMin->z)
						{// Z��ꔻ��
							pPos->z = g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.z - vtxMin->z;
							//pMove->x = 0.0f;
							pMove->z = 0.0f;

							bLand = true;
						}
						else if (pPosOld->z + vtxMax->z <= g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.z && g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.z <= pPos->z + vtxMax->z)
						{// Z���ꔻ��
							pPos->z = g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.z - vtxMax->z;
							//pMove->x = 0.0f;
							pMove->z = 0.0f;

							bLand = true;
						}
					}

					if (pPos->z + vtxMax->z > g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.z && pPos->z + vtxMin->z < g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.z)
					{// Z�͈͊m�F
						if (pPosOld->x + vtxMin->x >= g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.x && g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.x >= pPos->x + vtxMin->x)
						{// X�E�Ӕ���
							pPos->x = g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.x - vtxMin->x;
							pMove->x = 0.0f;
							//pMove->z = 0.0f;

							bLand = true;
						}
						else if (pPosOld->x + vtxMax->x <= g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.x && g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.x <= pPos->x + vtxMax->x)
						{// X���Ӕ���
							pPos->x = g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.x - vtxMax->x;
							pMove->x = 0.0f;
							//pMove->z = 0.0f;

							bLand = true;
						}
					}
				}

			/*	if (pPos->x + vtxMax->x > g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.x && pPos->x + vtxMin->x < g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.x + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.x)
				{// X�͈͊m�F
					if (pPos->z + vtxMax->z > g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.z && pPos->z + vtxMin->z < g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.z + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.z)
					{// Z�͈͊m�F
						if (pPosOld->y + vtxMin->y >= g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.y && g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.y >= pPos->y + vtxMin->y)
						{// X�E�Ӕ���
							pPos->y = g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMax.y - vtxMin->y;
							//pMove->x = 0.0f;
							//pMove->z = 0.0f;

							bLand = true;
						}
						else if (pPosOld->y + vtxMax->y <= g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.y && g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.y <= pPos->x + vtxMax->y)
						{// X���Ӕ���
							pPos->y = g_XEnemy[nCntXEnemy][nCntXEnemyNum].pos.y + g_XEnemy[nCntXEnemy][nCntXEnemyNum].vtxMin.y - vtxMax->y;
							//pMove->x = 0.0f;
							//pMove->z = 0.0f;

							bLand = true;
						}
					}
				}*/
			}
		}
	}

	return bLand;
}

//=========================================================================================================================
// �G����������
//=========================================================================================================================
void DeleteXEnemy(void)
{
	//�ϐ��錾
	int nCntXEnemy;

	for (nCntXEnemy = 0; nCntXEnemy < g_XEnemyNum; nCntXEnemy++)
	{
		for (int nCntXEnemyNum = 0; nCntXEnemyNum < g_XEnemyIni[nCntXEnemy].nSetNum; nCntXEnemyNum++)
		{
			g_XEnemy[nCntXEnemy][nCntXEnemyNum].bUse = false;				//�g�p���Ă��Ȃ���Ԃɂ���
			DeleteShadow(g_XEnemy[nCntXEnemy][nCntXEnemyNum].nIdxShadow);	//�e������
		}
	}
}