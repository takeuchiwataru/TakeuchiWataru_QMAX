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
// マクロ定義
//*****************************************************************************
#define PLAYER_LIFE			(3)									//プレイヤーライフ
#define PLAYER_REMAIN		(3)									//プレイヤーの残機
#define PLAYER_SHARP		(5)									//プレイヤーの剣の切味

//*****************************************************************************
// プレイヤーの構造体
//*****************************************************************************
typedef enum
{// プレイヤーの状態
	PLAYERSTATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL,		//通常状態
	PLAYERSTATE_DAMEGE,		//ダメージ状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_GAUGE_MAX,  //ゲージマックス状態
	PLAYERSTATE_MAX			//敵の状態の種類の総数
} PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//座標
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR	col;		//色
	PLAYERSTATE state;		//プレイヤーの状態
	int nCounterState;		//状態管理のカウンター
	int nLife;				//プレイヤーの体力
	int nRemain;		    //残機
	int nSharp;				//剣の切味
	int nCounterSharp;		//切味のカウンター
	int nCounterGauge;		//ゲージカウンター
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