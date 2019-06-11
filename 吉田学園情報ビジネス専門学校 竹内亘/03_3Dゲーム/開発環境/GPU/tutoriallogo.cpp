//=============================================================================
//
//	チュートリアルロゴ処理 [tutoriallogo.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "tutoriallogo.h"
#include "pressenter.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME       "data/TEXTURE/tutorial.png"			// 読み込むテクスチャファイル名
#define TEXTURE_SIZEX      (200)							// テクスチャを張り付ける幅
#define TEXTURE_SIZEY      (100)							// テクスチャを張り付ける高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTutorialLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTutorialLogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialLogo = NULL;	// 頂点バッファへのポインタ
D3DXVECTOR3             g_PosTutorialLogo;             // チュートリアルロゴ座標
//D3DXVECTOR3             g_MoveTutorialLogo;            // チュートリアルロゴ移動量
D3DXCOLOR				g_colorTutorialLogo;		    // チュートリアルロゴ色

//=============================================================================
// 初期化処理
//=============================================================================
void InitTutorialLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_PosTutorialLogo = D3DXVECTOR3(200.0f, 60.0f, 0.0f);
	//g_MoveTutorialLogo = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	g_colorTutorialLogo = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// 頂点情報の設定
	MakeVertexTutorialLogo(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialLogo(void)
{
	// テクスチャの開放
	if (g_pTextureTutorialLogo != NULL)
	{
		g_pTextureTutorialLogo->Release();
		g_pTextureTutorialLogo = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTutorialLogo != NULL)
	{
		g_pVtxBuffTutorialLogo->Release();
		g_pVtxBuffTutorialLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialLogo(void)
{
	//if (g_PosTutorialLogo.y <= SCREEN_HEIGHT / 2)
	//{// 真ん中に来るまで
	//	if (GetKeyboardTrigger(DIK_RETURN))
	//	{// ENTERキーが押された
	//		g_PosTutorialLogo.y = SCREEN_HEIGHT / 2;
	//	}
	//	else
	//	{
	//		g_PosTutorialLogo += g_MoveTutorialLogo;
	//		bool *disp;
	//		disp = GetDispPressEnter();
	//		disp = false;
	//	}

	//	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	//	// 頂点バッファをロックし,頂点データへのポインタを取得
	//	g_pVtxBuffTutorialLogo->Lock(0, 0, (void**)&pVtx, 0);

	//	// 頂点座標
	//	pVtx[0].pos = D3DXVECTOR3(g_PosTutorialLogo.x - TEXTURE_SIZEX, g_PosTutorialLogo.y - TEXTURE_SIZEY, g_PosTutorialLogo.z);
	//	pVtx[1].pos = D3DXVECTOR3(g_PosTutorialLogo.x + TEXTURE_SIZEX, g_PosTutorialLogo.y - TEXTURE_SIZEY, g_PosTutorialLogo.z);
	//	pVtx[2].pos = D3DXVECTOR3(g_PosTutorialLogo.x - TEXTURE_SIZEX, g_PosTutorialLogo.y + TEXTURE_SIZEY, g_PosTutorialLogo.z);
	//	pVtx[3].pos = D3DXVECTOR3(g_PosTutorialLogo.x + TEXTURE_SIZEX, g_PosTutorialLogo.y + TEXTURE_SIZEY, g_PosTutorialLogo.z);

	//	// 頂点バッファをアンロックする
	//	g_pVtxBuffTutorialLogo->Unlock();
	//}
	//else
	//{
	//	SetPressEnter(D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0.0f),300,50);
	//}

}
//=============================================================================
// タイトル画面
//=============================================================================
void DrawTutorialLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorialLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTutorialLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureTutorialLogo);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialLogo,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffTutorialLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_PosTutorialLogo.x - TEXTURE_SIZEX, g_PosTutorialLogo.y - TEXTURE_SIZEY, g_PosTutorialLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosTutorialLogo.x + TEXTURE_SIZEX, g_PosTutorialLogo.y - TEXTURE_SIZEY, g_PosTutorialLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosTutorialLogo.x - TEXTURE_SIZEX, g_PosTutorialLogo.y + TEXTURE_SIZEY, g_PosTutorialLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosTutorialLogo.x + TEXTURE_SIZEX, g_PosTutorialLogo.y + TEXTURE_SIZEY, g_PosTutorialLogo.z);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_colorTutorialLogo;
	pVtx[1].col = g_colorTutorialLogo;
	pVtx[2].col = g_colorTutorialLogo;
	pVtx[3].col = g_colorTutorialLogo;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorialLogo->Unlock();
}