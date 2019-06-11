//---------------------------------------------------------------------
// �����L���O���� [ranking.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "ranking.h"
#include "manager.h"
#include "scene.h"
#include "Logo.h"

#include "fade.h"

#include "UIScore.h"	// �j�ǉ�
#include "number.h"
#include "rankinglogo.h"
#include "rankingbg.h"

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
static CRenderer *m_pRenderer;
LPDIRECT3DTEXTURE9 CRanking::m_pTexture = NULL;

CScore * CRanking::m_apScore[MAX_RANKING] = {};		// �j�ǉ�

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//--------------------------------------------
//�����L���O�N���X �R���X�g���N�^
//--------------------------------------------
CRanking::CRanking()
{
	m_nCntTimer = 0;
	m_nCntCor = 0;
}

//--------------------------------------------
//�����L���O�N���X �f�X�g���N�^
//--------------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CRanking *CRanking::Create(void)
{
	//�^�C�g���̃|�C���^
	CRanking *pRanking;
	pRanking = new CRanking;
	//�^�C�g���̏�����
	pRanking->Init();
	//�^�C�g���̏���Ԃ�
	return pRanking;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	//�e�N�X�`���⃂�f���̓ǂݍ���
	CLogo::Load();

	// �j�ǉ�
	CNumber::Load();
	CRankingLogo::Load();
	CRankingBG::Load();

	//CRank::Load();
	//CRankingLogo::Load();

	//�I�u�W�F�N�g�̐���
	CRankingBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 1280, 720);

	//�I�u�W�F�N�g�̐���
	CLogo::Create(D3DXVECTOR3(250, 100, 0), 350, 150);

	// �j�ǉ�
	// �����L���O���S�̐���
	CRankingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 0), 100, 350);

	int aScore[MAX_RANKING] = {};

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_apScore[nCntRanking] == NULL)
		{
			aScore[nCntRanking] = CManager::GetRanking(nCntRanking);

			// �X�R�A�̐���
			m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, 170.0f + nCntRanking * 100.0f, 0), 30, 30);
			m_apScore[nCntRanking]->AddScore(aScore[nCntRanking]);
		}
	}

	//m_Rank = CRank::Create(D3DXVECTOR3(450.0f, 150.0f, 0), 60);
	//m_Logo = CRankingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0), 300);

	//int aScore[MAX_RANKING] = {};

	//for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	//{	//nCnt�Ԃ̃f�[�^���擾����
	//	aScore[nCnt] = *CManager::GetRankingScore(nCnt);
	//	//�X�R�AUI�̐���
	//	m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 120.0f, 150.0f + (nCnt * 100), 0));
	//	m_pScore[nCnt]->AddScore(aScore[nCnt]);
	//}
	return S_OK;
}

//=============================================================================
// �����L���O�N���X �I������
//=============================================================================
void CRanking::Uninit(void)
{
	//�e�N�X�`���⃂�f���̔j��
	CLogo::UnLoad();

	// �j�ǉ�
	CRankingLogo::UnLoad();
	CRankingBG::UnLoad();

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking] = NULL;
	}

	//CBg::UnLoad();
	//CRank::UnLoad();
	//CRankingLogo::UnLoad();
	CScene::ReleaseAll();
}

//=============================================================================
// �����L���O�N���X �X�V����
//=============================================================================
void CRanking::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�R���g���[���[�����擾
	CDirectInput *pInputJoypad = CManager::GetJoypad();

	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound();

	int GameScore = 0;
	int RankingScore = 0;
	//GameScore = *CManager::GetGameScore();
	//�F�ς��J�E���g
	m_nCntCor++;


	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_TITLE);
	}
	//�؂�ւ�����(�^�C�}�[)
	m_nCntTimer++;
	if (m_nCntTimer >= 600 && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_TITLE);
		m_nCntTimer = 0;
	}
}

//=============================================================================
// �����L���O�N���X �`�揈��
//=============================================================================
void CRanking::Draw(void)
{

}
