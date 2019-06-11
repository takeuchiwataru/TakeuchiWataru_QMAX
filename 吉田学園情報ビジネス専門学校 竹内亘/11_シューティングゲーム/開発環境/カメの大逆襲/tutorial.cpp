//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : �|���j
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "logo.h"

#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "remain.h"
#include "polygon.h"
#include "effect.h"
#include "particle.h"
#include "item.h"
#include "marineplant.h"
#include "pausemat.h"
#include "pauseselect.h"
#include "frame.h"
#include "image.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScore * CTutorial::m_pScore = NULL;
CPlayer *CTutorial::m_pPlayer[2] = {};
CRemain *CTutorial::m_pRemain[2] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;

	m_pRemain[0] = NULL;
	m_pRemain[1] = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}
//=============================================================================
// ����������
//=============================================================================
void CTutorial::Init(void)
{
	//// �`���[�g���A�����S�̓ǂݍ���
	//CTutorialLogo::Load();

	// �v���X�G���^�[�e�N�X�`������
	CPressEnter::Load();

	// �w�i�̃e�N�X�`���ǂݍ���
	CBg::Load();

	// �v���C���[�̃e�N�X�`���ǂݍ���
	CPlayer::Load();

	// �e�̃e�N�X�`���ǂݍ���
	CBullet::Load();

	// �����̃e�N�X�`���ǂݍ���
	CExplosion::Load();

	//// �G�̃e�N�X�`���ǂݍ���
	//CEnemy::Load();

	// �i���o�[�e�N�X�`���̓ǂݍ���
	CNumber::Load();

	// �G�t�F�N�g�e�N�X�`���̓ǂݍ���
	CEffect::Load();

	// �p�[�e�B�N���e�N�X�`���̓ǂݍ���
	CParticle::Load();

	// �A�C�e���e�N�X�`���̓ǂݍ���
	CItem::Load();

	// �C���e�N�X�`���̓ǂݍ���
	CMarinePlant::Load();

	// �t���[���̓ǂݍ���
	CFrame::Load();

	// �摜�̓ǂݍ���
	CImage::Load();

	//// �`���[�g���A�����S�̐���
	//CTutorialLogo::Create(D3DXVECTOR3(100, 100, 0.0f));

	// �v���X�G���^�[�N���X�̐���
	CPressEnter::Create(D3DXVECTOR3(1120, 700, 0.0f),CPressEnter::PRESSENTER_TUTORIAL);
	CPressEnter::DispPressEnter();

	// �w�i�N���X�̐���
	CBg::Create2(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

	// �v���C���[�̐���
	for (int nCntPlayer = 0; nCntPlayer < 2; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] == NULL)
		{
			m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CPlayer::PLAYERTYPE_000);
			m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CPlayer::PLAYERTYPE_001);
		}
		if (m_pRemain[nCntPlayer] == NULL)
		{// �c�@�̐���
			m_pRemain[0] = CRemain::Create(D3DXVECTOR3(200, 80, 0));
			m_pRemain[1] = CRemain::Create(D3DXVECTOR3(200, 160, 0));
		}
	}

	//// �G�̐���
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_TEST);
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_TEST);
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_TEST);

	// �X�R�A�N���X�̐���
	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(1250, 80, 0));
	}

	// �X�R�A�t���[���̐���
	CFrame::Create(D3DXVECTOR3(1120, 80, 0), CFrame::FRAME_SCORE);

	// �c�@1�摜�̐���
	CImage::Create(D3DXVECTOR3(90, 65, 0), CImage::IMAGE_REMAIN000);

	// �c�@2�摜�̐���
	CImage::Create(D3DXVECTOR3(90, 145, 0), CImage::IMAGE_REMAIN001);

	// �R���g���[���[�̐���
	CImage::Create(D3DXVECTOR3(1100, 550, 0), CImage::IMAGE_TUTORIAL);

	// PS����
	CImage::Create(D3DXVECTOR3(1100, 400, 0), CImage::IMAGE_TUTORIAL002);

}
//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	// �S�ĉ��
	CScene::ReleseAll();

	//// �`���[�g���A�����S�̔j��
	//CTutorialLogo::Unload();

	// �v���X�G���^�[�e�N�X�`���j��
	CPressEnter::Unload();

	// �w�i�̃e�N�X�`���j��
	CBg::Unload();

	// �v���C���[�̃e�N�X�`���j��
	CPlayer::Unload();

	// �e�̃e�N�X�`���j��
	CBullet::Unload();

	// �����̃e�N�X�`���j��
	CExplosion::Unload();

	//// �G�̃e�N�X�`���j��
	//CEnemy::Unload();

	// �i���o�[�̃e�N�X�`���j��
	CNumber::Unload();

	// �G�t�F�N�g�̃e�N�X�`���̔j��
	CEffect::Unload();

	// �p�[�e�B�N���̃e�N�X�`���̔j��
	CParticle::Unload();

	// �A�C�e���̃e�N�X�`���̔j��
	CItem::Unload();

	// �C���̃e�N�X�`���̔j��
	CMarinePlant::Unload();

	// �摜�̃e�N�X�`���̔j��
	CImage::Unload();

	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;

	m_pRemain[0] = NULL;
	m_pRemain[1] = NULL;

	m_pScore = NULL;
}
//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
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

	if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 1) == true ||
		pInputKeyboard->GetTrigger(DIK_1) == true)
	{// ���������ꂽ��
		pFade->Set(CManager::MODE_GAME, pFade->FADE_OUT);

		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	}

	//if (pInputJoyPad->GetTrigger(CInputJoyPad::DIJS_BUTTON_4))
	//{// �W���C�p�b�h
	//	pFade->Set(CManager::MODE_GAME, pFade->FADE_OUT);
	//}

	///*�f�o�b�O�p*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_TITLE);
	//}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}
