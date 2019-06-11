//=============================================================================
//
// チュートリアル画面処理 [tutorial.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "tutorial.h"
#include "sky.h"
#include "field.h"
#include "fade.h"
#include "pressenter.h"
#include "input.h"
#include "sound.h"
#include "tutorialbg.h"
#include "camera.h"
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//***************************************************************************** 
TUTORIAL_STATE g_TutorialState;		//状態
int g_MoveTimer;	//移動のタイマー
int g_nCntMove;	//移動のカウンター

//=============================================================================
// 初期化処理
//=============================================================================
void InitTutorial(void)
{
	g_nCntMove = 0;							//移動カウンターを初期化
	g_MoveTimer = 0;						//移動タイマーを初期化
	g_TutorialState = TUTORIAL_STATE_NONE;	//状態の初期化

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//チュートリアルbgの初期化処理
	InitTutorialBG();

	// 空の初期化処理
	InitSky();

	// フィールドの初期化処理
	InitField();

	SetTutorialBG(D3DXVECTOR3(0.0f, 150.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetTutorialBG(D3DXVECTOR3(1500.0f, 150.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{
	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//チュートリアルbgの終了処理
	UninitTutorialBG();

	// 空の終了処理
	UninitSky();

	// フィールドの終了処理
	UninitField();
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	FADE fade;
	fade = GetFade();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	//チュートリアルbgの更新処理
	UpdateTutorialBG();

	// 空の更新処理
	UpdateSky();

	// フィールドの更新処理
	UpdateField();

	//カメラの取得
	Camera *pCamera = GetCamera();

	switch (g_TutorialState)
	{
	case TUTORIAL_STATE_NONE:	//通常状態
		pCamera->posV.x -= 0.0f;
		pCamera->posV.z -= 0.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength.x;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength.z;
		break;
	case TUTORIAL_STATE_MOVE:	//移動状態


		pCamera->posV.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posV.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength.x;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength.z;
		g_MoveTimer++;

		if (g_MoveTimer == 150.0f)
		{//カウントが８５になった場合
			g_TutorialState = TUTORIAL_STATE_NONE;		//通常状態に戻す
			g_nCntMove++;								//移動カウンターを足す
			g_MoveTimer = 0;							//タイマーを初期化する
		}

		break;
	case TUTORIAL_STATE_REMOVE:	//戻る状態

		pCamera->posV.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posV.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength.x;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength.z;
		g_MoveTimer++;
		if (g_MoveTimer == 150.0f)
		{//カウントが８５になった場合
			g_TutorialState = TUTORIAL_STATE_NONE;		//通常状態に戻す
			g_nCntMove--;								//移動カウンターを足す
			g_MoveTimer = 0;							//タイマーを初期化する
		}
		break;
	}
	if (g_TutorialState == TUTORIAL_STATE_NONE)
	{//通常状態の場合
		if (g_nCntMove == 0)
		{
			if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoyPadTrigger(DIJS_BUTTON_20, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_12, 0) == true)
			{
				g_TutorialState = TUTORIAL_STATE_MOVE;
			}
		}
		if (g_nCntMove == 1)
		{
			if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoyPadTrigger(DIJS_BUTTON_21, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_13, 0) == true)
			{
				g_TutorialState = TUTORIAL_STATE_REMOVE;
			}
		}
	}
	if (g_nCntMove == 1)
	{
		for (int nCntJoyPad = 0; nCntJoyPad < 8; nCntJoyPad++)
		{
			if (GetJoyPadTrigger(nCntJoyPad, 0) == TRUE && fade == FADE_NONE)
			{
				SetFade(MODE_GAME);
			}
		}
		if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
		{// 決定ボタンが押された
			SetFade(MODE_GAME);
		}
	}
	//if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE && fade == FADE_NONE)
	//{// 決定ボタンが押された
	//	SetFade(MODE_GAME);
	//}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	//カメラの設置
	SetCamera();

	// 空の描画処理
	DrawSky();

	// フィールドの描画処理
	DrawField();

	//チュートリアルbgの描画処理
	DrawTutorialBG();
}