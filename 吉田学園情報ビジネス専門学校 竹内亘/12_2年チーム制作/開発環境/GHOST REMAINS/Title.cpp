//=============================================================================
//
// �^�C�g������ [Title.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include"Scene.h"
#include "manager.h"
#include "sound.h"
#include "Title.h"
#include "mesh.h"
#include "camera.h"
#include "spotLight.h"
#include "light.h"
#include "SceneModel.h"
#include "enemy.h"
#include "mesh.h"
#include "dungeon.h"
#include "player.h"
#include "Result.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJ	(80)
#define FILE_NAME ("data//TEXT//Stage.txt")

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init(void)
{
	m_fCntState = 0.0f;	//���ԏ�����

	CSpotLight *pSpotLight;
	Create(pSpotLight);
	//CLight *pLight;	Create(pLight);	//�J�����̐���
	CCamera *pCamera;	Create(pCamera);	//�J�����̐���

	CScene3D *pScene3D;
	CScene2D *pScene2D;

	// �����_��������ɂ���
	//pCamera->GetposR().y += 100.0f;

	//�I�u�W�F�N�g�̓ǂݍ���
	CSceneObjct::InitSwitch(true);
	LoadObject();
	CMotion::Load();
	CCharacter::Load();

	if (SceneCreate(pScene3D, 2))
	{// �^�C�g�����S
		pScene3D->Set(D3DXVECTOR3(-6300.0f, 1200.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(400.0f, 200.0f, 0.0f), CScene::TEX_Title, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// �v���X�G���^�[
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 350.0f, 650.0f, 0.0f), 200.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FLASH,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_PressEnter);
	}

	CSceneObjct * pObject;
	if (SceneCreate(pObject, 3))
	{
		pObject->Set(D3DXVECTOR3(-7000.0f, 875.0f, -3000.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CSceneModel::MODEL_BROCK, false, CSceneObjct::USE_MAX,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
		pObject->GetDrawType() = CScene::DRAW_TYPE_NO;
		CCamera::GetInfo().pChar = &pObject->GetPosition();
		CCamera::GetInfo().pMove = &pObject->GetPosold();
		CManager::GetCamera()->GetpDistance() = NULL;
		CManager::GetCamera()->GetRot().y = D3DX_PI * -0.15f;
		CManager::GetCamera()->Reset();
	}

	CEnemy *pEnemy;
	if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
		pEnemy->Set(D3DXVECTOR3(-7100.0f, 875.0f, -2850.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 0.9f, 0.0f), CMotion::TYPE_ENEMY);
	}

	//if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
	//	pEnemy->Set(D3DXVECTOR3(400.0f, 100.0f, -1200.0f),
	//		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CMotion::TYPE_ENEMY);
	//}
	CManager::GetSound()->Play(CSound::LABEL_TITLE);

	return S_OK;
}
//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard	*pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//�W���C�p�b�h���l��
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//�W���C�p�b�h���l��

	m_fCntState += 1.0f;

	//if (m_fCntState > 90.0f)
	//{
	//	if ((pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetAllTrigger() || pInputPad1->GetAllTrigger()) && CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
	//	{//�Z���N�g��
	//		CManager::SetFade(CManager::MODE_GAME, 0);
	//	}
	//}
	if (CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
	{
		if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A))
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_ENTTER);
			CManager::SetFade(CManager::MODE_PRACTICE, 0);
		}
		else if (m_fCntState > 300.0f)
		{
			CManager::GetResult()->GetnRankIn() = -1;
			CManager::SetFade(CManager::MODE_RANKING, 0);
		}
	}
}
//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void	CTitle::Uninit(void)
{
	CManager::GetpSpotLight()->Uninit();

	//BGM�̃X�g�b�v
	CManager::GetSound()->Stop(CSound::LABEL_TITLE);
}

//=============================================================================
// �I�u�W�F�N�g�̓ǂݍ��ݐ���
//=============================================================================
void CTitle::LoadObject(void)
{
	//�ϐ��錾
	D3DXVECTOR3 plusPos = D3DXVECTOR3((MAP_SIZE) * -CHIP_SIZE + CHIP_SIZE * 2.0f, 0.0f, -CHIP_SIZE * 0.5f);
	int nMaxObj = 0;
	//int nBlockX[256] = {};
	//int nBlockZ[256] = {};
	//int nNumber[255] = {};
	int * nBlockX = NULL;
	int * nBlockZ = NULL;
	float * fPosY = NULL;
	int * nNumber = NULL;
	int * nType = NULL;
	float * fAngle = NULL;
	float * fRot = NULL;
	int * nReflain = NULL;
	int * nStart = NULL;
	float * fSpeedX = NULL;
	float * fSpeedY = NULL;
	float * fSpeedZ = NULL;


	//�ϐ��錾
	FILE *pFile;

	//�e�L�X�g�̓ǂݍ���
	pFile = fopen(FILE_NAME, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &nMaxObj);		//�ǂݍ��ރ��f�����̓ǂݍ���

											//���I�m�ۂ���
		nBlockX = new int[nMaxObj];
		nBlockZ = new int[nMaxObj];
		fPosY = new float[nMaxObj];
		nNumber = new int[nMaxObj];
		nType = new int[nMaxObj];
		fAngle = new float[nMaxObj];
		fRot = new float[nMaxObj];
		nReflain = new int[nMaxObj];
		nStart = new int[nMaxObj];
		fSpeedX = new float[nMaxObj];
		fSpeedY = new float[nMaxObj];
		fSpeedZ = new float[nMaxObj];

		for (int nCntModel = 0; nCntModel < nMaxObj; nCntModel++)
		{
			fscanf(pFile, "%d", &nBlockX[nCntModel]);	//�u���b�NX
			fscanf(pFile, "%d", &nBlockZ[nCntModel]);	//�u���b�NZ
			fscanf(pFile, "%f", &fPosY[nCntModel]);		//����
			fscanf(pFile, "%d", &nType[nCntModel]);		//�^�C�v
			fscanf(pFile, "%d", &nNumber[nCntModel]);	//�Q�ƃi���o�[
			fscanf(pFile, "%f", &fAngle[nCntModel]);	//��]�l
			fscanf(pFile, "%f", &fRot[nCntModel]);		//����
			fscanf(pFile, "%d", &nReflain[nCntModel]);	//���˗�
			fscanf(pFile, "%d", &nStart[nCntModel]);	//�X�^�[�g�l
			fscanf(pFile, "%f", &fSpeedX[nCntModel]);	//�ړ���-X
			fscanf(pFile, "%f", &fSpeedY[nCntModel]);	//�ړ���-Y
			fscanf(pFile, "%f", &fSpeedZ[nCntModel]);	//�ړ���-Z
		}

		//�ǂݍ��݂��I������
		fclose(pFile);
	}

	//�ǂݍ��񂾃I�u�W�F�N�g�𐶐�����
	CSceneObjct *pObject;
	D3DXVECTOR3 pos;
	for (int nCntModel = 0; nCntModel < nMaxObj; nCntModel++)
	{
		if (SceneCreate(pObject, 0))
		{
			fAngle[nCntModel] *= 0.05f;
			fRot[nCntModel] *= D3DX_PI;
			pos = plusPos + D3DXVECTOR3(nBlockX[nCntModel] * 200.0f - CHIP_SIZE * 4.0f, fPosY[nCntModel], -nBlockZ[nCntModel] * 200.0f);
			if (nType[nCntModel] == 0)	//�u���b�N
			{
				pObject->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BROCK, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					0.0f, 0, 0, 0, nNumber[nCntModel]);
			}
			else if (nType[nCntModel] == 1)	//���
			{
				pObject->Set(pos + D3DXVECTOR3(0.0f, -5.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_SPEAR, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 20.0f, 0.0f), 0.0f, 5, 180, nStart[nCntModel], nNumber[nCntModel]);
			}
			else if (nType[nCntModel] == 2)	//�����鏰
			{
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, fRot[nCntModel], 0.0f), CSceneModel::MODEL_DFIELD, true, CSceneObjct::USE_MAX, D3DXVECTOR3(fSpeedX[nCntModel], fSpeedY[nCntModel], fSpeedZ[nCntModel]), fAngle[nCntModel], nReflain[nCntModel], 0, nStart[nCntModel], nNumber[nCntModel]);
			}
			else if (nType[nCntModel] == 3)	//�ړ��� - ��
			{
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, fRot[nCntModel], 0.0f), CSceneModel::MODEL_MFIELD, true, CSceneObjct::USE_MAX, D3DXVECTOR3(fSpeedX[nCntModel], fSpeedY[nCntModel], fSpeedZ[nCntModel]), fAngle[nCntModel], nReflain[nCntModel], 60, nStart[nCntModel], nNumber[nCntModel]);
			}
			else if (nType[nCntModel] == 10)	//�ړ��� - ��
			{
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, fRot[nCntModel], 0.0f), CSceneModel::MODEL_MFIELD2, true, CSceneObjct::USE_MAX, D3DXVECTOR3(fSpeedX[nCntModel], fSpeedY[nCntModel], fSpeedZ[nCntModel]), fAngle[nCntModel], nReflain[nCntModel], 60, nStart[nCntModel], nNumber[nCntModel]);

			}
			else if (nType[nCntModel] == 5)
			{//�{�^��
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BUTTONFLOR, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
				if (SceneCreate(pObject, MODEL_PRIORITY))
				{
					pObject->Set(pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BUTTON, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, nNumber[nCntModel]);
				}
			}
			else if (nType[nCntModel] == 6)
			{//����
				pObject->Set(pos + D3DXVECTOR3(0.0f, 500.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_DROP_STONE, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.05f, 0, 0, 0, 0);
			}
			else if (nType[nCntModel] == 7)
			{//�S�[��
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_GOAL, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
			}
			else if (nType[nCntModel] == 8)
			{//�v���C���[�̈ʒu
				if (CManager::GetMode() == CManager::MODE_GAME)
				{
					CManager::GetPlayer()->Getpos() = pos;
					CManager::GetCamera()->Reset();

					CEnemy *pEnemy;
					if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
						pEnemy->Set(pos + D3DXVECTOR3(2000.0f, 0.0f, 200.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY);
					}

					if (SceneCreate(pObject, 0))
					{
						pObject->Set(pos + D3DXVECTOR3(-200.0f, -30.0f, 200.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BUTTONFLOR, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
						if (SceneCreate(pObject, MODEL_PRIORITY))
						{
							pObject->Set(pos + D3DXVECTOR3(-200.0f, -30.0f, 200.0f),
								D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_NOLOOK, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, nNumber[nCntModel]);
						}
					}

					if (SceneCreate(pObject, 0))
					{
						pObject->Set(pos + D3DXVECTOR3(-200.0f, -30.0f, -200.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BUTTONFLOR, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
						if (SceneCreate(pObject, MODEL_PRIORITY))
						{
							pObject->Set(pos + D3DXVECTOR3(-200.0f, -30.0f, -200.0f),
								D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_WARP, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, nNumber[nCntModel]);
						}
					}
				}
			}
			else if (nType[nCntModel] == 9)
			{//�S�[��
				CSceneAnim3D *pAnim;
				if (SceneCreate(pAnim, 0))
				{
					pAnim->Set(pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(100.0f, 400.0f, 0.0f), CScene::TEX_Fire, true,
						CScene::DRAW_TYPE_MULTIPLY, 0, 8, 1, 3, CSceneAnim3D::ANIMATION_LOOP, CScene3D::STATE_FIRE);
				}
			}
		}
	}
	//�f�[�^��j������
	delete[] nBlockX;
	delete[] nBlockZ;
	delete[] fPosY;
	delete[] nNumber;
	delete[] nType;
	delete[] fAngle;
	delete[] fRot;
	delete[] nReflain;
	delete[] nStart;
	delete[] fSpeedX;
	delete[] fSpeedY;
	delete[] fSpeedZ;

	CMesh	*pField;
	CMesh	*pCeiling;
	CMesh *pMesh;
	D3DXVECTOR3 vtx[4];
	int nMax = MAP_SIZE * FIELD_SPLIT;
	if (SceneCreate(pField, MESH_PRIORITY))
	{
		pField->Set(CMesh::TYPE_FIELD, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, -500.0f, -CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, true);
		pField->SetNor();
		pField->BindTexture(CScene::Load(CScene::TEX_Field));
	}
	if (SceneCreate(pField, MESH_PRIORITY))
	{
		pField->Set(CMesh::TYPE_FIELD, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, -300.0f, -CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, true);
		pField->SetNor();
		pField->BindTexture(CScene::Load(CScene::TEX_Field));
		pField->GetDrawType() = CScene::DRAW_TYPE_OVERLAY;
		pField->GetfUV_X() *= 3.0f;
		pField->GetfUV_Y() *= 1.5f;

	}
	if (SceneCreate(pCeiling, MESH_PRIORITY))
	{
		pCeiling->Set(CMesh::TYPE_CEILING, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, 0.0f, -MAP_SIZE * CHIP_SIZE - CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, false);
		pCeiling->SetNor();
		pCeiling->BindTexture(CScene::Load(CScene::TEX_Wall));
	}

	vtx[0] = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * 0, 0.0f, -FIELD_SIZE * (FIELD_SPLIT - 1) - FIELD_SIZE * (nMax));
	vtx[1] = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * 0, 0.0f, -FIELD_SIZE *(FIELD_SPLIT - 1) - FIELD_SIZE * 0);
	vtx[2] = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * -nMax, 0.0f, -FIELD_SIZE *(FIELD_SPLIT - 1) - FIELD_SIZE * 0);
	vtx[3] = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * -nMax, 0.0f, -FIELD_SIZE *(FIELD_SPLIT - 1) - FIELD_SIZE * (nMax));

	if (SceneCreate(pMesh, MESH_PRIORITY))
	{
		pMesh->Set(CMesh::TYPE_WALL, D3DXVECTOR3(0.0f, -1000.0f, 0.0f), 10, 4, true);
		pMesh->SetWall(&vtx[0]);
		pMesh->BindTexture(CScene::Load(CScene::TEX_Wall));
		pMesh->SetNor();
	}
}