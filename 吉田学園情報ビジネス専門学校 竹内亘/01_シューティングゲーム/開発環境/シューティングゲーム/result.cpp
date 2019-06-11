//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
//#include "player.h"
//#include "enemy.h"
//#include "boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_TEXTURENAME		"data/TEXTURE/result000.png"	//テクスチャ名
//#define RESULT_TEXTURENAME_1	"data/TEXTURE/CLEAR.jpg"		//ゲームクリアテクスチャ
//#define RESULT_TEXTURENAME_2	"data/TEXTURE/OVER.jpg"			//ゲームオーバーテクスチャ
#define RESULT_POS_X			(0)								//背景の左上X座標
#define RESULT_POS_Y			(0)								//背景の左上Y座標
#define RESULT_WIDTH			(SCREEN_WIDTH)					//背景の幅
#define RESULT_HEIGHT			(SCREEN_HEIGHT)					//背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファへのポインタ

//=============================================================================
// リザルト初期化処理
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	////プレイヤーの取得
	//Player * pPlayer;
	//pPlayer = GetPlayer();

	////敵の取得
	//Enemy * pEnemy;
	//pEnemy = GetEnemy();

	////ボスの取得
	//Boss * pBoss;
	//pBoss = GetBoss();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME, &g_pTextureResult);

	//if (pPlayer->bDisp == false)
	//{//プレイヤーが死んだら
	//	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME_2, &g_pTextureResult);
	//	StopSound(SOUND_LABEL_BGM003);
	//}

	//else if (pEnemy->bUse == false)
	//{//敵が全滅したら
	//	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME_1, &g_pTextureResult);
	//	StopSound(SOUND_LABEL_BGM003);
	//}

	//else if (pBoss->bUse == true)
	//{//ボスが全滅したら
	//	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME_2, &g_pTextureResult);
	//	StopSound(SOUND_LABEL_BGM003);
	//}


	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

	// rhwの設定
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

	// 頂点バッファをアンロック
	g_pVtxBuffResult->Unlock();

	//PlaySound(SOUND_LABEL_BGM000);
}

//=============================================================================
// リザルト終了処理
//=============================================================================
void UninitResult(void)
{
	// テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=============================================================================
// リザルト更新処理
//=============================================================================
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		FADE *pFade;
		pFade = GetFade();
		//PlaySound(SOUND_LABEL_SE_DECIDE);

		if (*pFade != FADE_OUT)
		{
			StopSound(SOUND_LABEL_BGM000);
			SetFade(MODE_TITLE);
		}
	}
}

//=============================================================================
// リザルト描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}