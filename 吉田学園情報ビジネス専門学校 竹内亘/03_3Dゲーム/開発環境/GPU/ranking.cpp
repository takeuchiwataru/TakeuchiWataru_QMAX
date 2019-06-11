//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "ranking.h"
#include "rankingscore.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "meshWall.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKING_TEXTURE_NAME  "data/TEXTURE/title_bg000.jpg"// 読み込むテクスチャファイル名
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
	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// メッシュフィールドの初期化処理
	InitmeshField();

	//// メッシュフィールド2の初期化処理
	//InitMeshField2();

	// メッシュウォールの初期化処理
	InitMeshWall(0, D3DXVECTOR3(-25.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	InitMeshWall(1, D3DXVECTOR3(-25.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	InitMeshWall(2, D3DXVECTOR3(725.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	InitMeshWall(3, D3DXVECTOR3(725.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	//LPDIRECT3DDEVICE9 pDevice;

	//pDevice = GetDevice();

	//g_nCounterRanking = 0;  // カウンターを初期化

	//// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	RANKING_TEXTURE_NAME,
	//	&g_pTextureRanking);

	//// 頂点バッファの生成
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffRanking,
	//	NULL);

	//VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	//// 頂点バッファをロックし,頂点データへのポインタを取得
	//g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//// 頂点座標
	//pVtx[0].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);


	//// 頂点テクスチャ
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// 頂点カラー
	//pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

	//// テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// 頂点バッファをアンロックする
	//g_pVtxBuffRanking->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// メッシュフィールドの終了処理
	UninitmeshField();

	//// メッシュフィールド2の終了処理
	//UninitMeshField2();

	// メッシュウォールの終了処理
	UninitMeshWall();

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
	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	// メッシュフィールドの更新処理
	UpdatemeshField();

	//// メッシュフィールド2の終了処理
	//UpdateMeshField2();

	// メッシュウォールの更新処理
	UpdateMeshWall();

	//フェードの取得
	FADE *pFade;
	pFade = GetFade();

	g_nCounterRanking++;

	if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{// ENTERキーが押されたら
		SetFade(MODE_TITLE);

		// ランキングスコアの取得
		RANKINGSCORE *rankingscore;
		rankingscore = GetRankingScore();

		for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++, rankingscore++)
		{
			if (rankingscore->state == RANKINGSCORESTATE_UPDATE)
			{// 更新状態になっていたら
				rankingscore->state = RANKINGSCORESTATE_NONE;
				rankingscore->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}

	if (g_nCounterRanking % 200 == 0 && *pFade == FADE_NONE)
	{//一定時間たったら
		SetFade(MODE_TITLE);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	// カメラの設定
	SetCamera();

	// メッシュフィールドの描画処理
	DrawmeshField();

	//// メッシュフィールドの描画処理
	//DrawMeshField2();

	// メッシュウォールの描画処理
	DrawMeshWall();

	//LPDIRECT3DDEVICE9 pDevice;

	//// デバイスを取得する
	//pDevice = GetDevice();

	//// 頂点バッファをデバイスのデータストリームに設定
	//pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pTextureRanking);

	//// ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);
}