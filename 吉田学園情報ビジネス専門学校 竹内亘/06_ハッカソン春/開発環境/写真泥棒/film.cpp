//=============================================================================
//
// フィルム処理 [film.cpp]
// Author : Jukiya HayakawaFilm
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "film.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NAME		"data/TEXTURE/film.png"	// 読み込むテクスチャファイル名
#define TEXTURE_SIZE        (30)                            // テクスチャのサイズ
#define MAX_FILM			(10)                             // プレイヤーのライフ数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexFilm(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFilm = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFilm = NULL;	// 頂点バッファへのポインタ
FILM                    g_life[MAX_FILM];		// ライフ
int                     g_nCounterFilm;         // 現在のライフ数

//=============================================================================
// 初期化処理
//=============================================================================
void InitFilm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntFilm = 0; nCntFilm < MAX_FILM; nCntFilm++)
	{// ライフアイコン数だけ繰り返し
		g_life[nCntFilm].pos = D3DXVECTOR3(620.0f,SCREEN_HEIGHT - 50.0f, 0.0);   // 座標を初期化
		g_life[nCntFilm].bUse = true;                     // 使用している状態にする
	}
	g_nCounterFilm = MAX_FILM;							  // 現在のライフ数を初期化

	 // テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					  // デバイスへのポインタ
		TEXTURE_NAME,									  // ファイルの名前
		&g_pTextureFilm);								  // テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexFilm(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFilm(void)
{
	// テクスチャの開放
	if (g_pTextureFilm != NULL)
	{
		g_pTextureFilm->Release();
		g_pTextureFilm = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffFilm != NULL)
	{
		g_pVtxBuffFilm->Release();
		g_pVtxBuffFilm = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFilm(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFilm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFilm, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFilm);

	// ポリゴンの描画
	for (int nCntFilm = 0; nCntFilm < MAX_FILM; nCntFilm++)
	{// 表示するライフアイコン数だけ繰り返し
		if (g_life[nCntFilm].bUse == true)
		{// ライフが使用されている
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntFilm * 4,
				2);
		}
	}
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexFilm(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FILM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFilm,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffFilm->Lock(0, 0, (void**)&pVtx, 0);

	float pos = 0;
	// 頂点情報を設定
	for (int nCntFilm = 0; nCntFilm < MAX_FILM; nCntFilm++)
	{// ライフアイコン数だけ繰り返し
	 // 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_life[nCntFilm].pos.x - TEXTURE_SIZE + pos, g_life[nCntFilm].pos.y - TEXTURE_SIZE, g_life[nCntFilm].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_life[nCntFilm].pos.x + TEXTURE_SIZE + pos, g_life[nCntFilm].pos.y - TEXTURE_SIZE, g_life[nCntFilm].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_life[nCntFilm].pos.x - TEXTURE_SIZE + pos, g_life[nCntFilm].pos.y + TEXTURE_SIZE, g_life[nCntFilm].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_life[nCntFilm].pos.x + TEXTURE_SIZE + pos, g_life[nCntFilm].pos.y + TEXTURE_SIZE, g_life[nCntFilm].pos.z);


		// 頂点テクスチャ
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		pos -= 60.0f;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffFilm->Unlock();
}
//=============================================================================
// ライフの減少
//=============================================================================
void CutFilm(int cut)
{
	for (int nCntFilm = 0; nCntFilm < MAX_FILM; nCntFilm++)
	{// ライフアイコン数だけ繰り返し
		if (g_life[nCntFilm].bUse == true)
		{// ライフが使用されている
			g_life[nCntFilm].bUse = false;
			g_nCounterFilm--;
			if (g_nCounterFilm <= 0)
			{
				if (GetGameState() != GAMESTATE_END)
				{
					SetGameState(GAMESTATE_END);
				}
			}
			break;
		}
	}
}
int GetFilmNum(void)
{
	return g_nCounterFilm;
}