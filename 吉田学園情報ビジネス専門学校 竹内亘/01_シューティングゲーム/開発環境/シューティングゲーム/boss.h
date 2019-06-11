//=============================================================================
//
// ボス処理 [boss.h]
// Author :　竹内亘
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ENEMY	(256)		//敵の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{// 敵の状態
	BOSSSTATE_NORMAL = 0,		//通常状態
	BOSSSTATE_DAMEGE,			//ダメージ状態
	BOSSSTATE_DEATH,			//死亡状態
	BOSSSTATE_END,
	BOSSSTATE_MAX				//ボスの状態の種類の総数
} BOSSSTATE;

typedef struct
{// 敵の構造体
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	int nType;					//種類
	BOSSSTATE state;			//敵の状態
	int nCounterState;			//状態管理のカウンター
	int nLife;					//敵の体力
	int nCounterAnimBoss;		//アニメーションカウンター
	int nPartternAnimBoss;		//アニメーションパターン更新
	bool bUse;					//使用しているかどうか
} Boss;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nType);
void HitBoss(int nCntBoss, int nDamage);
Boss *GetBoss(void);

#endif
