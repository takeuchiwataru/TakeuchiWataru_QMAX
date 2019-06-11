//=============================================================================
//
// フレーム処理 [frame.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _FRAME_H_
#define _FRAME_H_

#include "main.h"

//*****************************************************************************
// フレームの構造体定義
//*****************************************************************************
typedef enum
{// フレームの種類
	FRAME_TIMER = 0,
	FRAME_SCORE,
	FRAME_LIFE,
	FRAME_MAX
}FRAME;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// 色
	float fWidth;			// 幅
	float fHeight;			// 高さ
	FRAME nType;			// 種類
	bool bUse;				// 使用しているかどうか
}Frame;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitFrame(void);
void UninitFrame(void);
void UpdateFrame(void);
void DrawFrame(void);

#endif

