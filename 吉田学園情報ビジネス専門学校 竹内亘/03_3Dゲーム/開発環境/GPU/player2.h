//=============================================================================
//
// プレイヤー処理 (親子関係なし) [player2.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _PLAYER2_H_
#define _PLAYER2_H_

#include "main.h"

//*****************************************************************************
// マクロ情報
//*****************************************************************************
#define MAX_PLAYERMODEL (10)		// プレイヤーのモデル数

//*****************************************************************************
// プレイヤーの構造体
//*****************************************************************************
typedef enum
{// プレイヤーの状態
	PLAYERSTATE2_APPEAR = 0,	// 出現状態
	PLAYERSTATE2_NORMAL,		// 通常状態
	PLAYERSTATE2_DAMEGE,			// ダメージ状態
	PLAYERSTATE2_DEATH,			// 死亡状態
	PLAYERSTATE2_MAX			// プレイヤーの状態の種類の総数
} PLAYERSTATE2;

typedef struct
{// プレイヤーの構造体
	D3DXVECTOR3 pos;						// 位置
	D3DXVECTOR3 rot;						// 向き
	D3DXVECTOR3 move;						// 移動
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	int nIdexShadow;						// 影の取得をするため
	int nLife;								// ライフ
	PLAYERSTATE2 state;						// プレイヤーの状態
	int nCounterState;						// 状態管理のカウンター
	D3DXVECTOR3 posOld;						// 位置
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	// モデルの最小値、最大値
	bool bDisp;								// 表示するかどうか
}Player2;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer2(void);
void UninitPlayer2(void);
void UpdatePlayer2(void);
void DrawPlayer2(void);
void HitPlayer(int nDamage);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
Player2 *GetPlayer2(void);

#endif
