//=========================================================================================================================
//
// �v���C���[���� [xplayer.cpp]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS		// scanf�G���[����
#include <stdio.h>					// stdio
#include "input.h"
#include "xplayer.h"
#include "xenemy.h"
#include "xobject.h"
#include "meshfield.h"
#include "shadow.h"
#include "camera.h"
#include "game.h"
#include "fade.h"
#include "item.h"
#include "itemfont.h"
#include "sound.h"
#include "flontpolygon.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define XPLAYER_UPSPPED_RUN		(1.2f)						// �v���C���[�������x�i�����j
#define XPLAYER_UPSPPED_WALK	(0.5f)						// �v���C���[�������x�i����j
#define XPLAYER_DOWNSPPED		(0.15f)						// �v���C���[�������x

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
XPLAYER							g_XPlayer;					// �v���C���[���
float							g_fDiffXPlayer;				// ����
int								g_nCntTimeXPlayer;			// �v���C���[�J�E���^�[

//=========================================================================================================================
// �v���C���[�̏���������
//=========================================================================================================================
void InitXPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FILE *pFile;
	int nCntXPlayer;

	g_XPlayer.nMaxPartsNum = 0;		// �v���C���[�p�[�c��
	g_fDiffXPlayer = 0.0f;			// �����v�Z
	g_nCntTimeXPlayer = 0;	// �v���C���[�J�E���^�[

	// �t�@�C���ݒ�
	pFile = fopen(XPLAYER_TEXT_INFO, "r");

	// �v���C���[�e�L�X�g�f�[�^�ǂݍ���
	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		fscanf(pFile, "%d", &g_XPlayer.nMaxPartsNum);	// �ǂݍ���

		for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
		{
			fscanf(pFile, "%s", &g_XPlayer.aModel[nCntXPlayer].FileName[0]);	// �ǂݍ���
		}
		
		for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
		{
			fscanf(pFile, "%d", &g_XPlayer.aModel[nCntXPlayer].nIndexParent);		// �ǂݍ���
			fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].Initpos.x);			// �ǂݍ���
			fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].Initpos.y);			// �ǂݍ���
			fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].Initpos.z);			// �ǂݍ���
			fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].Initrot.x);			// �ǂݍ���
			fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].Initrot.y);			// �ǂݍ���
			fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].Initrot.z);			// �ǂݍ���
		}

		fscanf(pFile, "%d", &g_XPlayer.nMaxAnimNum);	// �ǂݍ���

		for (int nCntXPlayerAnim = 0; nCntXPlayerAnim < g_XPlayer.nMaxAnimNum; nCntXPlayerAnim++)
		{
			fscanf(pFile, "%d", &g_XPlayer.nAnimloop[nCntXPlayerAnim]);				// �ǂݍ���
			fscanf(pFile, "%d", &g_XPlayer.nAnimkey[nCntXPlayerAnim]);				// �ǂݍ���
			fscanf(pFile, "%d", &g_XPlayer.nAnimBlend[nCntXPlayerAnim]);			// �ǂݍ���

			for (int nCntXPlayerAnimKey = 0; nCntXPlayerAnimKey < g_XPlayer.nAnimkey[nCntXPlayerAnim]; nCntXPlayerAnimKey++)
			{
				fscanf(pFile, "%d", &g_XPlayer.nAnimfram[nCntXPlayerAnim][nCntXPlayerAnimKey]);			// �ǂݍ���

				for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
				{
					fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].posAnim[nCntXPlayerAnim][nCntXPlayerAnimKey].x);	// �ǂݍ���
					fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].posAnim[nCntXPlayerAnim][nCntXPlayerAnimKey].y);	// �ǂݍ���
					fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].posAnim[nCntXPlayerAnim][nCntXPlayerAnimKey].z);	// �ǂݍ���
					fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].rotAnim[nCntXPlayerAnim][nCntXPlayerAnimKey].x);	// �ǂݍ���
					fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].rotAnim[nCntXPlayerAnim][nCntXPlayerAnimKey].y);	// �ǂݍ���
					fscanf(pFile, "%f", &g_XPlayer.aModel[nCntXPlayer].rotAnim[nCntXPlayerAnim][nCntXPlayerAnimKey].z);	// �ǂݍ���
				}
			}
		}

		fclose(pFile);	// �t�@�C�������
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}

	// X�t�@�C���̓ǂݍ���
	for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
	{
		D3DXLoadMeshFromX
		(
			&g_XPlayer.aModel[nCntXPlayer].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_XPlayer.aModel[nCntXPlayer].pBuffMat,
			NULL,
			&g_XPlayer.aModel[nCntXPlayer].nNumMat,
			&g_XPlayer.aModel[nCntXPlayer].pMesh
		);
	}

	// �ʒu�E�����̏����ݒ�
	g_XPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_XPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_XPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_XPlayer.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_XPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_XPlayer.vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	g_XPlayer.vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	g_XPlayer.nAnimnow = PLAYERANIM_NEUTRAL;
	g_XPlayer.nAnimChange = 0;
	g_XPlayer.nAnimkeynow = 0;
	g_XPlayer.nIdxShadow = 0;
	g_XPlayer.bAttack = false;

	g_XPlayer.bUse = false;

	for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
	{
		g_XPlayer.aModel[nCntXPlayer].pos = g_XPlayer.aModel[nCntXPlayer].Initpos;
		g_XPlayer.aModel[nCntXPlayer].posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XPlayer.aModel[nCntXPlayer].rot = g_XPlayer.aModel[nCntXPlayer].rotAnim[0][0];
		g_XPlayer.aModel[nCntXPlayer].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XPlayer.aModel[nCntXPlayer].vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
		g_XPlayer.aModel[nCntXPlayer].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	}

	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�̃|�C���^

	for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
	{
		// ���_���̎擾
		nNumVtx = g_XPlayer.aModel[nCntXPlayer].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_XPlayer.aModel[nCntXPlayer].pMesh->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_XPlayer.aModel[nCntXPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��
			{
				if (vtx.x > g_XPlayer.aModel[nCntXPlayer].vtxMax.x)
				{
					g_XPlayer.aModel[nCntXPlayer].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_XPlayer.aModel[nCntXPlayer].vtxMax.y)
				{
					g_XPlayer.aModel[nCntXPlayer].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_XPlayer.aModel[nCntXPlayer].vtxMax.z)
				{
					g_XPlayer.aModel[nCntXPlayer].vtxMax.z = vtx.z;
				}

				if (vtx.x < g_XPlayer.aModel[nCntXPlayer].vtxMin.x)
				{
					g_XPlayer.aModel[nCntXPlayer].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_XPlayer.aModel[nCntXPlayer].vtxMin.y)
				{
					g_XPlayer.aModel[nCntXPlayer].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_XPlayer.aModel[nCntXPlayer].vtxMin.z)
				{
					g_XPlayer.aModel[nCntXPlayer].vtxMin.z = vtx.z;
				}
			}

			pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
		}

		// ���_�o�b�t�@���A�����b�N
		g_XPlayer.aModel[nCntXPlayer].pMesh->UnlockVertexBuffer();
	}

	g_XPlayer.vtxMin.x = -20.0f;
	g_XPlayer.vtxMin.y = 0.0f;
	g_XPlayer.vtxMin.z = -20.0f;
	g_XPlayer.vtxMax.x = 20.0f;
	g_XPlayer.vtxMax.y = g_XPlayer.aModel[0].pos.y + g_XPlayer.aModel[0].vtxMax.y + g_XPlayer.aModel[1].pos.y + g_XPlayer.aModel[1].vtxMax.y + g_XPlayer.aModel[2].pos.y + g_XPlayer.aModel[2].vtxMax.y;
	g_XPlayer.vtxMax.z = 20.0f;
}

//=========================================================================================================================
// �v���C���[�̏I������
//=========================================================================================================================
void UninitXPlayer(void)
{
	// �ϐ��錾
	int nCntXPlayer;

	// ���b�V���̊J��
	for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
	{
		if (g_XPlayer.aModel[nCntXPlayer].pMesh != NULL)
		{
			g_XPlayer.aModel[nCntXPlayer].pMesh->Release();
			g_XPlayer.aModel[nCntXPlayer].pMesh = NULL;
		}
	}

	// �}�e���A���̊J��
	for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
	{
		if (g_XPlayer.aModel[nCntXPlayer].pBuffMat != NULL)
		{
			g_XPlayer.aModel[nCntXPlayer].pBuffMat->Release();
			g_XPlayer.aModel[nCntXPlayer].pBuffMat = NULL;
		}
	}
}

//=========================================================================================================================
// �v���C���[�̍X�V����
//=========================================================================================================================
void UpdateXPlayer(void)
{
	//�ϐ��錾
	Camera *pCamera = GetCamera();
	float fDiff = 0.0f;
	float frac = 0.0f;
	float fSpeed = 0.0f;
	int nCntXPlayer;
	bool bUseItemFont = false;

	QUESTSTATE pQuestState = GetQuestState();
	DIJOYSTATE pStick = GetStick();

	bool bDeletePartsTexture = DeletePartsTexture();

	//�A�C�e���t�H���g�̏����擾����
	bUseItemFont = GetUseItemFont();

	
	if (g_XPlayer.bUse == true)
	{
		g_XPlayer.posOld = g_XPlayer.pos;
		g_nCntTimeXPlayer++;

		if (g_XPlayer.bAttack == false && pQuestState == QUESTSTATE_SEARCH && bDeletePartsTexture == false)
		{
			if (bUseItemFont == false)
			{
				if ((GetKeyboardPress(DIK_UP) == true || (pStick.rgdwPOV[0] == 0 || pStick.rgdwPOV[0] == 31500 || pStick.rgdwPOV[0] == 4500)) || pStick.lY < -100)
				{// �C�ӂ̃L�[�i��j���������ꍇ
					if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true || GetButtonPress(7) == true)
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_RUN)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						fSpeed = XPLAYER_UPSPPED_RUN;
						g_XPlayer.nAnimnow = PLAYERANIM_RUN;
					}
					else
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_WALK)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						fSpeed = XPLAYER_UPSPPED_WALK;
						g_XPlayer.nAnimnow = PLAYERANIM_WALK;
					}

					if ((GetKeyboardPress(DIK_LEFT) == true || pStick.rgdwPOV[0] == 31500) || pStick.lX < -100)
					{// �C�ӂ̃L�[�i���j���������ꍇ
						g_XPlayer.move.x -= sinf(D3DX_PI * 0.75f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(D3DX_PI * 0.75f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (D3DX_PI * 0.75f + pCamera->rot.y);
					}
					else if ((GetKeyboardPress(DIK_RIGHT) == true || pStick.rgdwPOV[0] == 4500) || pStick.lX > 100)
					{// �C�ӂ̃L�[�i�E�j���������ꍇ
						g_XPlayer.move.x -= sinf(-D3DX_PI * 0.75f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(-D3DX_PI * 0.75f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (-D3DX_PI * 0.75f + pCamera->rot.y);
					}
					else
					{// ��݂̂̏ꍇ
						g_XPlayer.move.x -= sinf(D3DX_PI * 1.0f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(D3DX_PI * 1.0f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (D3DX_PI * 1.0f + pCamera->rot.y);
					}
				}
				else if ((GetKeyboardPress(DIK_DOWN) == true || (pStick.rgdwPOV[0] == 18000 || pStick.rgdwPOV[0] == 13500 || pStick.rgdwPOV[0] == 22500)) || pStick.lY > 100)
				{// �C�ӂ̃L�[�i���j���������ꍇ
					if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true || GetButtonPress(7) == true)
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_RUN)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						fSpeed = XPLAYER_UPSPPED_RUN;
						g_XPlayer.nAnimnow = PLAYERANIM_RUN;
					}
					else
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_WALK)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						fSpeed = XPLAYER_UPSPPED_WALK;
						g_XPlayer.nAnimnow = PLAYERANIM_WALK;
					}

					if ((GetKeyboardPress(DIK_LEFT) == true || pStick.rgdwPOV[0] == 22500) || pStick.lX < -100)
					{// �C�ӂ̃L�[�i���j���������ꍇ
						g_XPlayer.move.x -= sinf(D3DX_PI * 0.25f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(D3DX_PI * 0.25f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (D3DX_PI * 0.25f + pCamera->rot.y);
					}
					else if ((GetKeyboardPress(DIK_RIGHT) == true || pStick.rgdwPOV[0] == 13500) || pStick.lX > 100)
					{// �C�ӂ̃L�[�i�E�j���������ꍇ
						g_XPlayer.move.x -= sinf(-D3DX_PI * 0.25f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(-D3DX_PI * 0.25f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (-D3DX_PI * 0.25f + pCamera->rot.y);
					}
					else
					{// ���݂̂̏ꍇ
						g_XPlayer.move.x -= sinf(D3DX_PI * 0.0f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(D3DX_PI * 0.0f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (D3DX_PI * 0.0f + pCamera->rot.y);
					}
				}
				else if ((GetKeyboardPress(DIK_LEFT) == true || (pStick.rgdwPOV[0] == 27000 || pStick.rgdwPOV[0] == 31500 || pStick.rgdwPOV[0] == 22500)) || pStick.lX < -100)
				{// �C�ӂ̃L�[�i���j���������ꍇ
					if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true || GetButtonPress(7) == true)
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_RUN)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						fSpeed = XPLAYER_UPSPPED_RUN;
						g_XPlayer.nAnimnow = PLAYERANIM_RUN;
					}
					else
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_WALK)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						fSpeed = XPLAYER_UPSPPED_WALK;
						g_XPlayer.nAnimnow = PLAYERANIM_WALK;
					}

					if ((GetKeyboardPress(DIK_UP) == true || pStick.rgdwPOV[0] == 31500 || pStick.lY < -100))
					{// �C�ӂ̃L�[�i��j���������ꍇ
						g_XPlayer.move.x -= sinf(D3DX_PI * 0.75f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(D3DX_PI * 0.75f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (D3DX_PI * 0.75f + pCamera->rot.y);
					}
					else if ((GetKeyboardPress(DIK_DOWN) == true || pStick.rgdwPOV[0] == 22500 || pStick.lY > 100))
					{// �C�ӂ̃L�[�i���j���������ꍇ
						g_XPlayer.move.x -= sinf(D3DX_PI * 0.25f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(D3DX_PI * 0.25f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (D3DX_PI * 0.25f + pCamera->rot.y);
					}
					else
					{// ���݂̂̏ꍇ
						g_XPlayer.move.x -= sinf(D3DX_PI * 0.5f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(D3DX_PI * 0.5f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (D3DX_PI * 0.5f + pCamera->rot.y);
					}
				}
				else if ((GetKeyboardPress(DIK_RIGHT) == true || (pStick.rgdwPOV[0] == 9000 || pStick.rgdwPOV[0] == 4500 || pStick.rgdwPOV[0] == 22500)) || pStick.lX > 100)
				{// �C�ӂ̃L�[�i�E�j���������ꍇ
					if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true || GetButtonPress(7) == true)
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_RUN)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						fSpeed = XPLAYER_UPSPPED_RUN;
						g_XPlayer.nAnimnow = PLAYERANIM_RUN;
					}
					else
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_WALK)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						fSpeed = XPLAYER_UPSPPED_WALK;
						g_XPlayer.nAnimnow = PLAYERANIM_WALK;
					}

					if ((GetKeyboardPress(DIK_UP) == true || pStick.rgdwPOV[0] == 4500 || pStick.lY < -100))
					{// �C�ӂ̃L�[�i��j���������ꍇ
						g_XPlayer.move.x -= sinf(-D3DX_PI * 0.75f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(-D3DX_PI * 0.75f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (-D3DX_PI * 0.75f + pCamera->rot.y);
					}
					else if ((GetKeyboardPress(DIK_DOWN) == true || pStick.rgdwPOV[0] == 22500 || pStick.lY > 100))
					{// �C�ӂ̃L�[�i���j���������ꍇ
						g_XPlayer.move.x -= sinf(-D3DX_PI * 0.25f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(-D3DX_PI * 0.25f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (-D3DX_PI * 0.25f + pCamera->rot.y);
					}
					else
					{// �E�݂̂̏ꍇ
						g_XPlayer.move.x -= sinf(-D3DX_PI * 0.5f + pCamera->rot.y) * fSpeed;
						g_XPlayer.move.z -= cosf(-D3DX_PI * 0.5f + pCamera->rot.y) * fSpeed;

						g_XPlayer.rotDest.y = (-D3DX_PI * 0.5f + pCamera->rot.y);
					}
				}
				else
				{
					if (g_XPlayer.bAttack == false)
					{
						if (g_XPlayer.nAnimnow != PLAYERANIM_NEUTRAL)
						{
							g_nCntTimeXPlayer = 1;
							g_XPlayer.nAnimkeynow = 0;
							g_XPlayer.nAnimChange = 1;
						}

						g_XPlayer.nAnimnow = PLAYERANIM_NEUTRAL;
					}
				}
			}
		}

		if (g_XPlayer.nAnimnow == PLAYERANIM_WALK)
		{
			if ((g_XPlayer.nAnimkeynow == 0 || g_XPlayer.nAnimkeynow == 3 || g_XPlayer.nAnimkeynow == 5) && g_nCntTimeXPlayer == 1)
			{
				PlaySound(SOUND_LABEL_SE_WALK);
			}
		}
		if (g_XPlayer.nAnimnow == PLAYERANIM_RUN)
		{
			if ((g_XPlayer.nAnimkeynow == 3 || g_XPlayer.nAnimkeynow == 9) && g_nCntTimeXPlayer == 1)
			{
				PlaySound(SOUND_LABEL_SE_WALK);
			}
		}

		if (g_XPlayer.pos.x < -4810.0f)
		{
			g_XPlayer.pos.x = -4810.0f;
		}
		if (g_XPlayer.pos.x > 4810.0f)
		{
			g_XPlayer.pos.x = 4810.0f;
		}
		if (g_XPlayer.pos.z < -4810.0f)
		{
			g_XPlayer.pos.z = -4810.0f;
		}
		if (g_XPlayer.pos.z > 4810.0f)
		{
			g_XPlayer.pos.z = 4810.0f;
		}

		{
			// �ڕW��������
			if (g_XPlayer.rotDest.y > D3DX_PI)
			{
				g_XPlayer.rotDest.y -= D3DX_PI * 2.0f;
			}
			if (g_XPlayer.rotDest.y < -D3DX_PI)
			{
				g_XPlayer.rotDest.y += D3DX_PI * 2.0f;
			}
			// �����ݒ�
			fDiff = (g_XPlayer.rotDest.y - g_XPlayer.rot.y);

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
			g_XPlayer.rot.y += fDiff * 0.1f;

			// ���݌�������
			if (g_XPlayer.rot.y > D3DX_PI)
			{
				g_XPlayer.rot.y -= D3DX_PI * 2.0f;
			}
			if (g_XPlayer.rot.y < -D3DX_PI)
			{
				g_XPlayer.rot.y += D3DX_PI * 2.0f;
			}
		}

		// �ړ��l���
		g_XPlayer.pos += g_XPlayer.move;

		// ��������
		g_XPlayer.move.x += (0.0f - g_XPlayer.move.x) * XPLAYER_DOWNSPPED;
		g_XPlayer.move.z += (0.0f - g_XPlayer.move.z) * XPLAYER_DOWNSPPED;

		// �I�u�W�F�N�g�����蔻��
		CollisionXObject(&g_XPlayer.pos, &g_XPlayer.posOld, &g_XPlayer.move, &g_XPlayer.vtxMin, &g_XPlayer.vtxMax);
		CollisionMeshField(&g_XPlayer.pos, &g_XPlayer.posOld, &g_XPlayer.move, &g_XPlayer.vtxMin, &g_XPlayer.vtxMax);
		CollisionXEnemy(&g_XPlayer.pos, &g_XPlayer.posOld, &g_XPlayer.move, &g_XPlayer.vtxMin, &g_XPlayer.vtxMax);
		
		if (CollsionItem(g_XPlayer.vtxMin, g_XPlayer.vtxMax, &g_XPlayer.pos, &g_XPlayer.posOld) == true)
		{
			if (g_XPlayer.nAnimnow != PLAYERANIM_ATTACK)
			{
				g_XPlayer.bAttack = true;

				g_nCntTimeXPlayer = 1;
				g_XPlayer.nAnimkeynow = 0;
				g_XPlayer.nAnimChange = 1;
			}

			g_XPlayer.nAnimnow = PLAYERANIM_ATTACK;
		}

		D3DXVECTOR3 nShadow;

		nShadow = D3DXVECTOR3(g_XPlayer.aModel[0].mtxWorld._41, g_XPlayer.aModel[0].mtxWorld._42, g_XPlayer.aModel[0].mtxWorld._43);

		SetPostionShadow(g_XPlayer.nIdxShadow, nShadow, nShadow);	// �e�ʒu�X�V

		if (g_XPlayer.nAnimChange == 1)
		{
			if (g_nCntTimeXPlayer % g_XPlayer.nAnimBlend[g_XPlayer.nAnimnow] == 0)
			{
				g_nCntTimeXPlayer = 0;
				g_XPlayer.nAnimkeynow = (g_XPlayer.nAnimkeynow + 1) % g_XPlayer.nAnimkey[g_XPlayer.nAnimnow];
				g_XPlayer.nAnimChange = 0;
			}
		}
		else
		{
			if (g_nCntTimeXPlayer % g_XPlayer.nAnimfram[g_XPlayer.nAnimnow][g_XPlayer.nAnimkeynow] == 0)
			{
				g_nCntTimeXPlayer = 0;
				g_XPlayer.nAnimkeynow = (g_XPlayer.nAnimkeynow + 1) % g_XPlayer.nAnimkey[g_XPlayer.nAnimnow];

				if (g_XPlayer.nAnimloop[g_XPlayer.nAnimnow] != 1 && g_XPlayer.nAnimkeynow == g_XPlayer.nAnimkey[g_XPlayer.nAnimnow] - 1)
				{
					g_nCntTimeXPlayer = 1;
					g_XPlayer.nAnimkeynow = 0;
					g_XPlayer.nAnimChange = 1;

					if (g_XPlayer.nAnimnow == PLAYERANIM_ATTACK)
					{
						g_XPlayer.bAttack = false;
					}

					g_XPlayer.nAnimnow = PLAYERANIM_NEUTRAL;
				}
			}
		}

		if (g_XPlayer.nAnimChange == 1)
		{
			frac = (g_XPlayer.nAnimBlend[g_XPlayer.nAnimnow] - g_nCntTimeXPlayer) * 1.0f;;
		}
		else
		{
			frac = (g_XPlayer.nAnimfram[g_XPlayer.nAnimnow][(g_XPlayer.nAnimkeynow)] - g_nCntTimeXPlayer) * 1.0f;
		}

		g_XPlayer.aModel[0].posDest = g_XPlayer.aModel[0].Initpos + g_XPlayer.aModel[0].posAnim[g_XPlayer.nAnimnow][(g_XPlayer.nAnimkeynow + 1) % (g_XPlayer.nAnimkey[g_XPlayer.nAnimnow])];

		// �����ݒ�
		fDiff = (g_XPlayer.aModel[0].posDest.x - g_XPlayer.aModel[0].pos.x);
		// ���݌����ݒ�
		g_XPlayer.aModel[0].pos.x += fDiff / frac;

		// �����ݒ�
		fDiff = (g_XPlayer.aModel[0].posDest.y - g_XPlayer.aModel[0].pos.y);
		// ���݌����ݒ�
		g_XPlayer.aModel[0].pos.y += fDiff / frac;

		// �����ݒ�
		fDiff = (g_XPlayer.aModel[0].posDest.z - g_XPlayer.aModel[0].pos.z);
		// ���݌����ݒ�
		g_XPlayer.aModel[0].pos.z += fDiff / frac;

		for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
		{
			g_XPlayer.aModel[nCntXPlayer].rotDest = g_XPlayer.aModel[nCntXPlayer].rotAnim[g_XPlayer.nAnimnow][(g_XPlayer.nAnimkeynow + 1) % (g_XPlayer.nAnimkey[g_XPlayer.nAnimnow])];

			{
				// �ڕW��������
				if (g_XPlayer.aModel[nCntXPlayer].rotDest.x > D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rotDest.x -= D3DX_PI * 2.0f;
				}
				if (g_XPlayer.aModel[nCntXPlayer].rotDest.x < -D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rotDest.x += D3DX_PI * 2.0f;
				}
				// �����ݒ�
				fDiff = (g_XPlayer.aModel[nCntXPlayer].rotDest.x - g_XPlayer.aModel[nCntXPlayer].rot.x);

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
				g_XPlayer.aModel[nCntXPlayer].rot.x += fDiff / frac;

				// ���݌�������
				if (g_XPlayer.aModel[nCntXPlayer].rot.x > D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rot.x -= D3DX_PI * 2.0f;
				}
				if (g_XPlayer.aModel[nCntXPlayer].rot.x < -D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rot.x += D3DX_PI * 2.0f;
				}

				// �ڕW��������
				if (g_XPlayer.aModel[nCntXPlayer].rotDest.y > D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rotDest.y -= D3DX_PI * 2.0f;
				}
				if (g_XPlayer.aModel[nCntXPlayer].rotDest.y < -D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rotDest.y += D3DX_PI * 2.0f;
				}
				// �����ݒ�
				fDiff = (g_XPlayer.aModel[nCntXPlayer].rotDest.y - g_XPlayer.aModel[nCntXPlayer].rot.y);

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
				g_XPlayer.aModel[nCntXPlayer].rot.y += fDiff / frac;

				// ���݌�������
				if (g_XPlayer.aModel[nCntXPlayer].rot.y > D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rot.y -= D3DX_PI * 2.0f;
				}
				if (g_XPlayer.aModel[nCntXPlayer].rot.y < -D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rot.y += D3DX_PI * 2.0f;
				}

				// �ڕW��������
				if (g_XPlayer.aModel[nCntXPlayer].rotDest.z > D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rotDest.z -= D3DX_PI * 2.0f;
				}
				if (g_XPlayer.aModel[nCntXPlayer].rotDest.z < -D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rotDest.z += D3DX_PI * 2.0f;
				}
				// �����ݒ�
				fDiff = (g_XPlayer.aModel[nCntXPlayer].rotDest.z - g_XPlayer.aModel[nCntXPlayer].rot.z);

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
				g_XPlayer.aModel[nCntXPlayer].rot.z += fDiff / frac;

				// ���݌�������
				if (g_XPlayer.aModel[nCntXPlayer].rot.z > D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rot.z -= D3DX_PI * 2.0f;
				}
				if (g_XPlayer.aModel[nCntXPlayer].rot.z < -D3DX_PI)
				{
					g_XPlayer.aModel[nCntXPlayer].rot.z += D3DX_PI * 2.0f;
				}
			}
		}
	}
}

//=========================================================================================================================
// �v���C���[�̕`�揈��
//=========================================================================================================================
void DrawXPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pmat;							// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;						// 
	int nCntXPlayer;

	if (g_XPlayer.bUse == true)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_XPlayer.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll
		(
			&mtxRot,
			g_XPlayer.rot.y,
			g_XPlayer.rot.x,
			g_XPlayer.rot.z
		);

		D3DXMatrixMultiply
		(
			&g_XPlayer.mtxWorld,
			&g_XPlayer.mtxWorld,
			&mtxRot
		);

		// �ʒu�𔽉f
		D3DXMatrixTranslation
		(
			&mtxTrans,
			g_XPlayer.pos.x,
			g_XPlayer.pos.y,
			g_XPlayer.pos.z
		);

		D3DXMatrixMultiply
		(
			&g_XPlayer.mtxWorld,
			&g_XPlayer.mtxWorld,
			&mtxTrans
		);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_XPlayer.mtxWorld);

		for (nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
		{
			if (g_XPlayer.aModel[nCntXPlayer].nIndexParent < 0)
			{
				mtxParent = g_XPlayer.mtxWorld;
			}
			else
			{
				mtxParent = g_XPlayer.aModel[g_XPlayer.aModel[nCntXPlayer].nIndexParent].mtxWorld;
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_XPlayer.aModel[nCntXPlayer].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_XPlayer.aModel[nCntXPlayer].rot.y,
				g_XPlayer.aModel[nCntXPlayer].rot.x,
				g_XPlayer.aModel[nCntXPlayer].rot.z
			);

			D3DXMatrixMultiply
			(
				&g_XPlayer.aModel[nCntXPlayer].mtxWorld,
				&g_XPlayer.aModel[nCntXPlayer].mtxWorld,
				&mtxRot
			);

			// �ʒu�𔽉f
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_XPlayer.aModel[nCntXPlayer].pos.x,
				g_XPlayer.aModel[nCntXPlayer].pos.y,
				g_XPlayer.aModel[nCntXPlayer].pos.z
			);

			D3DXMatrixMultiply
			(
				&g_XPlayer.aModel[nCntXPlayer].mtxWorld,
				&g_XPlayer.aModel[nCntXPlayer].mtxWorld,
				&mtxTrans
			);

			D3DXMatrixMultiply
			(
				&g_XPlayer.aModel[nCntXPlayer].mtxWorld,
				&g_XPlayer.aModel[nCntXPlayer].mtxWorld,
				&mtxParent
			);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_XPlayer.aModel[nCntXPlayer].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pmat = (D3DXMATERIAL*)g_XPlayer.aModel[nCntXPlayer].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_XPlayer.aModel[nCntXPlayer].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pmat[nCntMat].MatD3D);

				// �e�N�X�`���ݒ�
				pDevice->SetTexture(0, NULL);

				// �v���C���[(�p�[�c)�̕`��
				g_XPlayer.aModel[nCntXPlayer].pMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================================================================================================
// �v���C���[�̐ݒ菈��
//=========================================================================================================================
void SetXPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	if (g_XPlayer.bUse == false)
	{
		g_XPlayer.pos = pos;
		g_XPlayer.Initpos = pos;
		g_XPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_XPlayer.rot = rot;
		g_XPlayer.rotDest = rot;
		g_XPlayer.Initrot = rot;
		g_XPlayer.nAnimnow = PLAYERANIM_NEUTRAL;
		g_XPlayer.nAnimChange = 0;
		g_XPlayer.nAnimkeynow = 0;
		g_XPlayer.nIdxShadow = SetShadow(g_XPlayer.pos, g_XPlayer.rot, 20.0f, 20.0f);
		g_XPlayer.bUse = true;

		for (int nCntXPlayer = 0; nCntXPlayer < g_XPlayer.nMaxPartsNum; nCntXPlayer++)
		{
			g_XPlayer.aModel[nCntXPlayer].pos = g_XPlayer.aModel[nCntXPlayer].Initpos;
			g_XPlayer.aModel[nCntXPlayer].rot = g_XPlayer.aModel[nCntXPlayer].rotAnim[0][0];
		}
	}
}

//=========================================================================================================================
// �v���C���[�̎擾����
//=========================================================================================================================
XPLAYER *GetXPlayer(void)
{
	return &g_XPlayer;
}

//=========================================================================================================================
// �v���C���[�̏Փˏ���
//=========================================================================================================================
bool CollisionXPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax)
{
	bool bLand = false;

	if (g_XPlayer.bUse == true)
	{// �g�p����Ă���
		if (pPos->y + vtxMax->y > g_XPlayer.pos.y + g_XPlayer.vtxMin.y && pPos->y + vtxMin->y < g_XPlayer.pos.y + g_XPlayer.vtxMax.y)
		{// X�͈͊m�F
			if (pPos->x + vtxMax->x > g_XPlayer.pos.x + g_XPlayer.vtxMin.x && pPos->x + vtxMin->x < g_XPlayer.pos.x + g_XPlayer.vtxMax.x)
			{// X�͈͊m�F
				if (pPosOld->z + vtxMin->z >= g_XPlayer.pos.z + g_XPlayer.vtxMax.z && g_XPlayer.pos.z + g_XPlayer.vtxMax.z > pPos->z + vtxMin->z)
				{// Z��ꔻ��
					pPos->z = g_XPlayer.pos.z + g_XPlayer.vtxMax.z - vtxMin->z;
					//pMove->x = 0.0f;
					pMove->z = 0.0f;

					bLand = true;
				}
				else if (pPosOld->z + vtxMax->z <= g_XPlayer.pos.z + g_XPlayer.vtxMin.z && g_XPlayer.pos.z + g_XPlayer.vtxMin.z < pPos->z + vtxMax->z)
				{// Z���ꔻ��
					pPos->z = g_XPlayer.pos.z + g_XPlayer.vtxMin.z - vtxMax->z;
					//pMove->x = 0.0f;
					pMove->z = 0.0f;

					bLand = true;
				}
			}

			if (pPos->z + vtxMax->z > g_XPlayer.pos.z + g_XPlayer.vtxMin.z && pPos->z + vtxMin->z < g_XPlayer.pos.z + g_XPlayer.vtxMax.z)
			{// Z�͈͊m�F
				if (pPosOld->x + vtxMin->x >= g_XPlayer.pos.x + g_XPlayer.vtxMax.x && g_XPlayer.pos.x + g_XPlayer.vtxMax.x > pPos->x + vtxMin->x)
				{// X�E�Ӕ���
					pPos->x = g_XPlayer.pos.x + g_XPlayer.vtxMax.x - vtxMin->x;
					pMove->x = 0.0f;
					//pMove->z = 0.0f;

					bLand = true;
				}
				else if (pPosOld->x + vtxMax->x <= g_XPlayer.pos.x + g_XPlayer.vtxMin.x && g_XPlayer.pos.x + g_XPlayer.vtxMin.x < pPos->x + vtxMax->x)
				{// X���Ӕ���
					pPos->x = g_XPlayer.pos.x + g_XPlayer.vtxMin.x - vtxMax->x;
					pMove->x = 0.0f;
					//pMove->z = 0.0f;

					bLand = true;
				}
			}
		}

		if (pPos->x + vtxMax->x > g_XPlayer.pos.x + g_XPlayer.vtxMin.x && pPos->x + vtxMin->x < g_XPlayer.pos.x + g_XPlayer.vtxMax.x)
		{// X�͈͊m�F
			if (pPos->z + vtxMax->z > g_XPlayer.pos.z + g_XPlayer.vtxMin.z && pPos->z + vtxMin->z < g_XPlayer.pos.z + g_XPlayer.vtxMax.z)
			{// Z�͈͊m�F
				if (pPosOld->y + vtxMin->y >= g_XPlayer.pos.y + g_XPlayer.vtxMax.y && g_XPlayer.pos.y + g_XPlayer.vtxMax.y > pPos->y + vtxMin->y)
				{// X�E�Ӕ���
					pPos->y = g_XPlayer.pos.y + g_XPlayer.vtxMax.y - vtxMin->y;
					//pMove->x = 0.0f;
					//pMove->z = 0.0f;

					bLand = true;
				}
				else if (pPosOld->y + vtxMax->y <= g_XPlayer.pos.y + g_XPlayer.vtxMin.y && g_XPlayer.pos.y + g_XPlayer.vtxMin.y < pPos->x + vtxMax->y)
				{// X���Ӕ���
					pPos->y = g_XPlayer.pos.y + g_XPlayer.vtxMin.y - vtxMax->y;
					//pMove->x = 0.0f;
					//pMove->z = 0.0f;

					bLand = true;
				}
			}
		}
	}

	return bLand;
}

//=========================================================================================================================
// �v���C���[������
//=========================================================================================================================
void DeleteXPlayer(void)
{
	if (g_XPlayer.bUse == true)
	{
		g_XPlayer.bUse = false;					//�g�p���Ă��Ȃ���Ԃɐݒ肷��
		DeleteShadow(g_XPlayer.nIdxShadow);		//�e������
	}
}