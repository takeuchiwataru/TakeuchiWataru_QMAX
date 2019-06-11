//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �|���j
//
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "logo.h"
#include "bg.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// ����������
//=============================================================================
void CResult::Init(void)
{
	// ���U���g���S�̓ǂݍ���
	CResultLogo::Load();

	// �w�i�̃e�N�X�`���ǂݍ���
	CBg::Load();

	// ���U���g���S�N���X�̐���
	CResultLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CResultLogo::RESULTTYPE_OVER);

	// �w�i�N���X�̐���
	CBg::Create(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

}
//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	// �S�ĉ��
	CScene::ReleseAll();

	// ���U���g���S�̔j��
	CResultLogo::Unload();

	// �w�i�̃e�N�X�`���j��
	CBg::Unload();
}
//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h(XInput)�̎擾
	CXInputJoyPad *pXInputJoyPad = CManager::GetXInputJoyPad();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 1) == true && pFade->FADE_NONE)
	{// ���������ꂽ��
		pFade->Set(CManager::MODE_RANKING, pFade->FADE_OUT);
	}

	///*�f�o�b�O�p*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_TITLE);
	//}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{

}
