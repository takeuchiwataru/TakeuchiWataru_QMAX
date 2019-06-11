//=============================================================================
//
// アイテム(モデルver)処理 [item2.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ITEM2_H_
#define _ITEM2_H_

#include "main.h"

//*****************************************************************************
// マクロ情報
//*****************************************************************************

//*****************************************************************************
// アイテムの構造体
//*****************************************************************************
typedef enum
{// アイテムの種類
	ITEMTYPE2_GOMI = 0,			// ゴミ
	ITEMTYPE2_PB,				// PB
	ITEMTYPE2_KAN,				// 缶
	ITEMTYPE2_BOOK,				// 本
	ITEMTYPE2_MAX
}ITEMTYPE2;

typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 rot;				// 向き
	D3DXVECTOR3 move;				// 移動
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3 VtxMinModel;		// モデルの最小値
	D3DXVECTOR3 VtxMaxModel;		// モデルの最大値
	int nIdexShadow;				// 影の取得をするため
	ITEMTYPE2 nType;				// アイテムの種類
	int nNumItem;					// アイテムの総数
	bool bUse;						// 使用しているかどうか
}ITEM2;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem2(void);
void UninitItem2(void);
void UpdateItem2(void);
void DrawItem2(void);
void SetItem2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, ITEMTYPE2 nType);
bool CollisionItem2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
ITEM2 *GetItem2(void);
int GetITEM(void);

#endif
