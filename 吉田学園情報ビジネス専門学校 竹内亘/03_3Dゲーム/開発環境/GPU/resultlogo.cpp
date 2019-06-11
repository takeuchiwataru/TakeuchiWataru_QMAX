//=============================================================================
//
// リザルトロゴ処理(ゲームクリア画面) [resultlogo.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "resultlogo.h"
#include "result.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME1       "data/TEXTURE/game_clear.png"		// 読み込むテクスチャファイル名
#define TEXTURE_SIZEX       (500)								// テクスチャを張り付ける幅
#define TEXTURE_SIZEY       (175)								// テクスチャを張り付ける高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexResultLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureResultLogo = NULL; // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultLogo = NULL; // 頂点バッファへのポインタ
D3DXVECTOR3             g_PosResultLogo;             // リザルトロゴ座標
D3DXCOLOR				g_colorResultLogo;		     // リザルトロゴ色
int                     g_nCounterResultLogo;         // タイトル画面に遷移するタイミング 


//=============================================================================
// 初期化処理
//=============================================================================
void InitResultLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_PosResultLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_colorResultLogo = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点情報の設定
	MakeVertexResultLogo(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultLogo(void)
{
		// テクスチャの破棄
	if (g_pTextureResultLogo != NULL)
	{
		g_pTextureResultLogo->Release();
		g_pTextureResultLogo = NULL;
	}
	

	// 頂点バッファの開放
	if (g_pVtxBuffResultLogo != NULL)
	{
		g_pVtxBuffResultLogo->Release();
		g_pVtxBuffResultLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultLogo(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_nCounterResultLogo++;

	if (g_nCounterResultLogo % 600 == 0 && *pFade == FADE_NONE)
	{// 一定時間がたつ
		SetFade(MODE_RANKING);
	}
}
//=============================================================================
// タイトル画面
//=============================================================================
void DrawResultLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffResultLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexResultLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME1,
		&g_pTextureResultLogo);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultLogo,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffResultLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_PosResultLogo.x - TEXTURE_SIZEX, g_PosResultLogo.y - TEXTURE_SIZEY, g_PosResultLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosResultLogo.x + TEXTURE_SIZEX, g_PosResultLogo.y - TEXTURE_SIZEY, g_PosResultLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosResultLogo.x - TEXTURE_SIZEX, g_PosResultLogo.y + TEXTURE_SIZEY, g_PosResultLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosResultLogo.x + TEXTURE_SIZEX, g_PosResultLogo.y + TEXTURE_SIZEY, g_PosResultLogo.z);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_colorResultLogo;
	pVtx[1].col = g_colorResultLogo;
	pVtx[2].col = g_colorResultLogo;
	pVtx[3].col = g_colorResultLogo;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファをアンロックする
	g_pVtxBuffResultLogo->Unlock();
}