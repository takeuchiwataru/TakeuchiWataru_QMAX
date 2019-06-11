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
	SOUND_LABEL_BGM_TITLE,		// タイトルBGM
	SOUND_LABEL_BGM_RANKING,	// ランキングBGM
	SOUND_LABEL_BGM_GAMECLEAR,	// ゲームクリアBGM
	SOUND_LABEL_BGM_GAMEOVER,	// ゲームオーバーBGM
	SOUND_LABEL_SE_KARASU,		// カラスの鳴き声
	SOUND_LABEL_SE_PAUSE000,	// ポーズ開く
	SOUND_LABEL_SE_PAUSE001,	// ポーズ閉じる
	SOUND_LABEL_SE_SELECT000,	// 選択音
	SOUND_LABEL_SE_ENTER000,	// 決定音
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
