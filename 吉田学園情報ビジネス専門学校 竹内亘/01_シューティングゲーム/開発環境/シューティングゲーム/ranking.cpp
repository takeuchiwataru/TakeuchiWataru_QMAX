//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "ranking.h"
#include "score.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RANKING		"data/TEXTURE/number000.png"	//読み込むテクスチャファイル名
#define RANKING_SIZE (50.0f)								//ランキングサイズ
#define RANKING_WIDE (15)									//ランキングの幅
#define RANKING_POS (30)									//ランキングの場所
#define MAX_NUMBER (8)										//ランキングの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// 頂点バッファへのポインタ
D3DXVECTOR3				g_RankingPos(700, 350, 0.0f);	// ランキングの頂点座標
int						g_nRankScore;					// ランキング
int						g_TexturePosRanking;			// テクスチャX座標
	
//=============================================================================
// ランキング初期化処理
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nScore;
	nScore = GetScore();

	if (nScore > g_nRankScore)
	{
		g_nRankScore = nScore;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile	(pDevice,				// デバイスへのポインタ
								TEXTURE_RANKING,		// ファイルの名前
								&g_pTextureRanking);	// テクスチャへのポインタ

			
	// 頂点情報の作成
	MakeVertexRanking(pDevice);
}

//=============================================================================
// ランキング終了処理
//=============================================================================
void UninitRanking(void)
{
	// テクスチャの開放
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=============================================================================
// ランキング更新処理
//=============================================================================
void UpdateRanking(void)
{
	int nAnswer = 1;
	int nScore;
	int nCntScore;

	// 頂点情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		nScore = g_nRankScore % (nAnswer * 10) / nAnswer;

		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 1.0f);

		nAnswer *= 10;
		pVtx += 4;	//頂点データを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffRanking->Unlock();


	// フェードの取得
	FADE * Fade;
	Fade = GetFade();

	if (GetKeyboardTrigger(DIK_RETURN) == true && *Fade == FADE_NONE)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);

		// モードの設定
		SetFade(MODE_TITLE);
	}

}

//=============================================================================
// ランキング描画処理
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntScore;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

	// ポリゴンの描画
	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUMBER,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	int nCntScore;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x - RANKING_SIZE, g_RankingPos.y - RANKING_SIZE, g_RankingPos.z);
		pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + RANKING_SIZE, g_RankingPos.y - RANKING_SIZE, g_RankingPos.z);
		pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x - RANKING_SIZE, g_RankingPos.y + RANKING_SIZE, g_RankingPos.z);
		pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + RANKING_SIZE, g_RankingPos.y + RANKING_SIZE, g_RankingPos.z);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データを４つ分進める
		g_RankingPos.x -= 80;
	}
	g_RankingPos.x = 700;

	//頂点バッファをアンロック
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void SetRank(int nValue)
{
	int nAnswer = 1;
	int nScore;
	int nCntScore;

	g_nRankScore += nValue;

	// 頂点情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_NUMBER; nCntScore++)
	{
		nScore = g_nRankScore % (nAnswer * 10) / nAnswer;

		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nScore), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nScore), 1.0f);

		nAnswer *= 10;
		pVtx += 4;	//頂点データを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffRanking->Unlock();
}
