//=============================================================================
//
// 背景描画処理 [bg01.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "bg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_TEXTURE_NAME  "data/TEXTURE/sky000.jpg"			// 読み込むテクスチャファイル名
#define BG_POS_X         (0)								// 背景の左上Ｘ座標
#define BG_POS_Y         (0)								// 背景の左上Ｙ座標
#define BG_WIDTH         (SCREEN_WIDTH)						// 背景の幅
#define BG_HEIGHT        (SCREEN_HEIGHT)					// 背景の高さ
#define ANIMATIONPATTERN (0.00020f * g_PatternAnimBG01)		// 背景テクスチャ座標を切り替える計算式

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureBG01 = NULL;       // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG01 = NULL;   // 頂点バッファへのポインタ
int g_CounterAnimBG01;                           // アニメーションカウンター 
int g_PatternAnimBG01;                           // アニメーションパターンNo.

//=============================================================================
// 初期化処理
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		                      BG_TEXTURE_NAME,
		                      &g_pTextureBG01);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBG01,
		                        NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBG01->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);


	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffBG01->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{
	// テクスチャの破棄
	if (g_pTextureBG01 != NULL)
	{
		g_pTextureBG01->Release();
		g_pTextureBG01 = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffBG01 != NULL)
	{
		g_pVtxBuffBG01->Release();
		g_pVtxBuffBG01 = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBG(void)
{
	g_PatternAnimBG01++; // パターンNO.を進める

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBG01->Lock(0, 0, (void**)&pVtx, 0);
	// テクスチャ座標の更新
	pVtx[0].tex.x = ANIMATIONPATTERN + 0.0f;
	pVtx[1].tex.x = ANIMATIONPATTERN + 0.25f;
	pVtx[2].tex.x = ANIMATIONPATTERN + 0.0f;
	pVtx[3].tex.x = ANIMATIONPATTERN + 0.25f;

	// 頂点バッファをアンロックする
	g_pVtxBuffBG01->Unlock();

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG01, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBG01);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		                   0,
		                   2);
}