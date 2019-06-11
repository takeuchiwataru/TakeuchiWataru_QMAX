//=============================================================================
//
// 敵処理 [enemy.h]
// Author :Mikiya Meguro
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ENEMY	(128)	// 敵の最大数
#define	ENEMY_DATA	(3)	// 敵の数
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_MAX			//状態の総数
}ENEMYSTATE;				//列挙型

typedef struct
{
		D3DXVECTOR3	pos;			//位置
		D3DXVECTOR3	move;			//位置
		int			nType;			//種類
		ENEMYSTATE	state;			//敵の状態
		int			nCounterState;	//状態管理のカウンター
		int			nCounterAnim;	//アニメーションカウンター
		int			nPatternAnim;	//アニメーションパターンNoを初期化
		bool		bUse;			//使用しているか	
		int			nLife;			//体力
		int			nCntWall;		//壁に当たったときにカウント
		int			nCunterStop;	//カウンターが一定以上になったらストップ
		int			nRandomCnt;		//ランダムで変わる
		int			nRandomMove;	//ランダムで変わる移動量
		float		fMoveEnemyX = 5.0f;
		float		fMoveEnemyY = 1.0f;
		D3DXCOLOR col;				//カラー
}Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif
