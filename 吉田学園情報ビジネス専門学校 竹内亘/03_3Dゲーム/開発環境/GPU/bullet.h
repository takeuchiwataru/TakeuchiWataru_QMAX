//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// 弾の構造体
//*****************************************************************************
typedef enum
{// 弾の種類
	BULLETTYPE_PLAYER = 0,	//プレイヤーの弾
	BULLETTYPE_ENEMY,		//敵の弾
	BULLETTYPE_MAX
} BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 move;			// 移動量
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	int nIdexShadow;			// 影を取得のため
	int nLife;					// 弾のライフ
	BULLETTYPE nType;			// 弾の種類
	D3DXVECTOR3 vecA;			// ベクトルA
	D3DXVECTOR3 vecB;			// ベクトルB
	D3DXVECTOR3 vecC;			// ベクトルC
	bool bUse;					// 使用しているかどうか
}Bullet;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);
//void SetPositionBillboard(int nIdexBillboard, D3DXVECTOR3 pos);




#endif
