//=============================================================================
//
// アイテム処理 [item.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ITEM	        (256)	 // アイテムの最大数
#define TEXTURE_ITEM_SIZE   (20)     // テクスチャを張り付けるアイテムの高さと幅の大きさ

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{// アイテムの種類
	ITEMTYPE_COIN = 0,		//コイン
	ITEMTYPE_COIN2,
	ITEMTYPE_MAX
}ITEMTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	ITEMTYPE nType;				// 種類
	D3DXCOLOR col;			// 色
	bool bUse;				// 使用しているかどうか
	int nCounterState;		// 状態管理のカウンター
	int nCounterAnim;		// アニメーションカウンター
	int nPatternAnim;		// アニメーションパターンNo.
	float fWidth;			// 幅
	float fHeight;			// 高さ
}Item;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight, ITEMTYPE nType);
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float * fWidth, float * fHeight);
Item *GetItem(void);
int GetCoin(void);


#endif