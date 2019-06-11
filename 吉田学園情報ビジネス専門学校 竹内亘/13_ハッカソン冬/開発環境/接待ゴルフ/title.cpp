//---------------------------------------------------------------------
// �^�C�g������ [title.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "title.h"
#include "manager.h"
#include "scene.h"
//#include "bg.h"
#include "fade.h"
#include "Logo.h"
#include "input.h"
#include "titlebg.h"
#include "press.h"

//--------------------------------------------
//�^�C�g���N���X �R���X�g���N�^
//--------------------------------------------
CTitle::CTitle()
{
	m_nCntTimer = 0;
}

//--------------------------------------------
//�^�C�g���N���X �f�X�g���N�^
//--------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CTitle *CTitle::Create(void)
{
	//�^�C�g���̃|�C���^
	CTitle *pTitle;
	pTitle = new CTitle;
	//�^�C�g���̏�����
	pTitle->Init();

	//�^�C�g���̏���Ԃ�
	return pTitle;
}



//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	//�e�N�X�`���⃂�f���̓ǂݍ���
	CLogo::Load();
	CTitleBG::Load();
	CPress::Load();

	//�I�u�W�F�N�g�̐���
	CTitleBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 1280, 720);

	//�I�u�W�F�N�g�̐���
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 300, 0), 500, 300);

	//�I�u�W�F�N�g�̐���
	CPress::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0), 350, 150);

	return S_OK;
}

//=============================================================================
// �^�C�g���N���X �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�^�C�g�����S�e�N�X�`���̔j��
	CLogo::UnLoad();

	CTitleBG::UnLoad();

	CScene::ReleaseAll();
}

//=============================================================================
// �^�C�g���N���X �X�V����
//=============================================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CDirectInput *pInputJoypad = CManager::GetJoypad();

	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound();

	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_TUTORIAL);
	}

	if (m_nCntTimer >= 300 && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_RANKING);
		m_nCntTimer = 0;
	}


	CDebugProc::Print(1, " �^�C�g��\n");
}

//=============================================================================
// �^�C�g���N���X �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}