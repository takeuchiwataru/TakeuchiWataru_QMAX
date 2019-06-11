//=============================================================================
//
// チュートリアル画面処理 [tutorial.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

typedef enum
{
	TUTORIAL_STATE_NONE,		//通常状態
	TUTORIAL_STATE_MOVE,		//移動状態
	TUTORIAL_STATE_REMOVE,		//戻る状態
	TUTORIAL_STATE_MAX,
}TUTORIAL_STATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif