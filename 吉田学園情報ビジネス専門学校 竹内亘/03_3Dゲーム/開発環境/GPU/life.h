//=============================================================================
//
// ライフアイコン処理 [life.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; // 座標
	int nLife;       // ライフ
	bool bUse;       // 使用しているかどうか
}LIFE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(int life);
void CutLife(int cut);
//void AddLife(int nValue);

#endif