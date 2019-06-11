//=============================================================================
//
// 動物の処理 [obstacle.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include "main.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef enum
{
	ANIMALTYPE_CAT = 0,    // 猫
	ANIMALTYPE_DOG,        // 犬
	ANIMALTYPE_CROW,       // カラス
	ANIMALTYPE_MAX
}ANIMALTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	              // 現在の位置
	D3DXVECTOR3 posold;	              // 前回の位置
	D3DXVECTOR3 rot;	              // 現在の向き
	D3DXVECTOR3 DestRot;              // 目的の向き
	D3DXVECTOR3 DiffRot;              // 差分の向き
	D3DXVECTOR3 move;	              // 移動量
	int         nMoveCounter;         // 移動管理カウンター
	int			nInxShadow;           // 影
	ANIMALTYPE	Type;                 // 種類
	D3DXMATRIX	mtxWorld;	          // ワールドマトリックス
	bool		bUse;                 // 使用しているかどうか
	D3DXVECTOR3	vtxMinObstacle, vtxMaxObstacle;	// モデルの最小値、最大値
}ANIMAL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitAnimal(void);
void UninitAnimal(void);
void UpdateAnimal(void);
void DrawAnimal(void);
void SetAnimal(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, ANIMALTYPE type);
void CollisionShutterAnimal(D3DXVECTOR3 pos, D3DXVECTOR3 radius);

#endif