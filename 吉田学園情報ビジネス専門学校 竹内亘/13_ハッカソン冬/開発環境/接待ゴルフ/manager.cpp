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
#include "bullet.h"
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
CRenderer		*CManager::m_pRenderer	= NULL;
CInputKeyboard	*CManager::m_pInput		= NULL;
CSound			*CManager::m_pSound		= NULL;
CDebugProc		*CManager::m_pDebugProc = {};
CScene3D        *CManager::m_Scene3D	= NULL;
CSceneMeshField *CManager::m_MeshField	= NULL;

LPD3DXMESH					CManager::m_pMeshModel[MAX_PARTS] = {};
LPD3DXBUFFER				CManager::m_pBuffMatModel[MAX_PARTS] = {};
LPDIRECT3DTEXTURE9			CManager::m_pTextureModel[MAX_PARTS] = {};
DWORD						CManager::m_nNumMatModel[MAX_PARTS] = {};

CManager::MODE	CManager::m_mode = CManager::MODE_TITLE;
CFade			*CManager::m_pFade = NULL;

CTitle			*CManager::m_pTitle = NULL;
CTutorial		*CManager::m_pTutorial = NULL;
CGame			*CManager::m_pGame = NULL;
CResult			*CManager::m_pResult = NULL;
CGameover		*CManager::m_pGameover = NULL;
CRanking		*CManager::m_pRanking = NULL;
CDirectInput    *CManager::m_pJoyPad = NULL;			//�W���C�p�b�h

int				CManager::m_nGameScore = 0;
int CManager::m_aScore[MAX_RANKING] = {};	// �j�ǉ�

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
	//�T�E���h������
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->InitSound(hWnd);
	}

	if (m_pJoyPad == NULL)
	{
		//�W���C�p�b�h�̃������𓮓I�m��
		m_pJoyPad = new CDirectInput;

		if (m_pJoyPad != NULL)
		{
			// ����������
			m_pJoyPad->Init(hInstance, hWnd);
		}
		else
		{
			MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
		}
}
	else
	{
		MessageBox(0, "NULL�ł���", "�x��", MB_OK);
	}

#ifdef _DEBUG
	//�f�o�b�N�v���V�[�W���̏�����
	m_pDebugProc->Init();
#endif

	//�������N���X�������
	//�e�N�X�`���̃��[�h
	CBullet::Load();

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
	//�I�u�W�F�N�g�N���X�̔j��
	CScene::ReleaseAll();

	CPlayer::UnLoad();
	//�L�[�{�[�h�N���X�̔j��
	if (m_pInput != NULL)
	{	// �I������
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;
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
	//�T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
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

	//�W���C�p�b�h�N���X�̔j��
	if (m_pJoyPad != NULL)
	{
		// �I������
		m_pJoyPad->Uninit();

		//�������̊J��
		delete m_pJoyPad;

		//NULL�ɂ���
		m_pJoyPad = NULL;
	}
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
	// �t�F�[�h�X�V����
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	if (m_pJoyPad != NULL)
	{
		//�W���C�p�b�h�̍X�V����
		m_pJoyPad->Update();
	}

#ifdef _DEBUG
	//�f�o�b�N�v���V�[�W���̍X�V
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Update();
	}
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
// �}�l�[�W���[�N���X �T�E���h���擾
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
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

#ifdef _DEBUG
//=============================================================================
// �}�l�[�W���[�N���X ��������
//=============================================================================
void CManager::CreateSceneDebug(void)
{

}
#endif

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
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_TITLE);
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;	//NULL�ɂ���
		break;
	case MODE_TUTORIAL:
		//BGM�̒�~
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_TUTORIAL);
		//m_pTutorial->UnLoad();
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;	//NULL�ɂ���
		break;
	case MODE_GAME:
		//BGM�̒�~
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_GAME);
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;		//NULL�ɂ���
		break;
	case MODE_RESULT:
		//BGM�̒�~
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_RESULT);
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = NULL;		//NULL�ɂ���
		break;
	case MODE_GAMEOVER:
		//BGM�̒�~
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_GAMEOVER);
		m_pGameover->Uninit();
		delete m_pGameover;
		m_pGameover = NULL;		//NULL�ɂ���
		break;
	case MODE_RANKING:
		//BGM�̒�~
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_RANKING);
		m_nGameScore = 0;
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;		//NULL�ɂ���
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
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_TITLE);
			m_nGameScore = 0;
			m_pTitle = CTitle::Create();
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{//BGM�̍Đ�
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_TUTORIAL);
			m_pTutorial->Load();
			m_pTutorial = CTutorial::Create();
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{//BGM�̍Đ�
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_GAME);
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{//BGM�̍Đ�
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_RESULT);
			m_pResult = CResult::Create();
		}
		break;
	case MODE_GAMEOVER:
		if (m_pGameover == NULL)
		{//BGM�̍Đ�
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_GAMEOVER);
			m_pGameover = CGameover::Create();
		}
		break;
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{//BGM�̍Đ�
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_RANKING);
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
// �t�@�C���ǂݍ���
//=============================================================================
void CManager::FileLoad(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile;		//�t�@�C���|�C���^
	char *pStrcur;		//���݂̐擪�̕�����
	char aLine[256];	//������
	char aStr[256];		//�ꎞ�ۑ�������
	int nIndex = 0;		//���݂̃C���f�b�N�X
	int nWord = 0;		//�|�b�v�ŕԂ��ꂽ�l��ێ�

	D3DXVECTOR3 ParentPos;	//�e�̈ʒu�����擾
#if 1
							//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME, "r");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		while (true)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//���o��
				pStrcur += strlen("NUM_MODEL = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				m_nNumModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������߂�
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//���o��
						pStrcur += strlen("MODEL_FILENAME = ");

						//�������ݒ�
						strcpy(aStr, pStrcur);

						//�K�v�ȕ�����̍Ō�̕����܂ł̕������𐔂���
						int nNullNum = PopString(pStrcur, &aStr[0]);

						//����������߂�
						strcpy(aStr, pStrcur);

						//�Ō�̕�����NULL����������
						aStr[nNullNum - 1] = '\0';

						//�Ώۂ̕����񂩂甲���o��
						strcpy(&m_aFileNameModel[nCntModel][0], aStr);

						// X�t�@�C���̓ǂݍ���
						D3DXLoadMeshFromX(&m_aFileNameModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMatModel[nCntModel],
							NULL,
							&m_nNumMatModel[nCntModel],
							&m_pMeshModel[nCntModel]);
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}

			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//TYPE��ǂݍ���
				if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
				{
					//���o��
					pStrcur += strlen("TYPE = ");
					//������̐擪��ݒ�
					strcpy(aStr, pStrcur);
					//�����񔲂��o��
					nIndex = atoi(pStrcur);
				}
			}

			//�X�N���v�g�̏I���
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	else
	{	//�t�@�C�����J���Ȃ�����
		printf("�t�@�C�����J���܂���ł���\n");
	}
	//�t�@�C�������
	fclose(pFile);
#endif

}

//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CManager::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//�P�s���ǂݍ���
		fgets(&pDst[0], 256, pFile);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//�@�t�@�C���ǂݍ��ݐ擪��r��
//=============================================================================
char *CManager::GetLineTop(char * pStr)
{
	while (1)
	{
		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//�@��������Ԃ�
//=============================================================================
int CManager::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//���o��
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//���o��
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//������̐���Ԃ�
	return nWord;
}

//=============================================================================
// ���͂̎擾
//=============================================================================
CDirectInput *CManager::GetJoypad(void)
{
	return m_pJoyPad;
}

//=============================================================================
// �����L���O�X�R�A�̎擾(�j�ǉ�)
//=============================================================================
int CManager::GetRanking(int index)
{
	return m_aScore[index];
}
//=============================================================================
// �����L���O�X�R�A�̎擾(�j�ǉ�)
//=============================================================================
void CManager::GetRankingScore(int nScore)
{
	int nData = 0;

	if (m_aScore[MAX_RANKING - 1] <= nScore)
	{
		m_aScore[MAX_RANKING - 1] = nScore;
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nNumber = 0; nNumber < MAX_RANKING - 1; nNumber++)
		{
			if (m_aScore[nNumber] < m_aScore[nNumber + 1])
			{
				nData = m_aScore[nNumber];
				m_aScore[nNumber] = m_aScore[nNumber + 1];
				m_aScore[nNumber + 1] = nData;
			}
		}
	}
}