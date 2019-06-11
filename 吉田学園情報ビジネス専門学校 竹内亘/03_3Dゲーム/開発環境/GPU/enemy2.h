//=============================================================================
//
// 敵2処理 [enemy2.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ENEMY2_H_
#define _ENEMY2_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{// 敵の種類
	ENEMYTYPE2_NORMAL = 0,			// 普通のカラス
	ENEMYTYPE2_MAX
} ENEMYTYPE2;

typedef struct
{
	DWORD nNumMat = 0;						// マテリアル情報の数
	D3DXVECTOR3 pos;						// 位置
	D3DXVECTOR3 posOld;						// 位置
	D3DXVECTOR3 rot;						// 向き
	D3DXVECTOR3 move;						// 向き
	D3DXMATRIX	mtxWorld;					// ワールドマトリックス
	int nIdxShadow;							// 影のインデックス
	ENEMYTYPE2 nType;						// モデルの種類
	int nIdexShadow;						// 影の取得をするため
	//bool bUse;								// 使用しているか
	bool bDisp;								// 表示するかどうか
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	// モデルの最小値、最大値
} ENEMY2;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy2(void);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
//bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
void SetEnemy2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE2 nType);
bool CollisionEnemy2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
ENEMY2 *GetEnemy2(void);

#endif