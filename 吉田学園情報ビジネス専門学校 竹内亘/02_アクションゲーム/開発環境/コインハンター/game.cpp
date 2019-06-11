//=============================================================================
//
// ゲームの処理 [game.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "block.h"
#include "item.h"
#include "score.h"
#include "timer.h"
#include "input.h"
#include "pause.h"
#include "pauselogo.h"
#include "pauseselect.h"
#include "fade.h"
#include "bg.h"
#include "rankingscore.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
// ブロック情報の構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	BLOCKTYPE nType;
}BlockInfo;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COIN_WIDTH		(30)				//コインの幅
#define COIN_HEIGHT		(50)				//コインの高さ

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲームの状態
int g_nCounterGameState;					//状態管理カウンター
bool g_bPause;								//ポーズ中かどうか

//***********************************
// ブロック情報のデータ
//***********************************
BlockInfo g_aBlockInfo[] =
{
	{ D3DXVECTOR3(-100,680,0),50,50,BLOCKTYPE_NOMALL },				//床左
	{ D3DXVECTOR3(750,680,0),50,50,BLOCKTYPE_NOMALL },				//床右
	{ D3DXVECTOR3(-100,500,0),50,50,BLOCKTYPE_NOMALL },				//2段目左
	{ D3DXVECTOR3(1000,500,0),50,50,BLOCKTYPE_NOMALL },				//2段目右
	{ D3DXVECTOR3(-100,300,0),50,50,BLOCKTYPE_NOMALL },				//3段目左
	{ D3DXVECTOR3(1150,300,0),50,50,BLOCKTYPE_NOMALL },				//3段目右
	{ D3DXVECTOR3(250,550,0),50,50,BLOCKTYPE_NOMALL },				//床からの柱
	{ D3DXVECTOR3(100,350,0),50,50,BLOCKTYPE_NOMALL },				//2段目からの柱
	{ D3DXVECTOR3(150,150,0),50,50,BLOCKTYPE_NOMALL },				//3段目からの柱
	{ D3DXVECTOR3(500,450,0),50,50,BLOCKTYPE_BERUTOKONBEA },		//真ん中(ベルトコンベア)
	{ D3DXVECTOR3(200,150,0),50,50,BLOCKTYPE_BERUTOKONBEA },		//上のベルトコンベア
	{ D3DXVECTOR3(50,150,0),50,50,BLOCKTYPE_NOMALL },				//4段目の壊せるブロックとの間
	{ D3DXVECTOR3(-100,150,0),50,50,BLOCKTYPE_NOMALL },				//4段目の壊せるブロックとの間
	{ D3DXVECTOR3(1100,150,0),50,50,BLOCKTYPE_NOMALL },				//4段目
	{ D3DXVECTOR3(1050,150,0),50,50,BLOCKTYPE_NOMALL },				//3段目柱
	{ D3DXVECTOR3(SCREEN_WIDTH / 2,250,0),50,50,BLOCKTYPE_JUMP },	//ジャンプ台
	{ D3DXVECTOR3(950,150,0),50,50,BLOCKTYPE_FALL },				//落ちる床

};

//=============================================================================
// ゲーム初期化処理
//=============================================================================
void InitGame(void)
{
	//背景初期化処理
	InitBG();

	//プレイヤーの初期化処理
	InitPlayer();

	//ブロックの初期化処理
	InitBlock();
	int nCntBlock;
	for (nCntBlock = 0; nCntBlock < sizeof g_aBlockInfo / sizeof(BlockInfo);nCntBlock++)
	{
		SetBlock(g_aBlockInfo[0].pos,650,50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[1].pos, 650, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[2].pos, 400, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[3].pos, 400, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[4].pos, 300, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[5].pos, 300, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[6].pos, 50, 130, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[7].pos, 50, 100, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[8].pos, 50, 150, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[9].pos, 300, 50, BLOCKTYPE_BERUTOKONBEA);
		SetBlock(g_aBlockInfo[10].pos, 300, 50, BLOCKTYPE_BERUTOKONBEA);
		SetBlock(g_aBlockInfo[11].pos, 100, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[12].pos, 100, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[13].pos, 400, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[14].pos, 50, 200, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[15].pos, 200, 50, BLOCKTYPE_JUMP);
		SetBlock(g_aBlockInfo[16].pos, 100, 50, BLOCKTYPE_FALL);

	}

	SetBlock(D3DXVECTOR3(100, 450, 0.0f), 50, 50, BLOCKTYPE_PUSH);
	SetBlock(D3DXVECTOR3(1000, 550, 0.0f), 50, 130, BLOCKTYPE_PUSH);
	SetBlock(D3DXVECTOR3(0, 150, 0.0f), 50, 50, BLOCKTYPE_BREAK);
	SetBlock(D3DXVECTOR3(1100, 300, 0.0f), 50, 50, BLOCKTYPE_BREAK);
	//SetBlock(D3DXVECTOR3(0, 150, 0.0f), 50, 50, BLOCKTYPE_BREAK);
	//SetBlock(D3DXVECTOR3(600, 300, 0.0f), 100, 100, BLOCKTYPE_JUMP);

	//アイテムの初期化処理
	InitItem();

	//アイテムのセット
	SetItem(D3DXVECTOR3(200, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//床近辺のコイン
	SetItem(D3DXVECTOR3(1100, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(400, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(850, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(630, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(630, 500, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	//SetItem(D3DXVECTOR3(200, 450, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	//SetItem(D3DXVECTOR3(1150, 450, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(550, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//ベルトコンベア上のコイン
	SetItem(D3DXVECTOR3(590, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(630, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN2);
	SetItem(D3DXVECTOR3(670, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(710, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(0, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);		//6個のコイン
	SetItem(D3DXVECTOR3(0, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(50, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(50, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(100, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(100, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(150, 100, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN2);
	SetItem(D3DXVECTOR3(250, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN2);

	SetItem(D3DXVECTOR3(1100, 100, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//右上のコイン
	SetItem(D3DXVECTOR3(1150, 50, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN2);
	SetItem(D3DXVECTOR3(1200, 100, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(1100, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//8個のコイン
	SetItem(D3DXVECTOR3(1100, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1150, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1150, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1200, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1200, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1250, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1250, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(50, 350, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//小部屋のコイン	
	SetItem(D3DXVECTOR3(0, 350, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(50, 450, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(0, 450, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(200, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1050, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(650, 150, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(700, 100, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(750, 50, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(800, 10, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	//スコアの初期化処理
	InitScore();

	//タイマーの初期化処理
	InitTimer();

	//ポーズの初期化処理
	InitPause();

	// ポーズロゴ初期化処理
	InitPauseLogo();

	// ポーズ項目初期化処理
	InitPauseSelect();

	// 爆発の初期化処理
	InitExplosion();

	g_gameState = GAMESTATE_NORMALL;	//通常状態に設定
	g_nCounterGameState = 0;
	g_bPause = false;
}
//=============================================================================
// ゲーム終了処理
//=============================================================================
void UninitGame(void)
{
	//背景終了処理
	UninitBG();

	//プレイヤーの終了処理
	UninitPlayer();

	//ブロックの終了処理
	UninitBlock();

	//アイテムの終了処理
	UninitItem();

	//スコアの終了処理
	UninitScore();

	//タイマーの終了処理
	UninitTimer();

	//ポーズの終了処理
	UninitPause();

	// ポーズロゴ終了処理
	UninitPauseLogo();

	// ポーズ項目終了処理
	UninitPauseSelect();

	// 爆発の終了処理
	UninitExplosion();
}
//=============================================================================
// ゲーム更新処理
//=============================================================================
void UpdateGame(void)
{
	//フェードの取得
	FADE *fade;
	fade = GetFade();

	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズON/OFF
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		// 背景更新処理
		UpdateBG();

		// プレイヤーの更新処理
		UpdatePlayer();

		// ブロックの更新処理
		UpdateBlock();

		//アイテムの更新処理
		UpdateItem();

		// スコアの更新処理
		UpdateScore();

		// タイマーの更新処理
		UpdateTimer();

		// 爆発の更新処理
		UpdateExplosion();

		switch (g_gameState)
		{
		case GAMESTATE_NORMALL:  // 通常状態
			break;

		case GAMESTATE_GAMEOVER:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{
				g_gameState = GAMESTATE_NONE;

				//画面の設定
				SetFade(MODE_GAMEOVER);
			}
			break;

		case GAMESTATE_END:     //終了状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{// 一定時間たったら
				g_gameState = GAMESTATE_NONE;
				SetRankingScore(GetScore());
				SetFade(MODE_RESULT);
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
		}

	}
}
//=============================================================================
// ゲーム描画処理
//=============================================================================
void DrawGame(void)
{
	//背景描画処理
	DrawBG();

	//プレイヤーの描画処理
	DrawPlayer();

	//ブロックの描画処理
	DrawBlock();

	//アイテムの描画処理
	DrawItem();

	//スコアの描画処理
	DrawScore();

	//タイマーの描画処理
	DrawTimer();

	//爆発の描画処理
	DrawExplosion();

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
