//=============================================================================
//
// �Q�[������ [Game.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include"Scene.h"
#include "manager.h"
#include "scene.h"
#include "Effect.h"
#include "player.h"
#include "mesh.h"
#include "dungeon.h"
#include "SceneModel.h"
#include "enemy.h"

#include "Game.h"
#include "Result.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
bool	CGame::m_bDuo = false;	//2�l�v���C���ǂ���

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME ("data//TEXT//Stage.txt")

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CGame::Init(void)
{
	m_state = STATE_NONE;
	m_fCntState = 0.0f;
	m_nCntTime = 0;
	CMotion::Load();
	CCharacter::Load();
	CSceneObjct::InitSwitch(false);

	CLight *pLight;		Create(pLight);		//���C�g�̐���
	CCamera *pCamera;	Create(pCamera);	//�J�����̐���

	CPlayer *pChar;
	if (SceneCreate(pChar, CHAR_PRIORITY))
	{
		pChar->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE, -100.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), CMotion::TYPE_BOX_Sword);
	}
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

	//���A-50
	//if (SceneCreate(pObject, MODEL_PRIORITY))
	//{
	//	pObject->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE, 150.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE + 300.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_DFIELD, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
	//}
	//if (SceneCreate(pObject, MODEL_PRIORITY))
	//{
	//	pObject->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE + 300, 150.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE + 300.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_MFIELD, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
	//}
	//if (SceneCreate(pObject, MODEL_PRIORITY))
	//{
	//	pObject->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE + 600, 150.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE + 300.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_MFIELD2, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
	//}


	//CSceneAnim3D *pAnim;
	//if (SceneCreate(pAnim, 3))
	//{
	//	pAnim->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE, 0.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE - 300.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(100.0f, 400.0f, 0.0f), CScene::TEX_Fire, true,
	//		CScene::DRAW_TYPE_MULTIPLY, 0, 8, 1, 3, CSceneAnim3D::ANIMATION_LOOP, CScene3D::STATE_FIRE);
	//}
	//CEnemy *pEnemy;
	//if (SceneCreate(pEnemy, CHAR_PRIORITY)) { pEnemy->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE, 0.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE + 1001.0f), 
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY); }

	LoadObject();
	CManager::GetSound()->Play(CSound::LABEL_GAME);
	CManager::GetSound()->Play(CSound::LABEL_SE_START);	//�S��
	return S_OK;
}
//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
	//if (pInputKey->GetTrigger(DIK_RETURN))
	//{
	//	CManager::SetFade(CManager::MODE_RESULT, 0); 
	//}
	switch (m_state)
	{
	case STATE_NONE:
		Pause();	//�|�[�Y�̍X�V
		break;
	case STATE_CLEAR:
		m_fCntState += 1.0f;

		switch ((int)m_fCntState)
		{
		case 60:
			break;
		case 240:
			CManager::SetFade(CManager::MODE_RESULT, 0);
			break;
		}
		if (m_fCntState > 90 && (
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(0)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(0)->GetTrigger(INPUT_B) ||
			CManager::GetInputJoyPad(1)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_B) ||
			CManager::GetInputKey()->GetTrigger(DIK_RETURN)))
		{
			CManager::SetFade(CManager::MODE_RESULT, 0);
		}
		break;

	case STATE_OVER:
		m_fCntState += 1.0f;
		switch ((int)m_fCntState)
		{
		case 240:
			CManager::SetFade(CManager::MODE_TITLE, 0);
			break;
		}
		if (m_fCntState > 60 && (
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_START) || 
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_A) ||
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_B) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_B) ||
			CManager::GetInputKey()->GetTrigger(DIK_RETURN)))
		{
			CManager::SetFade(CManager::MODE_TITLE, 0);
		}
		break;
	}
	
}
//=============================================================================
// �Q�[���̏I������
//=============================================================================
void	CGame::Uninit(void)
{
	//BGM�̃X�g�b�v
	CManager::GetSound()->Stop();

	for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
	{//�S�|�[�Y�̔j��
		if (m_pScene2D[nCount] != NULL)
		{//��������Ă���΍폜
			m_pScene2D[nCount]->Uninit();
			m_pScene2D[nCount] = NULL;
		}
	}

	CManager::GetCamera()->Uninit();
	CManager::GetLight()->Uninit();
}
//=============================================================================
// �Q�[���̏�ԕύX����
//=============================================================================
void	CGame::SetState(STATE state)
{
	CScene2D *pScene2D;

	if (CManager::GetMode() != CManager::MODE_GAME) { return; }
	if (m_state == STATE_NONE)
	{//�ʏ��ԂȂ�
		m_state = state;
		switch (m_state)
		{
		case STATE_CLEAR:
			CManager::GetSound()->Stop();
			CManager::GetSound()->Play(CSound::LABEL_CLEAR);

			m_fCntState = 0.0f;
			CManager::GetResult()->GetnTime() = m_nCntTime;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//��ʂ��Â�����
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}
			break;
		case STATE_OVER:
			CManager::GetSound()->Stop();
			CManager::GetSound()->Play(CSound::LABEL_OVER);
			CManager::GetSound()->Play(CSound::LABEL_SE_DETH);
			m_fCntState = 0.0f;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//��ʂ��Â�����
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}
			break;
		}
	}
}
//=============================================================================
// �Q�[���̃|�[�Y����
//=============================================================================
void	CGame::Pause(void)
{
	if (CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
	{
		CSound *pSound = CManager::GetSound();					//�T�E���h�̃|�C���^���擾
		CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
		CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//�W���C�p�b�h���l��
		CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//�W���C�p�b�h���l��
		bool bSelect = false;
		bool bPause = true;

		if (!CScene::GetbPause())
		{//�|�[�Y�łȂ�
			m_nCntTime++;
			if (pInputKey->GetTrigger(DIK_P) || pInputPad0->GetTrigger(INPUT_START) || pInputPad1->GetTrigger(INPUT_START))
			{//�|�[�Y�N��
				CManager::GetSound()->Play(CSound::LABEL_SE_PAUSE);

				CScene::GetbPause() = true;
				bSelect = true;
				m_nSelect = 1;

				if (SceneCreate(m_pScene2D[0], PAUSE_PRIORITY))
				{//��ʈÂ�����
					m_pScene2D[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
						D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.65f), CScene::TEX_MAX);
				}
				if (SceneCreate(m_pScene2D[1], PAUSE_PRIORITY))
				{//��Z���N�g�@�R���e�j���[
					m_pScene2D[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - GAME_PAUSE_INTERVAL, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 0, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Pause);
				}
				if (SceneCreate(m_pScene2D[2], PAUSE_PRIORITY))
				{//���Z���N�g�@���g���C
					m_pScene2D[2]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 1, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Pause);
				}
				if (SceneCreate(m_pScene2D[3], PAUSE_PRIORITY))
				{//���Z���N�g�@���^�C�A
					m_pScene2D[3]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 2, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Pause);
				}
				if (SceneCreate(m_pScene2D[4], PAUSE_PRIORITY))
				{//�}�[�J�[
					(m_pScene2D[4]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - GAME_PAUSE_LOGOX, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), 50.0f, 50.0f, D3DX_PI, 0, 1, 1, 100.0f, CScene2D::STATE_FLASH2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_MAX));
				}
			}
		}
		else if (pInputKey->GetTrigger(DIK_P) || pInputPad0->GetTrigger(INPUT_START) || pInputPad1->GetTrigger(INPUT_START)
			|| pInputPad0->GetTrigger(INPUT_B) || pInputPad1->GetTrigger(INPUT_B))
		{//�|�[�Y�~��
			bPause = false;
			CManager::GetSound()->Play(CSound::LABEL_SE_CANCEL);
		}

		if (CScene::GetbPause())
		{//�|�[�Y��
			if (pInputKey->GetTPress(DIK_UP) || 
				pInputPad0->GetTPress(INPUT_UP) || pInputPad0->GetTPress(INPUT_LS_U) ||
				pInputPad1->GetTPress(INPUT_UP) || pInputPad1->GetTPress(INPUT_LS_U))
			{ m_nSelect = (m_nSelect - 1 + 2) % 3 + 1; bSelect = true; }

			if (pInputKey->GetTPress(DIK_DOWN) || 
				pInputPad0->GetTPress(INPUT_DOWN) || pInputPad0->GetTPress(INPUT_LS_D) ||
				pInputPad1->GetTPress(INPUT_DOWN) || pInputPad1->GetTPress(INPUT_LS_D))
			{ m_nSelect = (m_nSelect - 1 + 1) % 3 + 1;  bSelect = true; }

			if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A) || pInputPad1->GetTrigger(INPUT_A))
			{
				CManager::GetSound()->Play(CSound::LABEL_SE_ENTTER);
				if (m_nSelect == 1) { bPause = false; }
				else if (m_nSelect == 2) { CManager::SetFade(CManager::MODE_GAME, 0); CScene::GetbPause() = false; return; }
				else if (m_nSelect == 3) { CManager::SetFade(CManager::MODE_TITLE, 0); CScene::GetbPause() = false; return; }
			}

			if (!bPause)
			{//�|�[�Y���I������
				CScene::GetbPause() = false;

				for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
				{//�S�|�[�Y�̔j��
					if (m_pScene2D[nCount] != NULL)
					{//��������Ă���΍폜
						m_pScene2D[nCount]->Uninit();
						m_pScene2D[nCount] = NULL;
					}
				}
			}
			else if (bSelect)
			{//��Ԃ̍X�V
				//CSceneAnim2D *p2DAnim;
				CManager::GetSound()->Play(CSound::LABEL_SE_CURSOR);

				for (int nCount = 1; nCount <= 3; nCount++)
				{
					if (m_nSelect == nCount)
					{ //�I������Ă���
						m_pScene2D[nCount]->GetState()[0] = CScene2D::STATE_BIG;
					}
					else
					{ //�I������ĂȂ�
						m_pScene2D[nCount]->GetState()[0] = CScene2D::STATE_SMALL;
					}
				}
				m_pScene2D[4]->SetPosition(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(-GAME_PAUSE_LOGOX * 1.5f, 0.0f, 0.0f));
				////���G�t�F�N�g
				//if (SceneCreate(p2DAnim, PAUSE_PRIORITY))
				//{
				//	p2DAnim->Set(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 200.0f, D3DX_PI, 0, 3, 3, 3, 0.0f, CScene2D::STATE_FADEIN,
				//		CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_MAX);
				//	p2DAnim->BindDrawType(CScene::DRAW_TYPE_OVERLAY);
				//}
			}
		}
	}//�t�F�[�h�m�F

}
//=============================================================================
// �I�u�W�F�N�g�̓ǂݍ��ݐ���
//=============================================================================
void CGame::LoadObject(void)
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
				CManager::GetPlayer()->Getpos() = pos;
				CManager::GetPlayer()->Getrot().y = D3DX_PI * -0.5f;
				CManager::GetPlayer()->GetfRot() = D3DX_PI * -0.5f;
				CManager::GetCamera()->GetRot().y = D3DX_PI * -0.5f;
				CManager::GetCamera()->Reset();

				CEnemy *pEnemy;
				if (SceneCreate(pEnemy, CHAR_PRIORITY)) { pEnemy->Set(pos + D3DXVECTOR3(2000.0f, 0.0f, 200.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY); }

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
}