//=============================================================================
//
// 背景の処理 [Result.cpp]
// Author : Ozaki
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "resultlogo.h"
//#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Result_WIDTH	(SCREEN_WIDTH)
#define Result_HEIGHT	(SCREEN_HEIGHT)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//VERTEX_2D g_aVertex[4];								//頂点情報を格納する
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//テクスチャのポインタ

//=============================================================================
// 初期化処理(ポリゴン)
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevise;						//デバイスのポインタ
													//デバイスの取得
	pDevise = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\movie.png",
		&g_pTextureResult);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);
	//ローカル変数
	VERTEX_2D*pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データのポインタの取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロック
	g_pVtxBuffResult->Unlock();

	InitResultlogo();
}

//=============================================================================
// 終了処理(ポリゴン)
//=============================================================================
void UninitResult(void)
{
	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	UninitResultlogo();
}
//=============================================================================
// 更新処理(ポリゴン)
//=============================================================================
void UpdateResult(void)
{
	D3DXVECTOR3 Resultrogo;

	FADE Fade;
	Fade = GetFade();

	//if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
	//{
	//	Resultrogo = *GetResultrogo();
	//	SetResultrogo(D3DXVECTOR3(1000.0f, SCREEN_WIDTH - 48, 0.0f));

	//	if (Resultrogo == D3DXVECTOR3(1000.0f, SCREEN_WIDTH - 48, 0.0f))
	//	{
	//		//PlaySound(SOUND_LABEL_SE_DECIDE);
	//		SetFade(MODE_RANKING);
	//		//StopSound(SOUND_LABEL_BGM_TITLE);
	//	}
	//}

	if (GetKeyboardTrigger(DIK_RETURN) == true && Fade == FADE_NONE)
	{
		SetFade(MODE_RANKING);
		//PlaySound(SOUND_LABEL_SE_DECIDE);
	}

	UpdateResultlogo();
}

//=============================================================================
// 描画処理(ポリゴン)
//=============================================================================
void DrawResult(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//デヴァイスを取得
	pDevice = GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	DrawResultlogo();

}