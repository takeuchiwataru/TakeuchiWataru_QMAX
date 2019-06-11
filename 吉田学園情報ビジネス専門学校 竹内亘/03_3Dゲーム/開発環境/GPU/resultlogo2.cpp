//=============================================================================
//
// リザルトロゴ処理(ゲームオーバー画面)[resultlogo2.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "resultlogo2.h"
#include "result2.h"
#include "fade.h"

//#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME2       "data/TEXTURE/game_over.png"  // 読み込むテクスチャファイル名 
#define TEXTURE_SIZEX       (500)                             // テクスチャを張り付ける幅
#define TEXTURE_SIZEY       (175)                             // テクスチャを張り付ける高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexResultLogo2(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureResultLogo2 = NULL; // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultLogo2 = NULL; // 頂点バッファへのポインタ
D3DXVECTOR3             g_PosResultLogo2;             // リザルトロゴ座標
D3DXCOLOR				g_colorResultLogo2;		     // リザルトロゴ色
int                     g_nCounterResultLogo2;         // タイトル画面に遷移するタイミング 

//=============================================================================
// 初期化処理
//=============================================================================
void InitResultLogo2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_PosResultLogo2 = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_colorResultLogo2 = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点情報の設定
	MakeVertexResultLogo2(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultLogo2(void)
{
	// テクスチャの破棄
	if (g_pTextureResultLogo2 != NULL)
	{
		g_pTextureResultLogo2->Release();
		g_pTextureResultLogo2 = NULL;
	}
	
	// 頂点バッファの開放
	if (g_pVtxBuffResultLogo2 != NULL)
	{
		g_pVtxBuffResultLogo2->Release();
		g_pVtxBuffResultLogo2 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultLogo2(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_nCounterResultLogo2++;

	if (g_nCounterResultLogo2 % 600 == 0 && *pFade == FADE_NONE)
	{// 一定時間がたつ
		SetFade(MODE_RANKING);
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawResultLogo2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffResultLogo2, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultLogo2);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexResultLogo2(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME2,
		&g_pTextureResultLogo2);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultLogo2,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffResultLogo2->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_PosResultLogo2.x - TEXTURE_SIZEX, g_PosResultLogo2.y - TEXTURE_SIZEY, g_PosResultLogo2.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosResultLogo2.x + TEXTURE_SIZEX, g_PosResultLogo2.y - TEXTURE_SIZEY, g_PosResultLogo2.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosResultLogo2.x - TEXTURE_SIZEX, g_PosResultLogo2.y + TEXTURE_SIZEY, g_PosResultLogo2.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosResultLogo2.x + TEXTURE_SIZEX, g_PosResultLogo2.y + TEXTURE_SIZEY, g_PosResultLogo2.z);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_colorResultLogo2;
	pVtx[1].col = g_colorResultLogo2;
	pVtx[2].col = g_colorResultLogo2;
	pVtx[3].col = g_colorResultLogo2;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファをアンロックする
	g_pVtxBuffResultLogo2->Unlock();
}