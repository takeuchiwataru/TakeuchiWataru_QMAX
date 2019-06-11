//=============================================================================
//
// フィルムフレームの処理 [filmframe.cpp]
// Author :　Jukiya Hayakawa
//
//=============================================================================
#include "filmframe.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FRAME_TEXTURE_NAME0	"data\\TEXTURE\\filmframe.png"		// テクスチャ名
#define	FRAME_SIZE_X			(330)								// 大きさ
#define	FRAME_SIZE_Y			(60)								// 大きさ
#define	MAX_FRAME			(1)									//ランクの最大数

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureFilmFrame = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFilmFrame = NULL;					// 頂点バッファへのポインタ
FILMFRAME g_aFilmFrame;													// ランクの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitFilmFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFilmFrame;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 情報の初期化
	g_aFilmFrame.pos = D3DXVECTOR3(350.0f, 650.0f, 0.0f);	//位置の初期化
	g_aFilmFrame.bUse = true;								//使用状態にする

														// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, FRAME_TEXTURE_NAME0, &g_apTextureFilmFrame);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFilmFrame,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFilmFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFilmFrame = 0; nCntFilmFrame < MAX_FRAME; nCntFilmFrame++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aFilmFrame.pos.x - FRAME_SIZE_X, g_aFilmFrame.pos.y - FRAME_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aFilmFrame.pos.x + FRAME_SIZE_X, g_aFilmFrame.pos.y - FRAME_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aFilmFrame.pos.x - FRAME_SIZE_X, g_aFilmFrame.pos.y + FRAME_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aFilmFrame.pos.x + FRAME_SIZE_X, g_aFilmFrame.pos.y + FRAME_SIZE_Y, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;

		pVtx += 4;	// 頂点データを４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffFilmFrame->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFilmFrame(void)
{

	// テクスチャの開放
	if (g_apTextureFilmFrame != NULL)
	{
		g_apTextureFilmFrame->Release();
		g_apTextureFilmFrame = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffFilmFrame != NULL)
	{
		g_pVtxBuffFilmFrame->Release();
		g_pVtxBuffFilmFrame = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFilmFrame(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawFilmFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffFilmFrame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntFilmFrame = 0; nCntFilmFrame < MAX_FRAME; nCntFilmFrame++)
	{
		if (g_aFilmFrame.bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureFilmFrame);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntFilmFrame,
				2);
		}
	}
}