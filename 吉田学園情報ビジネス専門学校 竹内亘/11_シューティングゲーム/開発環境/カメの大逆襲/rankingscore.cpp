//=============================================================================
//
// ランキングスコア処理 [rankingscore.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "rankingscore.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
//int CRankingScore::m_nRankingScore = 0;
CNumber * CRankingScore::m_apNumber[MAX_RANKINGSCORE][MAX_RANKING] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CRankingScore::CRankingScore()
{
	m_nRankingScore = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CRankingScore::~CRankingScore()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRankingScore::Init(D3DXVECTOR3 pos)
{
	for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
	{// 桁数分の繰り返し
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{// ランキング分の繰り返し
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
// 終了処理
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

	// オブジェクト(自分自身)の破棄
	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CRankingScore::Update(void)
{
	for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCount][nCntRanking]->Update();

			if (m_State[nCntRanking] == RANKINGSCORESTATE_UPDATE)
			{// 更新された状態だったら
				m_CounterCol++;
				if (m_CounterCol % 2 == 0)
				{// 一定時間がたったら
					if (m_aCol[nCntRanking].b == 0.0f)
					{// 赤だったら
						m_aCol[nCntRanking] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					else
					{// 白だったら
						m_aCol[nCntRanking] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					}
				}
			}
		}
	}
}
//=============================================================================
// 描画処理
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
// スコアの設置
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
// スコアの生成
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
