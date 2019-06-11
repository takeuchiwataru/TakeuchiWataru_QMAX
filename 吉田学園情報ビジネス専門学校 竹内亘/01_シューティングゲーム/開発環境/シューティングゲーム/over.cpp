//=============================================================================
//
// ゲームオーバー処理 [over.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "over.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OVER_TEXTURENAME	"data/TEXTURE/OVER.jpg"		//ゲームオーバーテクスチャ
#define OVER_POS_X			(0)								//背景の左上X座標
#define OVER_POS_Y			(0)								//背景の左上Y座標
#define OVER_WIDTH			(SCREEN_WIDTH)					//背景の幅
#define OVER_HEIGHT		(SCREEN_HEIGHT)					//背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureOver = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOver = NULL;	//頂点バッファへのポインタ

//=============================================================================
// ゲームオーバー初期化処理
//=============================================================================
void InitOver(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, OVER_TEXTURENAME, &g_pTextureOver);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffOver,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffOver->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(OVER_POS_X, OVER_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(OVER_WIDTH, OVER_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(OVER_POS_X, OVER_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(OVER_WIDTH, OVER_HEIGHT, 0.0f);

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
	g_pVtxBuffOver->Unlock();

	PlaySound(SOUND_LABEL_SE_GAMEOVER);
}

//=============================================================================
// ゲームオーバー終了処理
//=============================================================================
void UninitOver(void)
{
	// テクスチャの破棄
	if (g_pTextureOver != NULL)
	{
		g_pTextureOver->Release();
		g_pTextureOver = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffOver != NULL)
	{
		g_pVtxBuffOver->Release();
		g_pVtxBuffOver = NULL;
	}
}

//=============================================================================
// ゲームオーバー更新処理
//=============================================================================
void UpdateOver(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		FADE *pFade;
		pFade = GetFade();

		if (*pFade != FADE_OUT)
		{
			StopSound(SOUND_LABEL_SE_GAMEOVER);
			SetFade(MODE_RANKING);
		}
	}
}

//=============================================================================
// ゲームオーバー描画処理
//=============================================================================
void DrawOver(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffOver, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureOver);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}