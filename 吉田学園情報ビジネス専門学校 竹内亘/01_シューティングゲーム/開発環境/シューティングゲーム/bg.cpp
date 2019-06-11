//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "bg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_TEXTURENAME		"data/TEXTURE/bg100.png"		//テクスチャ名
#define BG_TEXTURENAME_1	"data/TEXTURE/bg101.png"		//テクスチャ名
#define BG_POS_X			(0)								//背景の左上X座標
#define BG_POS_Y			(0)								//背景の左上Y座標
#define BG_WIDTH			(SCREEN_WIDTH)					//背景の幅
#define BG_HEIGHT			(SCREEN_HEIGHT)					//背景の高さ
#define BG_MOVESPEED		(0.005f)						//背景の動く速さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;	//頂点バッファへのポインタ
int g_nCounterAnim;								//アニメーションカウンター
int g_nPartternAnim;							//アニメーションパターン更新

//=============================================================================
// 背景初期化処理
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureBG);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_1, &g_pTextureBG);

	//アニメーション
	g_nCounterAnim = 0;
	g_nPartternAnim = 0;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	// rhwの設定
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
// ポリゴン終了処理
//=============================================================================
void UninitBG(void)
{
	// テクスチャの破棄
	if (g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();
		g_pTextureBG = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=============================================================================
// ポリゴン更新処理
//=============================================================================
void UpdateBG(void)
{
	g_nCounterAnim++;
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの更新
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (g_nCounterAnim * BG_MOVESPEED));
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (g_nCounterAnim * BG_MOVESPEED));
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (g_nCounterAnim * BG_MOVESPEED));
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (g_nCounterAnim * BG_MOVESPEED));

	pVtx += 4;	//頂点データを４つ分進める

	// 頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
// ポリゴン描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBG);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}