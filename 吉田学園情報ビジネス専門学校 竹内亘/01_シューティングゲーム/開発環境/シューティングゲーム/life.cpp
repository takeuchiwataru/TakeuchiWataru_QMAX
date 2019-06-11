//=============================================================================
//
// ライフ処理 [life.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "life.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/life000.png"		//読み込むテクスチャファイル名
#define LIFE_SIZE (15.0f)									//ライフサイズ
#define LIFE_WIDE (25)										//ライフの幅
#define LIFE_POS (30)										//ライフの場所
#define MAX_LIFE (3)										//ライフの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;				// 頂点バッファへのポインタ
D3DXVECTOR3				g_LifePos(100, 50, 0.0f);			// ライフの頂点座標
LIFE					g_nLife[MAX_LIFE];					// ライフ
//int						g_TexturePosLife;				// テクスチャX座標
int g_Life;

//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntLife;
	g_Life = 3;
	//ライフの初期化
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		g_nLife[nCntLife].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_LIFE,			// ファイルの名前
		&g_pTextureLife);		// テクスチャへのポインタ

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

	// 頂点バッファの開放
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

	int nCntLife;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	// ポリゴンの描画
	for (nCntLife = 0; nCntLife < g_Life; nCntLife++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntLife, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	int nCntLife;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{

		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(g_LifePos.x - LIFE_SIZE, g_LifePos.y - LIFE_SIZE, g_LifePos.z);
		pVtx[1].pos = D3DXVECTOR3(g_LifePos.x + LIFE_SIZE, g_LifePos.y - LIFE_SIZE, g_LifePos.z);
		pVtx[2].pos = D3DXVECTOR3(g_LifePos.x - LIFE_SIZE, g_LifePos.y + LIFE_SIZE, g_LifePos.z);
		pVtx[3].pos = D3DXVECTOR3(g_LifePos.x + LIFE_SIZE, g_LifePos.y + LIFE_SIZE, g_LifePos.z);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データを４つ分進める
		g_LifePos.x -= 30;
	}
	g_LifePos.x = 100;

	//頂点バッファをアンロック
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// ライフ減少
//=============================================================================
void CutLife(int nCut)
{
	g_Life -= nCut;
}
