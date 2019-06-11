//=============================================================================
//
// ゲーム処理 [game.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// ゲームの状態
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,		//何もしてない
	GAMESTATE_NORMALL,		//通常状態
	GAMESTATE_GAMECLEAR,	//ゲームクリア状態
	GAMESTATE_GAMEOVER,		//ゲームオーバー状態
	GAMESTATE_END,			//終了状態
	GAMESTATE_MAX
}GAMESTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif