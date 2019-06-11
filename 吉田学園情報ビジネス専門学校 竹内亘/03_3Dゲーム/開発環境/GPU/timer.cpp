//=============================================================================
//
// タイマー処理 [timer.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "timer.h"
#include "fade.h"
#include "score.h"
#include "game.h"

//#include "item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIMER		"data/TEXTURE/number003.png"	//読み込むテクスチャファイル名
#define TIMER_SIZE (20.0f)									//タイマーサイズ
#define TIMER_WIDE (30)										//タイマーの幅
#define TIMER_POS (100)										//タイマーの場所
#define MAX_NUMBER (3)										//タイマーの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// 頂点バッファへのポインタ
D3DXVECTOR3				g_TimerPos(680, 60, 0.0f);	// タイマーの頂点座標
int						g_nCntTimer = 0;
bool					g_TimerStop;
Timer g_Timer;										// タイマーの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// タイマーの初期化
	g_Timer.nTimer = 60;
	g_TimerStop = false;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile	(pDevice,				// デバイスへのポインタ
								TEXTURE_TIMER,			// ファイルの名前
								&g_pTextureTimer);		// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexTimer(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimer(void)
{
	// テクスチャの開放
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimer(void)
{
	int nAnswer = 1;
	int nTimer;
	int nCntTimer;

	// 頂点情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_TimerStop == false)
	{
		g_nCntTimer++;
		if (g_nCntTimer >= 60)
		{
			g_Timer.nTimer -= 1;	//+でカウントUP,//-でカウントDOWN
			g_nCntTimer = 0;
		}

		if (g_Timer.nTimer >= 0)
		{
			for (nCntTimer = 0; nCntTimer < MAX_NUMBER; nCntTimer++)
			{
				nTimer = g_Timer.nTimer % (nAnswer * 10) / nAnswer;

				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nTimer), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * nTimer), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * nTimer), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nTimer), 1.0f);

				nAnswer *= 10;
				pVtx += 4;	//頂点データを４つ分進める
			}
		}
	}

	if (g_Timer.nTimer == 0)
	{//タイマーが0になったら
		SetGameState(GAMESTATE_END);
	}

	//頂点バッファをアンロック
	g_pVtxBuffTimer->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntTimer;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTimer);

	// ポリゴンの描画
	for (nCntTimer = 0; nCntTimer < MAX_NUMBER; nCntTimer++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTimer, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUMBER,		//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	int nCntTimer;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < MAX_NUMBER; nCntTimer++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_TimerPos.x - TIMER_SIZE, g_TimerPos.y - TIMER_SIZE, g_TimerPos.z);
		pVtx[1].pos = D3DXVECTOR3(g_TimerPos.x + TIMER_SIZE, g_TimerPos.y - TIMER_SIZE, g_TimerPos.z);
		pVtx[2].pos = D3DXVECTOR3(g_TimerPos.x - TIMER_SIZE, g_TimerPos.y + TIMER_SIZE, g_TimerPos.z);
		pVtx[3].pos = D3DXVECTOR3(g_TimerPos.x + TIMER_SIZE, g_TimerPos.y + TIMER_SIZE, g_TimerPos.z);

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
		g_TimerPos.x -= 40;
	}
	g_TimerPos.x = 680;

	//頂点バッファをアンロック
	g_pVtxBuffTimer->Unlock();
}

//=============================================================================
// タイマーストップ
//=============================================================================
void StopTimer(void)
{
	g_TimerStop = true;
	//AddScore(g_nTimer * 100);
}

//=============================================================================
// タイマーの取得
//=============================================================================
Timer *GetTimer(void)
{
	return &g_Timer;
}
