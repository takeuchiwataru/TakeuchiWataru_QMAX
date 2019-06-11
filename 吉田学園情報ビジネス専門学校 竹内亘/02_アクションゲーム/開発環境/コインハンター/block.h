//=============================================================================
//
// ブロック処理 [block.h]
// Author :　竹内亘
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{// ブロックの種類
	BLOCKTYPE_NOMALL = 0,		//普通ブロック
	BLOCKTYPE_BERUTOKONBEA,		//ベルトコンベア右
	BLOCKTYPE_BERUTOKONBEA2,	//ベルトコンベア左
	BLOCKTYPE_PUSH,				//押せるブロック
	BLOCKTYPE_BREAK,			//壊せるブロック
	BLOCKTYPE_JUMP,				//ジャンプブロック
	BLOCKTYPE_FALL,				//落下ブロック
	//BLOCKTYPE_YOKOMOVE,			//横移動ブロック
	//BLOCKTYPE_TATEMOVE,			//縦移動ブロック
	BLOCKTYPE_MAX
} BLOCKTYPE;

typedef struct
{
	D3DXVECTOR3 pos;			//ブロックの位置
	float fWidth;				//幅
	float fHeight;				//高さ
	BLOCKTYPE nType;			//種類
	D3DXVECTOR3 move;			//移動量
	bool bUse;					//使用してるかどうか
	// 移動を管理する
}Block;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,float fWidth,float fHeight, BLOCKTYPE nType);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove,float * fWidth,float * fHeight,Block **pBlock);

#endif
