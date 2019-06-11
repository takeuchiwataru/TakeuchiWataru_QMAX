//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// プレイヤーの構造体
//*****************************************************************************
typedef enum
{// プレイヤーの状態
	PLAYERSTATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL,		//通常状態
	PLAYERSTATE_DAMEGE,		//ダメージ状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_END,
	PLAYERSTATE_MAX			//敵の状態の種類の総数
} PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nLife;				//プレイヤーの体力
	int nCounterState;		//状態管理のカウンター
	PLAYERSTATE state;		//プレイヤーの状態
	bool bDisp;				//表示するかどうか
} Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
Player *GetPlayer(void);

#endif