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
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEXTURE_NAME  "data/TEXTURE/title_bg100.jpg" // 読み込むテクスチャファイル名
#define TITLE_POS_X         (0)                         // 背景の左上Ｘ座標
#define TITLE_POS_Y         (0)                         // 背景の左上Ｙ座標
#define TITLE_WIDTH         (SCREEN_WIDTH)              // 背景の幅
#define TITLE_HEIGHT        (SCREEN_HEIGHT)             // 背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureTitle = NULL;   // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;   // 頂点バッファへのポインタ 
int                     g_nCounterTitle;          // ランキング画面に遷移するタイミング 

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_nCounterTitle = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TITLE_TEXTURE_NAME,
		&g_pTextureTitle);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);


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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
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
	FADE *pFade;
	pFade = GetFade();
	bool *disp;
	disp = GetDispPressEnter();

	g_nCounterTitle++;

	if(GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{// ENTERキーが押された
		SetFade(MODE_TUTORIAL);
		PlaySound(SOUND_LABEL_SE_DECIDE);  // 決定音を流す
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
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	// タイトル画面の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}