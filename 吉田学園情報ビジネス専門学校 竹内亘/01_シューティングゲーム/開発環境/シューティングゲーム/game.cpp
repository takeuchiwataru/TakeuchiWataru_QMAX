//=============================================================================
//
// ゲームの処理 [game.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "sound.h"
#include "timer.h"
#include "pause.h"
#include "life.h"
#include "ranking.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_X			(300)				//敵のX座標
#define ENEMY_Y			(100)				//敵のY座標

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲームの状態
int g_nCounterGameState;					//状態管理カウンター
bool g_bPause;

//=============================================================================
// ゲーム初期化処理
//=============================================================================
void InitGame(void)
{
	//背景初期化処理
	InitBG();

	//背景初期化処理
	InitBG2();

	//プレイヤー初期化処理
	InitPlayer();

	//弾の発射初期化処理
	InitBullet();

	//爆発の初期化処理
	InitExplosion();

	//敵の初期化処理
	InitEnemy();

	//1列目
	SetEnemy(D3DXVECTOR3(ENEMY_X, ENEMY_Y, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 200, ENEMY_Y, 0.0f), 1);			
	SetEnemy(D3DXVECTOR3(ENEMY_X + 400, ENEMY_Y, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 600, ENEMY_Y, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 800, ENEMY_Y, 0.0f), 4);

	//2列目
	SetEnemy(D3DXVECTOR3(ENEMY_X - 100, ENEMY_Y + 100, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 100, ENEMY_Y + 100, 0.0f), 1);	
	SetEnemy(D3DXVECTOR3(ENEMY_X + 300, ENEMY_Y + 100, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 500, ENEMY_Y + 100, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 700, ENEMY_Y + 100, 0.0f), 4);

	//3列目
	SetEnemy(D3DXVECTOR3(ENEMY_X, ENEMY_Y + 200, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 200, ENEMY_Y + 200, 0.0f), 1);	
	SetEnemy(D3DXVECTOR3(ENEMY_X + 400, ENEMY_Y + 200, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 600, ENEMY_Y + 200, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 800, ENEMY_Y + 200, 0.0f), 4);

	//4列目
	SetEnemy(D3DXVECTOR3(ENEMY_X - 100, ENEMY_Y + 300, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 100, ENEMY_Y + 300, 0.0f), 1);	
	SetEnemy(D3DXVECTOR3(ENEMY_X + 300, ENEMY_Y + 300, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 500, ENEMY_Y + 300, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 700, ENEMY_Y + 300, 0.0f), 4);

	//ボスの初期化処理
	InitBoss();

	//スコアの初期化処理
	InitScore();

	//タイマーの初期化処理
	InitTimer();

	//ライフの初期化処理
	InitLife();

	//エフェクトの初期化処理
	InitEffect();

	PlaySound(SOUND_LABEL_BGM002);

	g_gameState = GAMESTATE_NORMALL;	//通常状態に設定
	g_nCounterGameState = 0;

	//ポーズの初期化処理
	InitPause();

	g_bPause = false;
}

//=============================================================================
// ゲーム終了処理
//=============================================================================
void UninitGame(void)
{
	//背景終了処理
	UninitBG();

	//背景終了処理
	UninitBG2();

	//プレイヤー終了処理
	UninitPlayer();

	//弾の発射終了処理
	UninitBullet();

	//爆発の終了処理
	UninitExplosion();

	//敵の終了処理
	UninitEnemy();

	//ボスの終了処理
	UninitBoss();

	//スコアの終了処理
	UninitScore();

	//タイマーの終了処理
	UninitTimer();

	//ライフの終了処理
	UninitLife();

	//エフェクトの終了処理
	UninitEffect();

	//ポーズの終了処理
	UninitPause();

}

//=============================================================================
// ゲーム更新処理
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズON/OFF
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		//背景更新処理
		UpdateBG();

		//背景更新処理
		UpdateBG2();

		//弾の発射更新処理
		UpdateBullet();

		//爆発の更新処理
		UpdateExplosion();

		//プレイヤー更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		//ボスの更新処理
		UpdateBoss();

		//スコアの更新処理
		UpdateScore();

		//タイマーの更新処理
		UpdateTimer();

		//ライフの更新処理
		UpdateLife();

		//エフェクトの更新処理
		UpdateEffect();
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMALL:
		break;

	case GAMESTATE_GAMECLEAR:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			//画面の設定
			SetFade(MODE_CLEAR);
		}
		break;

	case GAMESTATE_GAMEOVER:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			//画面の設定
			SetFade(MODE_OVER);
		}
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			StopSound(SOUND_LABEL_BGM002);

			//画面の設定
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//=============================================================================
// ゲーム描画処理
//=============================================================================
void DrawGame(void)
{
	//背景描画処理
	DrawBG();

	//背景描画処理
	DrawBG2();

	//プレイヤー描画処理
	DrawPlayer();

	//弾の発射描画処理
	DrawBullet();

	//爆発の描画処理
	DrawExplosion();

	//敵の描画処理
	DrawEnemy();

	//ボスの描画処理
	DrawBoss();

	//スコアの描画処理
	DrawScore();

	//タイマーの描画処理
	DrawTimer();

	//ライフの描画処理
	DrawLife();

	//エフェクトの描画処理
	DrawEffect();

	if (g_bPause == true)
	{//ポーズの描画処理
		DrawPause();
	}
}

//=============================================================================
// ゲーム状態の設定
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
// ゲーム状態の取得
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

