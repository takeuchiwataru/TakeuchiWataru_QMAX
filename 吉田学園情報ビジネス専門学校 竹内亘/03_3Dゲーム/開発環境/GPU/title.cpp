//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "pressenter.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "meshWall.h"
#include "model.h"
#include "billboard.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEXTURE_NAME  "data/TEXTURE/block100.png"				// 読み込むテクスチャファイル名
#define TITLE_POS_X         (0)                         // 背景の左上Ｘ座標
#define TITLE_POS_Y         (0)                         // 背景の左上Ｙ座標
#define TITLE_WIDTH         (SCREEN_WIDTH)              // 背景の幅
#define TITLE_HEIGHT        (SCREEN_HEIGHT)             // 背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureTitle = NULL;		// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		// 頂点バッファへのポインタ 
int                     g_nCounterTitle;			// ランキング画面に遷移するタイミング 
D3DXVECTOR3 g_posTitle;								// 位置
D3DXVECTOR3 g_rotTitle;								// 向き
D3DXMATRIX g_mtxWorldTitle;							// ワールドマトリックス

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	g_nCounterTitle = 0;

	//// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	TITLE_TEXTURE_NAME,
	//	&g_pTextureTitle);

	//// 頂点バッファの生成
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffTitle,
	//	NULL);

	//VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	//// 頂点バッファをロックし,頂点データへのポインタを取得
	//g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//// 頂点座標
	//pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

	//// 頂点テクスチャ
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////// 法線の設定
	////pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	////pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	////pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	////pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//// 頂点カラー
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// 頂点バッファをアンロックする
	//g_pVtxBuffTitle->Unlock();

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

	// モデルの初期化処理
	InitModel();
	SetModel(D3DXVECTOR3(715.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH);
	SetModel(D3DXVECTOR3(715.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH);
	SetModel(D3DXVECTOR3(-15.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH2);
	SetModel(D3DXVECTOR3(-15.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH2);

	SetModel(D3DXVECTOR3(400.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA);
	SetModel(D3DXVECTOR3(540.0f, 0.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA2);
	SetModel(D3DXVECTOR3(100.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA2);

	SetModel(D3DXVECTOR3(100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BURANKO);
	SetModel(D3DXVECTOR3(170.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BURANKO);
	SetModel(D3DXVECTOR3(500.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_SLIDE);
	SetModel(D3DXVECTOR3(300.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_JG);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_SEESAW);

	// ビルボードの初期化処理
	InitBillboard();
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, 10.0f));
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(100.0f, 0.0f, 650.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, 500.0f));
	SetBillboard(D3DXVECTOR3(250.0f, 0.0f, 250.0f));
	SetBillboard(D3DXVECTOR3(300.0f, 0.0f, 650.0f));
	SetBillboard(D3DXVECTOR3(350.0f, 0.0f, 500.0f));
	SetBillboard(D3DXVECTOR3(400.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(450.0f, 0.0f, 560.0f));
	SetBillboard(D3DXVECTOR3(500.0f, 0.0f, 100.0f));
	SetBillboard(D3DXVECTOR3(500.0f, 0.0f, 10.0f));
	SetBillboard(D3DXVECTOR3(550.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(600.0f, 0.0f, 600.0f));
	SetBillboard(D3DXVECTOR3(650.0f, 0.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(700.0f, 0.0f, 340.0f));

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

	// メッシュフィールドの終了処理
	UninitmeshField();

	//// メッシュフィールド2の終了処理
	//UninitMeshField2();

	// メッシュウォールの終了処理
	UninitMeshWall();

	// モデルの終了処理
	UninitModel();

	// ビルボードの終了処理
	UninitBillboard();

	// テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
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

	// メッシュフィールドの更新処理
	UpdatemeshField();

	//// メッシュフィールド2の更新処理
	//UpdateMeshField2();

	// メッシュウォールの更新処理
	UpdateMeshWall();

	// モデルの更新処理
	UpdateModel();

	// ビルボードの更新処理
	UpdateBillboard();

	FADE *pFade;
	pFade = GetFade();
	bool *disp;
	disp = GetDispPressEnter();

	g_nCounterTitle++;

	if(GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{// ENTERキーが押された
		SetFade(MODE_TUTORIAL);
		PlaySound(SOUND_LABEL_SE_ENTER000);  // 決定音を流す
		//StopSound(SOUND_LABEL_SE_ENTER000);
	}

	if (g_nCounterTitle % 500 == 0 && *pFade == FADE_NONE)
	{// 一定時間がたつ
		SetFade(MODE_RANKING);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// カメラの設定
	SetCamera();

	// メッシュフィールドの描画処理
	DrawmeshField();

	//// メッシュフィールド2の描画処理
	//DrawMeshField2();

	// メッシュウォールの描画処理
	DrawMeshWall();

	// モデルの描画処理
	DrawModel();

	// ビルボードの描画処理
	DrawBillboard();

	//D3DXMATRIX mtxView, mtxTrans;				//計算用マトリックス

	//// ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&g_mtxWorldTitle);

	//pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//g_mtxWorldTitle._11 = mtxView._11;
	//g_mtxWorldTitle._12 = mtxView._21;
	//g_mtxWorldTitle._13 = mtxView._31;
	//g_mtxWorldTitle._21 = mtxView._12;
	//g_mtxWorldTitle._22 = mtxView._22;
	//g_mtxWorldTitle._23 = mtxView._32;
	//g_mtxWorldTitle._31 = mtxView._13;
	//g_mtxWorldTitle._32 = mtxView._23;
	//g_mtxWorldTitle._33 = mtxView._33;

	//// 位置を反映
	//D3DXMatrixTranslation(&mtxTrans, g_posTitle.x, g_posTitle.y, g_posTitle.z);
	//D3DXMatrixMultiply(&g_mtxWorldTitle, &g_mtxWorldTitle, &mtxTrans);

	//// ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTitle);

	//// 頂点バッファをデバイスのデータストリームに設定
	//pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pTextureTitle);

	//// タイトル画面の描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);
}