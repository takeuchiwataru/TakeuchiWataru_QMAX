//=============================================================================
//
// ビルボード処理 [billboard.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BB_TEXTURENAME	"data/TEXTURE/grass.png"				// テクスチャ名
#define MAX_BB (256)											// ビルボードの最大数
#define BB_POS (20.0f)											// 頂点

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;			// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;				// テクスチャへのポインタ
//D3DXVECTOR3 g_posWall;									// 位置
//D3DXVECTOR3 g_rotWall;									// 向き
//D3DXMATRIX g_mtxWorldBillboard;								// ワールドマトリックス
Billboard g_aBillboard[MAX_BB];								// 壁の情報 
int g_nIdexShadowBillboard;							// 影の取得をするため

//=============================================================================
// 初期化処理
//=============================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	int nCntBillboard;

	// ビルボードの初期化処理
	for (nCntBillboard = 0; nCntBillboard < MAX_BB; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].bUse = false;
	}


	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BB,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BB_TEXTURENAME, &g_pTextureBillboard);

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BB; nCntBillboard++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BB_POS, BB_POS, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BB_POS, BB_POS, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BB_POS, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BB_POS, 0.0f, 0.0f);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
	// テクスチャの解放
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard(void)
{
	int nCntBillboard;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxView, mtxTrans;				//計算用マトリックス

	for (nCntBillboard = 0; nCntBillboard < MAX_BB; nCntBillboard++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
		g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
		g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
		g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
		g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
		g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
		g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
		g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
		g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBillboard);

		// アルファテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBillboard[nCntBillboard].bUse == true)	// ビルボードが使用されている
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBillboard,
				2);
		}

		// アルファテストを無効にする
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
//// 頂点情報の作成
////=============================================================================
//void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
//{
//	// 頂点バッファを生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//確保するバッファのサイズ
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,			//頂点フォーマット
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffWall,
//		NULL);
//
//	// 頂点情報の設定
//	VERTEX_3D *pVtx;	//頂点情報へのポインタ
//
//	// 頂点バッファをロックし、頂点データへのポインタを取得
//	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
//
//	// 頂点座標の設定
//	pVtx[0].pos = D3DXVECTOR3(-50.0f, 50.0f, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
//
//	// 法線の設定
//	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//
//	// 頂点カラーの設定
//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// テクスチャ座標の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	// 頂点バッファをアンロック
//	g_pVtxBuffWall->Unlock();
//}

//=============================================================================
// ビルボードの設定
//=============================================================================
int SetBillboard(D3DXVECTOR3 pos)
{
	int nCntBillboard;

	// 頂点情報の設定
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BB; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = pos;


			//// 頂点座標の設定
			//pVtx[0].pos = D3DXVECTOR3(-BB_POS, BB_POS, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(BB_POS, BB_POS, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(-BB_POS, 0.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(BB_POS, 0.0f, 0.0f);

			//g_aBillboard[nCntBillboard].rot = rot;
			g_aBillboard[nCntBillboard].bUse = true;			// 使用してる状態

			//g_aBillboard[nCntBillboard].nIdexShadow = SetShadow(g_aBillboard[nCntBillboard].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBillboard->Unlock();

	return nCntBillboard;
}

