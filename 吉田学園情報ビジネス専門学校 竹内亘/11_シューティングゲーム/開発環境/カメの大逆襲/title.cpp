//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : �|���j
//
//=============================================================================
#include "title.h"

#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "bg.h"
#include "logo.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_nTime = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	m_nTime = 0;

	// �w�i�̃e�N�X�`���ǂݍ���
	CBg::Load();

	// �w�i�N���X�̐���
	CBg::Create(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

	// �^�C�g�����S�̓ǂݍ���
	CTitleLogo::Load();

	// �^�C�g�����S�N���X�̐���
	CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	// �v���X�G���^�[�e�N�X�`������
	CPressEnter::Load();

	// �v���X�G���^�[�N���X�̐���
	CPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f),CPressEnter::PRESSENTER_TITLE);
	CPressEnter::DispPressEnter();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	// �S�ĉ��
	CScene::ReleseAll();

	// �w�i�̃e�N�X�`���j��
	CBg::Unload();

	// �^�C�g�����S�e�N�X�`���j��
	CTitleLogo::Unload();

	// �v���X�G���^�[�e�N�X�`���j��
	CPressEnter::Unload();
}
//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	m_nTime++;

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h�̎擾
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	// �W���C�p�b�h(XInput)�̎擾
	CXInputJoyPad *pXInputJoyPad = CManager::GetXInputJoyPad();

	// �T�E���h�̎擾
	CSound * pSound = CManager::GetSound();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 1) == true)

	{// // ���������ꂽ��
		pFade->Set(CManager::MODE_TUTORIAL,pFade->FADE_OUT);

		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	}

	if (m_nTime % 300 == 0)
	{// ��莞�Ԃ�������
		pFade->Set(CManager::MODE_RANKING, pFade->FADE_OUT);
	}

	///*�f�o�b�O�p*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_GAME);
	//}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}
