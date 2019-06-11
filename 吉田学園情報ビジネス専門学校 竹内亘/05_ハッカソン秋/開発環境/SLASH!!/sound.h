//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Meguro Mikiya
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
	SOUND_LABEL_BGM_TITLE = 0,	// BGMタイトル
	SOUND_LABEL_BGM_TUTORIAL,	// BGMチュートリアル
	SOUND_LABEL_BGM_GAME,		// BGMゲーム
	SOUND_LABEL_BGM_RESULT,		// BGMリザルト
	SOUND_LABEL_BGM_RANKING,	// BGMランキング
	SOUND_LABEL_SE_ZANGEKI,		// 斬撃
	SOUND_LABEL_SE_ZANKIKAIHUKU,// 残機回復
	SOUND_LABEL_SE_LIFEKAIHUKU,	// ライフ回復
	SOUND_LABEL_SE_KENMA,		// 研磨
	SOUND_LABEL_SE_KEN,			// 剣リロード
	SOUND_LABEL_SE_KAMINARI,	// 必殺技
	SOUND_LABEL_SE_BOMB000,		// 爆発音
	SOUND_LABEL_SE_DECIDE,		// 決定音
	SOUND_LABEL_SE_SELECT,
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
