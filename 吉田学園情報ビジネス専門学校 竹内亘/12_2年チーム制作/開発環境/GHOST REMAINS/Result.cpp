//=============================================================================
//
// ���U���g���� [Result.cpp]
// Author : �|���j
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include"Scene.h"
#include "manager.h"
#include "scene.h"
#include "Game.h"
#include "Result.h"
#include "sound.h"
#include "Number.h"
#include "SceneModel.h"
#include "spotLight.h"
#include "camera.h"
#include "motion.h"
#include "enemy.h"
#include "mesh.h"
#include "dungeon.h"
#include "player.h"

//=============================================================================
//	�ÓI�����o�ϐ���`
//=============================================================================
int CResult::m_nTime;
int CResult::m_nRankIn;

//=============================================================================
// ���U���g����������
//=============================================================================
HRESULT CResult::Init(void)
{
	m_nTimeEnemy = 0;
	m_nCntEnemy = 0;

	CSpotLight *pSpotLight;		Create(pSpotLight);
	CCamera *pCamera;	Create(pCamera);

	CMotion::Load();
	CCharacter::Load();
	CSceneObjct::InitSwitch(true);

	CScene2D *pScene2D;
	m_nRankIn = -1;

	if (SceneCreate(pScene2D, 2))
	{// ���U���g���S
		pScene2D->Set(D3DXVECTOR3(300.0f, 200.0f, 0.0f), 200.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_ResaltLogo);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// �v���X�G���^�[
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 430, 650.0f, 0.0f), 200.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FLASH, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_PressEnter);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// ��
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 20, 0.0f), 80.0f, 80.0f, D3DX_PI, 0, 1, 5, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_RankingMinute);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// �b
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - 20, 0.0f), 80.0f, 80.0f, D3DX_PI, 0, 1, 5, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_RankingSecond);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	// �i���o�[
	CResult_UI * pResultUI;
	Create(pResultUI);

	LoadObject();

	CSceneObjct * pObject;
	if (SceneCreate(pObject, 0))
	{
		pObject->Set(D3DXVECTOR3(-8500.0f, -300.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BROCK, false, CSceneObjct::USE_MAX,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
		pObject->GetDrawType() = CScene::DRAW_TYPE_NO;
		CCamera::GetInfo().pChar = &pObject->GetPosition();
		CCamera::GetInfo().pMove = &pObject->GetPosition();
		CManager::GetCamera()->GetpDistance() = NULL;
		CManager::GetCamera()->GetRot().y = D3DX_PI * 0.0f;
		CManager::GetCamera()->Reset();
	}

	//CSceneObjct * pObject;
	//if (SceneCreate(pObject, 0))
	//{
	//	pObject->Set(D3DXVECTOR3(0.0f, 10.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BROCK, false, CSceneObjct::USE_MAX,
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
	//	CCamera::GetInfo().pChar = &pObject->GetPosition();
	//	CCamera::GetInfo().pMove = &pObject->GetPosition();
	//	CManager::GetCamera()->GetpDistance() = NULL;
	//	CManager::GetCamera()->Reset();
	//}

	// �G
	CEnemy *pEnemy;
	if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
		pEnemy->Set(D3DXVECTOR3(-8500.0f, -400.0f, -2500.0f),
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_ENEMY);
	}

	//if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
	//	pEnemy->Set(D3DXVECTOR3(150.0f, 50.0f, 0.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY);
	//}
	//if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
	//	pEnemy->Set(D3DXVECTOR3(-150.0f, 50.0f, 0.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY);
	//}

	return S_OK;
}
//=============================================================================
// ���U���g�X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();	// �L�[�{�[�h���l��
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//�W���C�p�b�h���l��

	if (CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
	{
		if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A))
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_ENTTER);
			CManager::SetFade(CManager::MODE_RANKING, 0);
		}
	}

	// �G�����ԍ��ŏo�Ă���
	CEnemy *pEnemy;

	if (m_nCntEnemy <= 2)
	{
		m_nTimeEnemy++;
	}

	if (m_nTimeEnemy == 210)
	{
		if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
			pEnemy->Set(D3DXVECTOR3(-8700.0f, -400.0f, -2500.0f),
				D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_ENEMY);
		}
		m_nCntEnemy++;
	}

	if (m_nTimeEnemy == 100)
	{
		if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
			pEnemy->Set(D3DXVECTOR3(-8300.0f, -400.0f, -2500.0f),
				D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_ENEMY);
		}
		m_nCntEnemy++;
	}

}
//=============================================================================
// ���U���g�I������
//=============================================================================
void CResult::Uninit(void)
{
	CManager::GetSound()->Stop(CSound::LABEL_RESULT);

}
//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void CResult::Draw(void)
{

}
//=============================================================================
// ���U���g����������
//=============================================================================
HRESULT CResult_UI::Init(void)
{
	int &nTime = CManager::GetResult()->GetnTime();
	int &nRankIn = CManager::GetResult()->GetnRankIn();
	//int nTime = rand() % 100000;
	int nWKData;
	int nWKRank = 5;
	m_aData[5] = nTime;

	// ���[�h
	Load();

	// ����ւ�
	for (int nCount = 0; nCount < MAX_DATA; nCount++)
	{
		for (int nNumber = 0; nNumber < MAX_DATA - 1; nNumber++)
		{
			if (m_aData[nNumber] > m_aData[nNumber + 1])
			{
				if (nWKRank == nNumber + 1) { nWKRank--; }
				nWKData = m_aData[nNumber];
				m_aData[nNumber] = m_aData[nNumber + 1];
				m_aData[nNumber + 1] = nWKData;
			}
		}
	}
	nRankIn = nWKRank;

	// �Z�[�u
	Save();

	if (Create(m_pNumber[0]))
	{// ���U���g�X�R�A
		m_pNumber[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 0.0f), 50.0f, 70.0f, nTime / 60 / 60, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CNumber::STATE_SCORE);
	}
	if (Create(m_pNumber[1]))
	{// ���U���g�X�R�A
		m_pNumber[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2, 0.0f), 50.0f, 70.0f, nTime / 60 % 60, 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CNumber::STATE_SCORE);
	}
	CManager::GetSound()->Play(CSound::LABEL_RESULT);

	return S_OK;
}
//=============================================================================
// ���U���g�X�V����
//=============================================================================
void CResult_UI::Update(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_pNumber[nCount]->Update();
	}
}
//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void CResult_UI::Draw(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_pNumber[nCount]->Draw();
	}
}
//=============================================================================
// ���U���g�I������
//=============================================================================
void CResult_UI::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_pNumber[nCount]->Uninit();
	}
}
//=============================================================================
// ���[�h
//=============================================================================
void CResult_UI::Load(void)
{
	FILE *pFile;

	// �t�@�C���I�[�v��
	pFile = fopen("data/TEXT/ranking.txt", "r");

	if (pFile != NULL)
	{// �t�@�C�����J������
		for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
		{
			fscanf(pFile, "%d\n", &m_aData[nCount]);
		}
		// �t�@�C�������
		fclose(pFile);
	}

	else
	{
		printf("�t�@�C�����J���܂���\n");
	}
}
//=============================================================================
// �Z�[�u
//=============================================================================
void CResult_UI::Save(void)
{
	FILE *pFile;

	// �t�@�C���I�[�v��
	pFile = fopen("data/TEXT/ranking.txt", "w");

	if (pFile != NULL)
	{// �t�@�C�����J������
		for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
		{
			fprintf(pFile, "%d\n", m_aData[nCount]);
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		printf("�t�@�C�����J���܂���\n");
	}
}
//=============================================================================
// �I�u�W�F�N�g�̓ǂݍ��ݐ���
//=============================================================================
void CResult::LoadObject(void)
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
		pField->GetDrawType() = CScene::DRAW_TYPE_ADD;
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
