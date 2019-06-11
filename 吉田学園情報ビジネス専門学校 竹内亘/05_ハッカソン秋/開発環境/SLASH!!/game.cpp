//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "particle.h"
#include "item.h"
#include "score.h"
#include "life.h"
#include "attackgauge.h"
#include "reload.h"
#include "bullet.h"
#include "enemy.h"
#include "effect.h"
#include "remain.h"
#include "result.h"
#include "rankingscore.h"
#include "fade.h"
#include "pause.h"
#include "pauselogo.h"
#include "pauseselect.h"
#include "input.h"
#include "sound.h"

//=============================================================================
// グローバル変数宣言
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;   // ゲームの状態
int       g_nCounterGameState;            // ゲームの状態管理カウンター
int       g_GameCounter;                  // ゲームの進行カウンター
bool      g_bPuase;                       // ポーズ中かどうか
int       g_randSetEnemy;                 // 敵のセットするタイミング
int       g_randEnemyType;                // セットする敵の種類
int       g_randEnemyPosX;                // セットする敵の座標(X)
int       g_randSetItem;                 // アイテムのセットするタイミング
int       g_randItemType;                // セットするアイテムの種類
int       g_randItem;                // セットするアイテムの座標(X)

//=============================================================================
// ゲーム画面初期化処理
//=============================================================================
void InitGame(void)
{
	// 背景初期化処理
	InitBG01();

	// スコア初期化処理
	InitScore();

	// プレイヤー初期化処理
	InitPlayer();

	// パーティクル初期化処理
	InitParticle();

	// アイテム初期化処理
	InitItem();

	// 弾初期化処理
	InitBullet();

	// 敵初期化処理
	InitEnemy();
	
	// エフェクト初期化処理
	InitEffect();

	// 攻撃ゲージ初期化処理
	InitAttackGauge();

	Player *pPlayer;
	pPlayer = GetPlayer();

	// ライフ初期化処理
	InitLife();
	SetLife(pPlayer->nLife);

	// 残機初期化処理
	InitRemain();
	SetRemain(pPlayer->nRemain);

	// 切れ味初期化処理
	InitReload();
	SetReload(pPlayer->nSharp);

	// ポーズ初期化処理
	InitPause();

	// ポーズロゴ初期化処理
	InitPauseLogo();

	// ポーズ項目初期化処理
	InitPauseSelect();

	g_GameCounter = 0;
	g_GameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPuase = false;
	g_randSetEnemy = 250;
	g_randSetItem = 500;
}
//=============================================================================
// ゲーム画面終了処理
//=============================================================================
void UninitGame(void)
{
	// 背景終了処理
	UninitBG01();

	// スコア終了処理
	UninitScore();

	// プレイヤー終了処理
	UninitPlayer();

	// パーティクル終了処理
	UninitParticle();

	// アイテム終了処理
	UninitItem();

	// ライフ終了処理
	UninitLife();

	// 攻撃ゲージ終了処理
	UninitAttackGauge();

	// 残機終了処理
	UninitRemain();

	// 切れ味終了処理
	UninitReload();

	// エフェクト終了処理
	UninitEffect();

	// 弾終了処理
	UninitBullet();

	// 敵終了処理
	UninitEnemy();

	// ポーズ終了処理
	UninitPause();

	// ポーズロゴ終了処理
	UninitPauseLogo();

	// ポーズ項目終了処理
	UninitPauseSelect();
}
//=============================================================================
// ゲーム画面更新処理
//=============================================================================
void UpdateGame(void)
{
	g_GameCounter++;
	FADE fade;
	fade = GetFade();

	if (GetKeyboardTrigger(DIK_P) && fade == FADE_NONE)
	{// ポーズON/OFF
		g_bPuase = g_bPuase ? false : true;
	}

	if (g_bPuase == false)
	{// ポーズOFF
		// 敵の配置設定
		GameScene();

		// 背景更新処理
		UpdateBG01();

		// プレイヤー更新処理
		UpdatePlayer();

		// スコア更新処理
		UpdateScore();

		// パーティクル更新処理
		UpdateParticle();

		// アイテム更新処理
		UpdateItem();

		// ライフ更新処理
		UpdateLife();

		// 残機更新処理
		UpdateRemain();

		// 切れ味更新処理
		UpdateReload();

		// 攻撃ゲージ更新処理
		UpdateAttackGauge();

		// エフェクト更新処理
		UpdateEffect();

		// 弾更新処理
		UpdateBullet();

		// 敵更新処理
		UpdateEnemy();

		switch (g_GameState)
		{
		case GAMESTATE_NORMAL:  // 通常状態
			break;

		case GAMESTATE_END:     //終了状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{// 一定時間たったら
				g_GameState = GAMESTATE_NONE;
				SetRankingScore(GetScore());
				SetFade(MODE_RESULT);
			}
			break;
		}
	}
	else
	{
		// ポーズ更新処理
		UpdatePause();

		// ポーズロゴ更新処理
		UpdatePauseLogo();

		// ポーズ項目更新処理
		UpdatePauseSelect();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// ENTERキーが押された
			RESTART restart;
			restart = GetRestart();

			switch (restart)
			{
			case RESTART_CONTINUE:  // ゲーム再開
				break;
			case RESTART_RETRY:     // ゲームやり直し
				SetFade(MODE_GAME);
				return; // これ以上ゲームはUpdateしない
				break;
			case RESTART_QUIT:      // タイトル遷移
				SetFade(MODE_TITLE);
				return; // これ以上ゲームはUpdateしない
				break;
			}
			g_bPuase = g_bPuase ? false : true; // ポーズは解除
		}
	}
}
//=============================================================================
// ゲーム画面描画処理
//=============================================================================
void DrawGame(void)
{
	// 背景描画処理
	DrawBG01();

	// パーティクル描画処理
	DrawParticle();

	// アイテム描画処理
	DrawItem();

	// プレイヤー描画処理
	DrawPlayer();

	// 弾描画処理
	DrawBullet();

	// 敵描画処理
	DrawEnemy();

	// スコア描画処理
	DrawScore();
	
	// ライフ描画処理
	DrawLife();

	// 残機描画処理
	DrawRemain();

	// 攻撃ゲージ描画処理
	DrawAttackGauge();

	// 切れ味描画処理
	DrawReload();

	// エフェクト描画処理
	DrawEffect();

	if (g_bPuase == true)
	{// ポーズ中なら
		// ポーズ描画処理
		DrawPause();

		// ポーズロゴ描画処理
		DrawPauseLogo();

		// ポーズ項目描画処理
		DrawPauseSelect();
	}
}
//=============================================================================
// ゲーム画面設定処理
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	g_nCounterGameState = 0;
}
//=============================================================================
// ゲーム画面取得処理
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}
//=============================================================================
// ゲーム画面シーン作成
//=============================================================================
void GameScene(void)
{
	if (g_GameCounter >= 120)
	{// ある程度時間がたってから
		D3DXVECTOR3 EnemyPos(0.0f, -60.0f, 0.0f);
		if (rand() % g_randSetEnemy <= 2)
		{
			EnemyPos.x = rand() % 200 + 500.0f;
			g_randEnemyType = rand() % 4;
			SetEnemy(EnemyPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_randEnemyType);
		}
		if (rand()% g_randSetItem == 0)
		{
			D3DXVECTOR3 ItemPos(600, -60.0f, 0.0f);
			g_randItemType = rand() % 3;
			SetItem(ItemPos, g_randItemType, D3DXVECTOR3(0.0f, 10.0f, 0.0f));
		}
	}
	if (g_GameCounter % 2500 == 0)
	{
		if (g_randSetEnemy >= 5)
		{
			g_randSetEnemy -= 20;
		}
	}
}