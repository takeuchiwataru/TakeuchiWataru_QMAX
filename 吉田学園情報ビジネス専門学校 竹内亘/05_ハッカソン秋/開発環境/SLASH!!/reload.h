//=============================================================================
//
// 切れ味処理 [reload.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _RELOAD_H_
#define _RELOAD_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; // 座標
	int reload;      // 切れ味
	bool bUse;       // 使用しているかどうか
}Reload;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitReload(void);
void UninitReload(void);
void UpdateReload(void);
void DrawReload(void);
void SetReload(int reload);
void CutReload(int cut);
void AddReload(void);

#endif