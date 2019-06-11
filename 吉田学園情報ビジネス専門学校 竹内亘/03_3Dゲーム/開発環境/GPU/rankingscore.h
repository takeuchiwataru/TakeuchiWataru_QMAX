//=============================================================================
//
// ランキングスコア処理 [rankingscore.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANKINGSCORE        (5)             // ランキングスコアの数

//*****************************************************************************
// ランキングスコアの構造体
//*****************************************************************************
typedef enum
{//ランキングスコアの状態
	RANKINGSCORESTATE_NONE = 0, // 更新されていない状態
	RANKINGSCORESTATE_UPDATE,   // 更新された状態
	RANKINGSCORESTATE_MAX
}RANKINGSCORESTATE;

typedef struct
{
	D3DXVECTOR3 pos;         // 座標
	D3DXCOLOR col;           // 色
	RANKINGSCORESTATE state; // 状態
	int score;               // スコア
	int nCounterCol;         // 色を切り替えるタイミング
}RANKINGSCORE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRankingScore(void);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);
void SetRankingScore(int nScore);
RANKINGSCORE *GetRankingScore(void);

#endif