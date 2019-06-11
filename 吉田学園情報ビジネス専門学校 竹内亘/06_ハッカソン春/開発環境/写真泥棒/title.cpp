//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "title.h"
#include "titlelogo.h"
#include "pressenter.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

#include "camera.h"
#include "light.h"
#include "field.h"
#include "model.h"
#include "sky.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int            g_nCounterTitle;          // ランキング画面に遷移するタイミング

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle(void)
{
	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// フィールドの初期化処理
	InitField();

	// モデルの初期化処理
	InitModel();

	// 空の初期化処理
	InitSky();

	// タイトルロゴの初期化処理
	InitTitleLogo();

	g_nCounterTitle = 0;   // カウンターは0に
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// フィールドの終了処理
	UninitField();

	// モデルの終了処理
	UninitModel();

	// 空の終了処理
	UninitSky();

	// タイトルロゴの終了処理
	UninitTitleLogo();
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	// フィールドの更新処理
	UpdateField();

	// モデルの更新処理
	UpdateModel();

	// 空の更新処理
	UpdateSky();

	// タイトルロゴの更新処理
	UpdateTitleLogo();

	FADE fade;
	fade = GetFade();
	bool *disp;
	disp = GetDispPressEnter();

	g_nCounterTitle++;

	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE && *disp == true || GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE && fade == FADE_NONE && *disp == true)
	{// 決定ボタンが押された
		SetFade(MODE_TUTORIAL);
		PlaySound(SOUND_LABEL_SE_DECIDE);
	}

	for (int nCntPad = 0; nCntPad < 8; nCntPad++)
	{
		if (GetJoyPadTrigger(nCntPad, 0) == TRUE &&  fade == FADE_NONE && *disp == true)
		{
			SetFade(MODE_TUTORIAL);
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
	}

	if (g_nCounterTitle % 1800 == 0 && fade == FADE_NONE)
	{// 一定時間がたつ
		SetFade(MODE_RANKING);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	// カメラの描画処理
	SetCamera();

	// フィールドの描画処理
	DrawField();

	// モデルの描画処理
	DrawModel();

	// 空の描画処理
	DrawSky();

	// タイトルロゴの描画処理
	DrawTitleLogo();
}