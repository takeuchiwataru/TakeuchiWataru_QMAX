//=============================================================================
//
// モデル処理 [model.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{// モデルの種類
	MODELTYPE_BENCH = 0,		// ベンチ1
	MODELTYPE_BENCH2,			// ベンチ2
	MODELTYPE_BURANKO,			// ブランコ
	MODELTYPE_SLIDE,			// 滑り台
	MODELTYPE_TAIYA,			// タイヤ
	MODELTYPE_JG,				// ジャングルジム
	MODELTYPE_SEESAW,			// シーソー
	MODELTYPE_TAIYA2,			// タイヤ2
	MODELTYPE_MAX
} MODELTYPE;

typedef struct
{
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	// モデルの最小値、最大値
} VTXMODEL;

typedef struct
{
	DWORD nNumMat = 0;						// マテリアル情報の数
	D3DXVECTOR3 pos;						// 位置
	D3DXVECTOR3 rot;						// 向き
	D3DXVECTOR3 move;						// 向き
	D3DXMATRIX	mtxWorld;					// ワールドマトリックス
	int nIdxShadow;							// 影のインデックス
	MODELTYPE nType;						// モデルの種類
	bool bUse;								// 使用しているか
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	// モデルの最小値、最大値
} MODEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
//bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
MODEL *GetModel(void);

#endif