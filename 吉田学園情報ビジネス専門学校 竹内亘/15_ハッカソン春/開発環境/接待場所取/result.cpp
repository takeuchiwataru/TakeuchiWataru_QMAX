//---------------------------------------------------------------------
// ���U���g���� [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "result.h"
#include "manager.h"
#include "scene.h"
#include "Logo.h"

#include "fade.h"
#include "number.h"
#include "scene2D.h"
#include "game.h"
#include "objectBG.h"
#include "UIPressEnter.h"
#include "enemy.h"
#include "meshCylinder.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\ITEMLOGO.png"		//�e�N�X�`���̃t�@�C����
#define TEXTURENAME001			 "data\\TEXTURE\\UI\\LIMITLOGO.png"		//�e�N�X�`���̃t�@�C����


//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
CScore *CResult::m_pScore[1] = {};
D3DXVECTOR3 CResult::m_bluePos = D3DXVECTOR3(0, 0, 0);

//--------------------------------------------
//���U���g�N���X �R���X�g���N�^
//--------------------------------------------
CResult::CResult()
{
	m_nCntTimer = 0;
	m_nSoundCnt = 0;

	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		m_apTime[nCnt] = NULL;
		m_apItem[nCnt] = NULL;
	}
}

//--------------------------------------------
//���U���g�N���X �f�X�g���N�^
//--------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CResult *CResult::Create(void)
{
	//���U���g�̃|�C���^
	CResult *pResult;
	pResult = new CResult;
	//���U���g�̏�����
	pResult->Init();
	//���U���g�̏���Ԃ�
	return pResult;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	//�J���� ���C�g�̏�����
	CManager::GetCamera()->Init();
	CManager::GetLight()->Init();

	//�e�N�X�`���⃂�f���̓ǂݍ���
	CObjectBG::Load();
	CUIPressEnter::Load();

	CEnemy::Load();

	//���b�V���t�B�[���h����
	CSceneMeshField::Create(D3DXVECTOR3(-1000, 0, 2900), 7000.0f,3000.0f, 50, 10);
	//��̐���
	CSceneMeshCylinder::Create(D3DXVECTOR3(0, 18000, 0), 8000.0f, 28000.0f, 10, 1, CSceneMeshCylinder::CYLINDERTYPE_INWARD);

	int nNumEnemy = LoadNumEnemy();

	m_bluePos = D3DXVECTOR3((3000.0f / 100) * (nNumEnemy), 1, 200);

	CObjectBG::Create(m_bluePos, D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL000, CObjectBG::MOVETYPE_NONE, 0);

	if (nNumEnemy > 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < (int)(nNumEnemy / 2); nCntEnemy++)
		{
			CEnemy::Create(D3DXVECTOR3(-20.0f + (nCntEnemy * 63.0f), 10, 100.0f + (rand() % 30)), D3DXVECTOR3(D3DX_PI * -0.5f, D3DX_PI * 0.0f, (rand() % 628) / 100.0f), 10);
		}
	}

	// ���̖�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(-100.0f + (nCnt * 300.0f), 0, 400.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(0.0f + (nCnt * 300.0f), 0, 300.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(100.0f + (nCnt * 300.0f), 0, 350.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(1200.0f + (nCnt * 300.0f), 0, 400.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(1300.0f + (nCnt * 300.0f), 0, 300.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(1400.0f + (nCnt * 300.0f), 0, 350.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(2400.0f + (nCnt * 300.0f), 0, 400.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(2500.0f + (nCnt * 300.0f), 0, 300.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(2600.0f + (nCnt * 300.0f), 0, 350.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
	}

	// �v���X�G���^�[
	CUIPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 + 250, 0.0f), 400, 100);

	return S_OK;
}

//=============================================================================
// ���U���g�N���X �I������
//=============================================================================
void CResult::Uninit(void)
{
	CObjectBG::UnLoad();
	CUIPressEnter::UnLoad();
	CEnemy::UnLoad();

	CScene::ReleaseAll();
}

//=============================================================================
// ���U���g�N���X �X�V����
//=============================================================================
void CResult::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�R���g���[���[�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//�T�E���h�����擾
	//CSound *pSound = CManager::GetSound();
	CSound *pSound = CManager::GetSound(0);

	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_TITLE);
	}

#ifdef  _DEBUG
	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_BACK) == true && CFade::GetFade() == CFade::FADE_NONE
		/*	|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && CFade::GetFade() == CFade::FADE_NONE*/)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_GAME);
	}
#endif


	CDebugProc::Print(1, "	���U���g\n");

}

//=============================================================================
// ���U���g�N���X �`�揈��
//=============================================================================
void CResult::Draw(void)
{

}

//=============================================================================
// �u���[�V�[�g�̈ʒu�擾
//=============================================================================
D3DXVECTOR3 CResult::GetBluePos(void)
{
	return m_bluePos;
}

//=============================================================================
// �|�����G�̐��̃��[�h
//=============================================================================
int CResult::LoadNumEnemy(void)
{
	FILE *pFile = NULL;

	int nNumEnemy = 0;

	pFile = fopen(NUMENEMY_FILE, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &nNumEnemy);

		fclose(pFile);
	}

	return nNumEnemy;
}

//=============================================================================
// �A�C�e���l�����p�̐����ݒ菈��
//=============================================================================
void CResult::AddItem(int nValue)
{
	int nAnswer = 0;
	int nDigit = 1;
	//�^�C�����Z
	m_nItem = nValue;

	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		//�����̌v�Z
		nAnswer = m_nItem % (nDigit * 10) / nDigit;
		//���̌��̐������Z�b�g
		if (m_apItem[nCnt] != NULL)
		{
			m_apItem[nCnt]->SetNumber(nAnswer);
		}
		//���̌���
		nDigit *= 10;
	}
}

//=============================================================================
// �^�C���\���p�̐����ݒ菈��
//=============================================================================
void CResult::AddTime(int nValue)
{
	int nAnswer = 0;
	int nDigit = 1;
	//�^�C�����Z
	m_nTime = nValue;

	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		//�����̌v�Z
		nAnswer = m_nTime % (nDigit * 10) / nDigit;
		//���̌��̐������Z�b�g
		if (m_apTime[nCnt] != NULL)
		{
			m_apTime[nCnt]->SetNumber(nAnswer);
		}
		//���̌���
		nDigit *= 10;
	}
}


