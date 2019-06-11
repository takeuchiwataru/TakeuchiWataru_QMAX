//=============================================================================
//
// 影処理 [shadow.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SHADOW_TEXTURENAME	"data/TEXTURE/shadow000.jpg"			// テクスチャ名
#define MAX_SHADOW (256)											// 影の最大数
#define SHADOW_POS (10.0f)											// 影の位置

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;					// テクスチャへのポインタ
//D3DXVECTOR3 g_posShadow;									// 位置
//D3DXVECTOR3 g_rotShadow;									// 向き
//D3DXMATRIX g_mtxWorldShadow;								// ワールドマトリックス
Shadow g_aShadow[MAX_SHADOW];								// 影の情報 

//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// 影の初期化
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, SHADOW_TEXTURENAME, &g_pTextureShadow);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-SHADOW_POS, 0.0f, SHADOW_POS);
		pVtx[1].pos = D3DXVECTOR3(SHADOW_POS, 0.0f, SHADOW_POS);
		pVtx[2].pos = D3DXVECTOR3(-SHADOW_POS, 0.0f, -SHADOW_POS);
		pVtx[3].pos = D3DXVECTOR3(SHADOW_POS, 0.0f, -SHADOW_POS);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
	// テクスチャの解放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	// 減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
		D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureShadow);

		if (g_aShadow[nCntShadow].bUse == true)	// 影が使用されている
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntShadow,
				2);
		}
	}

	// 元の設定に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
//void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
//{
//	// 頂点バッファを生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,	//確保するバッファのサイズ
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,			//頂点フォーマット
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffShadow,
//		NULL);
//
//	// 頂点情報の設定
//	VERTEX_3D *pVtx;	//頂点情報へのポインタ
//
//	int nCntShadow;
//
//	// 頂点バッファをロックし、頂点データへのポインタを取得
//	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
//	{
//		// 頂点座標の設定
//		pVtx[0].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - 10.0f, 0.0f, g_aShadow[nCntShadow].pos.z + 10.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + 10.0f, 0.0f, g_aShadow[nCntShadow].pos.z + 10.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - 10.0f, 0.0f, g_aShadow[nCntShadow].pos.z - 10.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + 10.0f, 0.0f, g_aShadow[nCntShadow].pos.z - 10.0f);
//
//		// 法線の設定
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		// 頂点カラーの設定
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		// テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//	
//	// 頂点バッファをアンロック
//	g_pVtxBuffShadow->Unlock();
//}

//=============================================================================
// 影の設定
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	// 頂点情報の設定
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
			pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
			pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
			pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;			// 使用してる状態
			break;
		}
		pVtx += 4;

	}
	// 頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//=============================================================================
// 影の位置を設定
//=============================================================================
void SetPositionShadow(int nIdexShadow, D3DXVECTOR3 pos)
{	
	g_aShadow[nIdexShadow].pos = pos;
}
//=============================================================================
// 影の位置を設定
//=============================================================================
void DeleteShadow(int nIdexShadow)
{
	g_aShadow[nIdexShadow].bUse = false;
}


