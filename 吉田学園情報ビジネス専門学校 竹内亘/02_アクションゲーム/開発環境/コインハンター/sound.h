//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
typedef enum //ラベルと数と並びを揃える
{
	SOUND_LABEL_BGM_GAME = 0,	// ゲーム中のBGM
	SOUND_LABEL_BGM_TITLE,		// BGMタイトル
	SOUND_LABEL_BGM_GAMEOVER,	// ゲームオーバーBGM
	SOUND_LABEL_BGM_GAMECLEAR,	// ゲームクリアBGM
	SOUND_LABEL_SE_JUMP000,		// ジャンプ
	SOUND_LABEL_SE_JUMP001,		// ジャンプ
	SOUND_LABEL_SE_COINOOO,		// コイン
	SOUND_LABEL_SE_OSU,			// 押すブロックの音
	SOUND_LABEL_SE_BREAK,		// ブロックの壊れる音
	SOUND_LABEL_SE_DECIDE,		// 決定音
	SOUND_LABEL_SE_SELECT,		// 選択音
	SOUND_LABEL_MAX
} SOUND_LABEL;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
