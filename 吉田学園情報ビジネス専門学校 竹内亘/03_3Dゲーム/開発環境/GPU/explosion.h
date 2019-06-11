//=============================================================================
//
// 爆発処理 [explosion.h]
// Author :　竹内亘
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// 爆発の構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	//D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// 色
	int nCounterAnim;		// アニメーションカウンター
	int nPatternAnim;		// アニメーションパターン
	//float fHeight;			// 高さ
	//float fWidth;			// 幅
	//D3DXVECTOR3 pos;		// 位置
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	bool bUse;				// 使用しているかどうか
} Explosion;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col);

#endif
