//=============================================================================
//
// 弾処理 [bullet.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET				(2560)									//弾の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//プレイヤー状態
	BULLETTYPE_ENEMY,		//エネミー状態
	BULLETTYPE_BOSS,		//ボス状態
	BULLETTYPE_MAX			//状態の総数
}BULLETTYPE;				//列挙型

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	BULLETTYPE type;	//弾の種類
	int nLife;			//寿命
	bool bUse;			//使用しているかどうか
	D3DXCOLOR col;		//カラー
}Bullet;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type);
Bullet *GetBullet(void);
#endif