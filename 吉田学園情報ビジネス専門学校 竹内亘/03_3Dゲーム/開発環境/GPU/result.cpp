//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "result.h"
#include "fade.h"
#include "input.h"
//#include "sound.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "meshWall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_TEXTURE_NAME  ""	// 読み込むテクスチャファイル名data/TEXTURE/field004.jpg
#define RESULT_POS_X         (0)                            // 背景の左上Ｘ座標
#define RESULT_POS_Y         (0)                            // 背景の左上Ｙ座標
#define RESULT_WIDTH         (SCREEN_WIDTH)                 // 背景の幅
#define RESULT_HEIGHT        (SCREEN_HEIGHT)                // 背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureResult = NULL;       // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;   // 頂点バッファへのポインタ
int                     g_nCounterResult;          // タイトル画面に移行するタイミング 

//=============================================================================
// 初期化処理
//=============================================================================
void InitResult(void)
{
	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// メッシュフィールドの初期化処理
	InitmeshField();

	//// メッシュフィールド2の初期化処理
	//InitMeshField2();

	// メッシュウォールの初期化処理
	InitMeshWall(0, D3DXVECTOR3(-25.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	InitMeshWall(1, D3DXVECTOR3(-25.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	InitMeshWall(2, D3DXVECTOR3(725.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	InitMeshWall(3, D3DXVECTOR3(725.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	//LPDIRECT3DDEVICE9 pDevice;

	//pDevice = GetDevice();

	//g_nCounterResult = 0;

	//// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	RESULT_TEXTURE_NAME,
	//	&g_pTextureResult);

	//// 頂点バッファの生成
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffResult,
	//	NULL);

	//VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	//// 頂点バッファをロックし,頂点データへのポインタを取得
	//g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//// 頂点座標
	//pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);


	//// 頂点テクスチャ
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// 頂点カラー
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// 頂点バッファをアンロックする
	//g_pVtxBuffResult->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// メッシュフィールドの終了処理
	UninitmeshField();

	//// メッシュフィールド2の終了処理
	//UninitMeshField2();

	// メッシュウォールの終了処理
	UninitMeshWall();

	// テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	
	// 頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	// メッシュフィールドの更新処理
	UpdatemeshField();

	//// メッシュフィールド2の更新処理
	//UpdateMeshField2();

	// メッシュウォールの更新処理
	UpdateMeshWall();

	FADE *pFade;
	pFade = GetFade();

	g_nCounterResult++;

	//if (*pFade != FADE_OUT)
	//{
	//	SetFade(MODE_TITLE);
	//}

	if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{// ENTERキーが押された
		SetFade(MODE_RANKING);
		//PlaySound(SOUND_LABEL_SE_DECIDE);  // 決定音を流す
	}

	if (g_nCounterResult % 400 == 0 && *pFade == FADE_NONE)
	{// 一定時間がたったら
		SetFade(MODE_RANKING);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	// カメラの設定
	SetCamera();

	// メッシュフィールドの描画処理
	DrawmeshField();

	//// メッシュフィールド2の描画処理
	//DrawMeshField2();

	// メッシュウォールの描画処理
	DrawMeshWall();

	//LPDIRECT3DDEVICE9 pDevice;

	//// デバイスを取得する
	//pDevice = GetDevice();

	//// 頂点バッファをデバイスのデータストリームに設定
	//pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pTextureResult);

	//// ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);
}