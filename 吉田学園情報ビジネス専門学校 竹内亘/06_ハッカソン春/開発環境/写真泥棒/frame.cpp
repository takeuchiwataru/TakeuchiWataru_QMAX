//=============================================================================
//
// フレーム処理 [frame.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "frame.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_FRAME			(2)													// フレームの最大数
#define FRAME_TEXTURENAME	"data/TEXTURE/frame_timer000.png"				    // 読み込むテクスチャ名
#define FRAME_TEXTURENAME2	"data/TEXTURE/frame_score000.png"					// 読み込むテクスチャ名
#define FRAME_TEXTURENAME3	"data/TEXTURE/frame_life000.png"					// 読み込むテクスチャ名
#define FRAME_SIZE_X (100.0f)													// フレームサイズX
#define FRAME_SIZE_Y (50.0f)													// フレームサイズY
#define MAX_FRAME_TYPE		(2)													// フレームの種類

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexFrame(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pTextureFrame = NULL;			// テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;			// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureFrame[MAX_FRAME] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;			// 頂点バッファへのポインタ

//D3DXVECTOR3				g_FramePos(640, 50, 0.0f);	// フレームの頂点座標
Frame g_aFrame[MAX_FRAME];								// フレームの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// フレームの初期化処理
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		g_aFrame[nCntFrame].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFrame[nCntFrame].fHeight = 0.0f;
		g_aFrame[nCntFrame].fWidth = 0.0f;
		g_aFrame[nCntFrame].nType = (FRAME)nCntFrame;
		g_aFrame[nCntFrame].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		FRAME_TEXTURENAME,							// ファイルの名前
		&g_pTextureFrame[0]);						// テクスチャへのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		FRAME_TEXTURENAME2,							// ファイルの名前
		&g_pTextureFrame[1]);						// テクスチャへのポインタ


	// 頂点情報の作成
	MakeVertexFrame(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFrame(void)
{
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		//テクスチャの開放
		if (g_pTextureFrame[nCntFrame] != NULL)
		{
			g_pTextureFrame[nCntFrame]->Release();
			g_pTextureFrame[nCntFrame] = NULL;
		}

		//頂点バッファの開放
		if (g_pVtxBuffFrame != NULL)
		{
			g_pVtxBuffFrame->Release();
			g_pVtxBuffFrame = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFrame(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntFrame;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		if (g_aFrame[nCntFrame].bUse = true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureFrame[g_aFrame[nCntFrame].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFrame * 4, 2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexFrame(LPDIRECT3DDEVICE9 pDevice)
{

		// 頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,		//確保するバッファのサイズ
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,				//	頂点フォーマット
			D3DPOOL_MANAGED,
			&g_pVtxBuffFrame,
			NULL);

		// 頂点情報を設定
		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
		{
			////頂点座標の設定
			//pVtx[0].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x - FRAME_SIZE_X, g_aFrame[nCntFrame].pos.y - FRAME_SIZE_Y, g_aFrame[nCntFrame].pos.z);
			//pVtx[1].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x + FRAME_SIZE_X, g_aFrame[nCntFrame].pos.y - FRAME_SIZE_Y, g_aFrame[nCntFrame].pos.z);
			//pVtx[2].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x - FRAME_SIZE_X, g_aFrame[nCntFrame].pos.y + FRAME_SIZE_Y, g_aFrame[nCntFrame].pos.z);
			//pVtx[3].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x + FRAME_SIZE_X, g_aFrame[nCntFrame].pos.y + FRAME_SIZE_Y, g_aFrame[nCntFrame].pos.z);

			if (nCntFrame == FRAME_TIMER)
			{//タイマーフレーム
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(550, 0, 0);
				pVtx[1].pos = D3DXVECTOR3(750, 0, 0);
				pVtx[2].pos = D3DXVECTOR3(550, 100, 0);
				pVtx[3].pos = D3DXVECTOR3(750, 100, 0);

				//rhwの設定
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//頂点カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

				pVtx += 4;	//頂点データを４つ分進める
			}

			else if (nCntFrame == FRAME_SCORE)
			{//スコアフレーム
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(770, 0, 0);
				pVtx[1].pos = D3DXVECTOR3(1250, 0, 0);
				pVtx[2].pos = D3DXVECTOR3(770, 100, 0);
				pVtx[3].pos = D3DXVECTOR3(1250, 100, 0);

				//rhwの設定
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//頂点カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

				pVtx += 4;	//頂点データを４つ分進める
			}

			//頂点バッファをアンロック
			g_pVtxBuffFrame->Unlock();
		}
}






