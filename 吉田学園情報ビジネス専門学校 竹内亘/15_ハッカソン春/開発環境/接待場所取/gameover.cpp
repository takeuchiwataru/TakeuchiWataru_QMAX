//---------------------------------------------------------------------
// �Q�[���I�[�o�[���� [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "gameover.h"
#include "manager.h"
#include "scene.h"
#include "fade.h"
//--------------------------------------------
//�Q�[���I�[�o�[�N���X �R���X�g���N�^
//--------------------------------------------
CGameover::CGameover()
{
	m_nCntTimer = 0;
}

//--------------------------------------------
//�Q�[���I�[�o�[�N���X �f�X�g���N�^
//--------------------------------------------
CGameover::~CGameover()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CGameover *CGameover::Create(void)
{
	//�Q�[���I�[�o�[�̃|�C���^
	CGameover *pGameover;
	pGameover = new CGameover;
	//�Q�[���I�[�o�[�̏�����
	pGameover->Init();
	//�Q�[���I�[�o�[�̏���Ԃ�
	return pGameover;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGameover::Init(void)
{
	return S_OK;
}

//=============================================================================
// �Q�[���I�[�o�[�N���X �I������
//=============================================================================
void CGameover::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// �Q�[���I�[�o�[�N���X �X�V����
//=============================================================================
void CGameover::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�R���g���[���[�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_RANKING);
	}

	//�؂�ւ�����(�^�C�}�[)
	m_nCntTimer++;
	if (m_nCntTimer >= 600 && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_RANKING);
		m_nCntTimer = 0;
	}
}

//=============================================================================
// �Q�[���I�[�o�[�N���X �`�揈��
//=============================================================================
void CGameover::Draw(void)
{

}