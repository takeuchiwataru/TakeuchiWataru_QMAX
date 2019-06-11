//=============================================================================
//
// ライフアイコン処理 [life.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/Life000.png"	    // 読み込むテクスチャファイル名
#define TEXTURE_SIZE        (30)                            // テクスチャのサイズ
#define MAX_LIFE            (8)                             // 体力の最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;	// 頂点バッファへのポインタ
LIFE                    g_life[MAX_LIFE];       // ライフ
int                     g_nCounterLife;         // 現在のライフ数

//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{// ライフアイコン数だけ繰り返し
		g_life[nCntLife].pos = D3DXVECTOR3(30, 500, 0);  // 座標を初期化
		g_life[nCntLife].bUse = false;                  // 使用している状態にする
	}
	g_nCounterLife = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	      // デバイスへのポインタ
		TEXTURE_LIFE,		                  // ファイルの名前
		&g_pTextureLife);	                  // テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexLife(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	// テクスチャの開放
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	// ポリゴンの描画
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{// 表示するライフアイコン数だけ繰り返し
		if (g_life[nCntLife].bUse == true)
		{// ライフが使用されている
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntLife * 4,
				2);
		}
	}
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	float pos = 0;
	// 頂点情報を設定
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{// ライフアイコン数だけ繰り返し
		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_life[nCntLife].pos.x - TEXTURE_SIZE + pos, g_life[nCntLife].pos.y - TEXTURE_SIZE, g_life[nCntLife].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_life[nCntLife].pos.x + TEXTURE_SIZE + pos, g_life[nCntLife].pos.y - TEXTURE_SIZE, g_life[nCntLife].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_life[nCntLife].pos.x - TEXTURE_SIZE + pos, g_life[nCntLife].pos.y + TEXTURE_SIZE, g_life[nCntLife].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_life[nCntLife].pos.x + TEXTURE_SIZE + pos, g_life[nCntLife].pos.y + TEXTURE_SIZE, g_life[nCntLife].pos.z);


		// 頂点テクスチャ
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		pos += 80.0f;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}
//=============================================================================
// ライフの設定
//=============================================================================
void SetLife(int life)
{
	g_nCounterLife = life;  // ライフを設定

	Player *pPlayer;
	pPlayer = GetPlayer();
	for (int nCntLife = 0; nCntLife < life; nCntLife++)
	{// ライフアイコン数だけ繰り返し
		if (g_life[nCntLife].bUse == false)
		{// ライフが使用されていない
			g_life[nCntLife].bUse = true;
		}
	}
	
}
//=============================================================================
// ライフの減少
//=============================================================================
void CutLife(int cut)
{
	g_nCounterLife -= cut;

	for (int nCntLife = MAX_LIFE; nCntLife >= 0; nCntLife--)
	{// ライフアイコン数だけ繰り返し
		if (g_life[nCntLife].bUse == true)
		{// ライフが使用されている
			g_life[nCntLife].bUse = false;
			break;
		}
	}
}
//=============================================================================
// ライフの増加
//=============================================================================
void AddLife(int nValue)
{
	g_nCounterLife += nValue;

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{// ライフアイコン数だけ繰り返し
		if (g_life[nCntLife].bUse == false)
		{// ライフが使用されていない
			g_life[nCntLife].bUse = true;
			break;
		}
	}
}