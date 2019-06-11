//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "ranking.h"
#include "rankingscore.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKING_TEXTURE_NAME  "data/TEXTURE/ranking001.jpg" // 読み込むテクスチャファイル名
#define RANKING_POS_X         (0)                           // ランキング画面の左上Ｘ座標
#define RANKING_POS_Y         (0)                           // ランキング画面の左上Ｙ座標
#define RANKING_WIDTH         (SCREEN_WIDTH)                // ランキング画面の幅
#define RANKING_HEIGHT        (SCREEN_HEIGHT)               // ランキング画面の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureRanking = NULL;   // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;   // 頂点バッファへのポインタ
int                     g_nCounterRanking;          // タイトル画面に遷移するタイミング

//=============================================================================
// 初期化処理
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_nCounterRanking = 0;  // カウンターを初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		RANKING_TEXTURE_NAME,
		&g_pTextureRanking);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);


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
	g_pVtxBuffRanking->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	// テクスチャの破棄
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{
	FADE fade;
	fade = GetFade();

	g_nCounterRanking++;

	if (GetKeyboardTrigger(DIK_RETURN) && fade == FADE_NONE || g_nCounterRanking % 300 == 0 && fade == FADE_NONE)
	{// ENTERキーが押されるか一定時間が経過する
		SetFade(MODE_TITLE);
		// ランキングスコアの取得
		RANKINGSCORE *rankingscore;
		rankingscore = GetRankingScore();

		for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++, rankingscore++)
		{// ランキングスコアの数だけ繰り返し
			if (rankingscore->state == RANKINGSCORESTATE_UPDATE)
			{// 更新状態になっていたら
				rankingscore->state = RANKINGSCORESTATE_NONE;
				rankingscore->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}