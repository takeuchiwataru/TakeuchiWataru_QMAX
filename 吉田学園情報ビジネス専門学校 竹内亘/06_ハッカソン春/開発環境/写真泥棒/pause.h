//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
//*************************************
// 項目の状態
//*************************************
typedef enum
{
	PAUSESELECT_NONE = 0,   // 選択されていない状態
	PAUSESELECT_SELECT,     // 選択されている状態
	PAUSESELECT_PUSH,       // 押されている状態
	PAUSESELECT_MAX
}PAUSESELECT;

typedef enum
{
	RESTART_CONTINUE,  // コンティニュー
	RESTART_RETRY,     // ゲームリトライ
	RESTART_QUIT,      // タイトル遷移
	RESTART_MAX
}RESTART;

//*************************************
// 項目の構造体
//*************************************
typedef struct
{
	D3DXCOLOR col;       // 色
	PAUSESELECT select;  // 選択されているかどうか
	int nCounter;        // 描画するタイミングを計るカウンター
}PAUSE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//----------------
// 黒画面用
//----------------
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

//----------------
// ロゴ用
//----------------
void InitPauseLogo(void);
void UninitPauseLogo(void);
void UpdatePauseLogo(void);
void DrawPauseLogo(void);

//----------------
// 選択項目用
//----------------
void InitPauseSelect(void);
void UninitPauseSelect(void);
void UpdatePauseSelect(void);
void DrawPauseSelect(void);
RESTART GetRestart(void);

#endif