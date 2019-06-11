//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 竹内亘
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
// 静的メンバ変数
//=============================================================================
CScore * CGame::m_pScore = NULL;
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};
CRemain *CGame::m_pRemain[MAX_PLAYER] = {};

//CLife * CGame::m_pLife = NULL;


//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;

	m_pRemain[0] = NULL;
	m_pRemain[1] = NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
void CGame::Init(void)
{
	m_nTime = 0;

	// 背景のテクスチャ読み込み
	CBg::Load();

	// プレイヤーのテクスチャ読み込み
	CPlayer::Load();

	// 弾のテクスチャ読み込み
	CBullet::Load();

	// 爆発のテクスチャ読み込み
	CExplosion::Load();

	// 敵のテクスチャ読み込み
	CEnemy::Load();

	// ボスのテクスチャの読み込み
	CBoss::Load();

	// ナンバーテクスチャの読み込み
	CNumber::Load();

	//// ライフテクスチャの読み込み
	//CPolygon::Load();

	// エフェクトテクスチャの読み込み
	CEffect::Load();

	// パーティクルテクスチャの読み込み
	CParticle::Load();

	// アイテムテクスチャの読み込み
	CItem::Load();

	// 海藻テクスチャの読み込み
	CMarinePlant::Load();

	// ポーズ台紙の読み込み
	CPauseMat::Load();

	// ポーズ項目の読み込み
	CPauseSelect::Load();

	// フレームの読み込み
	CFrame::Load();

	// 画像の読み込み
	CImage::Load();

	// 分身の読み込み
	CAvatar::Load();

	// 画像の読み込み
	CImage::Load();

	// 背景クラスの生成
	CBg::Create2(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

	 //敵クラスの生成
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

	 //ボス
	CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 50, SCREEN_HEIGHT / 2.0f  -3500, 0.0f), CBoss::BOSSTYPE_000);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] == NULL)
		{// プレイヤークラスの生成
			m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CPlayer::PLAYERTYPE_000);
			m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CPlayer::PLAYERTYPE_001);
		}

		if(m_pRemain[nCntPlayer] == NULL)
		{// 残機の生成
			m_pRemain[0] = CRemain::Create(D3DXVECTOR3(200, 80, 0));
			m_pRemain[1] = CRemain::Create(D3DXVECTOR3(200, 160, 0));
		}
	}

	// スコアクラスの生成
	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(1250, 80, 0));
	}

	// スコアフレームの生成
	CFrame::Create(D3DXVECTOR3(1120, 80, 0), CFrame::FRAME_SCORE);

	// 残機1画像の生成
	CImage::Create(D3DXVECTOR3(90, 65, 0),CImage::IMAGE_REMAIN000);

	// 残機2画像の生成
	CImage::Create(D3DXVECTOR3(90, 145, 0), CImage::IMAGE_REMAIN001);

	//if (m_pLife == NULL)
	//{
	//	// ライフクラスの生成
	//	m_pLife = CLife::Create(D3DXVECTOR3(30, 80, 0));
	//}

	//// ライフフレームの生成
	//CFrame::Create(D3DXVECTOR3(120, 80, 0), CFrame::FRAME_LIFE);

	// 海藻の生成
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

	// コントローラーの説明
	CImage::Create(D3DXVECTOR3(1100, 600, 0), CImage::IMAGE_TUTORIAL);
}
//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	// 全て解放
	CScene::ReleseAll();

	// 背景のテクスチャ破棄
	CBg::Unload();

	// プレイヤーのテクスチャ破棄
	CPlayer::Unload();

	// 弾のテクスチャ破棄
	CBullet::Unload();

	// 爆発のテクスチャ破棄
	CExplosion::Unload();

	// 敵のテクスチャ破棄
	CEnemy::Unload();

	// ボスのテクスチャの破棄
	CBoss::Unload();

	// ナンバーのテクスチャ破棄
	CNumber::Unload();

	//// ライフテクスチャの破棄
	//CPolygon::Unload();

	// エフェクトのテクスチャの破棄
	CEffect::Unload();

	// パーティクルのテクスチャの破棄
	CParticle::Unload();

	// アイテムのテクスチャの破棄
	CItem::Unload();

	// 海藻のテクスチャの破棄
	CMarinePlant::Unload();

	// ポーズ台紙の破棄
	CPauseMat::Unload();

	// ポーズ項目の破棄
	CPauseSelect::Unload();

	// フレームの破棄
	CFrame::Unload();

	// 画像の破棄
	CImage::Unload();

	// 分身の破棄
	CAvatar::Unload();

	// 画像のテクスチャの破棄
	CImage::Unload();

	m_pScore = NULL;

	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;

	m_pRemain[0] = NULL;
	m_pRemain[1] = NULL;

	//m_pLife = NULL;
}
//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// フェードの取得
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

	///*デバッグ用*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_RESULT);
	//}
}
//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}
//=============================================================================
// スコアの取得
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}
//=============================================================================
// 残機の取得
//=============================================================================
CRemain * CGame::GetRemain(void)
{
	return m_pRemain[0];
}
//=============================================================================
// 残機の取得
//=============================================================================
CRemain * CGame::GetRemain2(void)
{
	return m_pRemain[1];
}
//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer[0];
}
//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer * CGame::GetPlayer2(void)
{
	return m_pPlayer[1];
}
////=============================================================================
//// ライフの取得
////=============================================================================
//CLife * CGame::GetLife(void)
//{
//	return m_pLife;
//}



