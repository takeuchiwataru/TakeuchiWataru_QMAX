//=============================================================================
//
// 残機処理 [remain.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "remain.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIMER		"data/TEXTURE/Player000.png"    // 読み込むテクスチャファイル名
#define TEXTURE_SIZE        (70)                            // テクスチャのサイズ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRemain(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRemain = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRemain = NULL;	// 頂点バッファへのポインタ
REMAIN                  g_remain[MAX_REMAINNUMBER]; // 残機
int                     g_nCounterRemain;           // 現在の残機数

//=============================================================================
// 初期化処理
//=============================================================================
void InitRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntRemain = 0; nCntRemain < MAX_REMAINNUMBER; nCntRemain++)
	{// ライフアイコン数だけ繰り返し
		g_remain[nCntRemain].pos = D3DXVECTOR3(30, 640, 0);  // 座標を初期化
		g_remain[nCntRemain].bUse = false;                  // 使用している状態にする
	}
	g_nCounterRemain = MAX_REMAINNUMBER - 7;                // 現在の残機数を初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	      // デバイスへのポインタ
		TEXTURE_TIMER,		                  // ファイルの名前
		&g_pTextureRemain);	                  // テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexRemain(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRemain(void)
{
	// テクスチャの開放
	if (g_pTextureRemain != NULL)
	{
		g_pTextureRemain->Release();
		g_pTextureRemain = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffRemain != NULL)
	{
		g_pVtxBuffRemain->Release();
		g_pVtxBuffRemain = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRemain(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRemain, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRemain);

	// ポリゴンの描画
	for (int nCntRemain = 0; nCntRemain < MAX_REMAINNUMBER; nCntRemain++)
	{// 表示するライフアイコン数だけ繰り返し
		if (g_remain[nCntRemain].bUse == true)
		{// ライフが使用されている
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntRemain * 4,
				2);
		}
	}
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRemain(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_REMAINNUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRemain,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffRemain->Lock(0, 0, (void**)&pVtx, 0);

	float pos = 0;
	// 頂点情報を設定
	for (int nCntRemain = 0; nCntRemain < MAX_REMAINNUMBER; nCntRemain++)
	{// ライフアイコン数だけ繰り返し
	 // 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_remain[nCntRemain].pos.x - TEXTURE_SIZE + pos, g_remain[nCntRemain].pos.y - TEXTURE_SIZE, g_remain[nCntRemain].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_remain[nCntRemain].pos.x + TEXTURE_SIZE + pos, g_remain[nCntRemain].pos.y - TEXTURE_SIZE, g_remain[nCntRemain].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_remain[nCntRemain].pos.x - TEXTURE_SIZE + pos, g_remain[nCntRemain].pos.y + TEXTURE_SIZE, g_remain[nCntRemain].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_remain[nCntRemain].pos.x + TEXTURE_SIZE + pos, g_remain[nCntRemain].pos.y + TEXTURE_SIZE, g_remain[nCntRemain].pos.z);


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
		pos += 60.0f;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRemain->Unlock();
}
//=============================================================================
// 残機の設定
//=============================================================================
void SetRemain(int remain)
{
	g_nCounterRemain = remain;  // 残機数を設定

	for (int nCntRemain = 0; nCntRemain < remain - 1; nCntRemain++)
	{// ライフアイコン数だけ繰り返し
		if (g_remain[nCntRemain].bUse == false)
		{// ライフが使用されている
			g_remain[nCntRemain].bUse = true;
		}
	}
}
//=============================================================================
// 残機の増加
//=============================================================================
void AddRemain(void)
{
	for (int nCntRemain = 0; nCntRemain < MAX_REMAINNUMBER; nCntRemain++)
	{// ライフアイコン数だけ繰り返し
		if (g_remain[nCntRemain].bUse == false)
		{// ライフが使用されている
			g_remain[nCntRemain].bUse = true;
			g_nCounterRemain++;
			break;
		}
	}
}
//=============================================================================
// 残機の減少
//=============================================================================
void CutRemain(void)
{
	for (int nCntRemain = MAX_REMAINNUMBER; nCntRemain >= 0; nCntRemain--)
	{// ライフアイコン数だけ繰り返し
		if (g_remain[nCntRemain].bUse == true)
		{// ライフが使用されている
			g_remain[nCntRemain].bUse = false;
			g_nCounterRemain--;
			break;
		}
	}
}