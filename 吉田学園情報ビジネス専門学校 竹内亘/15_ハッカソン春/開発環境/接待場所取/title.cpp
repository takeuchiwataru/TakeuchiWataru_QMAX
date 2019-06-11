//---------------------------------------------------------------------
// �^�C�g������ [title.cpp]
// Author : �|���j
//---------------------------------------------------------------------
#include "title.h"
#include "manager.h"
#include "scene.h"

#include "fade.h"
#include "Logo.h"
#include "meshField.h"
#include "field.h"
#include "meshOrbit.h"
#include "meshCylinder.h"
#include "billboard.h"
#include "billboardObject.h"
#include "player.h"
#include "shadow.h"
#include "effect.h"
#include "UIPressEnter.h"
#include "titleobject.h"
#include "explosion.h"

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
CPlayer		*CTitle::m_pPlayer = NULL;

//--------------------------------------------
//�^�C�g���N���X �R���X�g���N�^
//--------------------------------------------
CTitle::CTitle()
{
	m_nCntTimer = 0;
	m_pPlayer = NULL;
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
	//�J���� ���C�g�̏�����
	CManager::GetCamera()->Init();
	CManager::GetLight()->Init();

	//�e�N�X�`���⃂�f���̓ǂݍ���
	CLogo::Load();
	CField::Load();
	CBillBoardObject::Load();
	CShadow::Load();
	CEffect::Load();
	CUIPressEnter::Load();
	
	// �^�C�g���I�u�W�F�N�g�̓ǂݍ���
	CTitleObject::LoadModel();
	CTitleObject::LoadMat();

	// ���Ђ�Ђ�̓ǂݍ���
	CExplosion::Load();

	//��̐���
	CSceneMeshCylinder::Create(D3DXVECTOR3(0, 18000, 0), 8000.0f, 28000.0f, 10, 1, CSceneMeshCylinder::CYLINDERTYPE_INWARD);

	CField::Create(D3DXVECTOR3(-500, 0.1f, 3000), 1000, 5000, CField::FIELDTEX_GARDEN,10, 300);
	//CBillBoardObject::Create(D3DXVECTOR3(0, 10, -2520), D3DXVECTOR3(0, 0, 0), 200, 200, CBillBoardObject::TEXTYPE_TITLE);

	// �^�C�g���I�u�W�F�N�g�̐���
	CTitleObject::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���Ђ�Ђ�
	CExplosion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	// �v���X�G���^�[
	CUIPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 + 250, 0.0f),400,100);

	// �^�C�g�����S
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 - 200, 0.0f), 600, 350);

	m_nCntTimer = 0;

	return S_OK;
}

//=============================================================================
// �^�C�g���N���X �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�^�C�g�����S�e�N�X�`���̔j��
	CLogo::UnLoad();
	CField::UnLoad();
	CBillBoardObject::UnLoad();
	CShadow::UnLoad();
	CEffect::UnLoad();
	CUIPressEnter::UnLoad();

	// �^�C�g���I�u�W�F�N�g�̔j��
	CTitleObject::UnloadModel(); 
	CTitleObject::UnloadMat();

	// ���Ђ�Ђ�̔j��
	CExplosion::Unload();

	if (m_pPlayer != NULL)
	{
		//m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	CScene::ReleaseAll();
}
//=============================================================================
// �^�C�g���N���X �X�V����
//=============================================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);


	//CFade::SetFade(CManager::MODE_TITLE);


	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_TUTORIAL);
	}

	if (pInput->GetTrigger(DIK_R) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_TITLE);
	}

#ifdef  _DEBUG
	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_BACKSPACE) == true && CFade::GetFade() == CFade::FADE_NONE)
	{

		CFade::SetFade(CManager::MODE_RANKING);
	}
	if (pInput->GetTrigger(DIK_G) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_GAME);
	}
#endif

	CDebugProc::Print(1, " �^�C�g��\n");
}

//=============================================================================
// �^�C�g���N���X �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// �^�C�g���N���X �v���C���[���擾
//=============================================================================
CPlayer *CTitle::GetPlayer(void)
{
	return m_pPlayer;
}