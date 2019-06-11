//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	//読み込むテクスチャファイル名
#define SCORE_SIZE (15.0f)									//スコアサイズ
#define SCORE_WIDE (25)										//スコアの幅
#define SCORE_POS (30)										//スコアの場所
#define MAX_NUMBER (8)										//スコアの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
D3DXVECTOR3				g_ScorePos(1200, 50, 0.0f);	// スコアの頂点座標
int						g_nScore;					// スコア
int						g_TexturePos;				// テクスチャX座標

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nScore = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile	(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,			// ファイルの名前
								&g_pTextureScore);		// テクスチャへのポインタ
		
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

	// 頂点バッファの開放
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

	int nCntScore;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	// ポリゴンの描画
	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUMBER,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	int nCntScore;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{

		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(g_ScorePos.x - SCORE_SIZE, g_ScorePos.y - SCORE_SIZE, g_ScorePos.z);
		pVtx[1].pos = D3DXVECTOR3(g_ScorePos.x + SCORE_SIZE, g_ScorePos.y - SCORE_SIZE, g_ScorePos.z);
		pVtx[2].pos = D3DXVECTOR3(g_ScorePos.x - SCORE_SIZE, g_ScorePos.y + SCORE_SIZE, g_ScorePos.z);
		pVtx[3].pos = D3DXVECTOR3(g_ScorePos.x + SCORE_SIZE, g_ScorePos.y + SCORE_SIZE, g_ScorePos.z);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データを４つ分進める
		g_ScorePos.x -= 30;
	}
	g_ScorePos.x = 1200;

	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	int nAnswer = 1;
	int nScore;
	int nCntScore;

	g_nScore += nValue;

	// 頂点情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		nScore = g_nScore % (nAnswer * 10) / nAnswer;

		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 1.0f);

		nAnswer *= 10;
		pVtx += 4;	//頂点データを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// スコアの取得
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}
