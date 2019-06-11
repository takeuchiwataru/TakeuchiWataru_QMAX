//=============================================================================
//
// �}�l�[�W���[���� [Manager.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "light.h"
#include "spotLight.h"
#include "input.h"
#include "sound.h"

#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "motion.h"

#include "renderer.h"
#include "manager.h"

#include "Title.h"
#include "Select.h"
#include "Game.h"
#include "Practice.h"
#include "Ranking.h"
#include "Result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer		*CManager::m_pRenderer = NULL;			//�����_���[
CInputKeyboard	*CManager::m_pInputKey = NULL;			//�L�[�{�[�h
CInputJoyPad	*CManager::m_pJoyPad[JOYPAD_MAX] = {};	//�W���C�p�b�h
CDebugLog		*CManager::m_pDebugLog;					//�f�o�b�N���O
CManager::MODE	CManager::m_mode;						//���݂̃��[�h
CManager::MODE	CManager::m_NextMode;					//���̃��[�h
CFade			CManager::m_Fade;						//�t�F�[�h
CSound			*CManager::m_pSound = NULL;				//�T�E���h
int				CManager::m_nEndCount;					//�t�F�[�h�܂ł̃J�E���g
CCamera			*CManager::m_pCamera = NULL;			//�J����
CLight			*CManager::m_pLight = NULL;				//���C�g
CSpotLight		*CManager::m_pSpotLight = NULL;			//�X�|�b�g���C�g

CTitle			*CManager::m_pTitle = NULL;				//�^�C�g��
CSelect			*CManager::m_pSelect = NULL;			//�Z���N�g
CGame			*CManager::m_pGame = NULL;				//�Q�[��
CPractice		*CManager::m_pPractice = NULL;			//���K
CRanking		*CManager::m_pRanking = NULL;			//���K
CResult			*CManager::m_pResult = NULL;			//���K

CPlayer			*CManager::pPlayer = NULL;				//�v���C���[�̃|�C���^
														//=============================================================================
														// �R���X�g���N�^
														//=============================================================================
CManager::CManager(void)
{
	if (m_pRenderer == NULL)
	{//�����_���[�̐���
		m_pRenderer = new CRenderer;
	}
	if (m_pInputKey == NULL)
	{//�L�[�{�[�h�̐���
		m_pInputKey = new CInputKeyboard;
	}
	for (int nCount = 0; nCount < JOYPAD_MAX; nCount++)
	{//�W���C�p�b�h�̍ő吔��]
		if (m_pJoyPad[nCount] == NULL)
		{//�W���C�p�b�h�̐���
			Create(m_pJoyPad[nCount]);
		}
	}

	// �T�E���h�N���X�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}



	m_nEndCount = -1;
	m_pTitle = NULL;
	m_pSelect = NULL;
	m_pGame = NULL;
	m_pPractice = NULL;
	m_pRanking = NULL;
	m_pResult = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager(void) {}
//=============================================================================
// ����������
//=============================================================================
HRESULT  CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_pInputKey->Init(hInstance, hWnd);	//�L�[�{�[�h������
	m_pSound->Init(hWnd);

	//�f�o�b�N���O�̐���
	if (m_pDebugLog == NULL)
	{
		Create(m_pDebugLog);
	}

	m_mode = MODE_TITLE;
	m_NextMode = MODE_TITLE;
	SetMode();
	m_Fade.Init(CFade::STATE_OUT);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();
	m_Fade.Uninit();
	for (int nCount = 0; nCount < JOYPAD_MAX; nCount++) { m_pJoyPad[nCount]->Uninit(); }

	if (m_pInputKey != NULL)
	{//�L�[�{�[�h�̍폜
		m_pInputKey->Uninit();
		delete m_pInputKey;
		m_pInputKey = NULL;
	}
	if (m_pSound != NULL)
	{//�T�E���h�̍폜
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}


	if (m_pDebugLog != NULL)
	{//�f�o�b�N���O�̍폜
		m_pDebugLog->Uninit();
		delete m_pDebugLog;
		m_pDebugLog = NULL;
	}

	if (m_pCamera != NULL)
	{//�J�����̍폜
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{//���C�g�̍폜
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pSpotLight != NULL)
	{//���C�g�̍폜
		m_pSpotLight->Uninit();
		delete m_pSpotLight;
		m_pSpotLight = NULL;
	}

	if (m_pRenderer != NULL)
	{//�����_���[�̍폜
		m_pRenderer->UninitAll();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	delete this;
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CManager::Update(void)
{
	m_pSound->CountUp();
	m_Fade.Update();
	m_pInputKey->Update();
	m_pInputKey->GetCount();
	for (int nCount = 0; nCount < JOYPAD_MAX; nCount++) { m_pJoyPad[nCount]->Update(); }

	CScene::UpdateAll();
	if (!CScene::GetbPause())
	{
		if (CManager::GetCamera() != NULL) { CManager::GetCamera()->Update(); }
		if (CManager::GetLight() != NULL) { CManager::GetLight()->Update(); }
		if (CManager::GetpSpotLight() != NULL) { CManager::GetpSpotLight()->Update(); }
	}
	switch (m_mode)
	{//���[�h�ؑ�
	case MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Update(); }
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL) { m_pSelect->Update(); }
		break;
	case MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Update(); }
		break;
	case MODE_PRACTICE:
		if (m_pPractice != NULL) { m_pPractice->Update(); }
		break;
	case MODE_RESULT:
		if (m_pResult != NULL) { m_pResult->Update(); }
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL) { m_pRanking->Update(); }
		break;
	}

	if (m_nEndCount >= 0)
	{
		m_nEndCount--;
		if (m_nEndCount == -1) { m_Fade.Init(CFade::STATE_NOR_FADE); }
	}

	//���������̂������ŏ���
	CScene::UninitAll();
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}
//=============================================================================
// �t�F�[�h�Z�b�g����
//=============================================================================
void CManager::SetFade(MODE mode, int nEndCount)
{
	if (m_nEndCount < 0)
	{
		m_NextMode = mode;
		m_nEndCount = nEndCount;
	}
}
//=============================================================================
//�@���[�h�ؑ�
//=============================================================================
void CManager::SetMode(void)
{
	CScene::GetnCntStart() = 0;
	switch (m_mode)
	{//���[�h�ؑ�
	case MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Uninit(); delete m_pTitle; m_pTitle = NULL; }
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL) { m_pSelect->Uninit(); delete m_pSelect; m_pSelect = NULL; }
		break;
	case MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Uninit(); delete m_pGame; m_pGame = NULL; }
		break;
	case MODE_PRACTICE:
		if (m_pPractice != NULL) { m_pPractice->Uninit(); delete m_pPractice; m_pPractice = NULL; }
		break;
	case MODE_RESULT:
		if (m_pResult != NULL) { m_pResult->Uninit(); delete m_pResult; m_pResult = NULL; }
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL) { m_pRanking->Uninit(); delete m_pRanking; m_pRanking = NULL; }
		break;
	}

	CScene::ReleaseAll();

	m_mode = m_NextMode;
	switch (m_mode)
	{//���[�h�ؑ�
	case MODE_TITLE:
		CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�^�C�g���ɐ؂�ւ�\n");
		if (m_pTitle != NULL) { m_pTitle->Uninit(); delete m_pTitle; m_pTitle = NULL; }
		Create(m_pTitle);
		break;
	case MODE_SELECT:
		CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�Z���N�g�ɐ؂�ւ�\n");
		if (m_pSelect != NULL) { m_pSelect->Uninit(); delete m_pSelect; m_pSelect = NULL; }
		Create(m_pSelect);
		break;
	case MODE_GAME:
		CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�Q�[���ɐ؂�ւ�\n");
		if (m_pGame != NULL) { m_pGame->Uninit(); delete m_pGame; m_pGame = NULL; }
		Create(m_pGame);
		break;
	case MODE_PRACTICE:
		CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�v���N�e�B�X�ɐ؂�ւ�\n");
		if (m_pPractice != NULL) { m_pPractice->Uninit(); delete m_pPractice; m_pPractice = NULL; }
		Create(m_pPractice);
		break;
	case MODE_RESULT:
		CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "���U���g�ɐ؂�ւ�\n");
		if (m_pResult != NULL) { m_pResult->Uninit(); delete m_pResult; m_pResult = NULL; }
		Create(m_pResult);
		break;
	case MODE_RANKING:
		CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�����L���O�ɐ؂�ւ�\n");
		if (m_pRanking != NULL) { m_pRanking->Uninit(); delete m_pRanking; m_pRanking = NULL; }
		Create(m_pRanking);
		break;
	}
}
//=============================================================================
//�@�����_���Ő����v���C���[�擾
//=============================================================================
//CScenePlayer *&CManager::GetRandPlayer(void)
//{
//	//�����m�F
//	if (m_pPlayer[1] == NULL)
//	{//2�l��������Ă���
//		return m_pPlayer[0];
//	}
//	else if (m_pPlayer[1]->GetfLife()[0] == 0.0f)
//	{//2�l�ڂ����S���Ă���
//		return m_pPlayer[0];
//	}
//	else if (m_pPlayer[0]->GetfLife()[0] == 0.0f)
//	{//1�l�ڂ����S���Ă���
//		return m_pPlayer[1];
//	}
//
//	//�v���C���[���S�������Ă���
//	return m_pPlayer[rand() % MAX_PLAYER];
//}
//=============================================================================
//�@�߂��ɂ��鐶���v���C���[�擾
//=============================================================================
//CScenePlayer *&CManager::GetNearPlayer(D3DXVECTOR3 pos)
//{
//	if (m_pPlayer[1] == NULL)
//	{//2�l��������Ă���
//		return m_pPlayer[0];
//	}
//	else if (m_pPlayer[1]->GetfLife()[0] == 0.0f)
//	{//2�l�ڂ����S���Ă���
//		return m_pPlayer[0];
//	}
//	else if (m_pPlayer[0]->GetfLife()[0] == 0.0f)
//	{//1�l�ڂ����S���Ă���
//		return m_pPlayer[1];
//	}
//
//	//�v���C���[���S�������Ă���
//	D3DXVECTOR3 pos0 = m_pPlayer[0]->GetPositionOld()[0], pos1 = m_pPlayer[1]->GetPositionOld()[0];
//
//	//2�l��r���ď������ق���Ԃ�
//	if (powf(pos.x - pos0.x, 2) + powf(pos.z - pos0.z, 2) < powf(pos.x - pos1.x, 2) + powf(pos.z - pos1.z, 2))
//	{
//		return m_pPlayer[0];
//	}
//	else { return m_pPlayer[1]; }
//
//	return m_pPlayer[0];
//}
//=============================================================================
//�@�߂��ɂ��鐶���v���C���[�擾
//=============================================================================
//CScenePlayer *&CManager::GetNearPlayer(D3DXVECTOR3 pos, float &fDistance)
//{
//	if (m_pPlayer[1] == NULL)
//	{//2�l��������Ă���
//		return m_pPlayer[0];
//	}
//	else if (m_pPlayer[1]->GetfLife()[0] == 0.0f)
//	{//2�l�ڂ����S���Ă���
//		return m_pPlayer[0];
//	}
//	else if (m_pPlayer[0]->GetfLife()[0] == 0.0f)
//	{//1�l�ڂ����S���Ă���
//		return m_pPlayer[1];
//	}
//
//	//�v���C���[���S�������Ă���
//	D3DXVECTOR3 pos0 = m_pPlayer[0]->GetPositionOld()[0],
//				pos1 = m_pPlayer[1]->GetPositionOld()[0];
//	float		fDistance0 = (powf(pos.x - pos0.x, 2) + powf(pos.z - pos0.z, 2)),
//				fDistance1 = powf(pos.x - pos1.x, 2) + powf(pos.z - pos1.z, 2);
//
//	//2�l��r���ď������ق���Ԃ�
//	fDistance = powf(pos.x - pos0.x, 2) + powf(pos.z - pos0.z, 2);
//	if (fDistance0 < fDistance1)
//	{
//		fDistance = fDistance0; 
//		return m_pPlayer[0];
//	}
//	else 
//	{ 
//		fDistance = fDistance0; 
//		return m_pPlayer[1];
//	}
//
//	return m_pPlayer[0];
//}
