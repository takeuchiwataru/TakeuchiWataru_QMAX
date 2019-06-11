//=============================================================================
//
// タイトルロゴ処理 [titlelogo.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "titlelogo.h"
#include "pressenter.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME       "data/TEXTURE/title100.png"			// 読み込むテクスチャファイル名
#define TEXTURE_SIZEX      (400)							// テクスチャを張り付ける幅
#define TEXTURE_SIZEY      (250)							// テクスチャを張り付ける高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTitleLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTitleLogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;	// 頂点バッファへのポインタ
D3DXVECTOR3             g_PosTitleLogo;             // タイトルロゴ座標
D3DXVECTOR3             g_MoveTitleLogo;            // タイトルロゴ移動量
D3DXCOLOR				g_colorTitleLogo;		    // タイトルロゴ色

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_PosTitleLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, -200, 0.0f);
	g_MoveTitleLogo = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	g_colorTitleLogo = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点情報の設定
	MakeVertexTitleLogo(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleLogo(void)
{
	// テクスチャの開放
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();
		g_pTextureTitleLogo = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();
		g_pVtxBuffTitleLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleLogo(void)
{
	if (g_PosTitleLogo.y <= SCREEN_HEIGHT / 2)
	{// 真ん中に来るまで
		if (GetKeyboardTrigger(DIK_RETURN))
		{// ENTERキーが押された
			g_PosTitleLogo.y = SCREEN_HEIGHT / 2;
		}
		else
		{
			g_PosTitleLogo += g_MoveTitleLogo;
			bool *disp;
			disp = GetDispPressEnter();
			disp = false;
		}

		VERTEX_2D *pVtx;   // 頂点情報へのポインタ

		// 頂点バッファをロックし,頂点データへのポインタを取得
		g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_PosTitleLogo.x - TEXTURE_SIZEX, g_PosTitleLogo.y - TEXTURE_SIZEY, g_PosTitleLogo.z);
		pVtx[1].pos = D3DXVECTOR3(g_PosTitleLogo.x + TEXTURE_SIZEX, g_PosTitleLogo.y - TEXTURE_SIZEY, g_PosTitleLogo.z);
		pVtx[2].pos = D3DXVECTOR3(g_PosTitleLogo.x - TEXTURE_SIZEX, g_PosTitleLogo.y + TEXTURE_SIZEY, g_PosTitleLogo.z);
		pVtx[3].pos = D3DXVECTOR3(g_PosTitleLogo.x + TEXTURE_SIZEX, g_PosTitleLogo.y + TEXTURE_SIZEY, g_PosTitleLogo.z);

		// 頂点バッファをアンロックする
		g_pVtxBuffTitleLogo->Unlock();
	}
	else
	{
		SetPressEnter(D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0.0f),200,70);
	}

}
//=============================================================================
// タイトル画面
//=============================================================================
void DrawTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTitleLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureTitleLogo);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleLogo,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_PosTitleLogo.x - TEXTURE_SIZEX, g_PosTitleLogo.y - TEXTURE_SIZEY, g_PosTitleLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosTitleLogo.x + TEXTURE_SIZEX, g_PosTitleLogo.y - TEXTURE_SIZEY, g_PosTitleLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosTitleLogo.x - TEXTURE_SIZEX, g_PosTitleLogo.y + TEXTURE_SIZEY, g_PosTitleLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosTitleLogo.x + TEXTURE_SIZEX, g_PosTitleLogo.y + TEXTURE_SIZEY, g_PosTitleLogo.z);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_colorTitleLogo;
	pVtx[1].col = g_colorTitleLogo;
	pVtx[2].col = g_colorTitleLogo;
	pVtx[3].col = g_colorTitleLogo;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファをアンロックする
	g_pVtxBuffTitleLogo->Unlock();
}