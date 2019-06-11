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
typedef enum
{
	SOUND_LABEL_BGM000 = 0,			// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_BGM002,				// BGM2
	SOUND_LABEL_BGM003,				// BGM3(ボス)
	SOUND_LABEL_SE_SHOT,			// 弾発射音0
	SOUND_LABEL_SE_SHOT001,			// 弾発射音1
	SOUND_LABEL_SE_SHOT002,			// 弾発射音2
	SOUND_LABEL_SE_HIT000,			// ヒット音0
	SOUND_LABEL_SE_HIT001,			// ヒット音1
	SOUND_LABEL_SE_HIT002,			// ヒット音2
	SOUND_LABEL_SE_EXPLOSION,		// 爆発音0
	SOUND_LABEL_SE_EXPLOSION001,	// 爆発音1
	SOUND_LABEL_SE_GAMECLEAR,		// ゲームクリア
	SOUND_LABEL_SE_GAMEOVER,		// ゲームオーバー
	SOUND_LABEL_SE_DECIDE,			// 決定音
	SOUND_LABEL_MAX,
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
