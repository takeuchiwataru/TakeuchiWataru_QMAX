//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define TEXTURE_SIZE        (30)                            // テクスチャのサイズ
#define MAX_SCORENUMBER     (8)                             // スコアの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
D3DXVECTOR3             g_ScorePos;                 // 頂点座標
int                     g_TexturePos;               // テクスチャX座標
int						g_nScore;					// スコア

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nScore = 0;                             // スコアの初期化
	g_ScorePos = D3DXVECTOR3(1230, 30, 0.0f); // 座標の初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	// ポリゴンの描画
	for (int nCntScore = 0; nCntScore < MAX_SCORENUMBER; nCntScore++)
	{// 表示するスコアの桁数だけ繰り返し
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntScore * 4,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORENUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	for (int nCntScore = 0; nCntScore < MAX_SCORENUMBER; nCntScore++)
	{// スコアの桁数だけ繰り返し
		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_ScorePos.x - TEXTURE_SIZE, g_ScorePos.y - TEXTURE_SIZE, g_ScorePos.z);
		pVtx[1].pos = D3DXVECTOR3(g_ScorePos.x + TEXTURE_SIZE, g_ScorePos.y - TEXTURE_SIZE, g_ScorePos.z);
		pVtx[2].pos = D3DXVECTOR3(g_ScorePos.x - TEXTURE_SIZE, g_ScorePos.y + TEXTURE_SIZE, g_ScorePos.z);
		pVtx[3].pos = D3DXVECTOR3(g_ScorePos.x + TEXTURE_SIZE, g_ScorePos.y + TEXTURE_SIZE, g_ScorePos.z);


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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
		g_ScorePos.x -= 50;
	}
	g_ScorePos.x = 1000;
	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	int Score = 1;
	// 頂点バッファを生成
	VERTEX_2D *pVtx;
	g_nScore += nValue;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntScore = 0; nCntScore < MAX_SCORENUMBER; nCntScore++)
	{// スコアの桁数だけ繰り返し
		g_TexturePos = g_nScore % (Score * 10) / Score;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TexturePos), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TexturePos), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TexturePos), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TexturePos), 1.0f);

		pVtx += 4;
		Score *= 10;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// スコアの取得
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}