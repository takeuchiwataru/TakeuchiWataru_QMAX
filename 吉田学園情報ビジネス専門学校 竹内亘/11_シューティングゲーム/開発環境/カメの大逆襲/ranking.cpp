//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "logo.h"
#include "number.h"
#include "score.h"
#include "bg.h"
#include "rankingrank.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CScore * CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking()
{
	m_nTime = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
void CRanking::Init(void)
{
	int aScore[MAX_RANKING] = {};

	m_nTime = 0;

	// 背景のテクスチャ読み込み
	CBg::Load();

	// ナンバーテクスチャの読み込み
	CNumber::Load();

	// ランキングランクの読み込み
	CRankingRank::Load();

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_apScore[nCntRanking] == NULL)
		{
			aScore[nCntRanking] = CManager::GetRanking(nCntRanking);

			// スコアの生成
			m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 170.0f + nCntRanking * 100.0f, 0));
			m_apScore[nCntRanking]->AddScore(aScore[nCntRanking]);
		}
	}

	// 背景クラスの生成
	CBg::Create(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

	// ランキングランクの生成
	CRankingRank::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2, 0.0f));

	//// ランキングロゴの読み込み
	//CRankingLogo::Load();

	//// ランキングロゴの生成
	//CRankingLogo::Create(D3DXVECTOR3(250, 100, 0.0f));
}
//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	// 全て解放
	CScene::ReleseAll();

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking] = NULL;
	}

	// ナンバーのテクスチャ破棄
	CNumber::Unload();

	// 背景のテクスチャ破棄
	CBg::Unload();

	// ランキングランクテクスチャの破棄
	CRankingRank::Unload();

	//// ランキングロゴの破棄
	//CRankingLogo::Unload();
}
//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
{
	m_nTime++;

	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ジョイパッド(XInput)の取得
	CXInputJoyPad *pXInputJoyPad = CManager::GetXInputJoyPad();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 1) == true && pFade->FADE_NONE)
	{// 何か押されたら
		pFade->Set(CManager::MODE_TITLE, pFade->FADE_OUT);
	}

	if (m_nTime % 300 == 0)
	{// 一定時間たったら
		pFade->Set(CManager::MODE_TITLE, pFade->FADE_OUT);
	}

	///*デバッグ用*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_TITLE);
	//}
}
//=============================================================================
// 描画処理
//=============================================================================
void CRanking::Draw(void)
{

}
