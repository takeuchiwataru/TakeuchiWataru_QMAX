//---------------------------------------------------------------------
// ランキング処理 [ranking.cpp]
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
//静的メンバ変数宣言
//--------------------------------------------
static CRenderer *m_pRenderer;
LPDIRECT3DTEXTURE9 CRanking ::m_pTexture = NULL;
CScore *CRanking::m_pScore[MAX_RANKING] = {};

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//--------------------------------------------
//ランキングクラス コンストラクタ
//--------------------------------------------
CRanking::CRanking()
{
	m_nCntTimer = 0;
	m_nCntCor = 0;
	m_nFadeCnt = 0;
	m_bFade = false;
}

//--------------------------------------------
//ランキングクラス デストラクタ
//--------------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CRanking *CRanking::Create(void)
{
	//タイトルのポインタ
	CRanking *pRanking;
	pRanking = new CRanking;
	//タイトルの初期化
	pRanking->Init();
	//タイトルの情報を返す
	return pRanking;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	//テクスチャやモデルの読み込み
	CLogo::Load();
	CUIPressEnter::Load();
	CRank::Load();

	//オブジェクトの生成
	CLogo *pLogo = CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 80, 0), 300, 100);

	pLogo->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	int aScore[MAX_RANKING] = {};

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{	//nCnt番のデータを取得する
		aScore[nCnt] = *CManager::GetRankingScore(nCnt);
		//スコアUIの生成
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
// ランキングクラス 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	//テクスチャやモデルの破棄
	CLogo::UnLoad();
	CUIPressEnter::UnLoad();
	CRank::UnLoad();

	CScene::ReleaseAll();
}

//=============================================================================
// ランキングクラス 更新処理
//=============================================================================
void CRanking::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//ジョイパッド情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);

	int GameScore = 0;
	int RankingScore = 0;
	GameScore = *CManager::GetGameScore();
	//色変えカウント
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

	//切り替え処理
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

	//切り替え処理(タイマー)
	m_nCntTimer++;
	if (m_nCntTimer >= 900 && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_TITLE);
		m_nCntTimer = 0;
	}

}

//=============================================================================
// ランキングクラス 描画処理
//=============================================================================
void CRanking::Draw(void)
{

}
