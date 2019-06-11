//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANKINGSCORE        (5)             // ランキングスコアの数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	RANKINGOLD_TITLE = 0,
	RANKINGOLD_SELECT,
	RANKINGOLD_MAX
}RANKINGOLD;

//*************************************
// ランキングスコアの状態
//*************************************
typedef enum
{
	RANKINGSCORESTATE_NONE = 0, // 更新されていない状態
	RANKINGSCORESTATE_UPDATE,   // 更新された状態
	RANKINGSCORESTATE_MAX
}RANKINGSCORESTATE;

//*************************************
// ランキングスコアの構造体
//*************************************
typedef struct
{
	D3DXVECTOR3 pos;         // 座標
	D3DXCOLOR colStd;        // 元の色
	D3DXCOLOR col;           // 現在の色
	RANKINGSCORESTATE state; // 状態
	int score;               // スコア
	int nCounterCol;         // 色を切り替えるタイミング
}RANKINGSCORE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SetRankingOld(RANKINGOLD rankold);

//------------------
//  ロゴ用
//------------------
void InitRankingLogo(void);
void UninitRankingLogo(void);
void UpdateRankingLogo(void);
void DrawRankingLogo(void);

//------------------
//  順位用
//------------------
void InitRankingRank(void);
void UninitRankingRank(void);
void UpdateRankingRank(void);
void DrawRankingRank(void);

//------------------
//  スコア用
//------------------
void InitRankingScore(void);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);
void SetRankingScore(int nScore);
RANKINGSCORE *GetRankingScore(void);

#endif