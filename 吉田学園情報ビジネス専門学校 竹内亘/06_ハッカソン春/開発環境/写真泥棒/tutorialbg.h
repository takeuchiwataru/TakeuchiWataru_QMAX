//=============================================================================
//
// チュートリアル背景の処理 [tutorialbg.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

#include "main.h"

//*****************************************************************************
// ポリゴンの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 move;			// 移動量
	bool		bUse;			// 使用しているかどうか
	D3DXMATRIX	mtxWorldTutorialBG;
} TUTORIALBG;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTutorialBG(void);
void UninitTutorialBG(void);
void UpdateTutorialBG(void);
void DrawTutorialBG(void);
void SetTutorialBG(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif