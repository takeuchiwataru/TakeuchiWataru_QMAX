//---------------------------------------------------------------------
// ���U���g���� [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "result.h"
#include "manager.h"
#include "scene.h"
#include "Logo.h"

//#include "bg.h"
#include "fade.h"
//#include "resultlogo.h"
//--------------------------------------------
//���U���g�N���X �R���X�g���N�^
//--------------------------------------------
CResult::CResult()
{
	m_nCntTimer = 0;
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
	//�e�N�X�`���⃂�f���̓ǂݍ���
	CLogo::Load();

	//�I�u�W�F�N�g�̐���
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200, 0), 400, 200);

	//�v���X�G���^�[�̐���
	//CPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650, 0), 150);

	return S_OK;
}

//=============================================================================
// ���U���g�N���X �I������
//=============================================================================
void CResult::Uninit(void)
{
	//�e�N�X�`���⃂�f���̔j��
	CLogo::UnLoad();

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
	CDirectInput *pInputJoypad = CManager::GetJoypad();

	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound();
	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_RANKING);
	}

	//�؂�ւ�����(�^�C�}�[)
	m_nCntTimer++;
	if (m_nCntTimer >= 420 && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_RANKING);
		m_nCntTimer = 0;
	}

	CDebugProc::Print(1, "	���U���g\n");

}

//=============================================================================
// ���U���g�N���X �`�揈��
//=============================================================================
void CResult::Draw(void)
{

}