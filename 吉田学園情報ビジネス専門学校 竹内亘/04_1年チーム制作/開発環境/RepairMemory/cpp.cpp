//=============================================================================
//
// タイトル画面 [title.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "input.h"
//#include "sound.h"
#include "start.h"
#include "fade.h"
//#include "meshFild.h"
#include "polygon.h"
#include "flontpolygon.h"

//=============================================================================
// マクロ定義
//=============================================================================


//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTitle = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
int g_nCntTime;										//エフェクトのカウンター
int g_nCntTimeTitle;								//タイトル時間のカウンター

//=============================================================================
// タイトル初期化処理
//=============================================================================
void InitTitle(void)
{
	//変数宣言
	g_nCntTime = 0;
	g_nCntTimeTitle = 0;

	//関数呼び出し
	InitPolygon();		//ポリゴン
	//InitMeshFild();		//メッシュフィールド
	InitStart();		//スタートボタン
	InitFlontPolygon();	//フロントポリゴン

	//タイトル
	SetFlontPolygon(0, D3DXVECTOR3(610.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1200.0f, 300.0f);

	//ボタンのセット
	SetEnter(D3DXVECTOR3(630.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitTitle(void)
{
	//関数呼び出し
	UninitPolygon();			//ポリゴン
	//UninitMeshFild();		//メッシュフィールド
	UninitStart();			//スタートボタン
	UninitFlontPolygon();	//フロントポリゴン
	
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateTitle(void)
{
	//時間を加算する
	g_nCntTime++;
	g_nCntTimeTitle++;

	//フェード情報を取得する
	FADE fade;
	fade = GetFade();

	//関数呼び出し
	UpdatePolygon();		//ポリゴン
	//UpdateMeshFild();		//メッシュフィールド
	UpdateStart();			//スタートボタン
	UpdateFlontPolygon();	//フロントポリゴン
	
	
	//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{
			//スタートボタンの設定
			SetPush(STARTSTRACT_ENTER);

			//フェードモード設定
			SetFade(MODE_STORY);
			//PlaySound(SOUND_LABEL_SE_ENTER);	//決定音
		}
	}
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawTitle(void)
{
	//関数呼び出し
	DrawPolygon();		//ポリゴン
	//DrawMeshFild();	//メッシュフィールド
	DrawStart();		//スタートボタン
	DrawFlontPolygon();	//フロントポリゴン
}