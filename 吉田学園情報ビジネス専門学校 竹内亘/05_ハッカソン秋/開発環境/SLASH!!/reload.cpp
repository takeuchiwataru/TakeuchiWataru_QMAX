//=============================================================================
//
// 切れ味処理 [reload.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "reload.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RELOAD		"data/TEXTURE/剣.png"	    // 読み込むテクスチャファイル名
#define TEXTURE_SIZE        (120)                            // テクスチャのサイズ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexReload(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureReload = NULL;  // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReload = NULL;  // 頂点バッファへのポインタ
Reload                  g_Reload[PLAYER_SHARP];   // 切れ味

//=============================================================================
// 初期化処理
//=============================================================================
void InitReload(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntReload = 0; nCntReload < PLAYER_SHARP; nCntReload++)
	{// 切れ味数だけ繰り返し
		g_Reload[nCntReload].pos = D3DXVECTOR3(900, 650, 0);  // 座標を初期化
		g_Reload[nCntReload].bUse = false;                  // 使用している状態にする
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	      // デバイスへのポインタ
		TEXTURE_RELOAD,		                  // ファイルの名前
		&g_pTextureReload);	                  // テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexReload(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitReload(void)
{
	// テクスチャの開放
	if (g_pTextureReload != NULL)
	{
		g_pTextureReload->Release();
		g_pTextureReload = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffReload != NULL)
	{
		g_pVtxBuffReload->Release();
		g_pVtxBuffReload = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateReload(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawReload(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffReload, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureReload);

	// ポリゴンの描画
	for (int nCntReload = 0; nCntReload < PLAYER_SHARP; nCntReload++)
	{// 表示する切れ味数だけ繰り返し
		if (g_Reload[nCntReload].bUse == true)
		{// 切れ味が使用されている
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntReload * 4,
				2);
		}
	}
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexReload(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PLAYER_SHARP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReload,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffReload->Lock(0, 0, (void**)&pVtx, 0);

	float pos = 0;
	// 頂点情報を設定
	for (int nCntReload = 0; nCntReload < PLAYER_SHARP; nCntReload++)
	{// 切れ味数だけ繰り返し
	 // 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_Reload[nCntReload].pos.x - TEXTURE_SIZE + pos, g_Reload[nCntReload].pos.y - TEXTURE_SIZE, g_Reload[nCntReload].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_Reload[nCntReload].pos.x + TEXTURE_SIZE + pos, g_Reload[nCntReload].pos.y - TEXTURE_SIZE, g_Reload[nCntReload].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_Reload[nCntReload].pos.x - TEXTURE_SIZE + pos, g_Reload[nCntReload].pos.y + TEXTURE_SIZE, g_Reload[nCntReload].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_Reload[nCntReload].pos.x + TEXTURE_SIZE + pos, g_Reload[nCntReload].pos.y + TEXTURE_SIZE, g_Reload[nCntReload].pos.z);


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

		pVtx += 4;
		pos += 30.0f;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffReload->Unlock();
}
//=============================================================================
// 切れ味の設定
//=============================================================================
void SetReload(int Reload)
{
	for (int nCntReload = 0; nCntReload < Reload; nCntReload++)
	{// 切れ味数だけ繰り返し
		if (g_Reload[nCntReload].bUse == false)
		{// 切れ味が使用されていない
			g_Reload[nCntReload].bUse = true;
		}
	}

}
//=============================================================================
// 切れ味の減少
//=============================================================================
void CutReload(int cut)
{
	for (int nCntReload = PLAYER_SHARP; nCntReload >= 0; nCntReload--)
	{// 切れ味数だけ繰り返し
		if (g_Reload[nCntReload].bUse == true)
		{// 切れ味が使用されている
			g_Reload[nCntReload].bUse = false;
			break;
		}
	}
}
//=============================================================================
// 切れ味の増加
//=============================================================================
void AddReload(void)
{
	for (int nCntReload = 0; nCntReload < PLAYER_SHARP; nCntReload++)
	{// 切れ味の数だけ繰り返し
		if (g_Reload[nCntReload].bUse == false)
		{// 切れ味が使用されていない
			g_Reload[nCntReload].bUse = true;
		}
	}
}