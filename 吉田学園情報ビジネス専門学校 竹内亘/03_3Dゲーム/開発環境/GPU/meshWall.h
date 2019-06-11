//=============================================================================
//
// ポリゴン処理 [meshWall.h]
// Author : 竹内亘  
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 rot;					// 向き
	D3DXMATRIX	mtrxWorld;				// ワールドマトリックス
	float fHeght;						// 高さ
	float fWidth;						// 幅
	int nVtxIndex = 0;
	int nIdxIndex = 0;
	float fPos_X = 0;
	float fPos_Y = 0;
	float fXpos = 0;
	float fYpos = 0;
	bool bUse;							// 使用しているかどうか
} MeshWall;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshWall(int nIdxMeshWall, D3DXVECTOR3 pos , D3DXVECTOR3 rot);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
MeshWall *GetMeshWall(void);

#endif
