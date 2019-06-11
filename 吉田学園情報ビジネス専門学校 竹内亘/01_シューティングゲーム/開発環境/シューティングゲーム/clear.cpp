//=============================================================================
//
// ゲームクリア処理 [clear.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "clear.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLEAR_TEXTURENAME	"data/TEXTURE/CLEAR.jpg"		//ゲームオーバーテクスチャ
#define CLEAR_POS_X			(0)								//背景の左上X座標
#define CLEAR_POS_Y			(0)								//背景の左上Y座標
#define CLEAR_WIDTH			(SCREEN_WIDTH)					//背景の幅
#define CLEAR_HEIGHT		(SCREEN_HEIGHT)					//背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureClear = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;	//頂点バッファへのポインタ

//=============================================================================
// ゲームクリア初期化処理
//=============================================================================
void InitClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, CLEAR_TEXTURENAME, &g_pTextureClear);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffClear,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(CLEAR_POS_X, CLEAR_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(CLEAR_WIDTH, CLEAR_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(CLEAR_POS_X, CLEAR_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CLEAR_WIDTH, CLEAR_HEIGHT, 0.0f);

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
	g_pVtxBuffClear->Unlock();

	PlaySound(SOUND_LABEL_SE_GAMECLEAR);
}

//=============================================================================
// ゲームクリア終了処理
//=============================================================================
void UninitClear(void)
{
	// テクスチャの破棄
	if (g_pTextureClear != NULL)
	{
		g_pTextureClear->Release();
		g_pTextureClear = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}
}

//=============================================================================
// ゲームクリア更新処理
//=============================================================================
void UpdateClear(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		FADE *pFade;
		pFade = GetFade();
		//PlaySound(SOUND_LABEL_SE_DECIDE);

		if (*pFade != FADE_OUT)
		{
			StopSound(SOUND_LABEL_SE_GAMECLEAR);
			SetFade(MODE_RANKING);
		}
	}
}

//=============================================================================
// ゲームクリア描画処理
//=============================================================================
void DrawClear(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureClear);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}