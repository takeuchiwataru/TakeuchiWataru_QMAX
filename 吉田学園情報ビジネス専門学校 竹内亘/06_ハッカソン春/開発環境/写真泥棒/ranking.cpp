//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "ranking.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "input.h"

#include "field.h"
#include "model.h"
#include "sky.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//---------------
//   ロゴ用
//---------------
#define RANKINGLOGO_TEXTURE_NAME      "data/TEXTURE/ranking.png"  // 読み込むテクスチャファイル名
#define RANKINGLOGO_TEXTURE_SIZEX     (260)                            // テクスチャを張り付ける幅
#define RANKINGLOGO_TEXTURE_SIZEY     (70)                             // テクスチャを張り付ける高さ

//---------------
//   順位用
//---------------
#define RANNKINGRANK_TEXTURE_NAME     "data/TEXTURE/ranking_rank.png"  // 読み込むテクスチャファイル名
#define RANNKINGRANK_POS_X           (200)                             // ランキングランクの左上Ｘ座標
#define RANNKINGRANK_POS_Y           (150)                             // ランキングランク左上Ｙ座標
#define RANNKINGRANK_WIDTH           (450)                             // ランキングランクの幅
#define RANNKINGRANK_HEIGHT          (640)                             // ランキングランクの高さ

//---------------
//  スコア用
//---------------
#define	RANKINGSCORE_TEXTURE_SCORE    "data/TEXTURE/number000.png"       // 読み込むテクスチャファイル名
#define RANKINGSCORE_TEXTURE_SIZE     (40)                               // テクスチャのサイズ
#define MAX_RANKINGSCORENUMBER        (3)                                // ランキングスコアの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRankingLogo(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexRankingRank(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int        g_nCounterRanking;                // タイトル画面に遷移するタイミング
RANKINGOLD g_RankingOld = RANKINGOLD_TITLE;  // どの画面から遷移してきたか

//------------
//  ロゴ用
//------------
LPDIRECT3DTEXTURE9		g_pTextureRankingLogo = NULL; // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingLogo = NULL; // 頂点バッファへのポインタ
D3DXVECTOR3             g_PosRankingLogo;             // ランキングロゴ座標
D3DXCOLOR				g_colorRankingLogo;		      // ランキングロゴ色

//------------
//  順位用
//------------
LPDIRECT3DTEXTURE9		g_pTextureRankingRank = NULL; // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingRank = NULL; // 頂点バッファへのポインタ
D3DXCOLOR				g_colorRankingRank;		      // ランキングランク色

//---------------
//  スコア用
//---------------
LPDIRECT3DTEXTURE9		g_pTextureRankingScore = NULL;     // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;	   // 頂点バッファへのポインタ
D3DXVECTOR3             g_RankingScorePos;                 // 頂点座標
int                     g_TextureRankingScorePos;          // テクスチャX座標
RANKINGSCORE            g_aRankingScore[MAX_RANKINGSCORE]; // ランキングスコア

//=============================================================================
// 初期化処理
//=============================================================================
void InitRanking(void)
{
	// 順位初期化処理
	InitRankingRank();

	// ロゴ初期化処理
	InitRankingLogo();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// フィールドの初期化処理
	InitField();

	// モデルの初期化処理
	InitModel();

	// 空の初期化処理
	InitSky();

	g_nCounterRanking = 0;            // カウンターを0に
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	// 順位終了処理
	UninitRankingRank();

	// ロゴ終了処理
	UninitRankingLogo();

	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// フィールドの終了処理
	UninitField();

	// モデルの終了処理
	UninitModel();

	// 空の終了処理
	UninitSky();
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{
	// 順位の更新処理
	UpdateRankingRank();

	// ロゴの更新処理
	UpdateRankingLogo();

	// スコアの更新処理
	UpdateRankingScore();

	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	// フィールドの更新処理
	UpdateField();

	// モデルの更新処理
	UpdateModel();

	// 空の更新処理
	UpdateSky();

	g_nCounterRanking++;
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE ||
		GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE && GetFade() == FADE_NONE ||
		g_nCounterRanking % 340 == 0 && GetFade() == FADE_NONE)
	{// 決定ボタンが押されたか一定時間が経過する
		// ランキングスコアの取得
		RANKINGSCORE *rankingscore;
		rankingscore = GetRankingScore();

		for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++, rankingscore++)
		{// ランキングスコアの数だけ繰り返し
			if (rankingscore->state == RANKINGSCORESTATE_UPDATE)
			{// 更新状態になっていたら
				rankingscore->state = RANKINGSCORESTATE_NONE;
				rankingscore->col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
		}
		SetFade(MODE_TITLE);   // タイトル画面へ
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	// カメラの設定処理
	SetCamera();

	// フィールドの描画処理
	DrawField();

	// モデルの描画処理
	DrawModel();

	// 空の描画処理
	DrawSky();

	// 順位描画処理
	DrawRankingRank();

	// ロゴ描画処理
	DrawRankingLogo();

	// スコア描画処理
	DrawRankingScore();
}
//=============================================================================
// どの画面から遷移してきたかを設定
//=============================================================================
void SetRankingOld(RANKINGOLD rankold)
{
	g_RankingOld = rankold;    
}

//=============================================================================
// ランキングロゴの初期化処理
//=============================================================================
void InitRankingLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_PosRankingLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, 80, 0.0f);
	g_colorRankingLogo = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点情報の設定
	MakeVertexRankingLogo(pDevice);
}

//=============================================================================
// ランキングロゴの終了処理
//=============================================================================
void UninitRankingLogo(void)
{
	// テクスチャの破棄
	if (g_pTextureRankingLogo != NULL)
	{
		g_pTextureRankingLogo->Release();
		g_pTextureRankingLogo = NULL;
	}


	// 頂点バッファの開放
	if (g_pVtxBuffRankingLogo != NULL)
	{
		g_pVtxBuffRankingLogo->Release();
		g_pVtxBuffRankingLogo = NULL;
	}
}

//=============================================================================
// ランキングロゴの更新処理
//=============================================================================
void UpdateRankingLogo(void)
{
}
//=============================================================================
// ランキングロゴの描画処理
//=============================================================================
void DrawRankingLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffRankingLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ランキングロゴの頂点情報の作成
//=============================================================================
void MakeVertexRankingLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		RANKINGLOGO_TEXTURE_NAME,
		&g_pTextureRankingLogo);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingLogo,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffRankingLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_PosRankingLogo.x - RANKINGLOGO_TEXTURE_SIZEX, g_PosRankingLogo.y - RANKINGLOGO_TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosRankingLogo.x + RANKINGLOGO_TEXTURE_SIZEX, g_PosRankingLogo.y - RANKINGLOGO_TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosRankingLogo.x - RANKINGLOGO_TEXTURE_SIZEX, g_PosRankingLogo.y + RANKINGLOGO_TEXTURE_SIZEY, g_PosRankingLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosRankingLogo.x + RANKINGLOGO_TEXTURE_SIZEX, g_PosRankingLogo.y + RANKINGLOGO_TEXTURE_SIZEY, g_PosRankingLogo.z);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_colorRankingLogo;
	pVtx[1].col = g_colorRankingLogo;
	pVtx[2].col = g_colorRankingLogo;
	pVtx[3].col = g_colorRankingLogo;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファをアンロックする
	g_pVtxBuffRankingLogo->Unlock();
}

//=============================================================================
// 順位の初期化処理
//=============================================================================
void InitRankingRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_colorRankingRank = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点情報の設定
	MakeVertexRankingRank(pDevice);
}

//=============================================================================
// 順位の終了処理
//=============================================================================
void UninitRankingRank(void)
{
	// テクスチャの開放
	if (g_pTextureRankingRank != NULL)
	{
		g_pTextureRankingRank->Release();
		g_pTextureRankingRank = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRankingRank != NULL)
	{
		g_pVtxBuffRankingRank->Release();
		g_pVtxBuffRankingRank = NULL;
	}
}

//=============================================================================
// 順位の更新処理
//=============================================================================
void UpdateRankingRank(void)
{
}
//=============================================================================
// 順位の描画処理
//=============================================================================
void DrawRankingRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffRankingRank, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingRank);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 順位の頂点情報の作成
//=============================================================================
void MakeVertexRankingRank(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		RANNKINGRANK_TEXTURE_NAME,
		&g_pTextureRankingRank);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingRank,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffRankingRank->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(RANNKINGRANK_POS_X, RANNKINGRANK_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RANNKINGRANK_WIDTH, RANNKINGRANK_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RANNKINGRANK_POS_X, RANNKINGRANK_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RANNKINGRANK_WIDTH, RANNKINGRANK_HEIGHT, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_colorRankingRank;
	pVtx[1].col = g_colorRankingRank;
	pVtx[2].col = g_colorRankingRank;
	pVtx[3].col = g_colorRankingRank;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファをアンロックする
	g_pVtxBuffRankingRank->Unlock();
}

//=============================================================================
// ランキングスコアの初期化処理
//=============================================================================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nRankingScore = 30;
	g_RankingScorePos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 165, 0.0f);  // 座標の初期化
	g_aRankingScore[0].col = D3DXCOLOR(1.0f, 0.9f, 0.0f, 1.0f);
	g_aRankingScore[1].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	g_aRankingScore[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
	g_aRankingScore[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_aRankingScore[4].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++)
	{// ランキングスコアの数だけ繰り返し
		g_aRankingScore[nCntRankingScore].pos = g_RankingScorePos;                 // ランキングスコア座標を初期化
		g_aRankingScore[nCntRankingScore].colStd = g_aRankingScore[nCntRankingScore].col; // ランキングスコアの通常の色を初期化
		g_aRankingScore[nCntRankingScore].score = nRankingScore;                   // ランキングスコアを初期化
		g_aRankingScore[nCntRankingScore].nCounterCol = 0;                         // カウンターは初期化
		g_aRankingScore[nCntRankingScore].state = RANKINGSCORESTATE_NONE;          // 更新されていない状態に
		nRankingScore -= 5;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		RANKINGSCORE_TEXTURE_SCORE,		    // ファイルの名前
		&g_pTextureRankingScore);	        // テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexRankingScore(pDevice);
}
//=============================================================================
// ランキングスコアの終了処理
//=============================================================================
void UninitRankingScore(void)
{
	// テクスチャの開放
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}
}

//=============================================================================
// ランキングスコアの更新処理
//=============================================================================
void UpdateRankingScore(void)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++)
	{// ランキングスコアの数だけ繰り返し
		if (g_aRankingScore[nCntRankingScore].state == RANKINGSCORESTATE_UPDATE)
		{// 更新された状態だったら
			g_aRankingScore[nCntRankingScore].nCounterCol++;
			if (g_aRankingScore[nCntRankingScore].nCounterCol % 2 == 0)
			{// 一定時間がたったら
				if (g_aRankingScore[nCntRankingScore].col.b == 0.0f)
				{// 赤だったら
					g_aRankingScore[nCntRankingScore].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{// 白だったら
					g_aRankingScore[nCntRankingScore].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
		}
		else
		{// 通常の状態なら
			g_aRankingScore[nCntRankingScore].col = g_aRankingScore[nCntRankingScore].colStd;
		}
		for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORENUMBER; nCntRankingScore1++)
		{// スコアの桁数だけ繰り返し
		 // 頂点カラー
			pVtx[0].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[1].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[2].col = g_aRankingScore[nCntRankingScore].col;
			pVtx[3].col = g_aRankingScore[nCntRankingScore].col;
			pVtx += 4;
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRankingScore->Unlock();
}
//=============================================================================
// ランキングスコアの描画処理
//=============================================================================
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingScore);

	// ポリゴンの描画
	for (int nCntRankingScore2 = 0; nCntRankingScore2 < MAX_RANKINGSCORENUMBER * MAX_RANKINGSCORE; nCntRankingScore2++)
	{// 表示するランキングスコアの桁数だけ繰り返し
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			(nCntRankingScore2 * 4),
			2);
	}
}
//=============================================================================
// ランキングスコアの頂点情報の作成
//=============================================================================
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKINGSCORENUMBER * MAX_RANKINGSCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORE; nCntRankingScore1++)
	{// ランキングスコアの数だけ繰り返し
		int RankingScore = 1;
		for (int nCntRankingScore2 = 0; nCntRankingScore2 < MAX_RANKINGSCORENUMBER; nCntRankingScore2++)
		{// ランキングスコアの桁数だけ繰り返し
			g_TextureRankingScorePos = g_aRankingScore[nCntRankingScore1].score % (RankingScore * 10) / RankingScore;
			// 頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_RankingScorePos.x - RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.y - RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[1].pos = D3DXVECTOR3(g_RankingScorePos.x + RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.y - RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[2].pos = D3DXVECTOR3(g_RankingScorePos.x - RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.y + RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.z);
			pVtx[3].pos = D3DXVECTOR3(g_RankingScorePos.x + RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.y + RANKINGSCORE_TEXTURE_SIZE, g_RankingScorePos.z);

			// 頂点テクスチャ
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// 頂点カラー
			pVtx[0].col = g_aRankingScore[nCntRankingScore1].col;
			pVtx[1].col = g_aRankingScore[nCntRankingScore1].col;
			pVtx[2].col = g_aRankingScore[nCntRankingScore1].col;
			pVtx[3].col = g_aRankingScore[nCntRankingScore1].col;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_TextureRankingScorePos * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_TextureRankingScorePos * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_TextureRankingScorePos * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_TextureRankingScorePos * 0.1f), 1.0f);

			pVtx += 4;
			g_RankingScorePos.x -= 70;
			RankingScore *= 10;
		}
		g_RankingScorePos.y += 100;
		g_RankingScorePos.x = SCREEN_WIDTH / 2 + 100;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRankingScore->Unlock();
}
//=============================================================================
// ランキングスコアとゲームスコアの比較
//=============================================================================
void SetRankingScore(int nScore)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++)
	{// ランキングスコアの数だけ繰り返し
		if (g_aRankingScore[nCntRankingScore].score < nScore)
		{// ハイスコアが更新された
			g_aRankingScore[nCntRankingScore].score = nScore;

			int RankingScore = 1;
			// 頂点情報を設定
			for (int nCntRankingScore1 = 0; nCntRankingScore1 < MAX_RANKINGSCORENUMBER; nCntRankingScore1++)
			{// スコアの桁数だけ繰り返し
				g_TextureRankingScorePos = g_aRankingScore[nCntRankingScore].score % (RankingScore * 10) / RankingScore;

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (g_TextureRankingScorePos * 0.1f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (g_TextureRankingScorePos * 0.1f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (g_TextureRankingScorePos * 0.1f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (g_TextureRankingScorePos * 0.1f), 1.0f);

				RankingScore *= 10;        // 桁をずらすため
				pVtx += 4;
			}
			g_aRankingScore[nCntRankingScore].state = RANKINGSCORESTATE_UPDATE;  // 更新された状態に
			break;
		}
		pVtx += 4 * MAX_RANKINGSCORENUMBER; // ランキングスコアの桁数分だけ進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRankingScore->Unlock();
}
//=============================================================================
// ランキングスコアの取得
//=============================================================================
RANKINGSCORE *GetRankingScore(void)
{
	return &g_aRankingScore[0];
}