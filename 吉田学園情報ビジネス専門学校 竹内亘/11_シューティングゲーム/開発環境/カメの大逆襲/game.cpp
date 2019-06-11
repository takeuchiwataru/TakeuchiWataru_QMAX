//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �|���j
//
//=============================================================================
#include "game.h"

#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"

#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "boss.h"
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
#include "avatar.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScore * CGame::m_pScore = NULL;
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};
CRemain *CGame::m_pRemain[MAX_PLAYER] = {};

//CLife * CGame::m_pLife = NULL;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;

	m_pRemain[0] = NULL;
	m_pRemain[1] = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}
//=============================================================================
// ����������
//=============================================================================
void CGame::Init(void)
{
	m_nTime = 0;

	// �w�i�̃e�N�X�`���ǂݍ���
	CBg::Load();

	// �v���C���[�̃e�N�X�`���ǂݍ���
	CPlayer::Load();

	// �e�̃e�N�X�`���ǂݍ���
	CBullet::Load();

	// �����̃e�N�X�`���ǂݍ���
	CExplosion::Load();

	// �G�̃e�N�X�`���ǂݍ���
	CEnemy::Load();

	// �{�X�̃e�N�X�`���̓ǂݍ���
	CBoss::Load();

	// �i���o�[�e�N�X�`���̓ǂݍ���
	CNumber::Load();

	//// ���C�t�e�N�X�`���̓ǂݍ���
	//CPolygon::Load();

	// �G�t�F�N�g�e�N�X�`���̓ǂݍ���
	CEffect::Load();

	// �p�[�e�B�N���e�N�X�`���̓ǂݍ���
	CParticle::Load();

	// �A�C�e���e�N�X�`���̓ǂݍ���
	CItem::Load();

	// �C���e�N�X�`���̓ǂݍ���
	CMarinePlant::Load();

	// �|�[�Y�䎆�̓ǂݍ���
	CPauseMat::Load();

	// �|�[�Y���ڂ̓ǂݍ���
	CPauseSelect::Load();

	// �t���[���̓ǂݍ���
	CFrame::Load();

	// �摜�̓ǂݍ���
	CImage::Load();

	// ���g�̓ǂݍ���
	CAvatar::Load();

	// �摜�̓ǂݍ���
	CImage::Load();

	// �w�i�N���X�̐���
	CBg::Create2(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

	 //�G�N���X�̐���
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 500, 0.0f),CEnemy::ENEMYTYPE_000);
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 150, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_000);
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 150, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_000);

	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 150, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_001);

	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 1000, 0.0f), CEnemy::ENEMYTYPE_001);
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100, SCREEN_HEIGHT / 2.0f - 1000, 0.0f), CEnemy::ENEMYTYPE_001);
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f - 1000, 0.0f), CEnemy::ENEMYTYPE_000);
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 1800, 0.0f), CEnemy::ENEMYTYPE_000);
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 250, SCREEN_HEIGHT / 2.0f - 1800, 0.0f), CEnemy::ENEMYTYPE_000);

	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 200,  SCREEN_HEIGHT / 2.0f - 2300, 0.0f), CEnemy::ENEMYTYPE_001);
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 200, SCREEN_HEIGHT / 2.0f - 2300, 0.0f), CEnemy::ENEMYTYPE_001);

	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 300, SCREEN_HEIGHT / 2.0f - 2800, 0.0f), CEnemy::ENEMYTYPE_001);
	CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300, SCREEN_HEIGHT / 2.0f - 2800, 0.0f), CEnemy::ENEMYTYPE_001);

	 //�{�X
	CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f  -3500, 0.0f), CBoss::BOSSTYPE_000);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] == NULL)
		{// �v���C���[�N���X�̐���
			m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CPlayer::PLAYERTYPE_000);
			m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CPlayer::PLAYERTYPE_001);
		}

		if(m_pRemain[nCntPlayer] == NULL)
		{// �c�@�̐���
			m_pRemain[0] = CRemain::Create(D3DXVECTOR3(200, 80, 0));
			m_pRemain[1] = CRemain::Create(D3DXVECTOR3(200, 160, 0));
		}
	}

	// �X�R�A�N���X�̐���
	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(1250, 80, 0));
	}

	// �X�R�A�t���[���̐���
	CFrame::Create(D3DXVECTOR3(1120, 80, 0), CFrame::FRAME_SCORE);

	// �c�@1�摜�̐���
	CImage::Create(D3DXVECTOR3(90, 65, 0),CImage::IMAGE_REMAIN000);

	// �c�@2�摜�̐���
	CImage::Create(D3DXVECTOR3(90, 145, 0), CImage::IMAGE_REMAIN001);

	//if (m_pLife == NULL)
	//{
	//	// ���C�t�N���X�̐���
	//	m_pLife = CLife::Create(D3DXVECTOR3(30, 80, 0));
	//}

	//// ���C�t�t���[���̐���
	//CFrame::Create(D3DXVECTOR3(120, 80, 0), CFrame::FRAME_LIFE);

	// �C���̐���
	CMarinePlant::Create(D3DXVECTOR3(300, -300, 0));
	CMarinePlant::Create(D3DXVECTOR3(400, -300, 0));
	CMarinePlant::Create(D3DXVECTOR3(500, -300, 0));

	CMarinePlant::Create(D3DXVECTOR3(600, -700, 0));
	CMarinePlant::Create(D3DXVECTOR3(700, -700, 0));
	CMarinePlant::Create(D3DXVECTOR3(800, -700, 0));

	CMarinePlant::Create(D3DXVECTOR3(400, -1100, 0));
	CMarinePlant::Create(D3DXVECTOR3(500, -1100, 0));
	CMarinePlant::Create(D3DXVECTOR3(600, -1100, 0));

	CMarinePlant::Create(D3DXVECTOR3(500, -1500, 0));
	CMarinePlant::Create(D3DXVECTOR3(600, -1500, 0));
	CMarinePlant::Create(D3DXVECTOR3(700, -1500, 0));

	CMarinePlant::Create(D3DXVECTOR3(300, -2000, 0));
	CMarinePlant::Create(D3DXVECTOR3(700, -2000, 0));

	CMarinePlant::Create(D3DXVECTOR3(400, -2500, 0));
	CMarinePlant::Create(D3DXVECTOR3(500, -2500, 0));
	CMarinePlant::Create(D3DXVECTOR3(600, -2500, 0));

	CMarinePlant::Create(D3DXVECTOR3(400, -3000, 0));
	CMarinePlant::Create(D3DXVECTOR3(600, -3000, 0));


	//CItem::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CItem::ITEMTYPE_003);
	//CItem::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100, SCREEN_HEIGHT / 2.0f, 0.0f), CItem::ITEMTYPE_003);

	// �R���g���[���[�̐���
	CImage::Create(D3DXVECTOR3(1100, 600, 0), CImage::IMAGE_TUTORIAL);
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	// �S�ĉ��
	CScene::ReleseAll();

	// �w�i�̃e�N�X�`���j��
	CBg::Unload();

	// �v���C���[�̃e�N�X�`���j��
	CPlayer::Unload();

	// �e�̃e�N�X�`���j��
	CBullet::Unload();

	// �����̃e�N�X�`���j��
	CExplosion::Unload();

	// �G�̃e�N�X�`���j��
	CEnemy::Unload();

	// �{�X�̃e�N�X�`���̔j��
	CBoss::Unload();

	// �i���o�[�̃e�N�X�`���j��
	CNumber::Unload();

	//// ���C�t�e�N�X�`���̔j��
	//CPolygon::Unload();

	// �G�t�F�N�g�̃e�N�X�`���̔j��
	CEffect::Unload();

	// �p�[�e�B�N���̃e�N�X�`���̔j��
	CParticle::Unload();

	// �A�C�e���̃e�N�X�`���̔j��
	CItem::Unload();

	// �C���̃e�N�X�`���̔j��
	CMarinePlant::Unload();

	// �|�[�Y�䎆�̔j��
	CPauseMat::Unload();

	// �|�[�Y���ڂ̔j��
	CPauseSelect::Unload();

	// �t���[���̔j��
	CFrame::Unload();

	// �摜�̔j��
	CImage::Unload();

	// ���g�̔j��
	CAvatar::Unload();

	// �摜�̃e�N�X�`���̔j��
	CImage::Unload();

	m_pScore = NULL;

	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;

	m_pRemain[0] = NULL;
	m_pRemain[1] = NULL;

	//m_pLife = NULL;
}
//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	//m_nTime++;

	//if (m_nTime >= 100)
	//{
	//	int nRand = rand() % 100 + 1;

	//	if (nRand > 10 && nRand < 60)
	//	{
	//		CEnemy::Create(D3DXVECTOR3(280, SCREEN_HEIGHT / 2.0f - 200, 0.0f), CEnemy::ENEMYTYPE_002);
	//	}

	//	if (nRand > 10 && nRand < 40)
	//	{
	//		CEnemy::Create(D3DXVECTOR3(280, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CEnemy::ENEMYTYPE_002);
	//	}

	//}
	//if (m_nTime == 100)
	//{
	//	m_nTime = 0;
	//}

	//if (pInputKeyboard->GetTrigger(DIK_R) == true)
	//{// 
	//	if (CFade::GetFade() == CFade::FADE_NONE)
	//	{
	//		CManager::GetRankingScore(m_pScore->GetScore());
	//	}
	//	pFade->Set(CManager::MODE_RESULT, pFade->FADE_OUT);
	//}

	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	pFade->Set(CManager::MODE_RESULT, pFade->FADE_OUT);
	//}

	///*�f�o�b�O�p*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_RESULT);
	//}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}
//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}
//=============================================================================
// �c�@�̎擾
//=============================================================================
CRemain * CGame::GetRemain(void)
{
	return m_pRemain[0];
}
//=============================================================================
// �c�@�̎擾
//=============================================================================
CRemain * CGame::GetRemain2(void)
{
	return m_pRemain[1];
}
//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer[0];
}
//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer * CGame::GetPlayer2(void)
{
	return m_pPlayer[1];
}
////=============================================================================
//// ���C�t�̎擾
////=============================================================================
//CLife * CGame::GetLife(void)
//{
//	return m_pLife;
//}



