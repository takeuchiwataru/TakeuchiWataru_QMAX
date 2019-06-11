//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "result.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "sky.h"
#include "field.h"
#include "shadow.h"
#include "player.h"
#include "effect.h"
#include "animal.h"
#include "score.h"
#include "timer.h"
#include "frame.h"
#include "particle.h"
#include "model.h"
#include "film.h"
#include "filmframe.h"
#include "pause.h"
#include "ranking.h"
#include "sound.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	ANIMALTYPE type;
}ANIMAL_INFO;

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数宣言
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;   // ゲームの状態
int       g_nCounterGameState;            // ゲームの状態管理カウンター
bool      g_bPuase;                       // ポーズ中かどうか

ANIMAL_INFO g_AnimalInfo[] = 
{
	{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(800.0f,0.0f,400.0f),D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(-300.0f,0.0f,0.0f),D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(-800.0f,0.0f,-130.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(-800.0f,0.0f,830.0f),D3DXVECTOR3(3.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(-800.0f,0.0f,1030.0f),D3DXVECTOR3(10.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(0.0f,0.0f,1100.0f),D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(850.0f,0.0f,1130.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(-450.0f,0.0f,-1130.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_DOG },

	{ D3DXVECTOR3(500.0f,0.0f,-1000.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(500.0f,0.0f,-500.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(900.0f,0.0f,-600.0f),D3DXVECTOR3(2.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(-400.0f,0.0f,-600.0f),D3DXVECTOR3(2.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(450.0f,0.0f,800.0f),D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(500.0f,0.0f,-0.0f),D3DXVECTOR3(1.0f,1.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(0.0f,0.0f,-500.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXVECTOR3(0.0f,D3DX_PI * 1.0f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(-500.0f,0.0f,-720.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * 1.0f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(-50.0f,0.0f,-920.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * 1.0f,0.0f), ANIMALTYPE_CROW },

};

//=============================================================================
// ゲーム画面初期化処理
//=============================================================================
void InitGame(void)
{
	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// フィールドの初期化処理
	InitField();

	// 空の初期化処理
	InitSky();

	// 影の初期化処理
	InitShadow();

	// プレイヤーの初期化処理
	InitPlayer();

	// モデルの初期化処理
	InitModel();

	// 動物の初期化処理
	InitAnimal();

	for (int nCntAnimal = 0; nCntAnimal < sizeof g_AnimalInfo / sizeof(ANIMAL_INFO); nCntAnimal++)
	{// 動物を設置する回数繰り返し
		SetAnimal(g_AnimalInfo[nCntAnimal].pos, g_AnimalInfo[nCntAnimal].move, g_AnimalInfo[nCntAnimal].rot, g_AnimalInfo[nCntAnimal].type);
	}

	// エフェクトの初期化処理
	InitEffect();

	// パーティクルの初期化処理
	InitParticle();

	// スコアの初期化処理
	InitScore();

	// タイマーの初期化処理
	InitTimer();

	// フレームの初期化処理
	InitFrame();

	// フィルムの初期化処理
	InitFilm();

	// フィルムのフレームの初期化処理
	InitFilmFrame();

	// ポーズ初期化処理
	InitPause();

	// ポーズロゴ初期化処理
	InitPauseLogo();

	// ポーズ項目初期化処理
	InitPauseSelect();

	g_GameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPuase = false;
}
//=============================================================================
// ゲーム画面終了処理
//=============================================================================
void UninitGame(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// フィールドの終了処理
	UninitField();

	// 空の終了処理
	UninitSky();

	// 影の終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();

	// モデルの終了処理
	UninitModel();

	// 動物の終了処理
	UninitAnimal();

	// エフェクトの終了処理
	UninitEffect();

	// パーティクルの終了処理
	UninitParticle();

	// スコアの終了処理
	UninitScore();

	// タイマーの終了処理
	UninitTimer();

	// フレームの終了処理
	UninitFrame();

	// フィルムの終了処理
	UninitFilm();

	// フィルムのフレームの終了処理
	UninitFilmFrame();

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
	FADE fade;
	fade = GetFade();

	if (GetJoyPadTrigger(DIJS_BUTTON_9,0) == TRUE && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL || GetKeyboardTrigger(DIK_P) == true && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL)
	{// ポーズON/OFF
		g_bPuase = g_bPuase ? false : true;
	}

	if (g_bPuase == false)
	{// ポーズOFF
	    // カメラの更新処理
		UpdateCamera();

		// ライトの更新処理
		UpdateLight();

		// フィールドの更新処理
		UpdateField();

		// 空の更新処理
		UpdateSky();

		// 影の更新処理
		UpdateShadow();

		// プレイヤーの更新処理
		UpdatePlayer();

		// モデルの更新処理
		UpdateModel();

		// 動物の更新処理
		UpdateAnimal();

		// エフェクトの更新処理
		UpdateEffect();

		// パーティクルの更新処理
		UpdateParticle();

		// スコアの更新処理
		UpdateScore();

		// タイマーの更新処理
		UpdateTimer();

		// フレームの更新処理
		UpdateFrame();

		// フィルムの更新処理
		UpdateFilm();

		// フィルムのフレームの更新処理
		UpdateFilmFrame();

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F3) && g_GameState == GAMESTATE_NORMAL)
		{// デバック用
			g_GameState = GAMESTATE_END;
		}
#endif

		switch (g_GameState)
		{
		case GAMESTATE_NORMAL:  // 通常状態
			break;

		case GAMESTATE_RETRY:   // やり直し状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
			{// 一定時間たったら
				g_GameState = GAMESTATE_NONE_RETRY;
				SetFade(MODE_GAME);
			}
			break;

		case GAMESTATE_END:     //終了状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
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

		if (GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// 決定ボタンが押された
			RESTART restart;
			restart = GetRestart();
			FADE fade;
			fade = GetFade();

			if (fade == FADE_NONE)
			{// フェード状態でない
				switch (restart)
				{
				case RESTART_CONTINUE:  // ゲーム再開
					break;
				case RESTART_RETRY:     // ゲームやり直し
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_GAME);
					return; // これ以上ゲームはUpdateしない
					break;
				case RESTART_QUIT:      // タイトル遷移
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_TITLE);
					return; // これ以上ゲームはUpdateしない
					break;
				}
				g_bPuase = g_bPuase ? false : true; // ポーズは解除
			}
		}
	}
}
//=============================================================================
// ゲーム画面描画処理
//=============================================================================
void DrawGame(void)
{		
	// カメラの設定
	SetCamera();

	// フィールドの描画処理
	DrawField();

	// 空の描画処理
	DrawSky();

	// プレイヤーの描画処理
	DrawPlayer();

	// モデルの描画処理
	DrawModel();

	// 動物の描画処理
	DrawAnimal();

	// エフェクトの描画処理
	DrawEffect();

	// パーティクルの描画処理
	DrawParticle();

	// 影の描画処理
	DrawShadow();

	// スコアの描画処理
	DrawScore();

	// タイマーの描画処理
	DrawTimer();

	// フレームの描画処理
	DrawFrame();

	// フィルムの描画処理
	DrawFilm();

	// フィルムのフレームの描画処理
	DrawFilmFrame();

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