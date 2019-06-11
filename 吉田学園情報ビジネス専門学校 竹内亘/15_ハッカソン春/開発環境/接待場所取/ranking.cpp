//---------------------------------------------------------------------
// �����L���O���� [ranking.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "ranking.h"
#include "manager.h"
#include "scene.h"

#include "Logo.h"
#include "number.h"
#include "UIScore.h"
#include "UIPressEnter.h"
#include "fade.h"
#include "rank.h"

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
static CRenderer *m_pRenderer;
LPDIRECT3DTEXTURE9 CRanking ::m_pTexture = NULL;
CScore *CRanking::m_pScore[MAX_RANKING] = {};

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
	m_nFadeCnt = 0;
	m_bFade = false;
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
	CUIPressEnter::Load();
	CRank::Load();

	//�I�u�W�F�N�g�̐���
	CLogo *pLogo = CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 80, 0), 300, 100);

	pLogo->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	int aScore[MAX_RANKING] = {};

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{	//nCnt�Ԃ̃f�[�^���擾����
		aScore[nCnt] = *CManager::GetRankingScore(nCnt);
		//�X�R�AUI�̐���
		m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 220.0f, 200.0f + (nCnt * 80), 0),50,40);
		m_pScore[nCnt]->AddScore(aScore[nCnt]);
	}

	CRank *pRank = CRank::Create(D3DXVECTOR3(460.0f, 190.0f, 0.0f), 100, 60, 0);
	pRank->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0));

	pRank = CRank::Create(D3DXVECTOR3(450.0f, 270.0f, 0.0f), 80, 60, 1);
	pRank->SetColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0));

	pRank = CRank::Create(D3DXVECTOR3(450.0f, 350.0f, 0.0f), 70, 60, 2);
	pRank->SetColor(D3DXCOLOR(1.0f, 0.7f, 0.3f, 1.0));

	pRank = CRank::Create(D3DXVECTOR3(450.0f, 430.0f, 0.0f), 80, 60, 3);
	pRank->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0));

	pRank = CRank::Create(D3DXVECTOR3(450.0f, 510.0f, 0.0f), 80, 60, 4);
	pRank->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0));

	CUIPressEnter::Create(D3DXVECTOR3(650, 650, 0), 300, 70);

	m_nFadeCnt = 0;
	m_bFade = false;

	return S_OK;
}

//=============================================================================
// �����L���O�N���X �I������
//=============================================================================
void CRanking::Uninit(void)
{
	//�e�N�X�`���⃂�f���̔j��
	CLogo::UnLoad();
	CUIPressEnter::UnLoad();
	CRank::UnLoad();

	CScene::ReleaseAll();
}

//=============================================================================
// �����L���O�N���X �X�V����
//=============================================================================
void CRanking::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�W���C�p�b�h�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	int GameScore = 0;
	int RankingScore = 0;
	GameScore = *CManager::GetGameScore();
	//�F�ς��J�E���g
	m_nCntCor++;

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		RankingScore = m_pScore[nCnt]->GetScore();
		if (RankingScore == GameScore)
		{
			if(m_nCntCor % 6 == 0)
			{
				m_pScore[nCnt]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
			else
			{
				m_pScore[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			break;
		}
	}

	//�؂�ւ�����
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		if (m_bFade == false)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
			m_bFade = true;
		}
	}

	if (m_bFade == true)
	{
		m_nFadeCnt++;
		if (m_nFadeCnt >= 10 && CFade::GetFade() == CFade::FADE_NONE)
		{
			CFade::SetFade(CManager::MODE_TITLE);
			m_nFadeCnt = 0;
		}
	}

	//�؂�ւ�����(�^�C�}�[)
	m_nCntTimer++;
	if (m_nCntTimer >= 900 && CFade::GetFade() == CFade::FADE_NONE)
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
