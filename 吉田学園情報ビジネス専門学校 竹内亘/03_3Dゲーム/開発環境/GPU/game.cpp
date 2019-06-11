//=============================================================================
//
// ゲームの処理 [game.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "player2.h"
#include "model.h"
#include "enemy2.h"
#include "shadow.h"
#include "billboard.h"
#include "bullet.h"
#include "meshField.h"
#include "meshWall.h"
#include "explosion.h"
#include "effect.h"
#include "frame.h"
#include "score.h"
#include "timer.h"
#include "pause.h"
#include "pauselogo.h"
#include "pauseselect.h"
#include "particle.h"
#include "item2.h"
#include "life.h"
#include "sound.h"
//#include "polygon.h"
//#include "player.h"
//#include "enemy.h"
//#include "wall.h"
//#include "item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲームの状態
int g_nCounterGameState;					//状態管理カウンター
bool g_bPause;								//ポーズ中かどうか

//=============================================================================
// ゲーム初期化処理
//=============================================================================
void InitGame(void)
{
	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//// ポリゴンの初期化処理
	//InitPolygon();

	// メッシュフィールドの初期化処理
	InitmeshField();

	//// メッシュフィールド2の初期化処理
	//InitMeshField2();

	// 影の初期化処理
	InitShadow();

	//// プレイヤーの初期化処理
	//InitPlayer();

	// プレイヤー(親子関係なし)の初期化処理
	InitPlayer2();

	// モデルの初期化処理
	InitModel();
	SetModel(D3DXVECTOR3(715.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH);
	SetModel(D3DXVECTOR3(715.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH);
	SetModel(D3DXVECTOR3(-15.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),MODELTYPE_BENCH2);
	SetModel(D3DXVECTOR3(-15.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH2);

	SetModel(D3DXVECTOR3(400.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA);
	SetModel(D3DXVECTOR3(540.0f, 0.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA2);
	SetModel(D3DXVECTOR3(100.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA2);

	SetModel(D3DXVECTOR3(100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),MODELTYPE_BURANKO);
	SetModel(D3DXVECTOR3(170.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BURANKO);
	SetModel(D3DXVECTOR3(500.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_SLIDE);
	SetModel(D3DXVECTOR3(300.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_JG);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_SEESAW);

	//// 敵の初期化処理
	//InitEnemy();
	//SetEnemy(D3DXVECTOR3(0.0f,0.0f,150.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f),ENEMYTYPE_NORMALL);
	//SetEnemy(D3DXVECTOR3(100.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_NORMALL);
	//SetEnemy(D3DXVECTOR3(200.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_NORMALL);

	// 敵(親子関係なし)の初期化処理
	InitEnemy2();
	SetEnemy2(D3DXVECTOR3(50.0f, 0.0f, 150.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(250.0f, 0.0f, 150.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(450.0f, 0.0f, 150.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(50.0f, 0.0f, 400.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(300.0f, 0.0f, 400.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(600.0f, 0.0f, 400.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);

	//// 壁の初期化処理
	//InitWall();
	//SetWall(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	//SetWall(D3DXVECTOR3(-50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	// メッシュウォールの初期化処理
	InitMeshWall(0, D3DXVECTOR3(-25.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	InitMeshWall(1, D3DXVECTOR3(-25.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	InitMeshWall(2, D3DXVECTOR3(725.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	InitMeshWall(3, D3DXVECTOR3(725.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	// ビルボードの初期化処理
	InitBillboard();
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, 10.0f));
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(100.0f, 0.0f, 650.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, 500.0f));
	SetBillboard(D3DXVECTOR3(250.0f, 0.0f, 250.0f));
	SetBillboard(D3DXVECTOR3(300.0f, 0.0f, 650.0f));
	SetBillboard(D3DXVECTOR3(350.0f, 0.0f, 500.0f));
	SetBillboard(D3DXVECTOR3(400.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(450.0f, 0.0f, 560.0f));
	SetBillboard(D3DXVECTOR3(500.0f, 0.0f, 100.0f));
	SetBillboard(D3DXVECTOR3(500.0f, 0.0f, 10.0f));
	SetBillboard(D3DXVECTOR3(550.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(600.0f, 0.0f, 600.0f));
	SetBillboard(D3DXVECTOR3(650.0f, 0.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(700.0f, 0.0f, 340.0f));

	// 弾の初期化処理
	InitBullet();

	// 爆発の初期化処理
	InitExplosion();

	// エフェクトの初期化処理
	InitEffect();

	// フレームの初期化処理
	InitFrame();

	// スコアの初期化処理
	InitScore();

	// タイマーの初期化処理
	InitTimer();

	// ポーズの初期化処理
	InitPause();

	// ポーズロゴ初期化処理
	InitPauseLogo();

	// ポーズ項目初期化処理
	InitPauseSelect();

	// パーティクルの初期化処理
	InitParticle();

	//// アイテムの初期化処理
	//InitItem();
	////SetItem(D3DXVECTOR3(80.0f, 0.0f, 30.0f),20,20, ITEMTYPE_COIN);

	// アイテム(モデルver)の初期化処理
	InitItem2();
	SetItem2(D3DXVECTOR3(100.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_GOMI);
	SetItem2(D3DXVECTOR3(580.0f, 0.0f, 430.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_GOMI);

	SetItem2(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_BOOK);
	SetItem2(D3DXVECTOR3(150.0f, 0.0f, 430.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_BOOK);
	SetItem2(D3DXVECTOR3(610.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_BOOK);

	SetItem2(D3DXVECTOR3(200.0f, 0.0f, 190.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(300.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(700.0f, 0.0f, 45.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(500.0f, 0.0f, 670.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(320.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(60.0f, 0.0f, 680.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);

	SetItem2(D3DXVECTOR3(100.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);
	SetItem2(D3DXVECTOR3(620.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);
	SetItem2(D3DXVECTOR3(500.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);
	SetItem2(D3DXVECTOR3(350.0f, 0.0f, 490.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);
	SetItem2(D3DXVECTOR3(20.0f, 0.0f, 30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);

	// ライフの初期化処理
	InitLife();

	//Player *pPlayer;
	//pPlayer = GetPlayer();
	//SetLife(pPlayer->nLife);

	// プレイヤーの取得
	Player2 *pPlayer;
	pPlayer = GetPlayer2();
	SetLife(pPlayer->nLife);

	g_gameState = GAMESTATE_NORMALL;	//通常状態に設定
	g_nCounterGameState = 0;
	g_bPause = false;
}

//=============================================================================
// ゲーム終了処理
//=============================================================================
void UninitGame(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	//// ポリゴンの終了処理
	//UninitPolygon();

	// メッシュフィールドの終了処理
	UninitmeshField();

	//// メッシュフィールド2の終了処理
	//UninitMeshField2();

	//// プレイヤーの終了処理
	//UninitPlayer();

	// プレイヤー(親子関係なし)の終了処理
	UninitPlayer2();

	// モデルの終了処理
	UninitModel();

	//// 敵の終了処理
	//UninitEnemy();

	// 敵(親子関係なし)の終了処理
	UninitEnemy2();

	// 影の終了処理
	UninitShadow();

	//// 壁の終了処理
	//UninitWall();

	// メッシュウォールの終了処理
	UninitMeshWall();

	// ビルボードの終了処理
	UninitBillboard();

	// 弾の終了処理
	UninitBullet();

	// 爆発の終了処理
	UninitExplosion();

	// エフェクトの終了処理
	UninitEffect();

	// フレームの終了処理
	UninitFrame();

	// タイマーの終了処理
	UninitTimer();

	// スコアの終了処理
	UninitScore();

	// ポーズロゴ終了処理
	UninitPauseLogo();

	// ポーズ項目終了処理
	UninitPauseSelect();

	// 爆発の終了処理
	UninitExplosion();
	
	// パーティクルの終了処理
	UninitParticle();

	//// アイテムの終了処理
	//UninitItem();

	// アイテム(モデルver)の終了処理
	UninitItem2();

	// ライフの終了処理
	UninitLife();
}

//=============================================================================
// ゲーム更新処理
//=============================================================================
void UpdateGame(void)
{
	// アイテムの取得
	ITEM2 *pItem;
	pItem = GetItem2();

	// タイマーの取得
	Timer *pTimer;
	pTimer = GetTimer();

	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズON/OFF
		g_bPause = g_bPause ? false : true;
		PlaySound(SOUND_LABEL_SE_PAUSE000);
		StopSound(SOUND_LABEL_SE_PAUSE001);
	}

	if (g_bPause == false)
	{
		// カメラの更新処理
		UpdateCamera();

		// ライトの更新処理
		UpdateLight();

		//// ポリゴンの更新処理
		//UpdatePolygon();

		// メッシュフィールドの更新処理
		UpdatemeshField();

		//// メッシュフィールド2の更新処理
		//UpdateMeshField2();

		//// プレイヤーの更新処理
		//UpdatePlayer();

		// プレイヤー(親子関係なし)の更新処理
		UpdatePlayer2();

		// モデルの更新処理
		UpdateModel();

		//// 敵の更新処理
		//UpdateEnemy();

		// 敵(親子関係なし)の更新処理
		UpdateEnemy2();

		// 影の更新処理
		UpdateShadow();

		//// 壁の更新処理
		//UpdateWall();

		// メッシュウォールの更新処理
		UpdateMeshWall();

		// ビルボードの更新処理
		UpdateBillboard();

		// 弾の更新処理
		UpdateBullet();

		// 爆発の更新処理
		UpdateExplosion();

		// エフェクトの更新処理
		UpdateEffect();

		// フレームの更新処理
		UpdateFrame();

		// タイマーの更新処理
		UpdateTimer();

		// スコアの更新処理
		UpdateScore();

		// パーティクルの更新処理
		UpdateParticle();

		//// アイテムの更新処理
		//UpdateItem();

		// アイテム(モデルver)の更新処理
		UpdateItem2();

		// ライフの更新処理
		UpdateLife();

		switch (g_gameState)
		{
		case GAMESTATE_NORMALL:		// 通常状態
			break;

		case GAMESTATE_GAMECLEAR:	// ゲームクリア状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{// 一定時間たったら
				AddScore(pTimer->nTimer * 100);
				g_gameState = GAMESTATE_NONE;
				SetFade(MODE_GAMECLEAR);
			}
			break;

		//case GAMESTATE_GAMEOVER:	// ゲームオーバー状態
		//	g_nCounterGameState++;
		//	if (g_nCounterGameState >= 60)
		//	{// 一定時間たったら
		//		g_gameState = GAMESTATE_NONE;
		//		SetFade(MODE_GAMEOVER);
		//	}
		//	break;

		case GAMESTATE_END:			// 終了状態
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{// 一定時間たったら
				g_gameState = GAMESTATE_NONE;
				//SetRankingScore(GetScore());
				SetFade(MODE_GAMEOVER);
			}
			break;
		}
	}
	else
	{//ポーズの更新処理
		UpdatePause();

		// ポーズロゴ更新処理
		UpdatePauseLogo();

		// ポーズ項目更新処理
		UpdatePauseSelect();

		//フェードの取得
		FADE *pFade;
		pFade = GetFade();

		if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
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
			g_bPause = g_bPause ? false : true; // ポーズは解除
			PlaySound(SOUND_LABEL_SE_PAUSE001);
			StopSound(SOUND_LABEL_SE_PAUSE000);
		}
	}
}

//=============================================================================
// ゲーム描画処理
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	//// ポリゴンの描画処理
	//DrawPolygon();

	// メッシュフィールドの描画処理
	DrawmeshField();

	//// メッシュフィールド2の描画処理
	//DrawMeshField2();

	//// プレイヤーの描画処理
	//DrawPlayer();

	// プレイヤーの描画処理
	DrawPlayer2();

	// モデルの描画処理
	DrawModel();

	//// 敵の描画処理
	//DrawEnemy();

	// 敵(親子関係なし)の描画処理
	DrawEnemy2();

	//// 壁の描画処理
	//DrawWall();

	// メッシュウォールの描画処理
	DrawMeshWall();

	// 影の描画処理
	DrawShadow();

	// ビルボードの描画処理
	DrawBillboard();

	// 弾の描画処理
	DrawBullet();

	// 爆発の描画処理
	DrawExplosion();

	// エフェクトの描画処理
	DrawEffect();

	// フレームの描画処理
	DrawFrame();

	// タイマーの描画処理
	DrawTimer();

	// スコアの描画処理
	DrawScore();

	// パーティクルの描画処理
	DrawParticle();

	//// アイテムの描画処理
	//DrawItem();

	// アイテム(モデルver)の描画処理
	DrawItem2();

	// ライフの描画処理
	DrawLife();

	if (g_bPause == true)
	{//ポーズの描画処理
		DrawPause();

		// ポーズロゴ描画処理
		DrawPauseLogo();

		// ポーズ項目描画処理
		DrawPauseSelect();
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