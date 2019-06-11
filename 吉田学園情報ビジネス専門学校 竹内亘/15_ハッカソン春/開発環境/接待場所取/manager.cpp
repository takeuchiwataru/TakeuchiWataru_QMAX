//---------------------------------------------------------------------
// �}�l�[�W���[���� [manager.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "billboard.h"
#include "player.h"
#include "input.h"
#include "meshField.h"
#include "meshOrbit.h"

#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "ranking.h"

#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME						("model.txt")

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
static CRenderer *m_pRenderer;
CRenderer		*CManager::m_pRenderer			= NULL;
CInputKeyboard	*CManager::m_pInput				= NULL;
CInputJoypad	*CManager::m_pInputJoypad		= NULL;
CSound			*CManager::m_pSound[MAX_SOUND] = {};
CDebugProc		*CManager::m_pDebugProc			= {};
CScene3D        *CManager::m_Scene3D			= NULL;
CSceneMeshField *CManager::m_MeshField			= NULL;

LPD3DXMESH					CManager::m_pMeshModel[MAX_PARTS] = {};
LPD3DXBUFFER				CManager::m_pBuffMatModel[MAX_PARTS] = {};
LPDIRECT3DTEXTURE9			CManager::m_pTextureModel[MAX_PARTS] = {};
DWORD						CManager::m_nNumMatModel[MAX_PARTS] = {};

CManager::MODE	CManager::m_mode = CManager::MODE_TITLE;
CFade			*CManager::m_pFade = NULL;

CTitle			*CManager::m_pTitle			= NULL;
CTutorial		*CManager::m_pTutorial		= NULL;
CGame			*CManager::m_pGame			= NULL;
CResult			*CManager::m_pResult		= NULL;
CGameover		*CManager::m_pGameover		= NULL;
CRanking		*CManager::m_pRanking		= NULL;
CCamera			*CManager::m_pCamera		= NULL;
CLight			*CManager::m_pLight			= NULL;
int				CManager::m_nScore[MAX_RANKING] = {};
int				CManager::m_nGameScore = 0;
int				CManager::m_nItemNum = 0;
int				CManager::m_nTime = 0;
int				CManager::m_nTitle = 0;
//--------------------------------------------
//�}�l�[�W���[�N���X �R���X�g���N�^
//--------------------------------------------
CManager::CManager()
{
}

//--------------------------------------------
//�}�l�[�W���[�N���X �f�X�g���N�^
//--------------------------------------------
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, bool bWindow)
{
	//ReleaseAll�ŏ����Ȃ����̂�new�ŏ���create�ł͂Ȃ�
	//�����_�����O������
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{	// ����������
		m_pRenderer->Init(hWnd, bWindow);
	}

	// ���͏�񏉊���
	m_pInput = new CInputKeyboard;
	if (m_pInput != NULL)
	{	// ����������
		m_pInput->Init(hInstance,hWnd);
	}
	//�Q�[���p�b�h
	m_pInputJoypad = new CInputJoypad;
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Init(hInstance, hWnd);
	}

	for (int nCnt = 0; nCnt < MAX_SOUND; nCnt++)
	{
		m_pSound[nCnt] = new CSound;
		if (m_pSound[nCnt] != NULL)
		{
			m_pSound[nCnt]->InitSound(hWnd);
		}
	}

	//�J����������
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{
		m_pCamera->Init();
	}
	//���C�g������
	m_pLight = new CLight;
	if (m_pLight != NULL)
	{
		m_pLight->Init();
	}

#ifdef _DEBUG
	//�f�o�b�N�v���V�[�W���̏�����
	m_pDebugProc->Init();
#endif

	//�����L���O�̏�����
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_nScore[nCnt] = 5000 - (nCnt * 1000);
	}

	m_nTitle = 0;

	//�ŏ��̃��[�h��ݒ�
	m_mode = MODE_TITLE;
	//�t�F�[�h�̐ݒ�
	m_pFade = CFade::Create(m_mode);
	//���݂̃��[�h�̐ݒ�
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// �}�l�[�W���[�N���X �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�L�[�{�[�h�N���X�̔j��
	if (m_pInput != NULL)
	{	// �I������
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;
	}
	//�Q�[���p�b�h
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}
	//�����_�����O�N���X�̔j��
	if (m_pRenderer != NULL)
	{	// �I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�t�F�[�h�N���X�̔j��
	if (m_pFade != NULL)
	{	// �I������
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}


	for (int nCnt = 0; nCnt < MAX_SOUND; nCnt++)
	{
		if (m_pSound[nCnt] != NULL)
		{
			m_pSound[nCnt]->UninitSound();
			delete m_pSound[nCnt];
			m_pSound[nCnt] = NULL;
		}
	}

	//�^�C�g���N���X�̔j��
	if (m_pTitle != NULL)
	{	// �I������
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;
	}
	//�`���[�g���A���N���X�̔j��
	if (m_pTutorial != NULL)
	{	// �I������
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;
	}
	//�Q�[���N���X�̔j��
	if (m_pGame != NULL)
	{	// �I������
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
	}
	//���U���g�N���X�̔j��
	if (m_pResult != NULL)
	{	// �I������
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = NULL;
	}
	//�Q�[���I�[�o�[�N���X�̔j��
	if (m_pGameover != NULL)
	{	// �I������
		m_pGameover->Uninit();
		delete m_pGameover;
		m_pGameover = NULL;
	}
	//�����L���O�N���X�̔j��
	if (m_pRanking != NULL)
	{	// �I������
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;
	}

	//�J�����I������
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//���C�g�I������
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//�I�u�W�F�N�g�N���X�̔j��
	CScene::ReleaseAll();
}

//=============================================================================
// �}�l�[�W���[�N���X �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �����_�����O�X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// �L�[�{�[�h�X�V����
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}
	// �Q�[���p�b�h�X�V����
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();
	}
	// �t�F�[�h�X�V����
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	//�J�����X�V����
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	//���C�g�X�V����
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

#ifdef _DEBUG
	//�f�o�b�N�v���V�[�W���̍X�V
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Update();
	}

	CDebugProc::Print(1, " �^�C�g�� %d \n", m_nTitle);

#endif

	//���[�h���Ƃ̍X�V����
	switch (m_mode)
	{
	case MODE_TITLE:
		//�^�C�g���̍X�V����
		m_pTitle->Update();
		break;
	case MODE_TUTORIAL:
		//�`���[�g���A���̍X�V����
		m_pTutorial->Update();
		break;
	case MODE_GAME:
		//�Q�[���̍X�V����
		m_pGame->Update();
		break;
	case MODE_RESULT:
		//���U���g�̍X�V����
		m_pResult->Update();
		break;
	case MODE_GAMEOVER:
		//�Q�[���I�[�o�[�̍X�V����
		m_pGameover->Update();
		break;
	case MODE_RANKING:
		//�����L���O�̍X�V����
		m_pRanking->Update();
		break;
	}
}

//=============================================================================
// �}�l�[�W���[�N���X �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	//�����_�����O��ݒ�
	if (m_pRenderer != NULL)
	{	// �`�揈��
		m_pRenderer->Draw();
	}

	//�J������ݒ�
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}

	//���[�h���Ƃ̍X�V����
	switch (m_mode)
	{
	case MODE_TITLE:
		//�^�C�g���̕`�揈��
		m_pTitle->Draw();
		break;
	case MODE_TUTORIAL:
		//�`���[�g���A���̕`�揈��
		m_pTutorial->Draw();
		break;
	case MODE_GAME:
		//�Q�[���̕`�揈��
		m_pGame->Draw();
		break;
	case MODE_RESULT:
		//���U���g�̕`�揈��
		m_pResult->Draw();
		break;
	case MODE_GAMEOVER:
		//�Q�[���I�[�o�[�̕`�揈��
		m_pGameover->Draw();
		break;
	case MODE_RANKING:
		//�����L���O�̕`�揈��
		m_pRanking->Draw();
		break;
	}
}
//=============================================================================
// �}�l�[�W���[�N���X �����_�����O���擾
//=============================================================================
CRenderer *CManager::GetRenderer (void)
{
	return m_pRenderer;
}

//=============================================================================
// �}�l�[�W���[�N���X �L�[�{�[�h���擾
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInput;
}
//=============================================================================
// �}�l�[�W���[�N���X �W���C�X�e�B�b�N���擾
//=============================================================================
CInputJoypad *CManager::GetCInputJoypad(void)
{
	return m_pInputJoypad;
}
//=============================================================================
// �}�l�[�W���[�N���X �T�E���h���擾
//=============================================================================
CSound *CManager::GetSound(int nNum)
{
	return m_pSound[nNum];
}

//=============================================================================
// �}�l�[�W���[�N���X �V�[��3D���擾
//=============================================================================
CScene3D * CManager::GetScene3D(void)
{
	return m_Scene3D;
}

//=============================================================================
// �}�l�[�W���[�N���X ���b�V���t�B�[���h���擾
//=============================================================================
CSceneMeshField * CManager::GetSceneMeshField(void)
{
	return m_MeshField;
}

//=============================================================================
// �}�l�[�W���[�N���X �t�F�[�h���擾
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	//���݂̃��[�h
	switch (m_mode)
	{
	case MODE_TITLE:
		//BGM�̒�~
		if (m_pTitle != NULL)
		{
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_TITLE);
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;	//NULL�ɂ���
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			//BGM�̒�~
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_TUTORIAL);
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;	//NULL�ɂ���
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			//BGM�̒�~
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_GAME);
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;		//NULL�ɂ���
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			//BGM�̒�~
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_RESULT);
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;		//NULL�ɂ���
		}
		break;
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			//BGM�̒�~
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_GAMEOVER);
			m_pGameover->Uninit();
			delete m_pGameover;
			m_pGameover = NULL;		//NULL�ɂ���
		}
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			//BGM�̒�~
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_RANKING);
			m_nGameScore = 0;
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;		//NULL�ɂ���
		}
		break;
	}

	//���݂̃��[�h��؂�ւ�
	m_mode = mode;

	//�V������ʂ̃��[�h
	switch (mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{//BGM�̍Đ�
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_TITLE);
			m_nGameScore = 0;
			m_nTitle++;
			m_pTitle = CTitle::Create();
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{//BGM�̍Đ�
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_TUTORIAL);
			m_pTutorial->Load();
			m_pTutorial = CTutorial::Create();
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{//BGM�̍Đ�
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_GAME);
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{//BGM�̍Đ�
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_RESULT);
			m_pResult = CResult::Create();
		}
		break;
	case MODE_GAMEOVER:
		if (m_pGameover == NULL)
		{//BGM�̍Đ�
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_GAMEOVER);
			m_pGameover = CGameover::Create();
		}
		break;
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{//BGM�̍Đ�
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_RANKING);
			m_pRanking = CRanking::Create();
		}
		break;
	}
}

//=============================================================================
// ���[�h�̎擾����
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// �}�l�[�W���[�N���X �J�������擾
//=============================================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// �}�l�[�W���[�N���X ���C�g���擾
//=============================================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}



//=============================================================================
// �����L���O���ёւ��Z�b�g
//=============================================================================
void CManager::RankingScore(int nScore)
{
	int nSaveScore = 0;

	//�X�R�A�X�V
	if (m_nScore[MAX_RANKING - 1] < nScore)
	{//�V�����X�R�A������������ւ�
		m_nScore[MAX_RANKING - 1] = nScore;
		//break;
	}
	//�\�[�g���� �傫����
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < MAX_RANKING - 1; nCnt2++)
		{
			if (m_nScore[nCnt2] < m_nScore[nCnt2 + 1])
			{//���Ɣ�ׂĎ�����������������ւ�
				nSaveScore = m_nScore[nCnt2];			//�ꎞ�ۑ�
				m_nScore[nCnt2] = m_nScore[nCnt2 + 1];	//���������ւ�
				m_nScore[nCnt2 + 1] = nSaveScore;		//�ۑ���������������
			}
		}
	}
}
//=============================================================================
//�����L���O���擾
//=============================================================================
int *CManager::GetRankingScore(int nidx)
{
	return &m_nScore[nidx];
}
//=============================================================================
//�Q�[���̃X�R�A���Z�b�g
//=============================================================================
void CManager::SetGameScore(int nScore)
{
	m_nGameScore = nScore;
}
//=============================================================================
//�Q�[���̃X�R�A���擾
//=============================================================================
int * CManager::GetGameScore()
{
	return &m_nGameScore;
}

//=============================================================================
//�Q�[���̃A�C�e�������擾
//=============================================================================
int * CManager::GetGameItem()
{
	return &m_nItemNum;
}

//=============================================================================
//�Q�[���̃^�C�����擾
//=============================================================================
int * CManager::GetGameTime()
{
	return &m_nTime;
}
