//---------------------------------------------------------------------
// �`���[�g���A������ [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "tutorial.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "Logo.h"

#include "2DTuto.h"
#include "UIPressEnter.h"
#include "fade.h"
#include "meshField.h"
#include "field.h"

#include "effect.h"
#include "number.h"
#include "UILife.h"
#include "UIItem.h"
#include "UIGauge.h"


#include "fade.h"
#include "Logo.h"
#include "meshField.h"
#include "field.h"
#include "meshOrbit.h"
#include "billboard.h"
#include "billboardObject.h"
#include "player.h"
#include "shadow.h"
#include "effect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[MAX_TUTORIALBG] = {};
CPlayer		*CTutorial::m_pPlayer = NULL;

//--------------------------------------------
//�`���[�g���A���N���X �R���X�g���N�^
//--------------------------------------------
CTutorial::CTutorial()
{
	m_nType = 0;
}

//--------------------------------------------
//�`���[�g���A���N���X �f�X�g���N�^
//--------------------------------------------
CTutorial::~CTutorial()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CTutorial *CTutorial::Create(void)
{
	//�`���[�g���A���̃|�C���^
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	pTutorial->Init();
	//�`���[�g���A���̏���Ԃ�
	return pTutorial;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//�J���� ���C�g�̏�����
	CManager::GetCamera()->Init();
	CManager::GetLight()->Init();


	//�e�N�X�`���⃂�f���̓ǂݍ���
	CLogo::Load();
	CUIPressEnter::Load();
	CField::Load();
	CUIItem::Load();
	CUIGauge::Load();
	CUILife::Load();
	CNumber::Load();
	CEffect::Load();
	C2DTUTO::Load();
	//�I�u�W�F�N�g�̐���

	C2DTUTO::Create(D3DXVECTOR3(0, 0, 0), 100, 100);

	//CField::Create(D3DXVECTOR3(-100, 0.1f, 15000), 200, 50300, CField::FIELDTEX_ROADWAY, 1, 300);
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);

	//�Q�[�W�𐶐�
	//CUIGauge::Create(D3DXVECTOR3(1100, 680, 0), 100, 300);
	// �v���X�G���^�[
	CUIPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 + 250, 0.0f), 400, 100);


	return S_OK;
}

//=============================================================================
// �`���[�g���A���N���X �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	//�e�N�X�`���⃂�f���̔j��
	CLogo::UnLoad();
	CUIPressEnter::UnLoad();
	CField::UnLoad();
	CUIItem::UnLoad();
	CUIGauge::UnLoad();
	CUILife::UnLoad();
	CNumber::UnLoad();
	CEffect::UnLoad();
	C2DTUTO::UnLoad();

	CScene::ReleaseAll();
}

//=============================================================================
// �`���[�g���A���N���X �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�W���C�p�b�h�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		//CSound *pSound = CManager::GetSound(1);
	//	pSound->PlaySound(pSound->SOUND_LABEL_SE_SODAFULL);
		CFade::SetFade(CManager::MODE_GAME);
	}

	if (pInput->GetTrigger(DIK_R) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_TITLE);
	}

	CDebugProc::Print(1, " �`���[�g���A��\n");
}

//=============================================================================
// �`���[�g���A���N���X �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}
//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CTutorial::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CTutorial::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TUTORIALBG; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}