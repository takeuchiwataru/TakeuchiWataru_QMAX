//=============================================================================
//
// ビルボードの処理 [billboard.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// 弾の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	int nIdexShadow;			// 影を取得のため
	bool bUse;					// 使用しているかどうか
}Billboard;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
int SetBillboard(D3DXVECTOR3 pos);


#endif
