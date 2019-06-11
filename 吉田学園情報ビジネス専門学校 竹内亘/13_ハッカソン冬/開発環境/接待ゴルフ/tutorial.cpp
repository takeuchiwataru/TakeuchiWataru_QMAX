//---------------------------------------------------------------------
// �`���[�g���A������ [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "tutorial.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "Logo.h"

//#include "bg.h"
#include "fade.h"
#include "tutorialbg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIALBG000_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial000.png"	//�e�N�X�`���̃t�@�C����
#define TUTORIALBG001_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial001.png"	//�e�N�X�`���̃t�@�C����
#define TUTORIALBG002_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial002.png"	//�e�N�X�`���̃t�@�C����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[MAX_TUTORIALBG] = {};

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
	//�`���[�g���A���̏�����
	//pTutorial->Load();
	pTutorial->Init();
	//�`���[�g���A���̏���Ԃ�
	return pTutorial;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//�e�N�X�`���⃂�f���̓ǂݍ���
	CLogo::Load();
	CTutorialBG::Load();

	//�I�u�W�F�N�g�̐���
	CTutorialBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 1000, 300);

	//�I�u�W�F�N�g�̐���
	CLogo::Create(D3DXVECTOR3(250, 100, 0), 350, 150);

	//CSceneMeshField::Create(D3DXVECTOR3(-500, 10, 0),300.0f,300.0f,10,10);

	return S_OK;
}

//=============================================================================
// �`���[�g���A���N���X �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	//�e�N�X�`���⃂�f���̔j��
	CLogo::UnLoad();

	CTutorialBG::UnLoad();
	CScene::ReleaseAll();
}

//=============================================================================
// �`���[�g���A���N���X �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�R���g���[���[�����擾
	CDirectInput *pInputJoypad = CManager::GetJoypad();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound();
	//�V�[��2D���擾
	//CScene2D *Scene2D;
	//Scene2D = pBg->GetScene2DBG(0);


	//�؂�ւ�����

		if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
			|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
			CFade::SetFade(CManager::MODE_GAME);
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

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG000_TEXTURENAME,
		&m_pTexture[0]);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG001_TEXTURENAME,
		&m_pTexture[1]);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG002_TEXTURENAME,
		&m_pTexture[2]);

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