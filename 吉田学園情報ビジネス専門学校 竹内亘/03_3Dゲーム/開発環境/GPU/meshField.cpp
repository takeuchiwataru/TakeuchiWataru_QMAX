//=============================================================================
//
// メッシュフィールド処理 [meshField.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "meshField.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURENAME	"data/TEXTURE/field005.jpg"						// テクスチャ名
#define MESHFIELD_POS (50.0f)													// ポリゴンの位置
#define MAX_MESHFIELD (14)
#define MAX_MF_X (15)															// X(横の数)
#define MAX_MF_Z (15)															// Z(縦の数)
#define VERTEX_KAZU ((MAX_MF_X + 1) * (MAX_MF_Z + 1))							// 頂点数
#define INDEX_KAZU ((((MAX_MF_X + 1) * 2) * (MAX_MF_Z)) + ((MAX_MF_Z - 1) * 2))	// インデックス数
#define POLYGON_KAZU (((MAX_MF_X * MAX_MF_Z) * 2) + ((MAX_MF_Z - 1) * 4))		// ポリゴン数											// ポリゴン数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexmeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffmeshField = NULL;			// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTexturemeshField = NULL;				// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;			// インデックスバッファのポインタ
D3DXVECTOR3 g_posmeshField;									// 位置
D3DXVECTOR3 g_rotmeshField;									// 向き
D3DXMATRIX g_mtxWorldmeshField;								// ワールドマトリックス
int g_nNumVertexMeshField;									// 頂点数
int g_nNumIndexMeshField;									// インデックス数
int g_nNumPolygonMeshField;									// ポリゴン数

//=============================================================================
// 初期化処理
//=============================================================================
void InitmeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	int nCntMFdepth;
	int nCntMFwidth;

	// 各初期化の設定
	g_nNumVertexMeshField = VERTEX_KAZU;		// 頂点数
	g_nNumIndexMeshField = INDEX_KAZU;			// インデックス数
	g_nNumPolygonMeshField = POLYGON_KAZU;		// ポリゴン数

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_KAZU,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffmeshField,
		NULL);

	// インデックスの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_KAZU,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,			// 2バイトのデータ
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURENAME, &g_pTexturemeshField);

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffmeshField->Lock(0, 0, (void**)&pVtx, 0);

	 //頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	//pVtx[4].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[6].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[7].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[8].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[9].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	//pVtx[10].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[11].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[12].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	//pVtx[13].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);

	//頂点座標の設定
	for (nCntMFdepth = 0; nCntMFdepth < MAX_MF_Z + 1; nCntMFdepth++)
	{// 縦の面の数だけ繰り返し
		for (nCntMFwidth = 0; nCntMFwidth < MAX_MF_X + 1; nCntMFwidth++)
		{// 横の面の数だけ繰り返し
			pVtx[nCntMFdepth * (MAX_MF_X + 1) + nCntMFwidth].pos = D3DXVECTOR3((-MESHFIELD_POS / 2) + nCntMFdepth * MESHFIELD_POS , 0.0f, (-MESHFIELD_POS / 2 )+ nCntMFwidth * MESHFIELD_POS);
			pVtx[nCntMFdepth * (MAX_MF_X + 1) + nCntMFwidth].nor = D3DXVECTOR3(0.0f, 1.0f , 0.0f);
			pVtx[nCntMFdepth * (MAX_MF_X + 1) + nCntMFwidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntMFdepth * (MAX_MF_X + 1) + nCntMFwidth].tex = D3DXVECTOR2(1.0f * (nCntMFdepth % (MAX_MF_X + 1)), 1.0f * (nCntMFwidth));
		}
	}

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(-MESHFIELD_POS, 0.0f, MESHFIELD_POS);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, MESHFIELD_POS);
	//pVtx[2].pos = D3DXVECTOR3(MESHFIELD_POS, 0.0f, MESHFIELD_POS);
	//pVtx[3].pos = D3DXVECTOR3(-MESHFIELD_POS, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(MESHFIELD_POS, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-MESHFIELD_POS, 0.0f, -MESHFIELD_POS);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -MESHFIELD_POS);
	//pVtx[8].pos = D3DXVECTOR3(MESHFIELD_POS, 0.0f, -MESHFIELD_POS);

	// // 法線の設定
	//pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//// 頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);

	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	//pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffmeshField->Unlock();

	WORD * pIdx;	// インデックスデータへのポインタ
	int nCntMesh = 0;

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMFdepth = 0; nCntMFdepth < MAX_MF_Z ; nCntMFdepth++)
	{
		for (nCntMFwidth = 0; nCntMFwidth < MAX_MF_X + 1; nCntMFwidth++)
		{
			pIdx[(nCntMFdepth * (MAX_MF_X + 1) * 2) + (nCntMFwidth * 2) + nCntMesh] = ((nCntMFdepth + 1) * (MAX_MF_X + 1)) + nCntMFwidth;
			pIdx[(nCntMFdepth * (MAX_MF_X + 1) * 2) + (nCntMFwidth * 2) + 1 + nCntMesh] = (nCntMFdepth * (MAX_MF_X + 1)) + nCntMFwidth;

			if (MAX_MF_Z > 1 && nCntMFdepth != MAX_MF_Z - 1 && nCntMFwidth == MAX_MF_X)
			{
				pIdx[(nCntMFdepth * (MAX_MF_X + 1) * 2) + (nCntMFwidth * 2) + 1 + nCntMesh + 1] = (nCntMFdepth * (MAX_MF_X + 1)) + nCntMFwidth;
				pIdx[(nCntMFdepth * (MAX_MF_X + 1) * 2) + (nCntMFwidth * 2) + 1 + nCntMesh + 2] = ((nCntMFdepth + 2) * (MAX_MF_X + 1));

				nCntMesh += 2;
			}
		}
	}

	// インデックスの設定
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;

	// インデックスバッファをアンロック
	g_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitmeshField(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffmeshField != NULL)
	{
		g_pVtxBuffmeshField->Release();
		g_pVtxBuffmeshField = NULL;
	}
	// テクスチャの解放
	if (g_pTexturemeshField != NULL)
	{
		g_pTexturemeshField->Release();
		g_pTexturemeshField = NULL;
	}
	// インデックスバッファの解放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatemeshField(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawmeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldmeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotmeshField.y, g_rotmeshField.x, g_rotmeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldmeshField, &g_mtxWorldmeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posmeshField.x, g_posmeshField.y, g_posmeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldmeshField, &g_mtxWorldmeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldmeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffmeshField, 0, sizeof(VERTEX_3D));

	// インデックスデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturemeshField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VERTEX_KAZU, 0, POLYGON_KAZU);		// 頂点数,0,描画するプリミティブ数(ポリゴン数)
}

////=============================================================================
//// 頂点情報の作成
////=============================================================================
//void MakeVertexmeshField(LPDIRECT3DDEVICE9 pDevice)
//{

//}

