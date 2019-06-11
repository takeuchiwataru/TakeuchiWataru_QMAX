//---------------------------------------------------------------------
// ランキング処理 [ranking.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "ranking.h"
#include "manager.h"
#include "scene.h"
#include "Logo.h"

#include "fade.h"

#include "UIScore.h"	// 亘追加
#include "number.h"
#include "rankinglogo.h"
#include "rankingbg.h"

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
static CRenderer *m_pRenderer;
LPDIRECT3DTEXTURE9 CRanking::m_pTexture = NULL;

CScore * CRanking::m_apScore[MAX_RANKING] = {};		// 亘追加

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

	// 亘追加
	CNumber::Load();
	CRankingLogo::Load();
	CRankingBG::Load();

	//CRank::Load();
	//CRankingLogo::Load();

	//オブジェクトの生成
	CRankingBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 1280, 720);

	//オブジェクトの生成
	CLogo::Create(D3DXVECTOR3(250, 100, 0), 350, 150);

	// 亘追加
	// ランキングロゴの生成
	CRankingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 0), 100, 350);

	int aScore[MAX_RANKING] = {};

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_apScore[nCntRanking] == NULL)
		{
			aScore[nCntRanking] = CManager::GetRanking(nCntRanking);

			// スコアの生成
			m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, 170.0f + nCntRanking * 100.0f, 0), 30, 30);
			m_apScore[nCntRanking]->AddScore(aScore[nCntRanking]);
		}
	}

	//m_Rank = CRank::Create(D3DXVECTOR3(450.0f, 150.0f, 0), 60);
	//m_Logo = CRankingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0), 300);

	//int aScore[MAX_RANKING] = {};

	//for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	//{	//nCnt番のデータを取得する
	//	aScore[nCnt] = *CManager::GetRankingScore(nCnt);
	//	//スコアUIの生成
	//	m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 120.0f, 150.0f + (nCnt * 100), 0));
	//	m_pScore[nCnt]->AddScore(aScore[nCnt]);
	//}
	return S_OK;
}

//=============================================================================
// ランキングクラス 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	//テクスチャやモデルの破棄
	CLogo::UnLoad();

	// 亘追加
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
// ランキングクラス 更新処理
//=============================================================================
void CRanking::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//コントローラー情報を取得
	CDirectInput *pInputJoypad = CManager::GetJoypad();

	//サウンド情報を取得
	CSound *pSound = CManager::GetSound();

	int GameScore = 0;
	int RankingScore = 0;
	//GameScore = *CManager::GetGameScore();
	//色変えカウント
	m_nCntCor++;


	//切り替え処理
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_TITLE);
	}
	//切り替え処理(タイマー)
	m_nCntTimer++;
	if (m_nCntTimer >= 600 && CFade::GetFade() == CFade::FADE_NONE)
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
