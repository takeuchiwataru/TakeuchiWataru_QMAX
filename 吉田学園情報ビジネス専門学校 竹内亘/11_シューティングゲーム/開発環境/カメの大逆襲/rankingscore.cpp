//=============================================================================
//
// �����L���O�X�R�A���� [rankingscore.cpp]
// Author : �|���j
//
//=============================================================================
#include "rankingscore.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
//int CRankingScore::m_nRankingScore = 0;
CNumber * CRankingScore::m_apNumber[MAX_RANKINGSCORE][MAX_RANKING] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRankingScore::CRankingScore()
{
	m_nRankingScore = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRankingScore::~CRankingScore()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CRankingScore::Init(D3DXVECTOR3 pos)
{
	for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
	{// �������̌J��Ԃ�
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{// �����L���O���̌J��Ԃ�
			m_apNumber[nCount][nCntRanking] = new CNumber;

			m_apNumber[nCount][nCntRanking]->InitRanking(D3DXVECTOR3(pos.x - (SCORE_INTERVAL_SIZE_X * nCount), pos.y +(SCORE_INTERVAL_SIZE_Y * nCntRanking) , pos.z));
			m_aCol[nCntRanking] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			m_State[nCntRanking] = RANKINGSCORESTATE_NONE;

		}
	}
	m_nRankingScore = 0;

	m_CounterCol = 0;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CRankingScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCount][nCntRanking]->Uninit();
		}
	}

	// �I�u�W�F�N�g(�������g)�̔j��
	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CRankingScore::Update(void)
{
	for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCount][nCntRanking]->Update();

			if (m_State[nCntRanking] == RANKINGSCORESTATE_UPDATE)
			{// �X�V���ꂽ��Ԃ�������
				m_CounterCol++;
				if (m_CounterCol % 2 == 0)
				{// ��莞�Ԃ���������
					if (m_aCol[nCntRanking].b == 0.0f)
					{// �Ԃ�������
						m_aCol[nCntRanking] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					else
					{// ����������
						m_aCol[nCntRanking] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					}
				}
			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CRankingScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCount][nCntRanking]->Draw();
		}
	}
}
//=============================================================================
// �X�R�A�̐ݒu
//=============================================================================
void CRankingScore::SetRankingScore(int nScore)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_nRankingScore <= nScore)
		{
			m_nRankingScore = nScore;
		}
		m_State[nCntRanking] = RANKINGSCORESTATE_UPDATE;
	}
}
//=============================================================================
// �X�R�A�̐���
//=============================================================================
CRankingScore * CRankingScore::Create(D3DXVECTOR3 pos)
{
	CRankingScore *pRankingScore = NULL;

	if (pRankingScore == NULL)
	{
		pRankingScore = new CRankingScore;

		if (pRankingScore != NULL)
		{
			pRankingScore->Init(pos);
		}
	}
	return pRankingScore;
}
