//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

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
	ENEMYSTATE_NORMAL = 0,		//通常状態
	ENEMYSTATE_DAMEGE,			//ダメージ状態
	ENEMYSTATE_MAX				//敵の状態の種類の総数
} ENEMYSTATE;

typedef struct
{// 敵の構造体
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	int nType;					//種類
	ENEMYSTATE state;			//敵の状態
	int nCounterState;			//状態管理のカウンター
	int nLife;					//敵の体力
	int nCounterAnimEnemy;		//アニメーションカウンター
	int nPartternAnimEnemy;		//アニメーションパターン更新
	bool bUse;					//使用しているかどうか
} Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy *GetEnemy(void);

#endif
