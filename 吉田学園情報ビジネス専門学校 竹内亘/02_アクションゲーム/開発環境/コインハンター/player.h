//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "block.h"

//*****************************************************************************
// プレイヤーの構造体
//*****************************************************************************
typedef enum
{// プレイヤーの状態
	PLAYERSTATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMALL,	//通常状態
	PLAYERSTATE_DAMEGE,		//ダメージ状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_END,
	PLAYERSTATE_MAX			//状態の種類の総数
} PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	int nDirectionMove;		//0が右、1が左
	D3DXCOLOR	col;		//色
	PLAYERSTATE state;		//プレイヤーの状態
	int nCounterState;		//状態管理のカウンター
	float fWidth;			//幅
	float fHeight;			//高さ
	//int nLife;				//プレイヤーの体力
	//int Remain;				//残機
	//int nSharp;				//剣の切味
	//int nCounterSharp;		//切味のカウンター
	//int nCounterGauge;		//ゲージカウンター
	bool bDisp;				//表示するかどうか
	bool bJump;				//ジャンプしてるかどうか
	Block *pBlock;			//対象のブロックへのポインタ
} Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
//void HitPlayer(int nDamage);
Player *GetPlayer(void);

#endif