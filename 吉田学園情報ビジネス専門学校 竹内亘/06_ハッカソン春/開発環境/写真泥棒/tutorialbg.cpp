//=============================================================================
//
// チュートリアル背景の処理 [tutorialbg.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "tutorialbg.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIALBG_TEXTURE_NAME0	"data\\TEXTURE\\tutorial000.png"	//テクスチャ名
#define TUTORIALBG_TEXTURE_NAME1	"data\\TEXTURE\\tutorial001.png"	//テクスチャ名
#define TUTORIALBG_SIZE_X		(650.0f)								// 大きさ
#define TUTORIALBG_SIZE_Y		(300.0f)								// 地面大きさ
#define MAX_TUTORIALBG			(2)										// チュートリアル背景の数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTutorialBG(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffTutorialBG = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureTutorialBG[MAX_TUTORIALBG];	// テクスチャへのポインタ
TUTORIALBG				g_aTutorialBG[MAX_TUTORIALBG];

//=============================================================================
// 初期化処理
//=============================================================================
void InitTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

												// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG_TEXTURE_NAME0, &g_pTextureTutorialBG[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG_TEXTURE_NAME1, &g_pTextureTutorialBG[1]);

	// 頂点情報の作成
	MakeVertexTutorialBG(pDevice);

	for (int nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		// ポリゴンの情報を設定
		g_aTutorialBG[nCntTutorialBG].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_aTutorialBG[nCntTutorialBG].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_aTutorialBG[nCntTutorialBG].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量

		g_aTutorialBG[nCntTutorialBG].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialBG(void)
{
	for (int nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		// テクスチャの破棄
		if (g_pTextureTutorialBG[nCntTutorialBG] != NULL)
		{
			g_pTextureTutorialBG[nCntTutorialBG]->Release();
			g_pTextureTutorialBG[nCntTutorialBG] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffTutorialBG != NULL)
	{
		g_pVtxBuffTutorialBG->Release();
		g_pVtxBuffTutorialBG = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialBG(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

									// デバイスの取得
	pDevice = GetDevice();

	for (int nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aTutorialBG[nCntTutorialBG].rot.y, g_aTutorialBG[nCntTutorialBG].rot.x, g_aTutorialBG[nCntTutorialBG].rot.z);
		D3DXMatrixMultiply(&g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG, &g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aTutorialBG[nCntTutorialBG].pos.x, g_aTutorialBG[nCntTutorialBG].pos.y, g_aTutorialBG[nCntTutorialBG].pos.z);
		D3DXMatrixMultiply(&g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG, &g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG);


		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTutorialBG, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorialBG[nCntTutorialBG]);

		if (g_aTutorialBG[nCntTutorialBG].bUse == true)	// 弾が使用されている
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntTutorialBG,
				2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTutorialBG(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_TUTORIALBG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialBG,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x - TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y + TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x + TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y + TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x - TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y - TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x + TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y - TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[1].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[2].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[3].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点データのポインタを4つ分進める
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorialBG->Unlock();
}

//=============================================================================
// チュートリアル背景の設定
//=============================================================================
void SetTutorialBG(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntTutorialBG;

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		if (g_aTutorialBG[nCntTutorialBG].bUse == false)
		{
			g_aTutorialBG[nCntTutorialBG].pos = pos;
			g_aTutorialBG[nCntTutorialBG].rot = rot;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x - TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y + TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x + TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y + TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x - TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y - TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x + TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y - TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);

			g_aTutorialBG[nCntTutorialBG].bUse = true;
			break;
		}
		pVtx += 4;	// 該当の位置まで進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffTutorialBG->Unlock();
}