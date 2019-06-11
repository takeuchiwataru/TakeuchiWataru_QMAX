//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "game.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME		"data/MODEL/benti000.x"		// モデル名
#define MODEL_NAME0		"data/MODEL/benti001.x"		// モデル名
#define MODEL_NAME1		"data/MODEL/buranko.x"		// モデル名
#define MODEL_NAME2		"data/MODEL/slide.x"		// モデル名
#define MODEL_NAME3		"data/MODEL/taiya.x"		// モデル名
#define MODEL_NAME4		"data/MODEL/JG.x"			// モデル名
#define MODEL_NAME5		"data/MODEL/seesaw.x"		// モデル名
#define MODEL_NAME6		"data/MODEL/taiya002.x"		// モデル名
#define MAX_MODEL		(256)						// モデル配置の最大数
#define MAX_MODEL_TYPE	(5)							// モデル種類の最大数
#define TEXTURE_NAME	"data/TEXTURE/mokume.png"	// テクスチャ名
//#define MAX_TEXTURE		(1)							// 読み込むテクスチャ数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshModel[MODELTYPE_MAX];							// メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatModel[MODELTYPE_MAX];					// マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9	g_pTextureModel = NULL;			// テクスチャへのポインタ
DWORD g_nNumMatModel[MODELTYPE_MAX];						// マテリアル情報の数
MODEL g_aModel[MODELTYPE_MAX][MAX_MODEL];						// モデルの情報
//VTXMODEL g_aModelVtx[MAX_MODEL_TYPE];							

//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char cFN[MODELTYPE_MAX][256] = { MODEL_NAME ,MODEL_NAME0,MODEL_NAME1, MODEL_NAME2,MODEL_NAME3,MODEL_NAME4,MODEL_NAME5,MODEL_NAME6 };

	for (int nCntModelType = 0; nCntModelType < MODELTYPE_MAX; nCntModelType++)
	{// モデルの種類繰り返し

	 // Xファイルの読み込み
		D3DXLoadMeshFromX(cFN[nCntModelType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatModel[nCntModelType],
			NULL,
			&g_nNumMatModel[nCntModelType],
			&g_pMeshModel[nCntModelType]);

		////テクスチャの読み込み
		//D3DXCreateTextureFromFile(pDevice,
		//	TEXTURE_NAME,
		//	&g_pTextureModel[0]);

		int nNumVtex;					// 頂点数
		DWORD sizeFvF;					// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;		// 頂点バッファへのポインタ

		// モデル初期化
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// モデルの数繰り返し
			g_aModel[nCntModelType][nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModel[nCntModelType][nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModel[nCntModelType][nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModel[nCntModelType][nCntModel].VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
			g_aModel[nCntModelType][nCntModel].VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
			g_aModel[nCntModelType][nCntModel].nType = MODELTYPE_BENCH;
			g_aModel[nCntModelType][nCntModel].bUse = false;

			// 頂点数を取得
			nNumVtex = g_pMeshModel[nCntModelType]->GetNumVertices();

			// 頂点フォーマットのサイズを取得
			sizeFvF = D3DXGetFVFVertexSize(g_pMeshModel[nCntModelType]->GetFVF());

			// 頂点バッファをロック
			g_pMeshModel[nCntModelType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				if (g_aModel[nCntModelType][nCntModel].VtxMinModel.x >= vtx.x)
				{
					g_aModel[nCntModelType][nCntModel].VtxMinModel.x = vtx.x;
				}
				if (g_aModel[nCntModelType][nCntModel].VtxMinModel.y >= vtx.y)
				{
					g_aModel[nCntModelType][nCntModel].VtxMinModel.y = vtx.y;
				}
				if (g_aModel[nCntModelType][nCntModel].VtxMinModel.z >= vtx.z)
				{
					g_aModel[nCntModelType][nCntModel].VtxMinModel.z = vtx.z;
				}

				if (g_aModel[nCntModelType][nCntModel].VtxMaxModel.x <= vtx.x)
				{
					g_aModel[nCntModelType][nCntModel].VtxMaxModel.x = vtx.x;
				}
				if (g_aModel[nCntModelType][nCntModel].VtxMaxModel.y <= vtx.y)
				{
					g_aModel[nCntModelType][nCntModel].VtxMaxModel.y = vtx.y;
				}
				if (g_aModel[nCntModelType][nCntModel].VtxMaxModel.z <= vtx.z)
				{
					g_aModel[nCntModelType][nCntModel].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff += sizeFvF;
			}
			// 頂点バッファをアンロック
			g_pMeshModel[nCntModelType]->UnlockVertexBuffer();
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	for (int nCntModelType = 0; nCntModelType < MODELTYPE_MAX; nCntModelType++)
	{
	 // メッシュの開放
		if (g_pMeshModel[nCntModelType] != NULL)
		{
			g_pMeshModel[nCntModelType]->Release();
			g_pMeshModel[nCntModelType] = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatModel[nCntModelType] != NULL)
		{
			g_pBuffMatModel[nCntModelType]->Release();
			g_pBuffMatModel[nCntModelType] = NULL;
		}
	}

	// テクスチャの破棄
	if (g_pTextureModel != NULL)
	{
		g_pTextureModel->Release();
		g_pTextureModel = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nCntModelType = 0; nCntModelType < MODELTYPE_MAX; nCntModelType++)
	{// モデルの種類繰り返し
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// モデルの数繰り返し
			if (g_aModel[nCntModelType][nCntModel].bUse == true)	
			{// モデルが使用されている

				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aModel[nCntModelType][nCntModel].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModelType][nCntModel].rot.y, g_aModel[nCntModelType][nCntModel].rot.x, g_aModel[nCntModelType][nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aModel[nCntModelType][nCntModel].mtxWorld, &g_aModel[nCntModelType][nCntModel].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModelType][nCntModel].pos.x, g_aModel[nCntModelType][nCntModel].pos.y, g_aModel[nCntModelType][nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aModel[nCntModelType][nCntModel].mtxWorld, &g_aModel[nCntModelType][nCntModel].mtxWorld, &mtxTrans);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModelType][nCntModel].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModelType][nCntModel].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel[g_aModel[nCntModelType][nCntModel].nType]; nCntMat++)
				{// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャ
					pDevice->SetTexture(0, g_pTextureModel);

					// モデル(パーツ)の描画
					g_pMeshModel[g_aModel[nCntModelType][nCntModel].nType]->DrawSubset(nCntMat);

				}
				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// モデルの設定
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nType][nCntModel].bUse == false)
		{
			g_aModel[nType][nCntModel].pos = pos;
			g_aModel[nType][nCntModel].rot = D3DXVECTOR3(0, 0, 0);
			g_aModel[nType][nCntModel].nType = nType;
			g_aModel[nType][nCntModel].bUse = true;
			break;
		}
	}
}

//=============================================================================
// モデルとの当たり判定処理
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	bool bHit = false;		// 当たったかどうか

	for (int nCntModelType = 0; nCntModelType < MODELTYPE_MAX; nCntModelType++)
	{// モデルの種類繰り返し
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// モデルの数繰り返し
			if (g_aModel[nCntModelType][nCntModel].bUse == true)
			{// モデルが使われている

				if (pPos->x >= g_aModel[nCntModelType][nCntModel].pos.x + g_aModel[nCntModelType][nCntModel].VtxMinModel.x &&
					pPos->x <= g_aModel[nCntModelType][nCntModel].pos.x + g_aModel[nCntModelType][nCntModel].VtxMaxModel.x)
				{// Z面の判定
					if (pPosold->z <= g_aModel[nCntModelType][nCntModel].pos.z + g_aModel[nCntModelType][nCntModel].VtxMinModel.z &&
						pPos->z >= g_aModel[nCntModelType][nCntModel].pos.z + g_aModel[nCntModelType][nCntModel].VtxMinModel.z)
					{// 手前の判定
						pPos->z = pPosold->z;
					}
					else if (pPosold->z >= g_aModel[nCntModelType][nCntModel].pos.z + (g_aModel[nCntModelType][nCntModel].VtxMaxModel.z) &&
						pPos->z <= g_aModel[nCntModelType][nCntModel].pos.z + (g_aModel[nCntModelType][nCntModel].VtxMaxModel.z))
					{// 奥の判定
						pPos->z = pPosold->z;
					}
				}
				if (pPos->z >= g_aModel[nCntModelType][nCntModel].pos.z + g_aModel[nCntModelType][nCntModel].VtxMinModel.z &&
					pPos->z <= g_aModel[nCntModelType][nCntModel].pos.z + g_aModel[nCntModelType][nCntModel].VtxMaxModel.z)
				{// X面の判定
					if (pPosold->x >= g_aModel[nCntModelType][nCntModel].pos.x + g_aModel[nCntModelType][nCntModel].VtxMaxModel.x &&
						pPos->x <= g_aModel[nCntModelType][nCntModel].pos.x + g_aModel[nCntModelType][nCntModel].VtxMaxModel.x)
					{// 右面の判定
						pPos->x = pPosold->x;
					}
					else if (pPosold->x <= g_aModel[nCntModelType][nCntModel].pos.x + (g_aModel[nCntModelType][nCntModel].VtxMinModel.x) &&
						pPos->x >= g_aModel[nCntModelType][nCntModel].pos.x + (g_aModel[nCntModelType][nCntModel].VtxMinModel.x))
					{// 左面の判定
						pPos->x = pPosold->x;
					}
				}
			}
		}
	}
	return bHit;
}

////=============================================================================
//// モデルとの当たり判定処理
////=============================================================================
//bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin)
//{
//	bool bHit = false;		// 当たったかどうか
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		if (g_aModel[nCntModel].bUse == true)
//		{// モデルが使われている
//			if (pPos->y < g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y
//				&& pPos->y > g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y)
//			{// モデルのY幅の中
//				if (pPos->z + VtxMin.z < g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z
//					&& pPos->z + VtxMax.z > g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z)
//				{// モデルのZ幅の中
//					if (pPos->x + VtxMin.x < g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x
//						&& pPos->x + VtxMax.x > g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x)
//					{// モデルのX幅の中
//						if (pPosold->x + 1 > g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x)
//						{// X幅の当たり判定
//							pPos->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x + VtxMax.x;
//							pPosold->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.x + VtxMax.x;
//							//pPos->x = pPosold->x;
//						}
//						else if (pPosold->x - 1 < g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x)
//						{
//							pPos->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x + VtxMin.x;
//							pPosold->x = g_aModel[nCntModel].pos.x + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.x + VtxMin.x;
//							//pPos->x = pPosold->x;
//						}
//
//						else if (pPosold->z + 1 > g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z)
//						{// Z幅の当たり判定
//							pPos->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z + VtxMax.z;
//							pPosold->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.z + VtxMax.z;
//							//pPos->z = pPosold->z;
//						}
//						else if (pPosold->z - 1 < g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z)
//						{
//							pPos->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z + VtxMin.z;
//							pPosold->z = g_aModel[nCntModel].pos.z + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.z + VtxMin.z;
//							//pPos->z = pPosold->z;
//						}
//
//						else if (pPosold->y >= g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y)
//						{// Y幅の当たり判定
//							pPos->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y;
//							pPosold->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMaxModel.y;
//							//pPos->y = pPosold->y;
//						}
//						else if (pPosold->y <= g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y)
//						{
//							pPos->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y;
//							pPosold->y = g_aModel[nCntModel].pos.y + g_aModelVtx[g_aModel[nCntModel].nType].VtxMinModel.y;
//							//pPos->y = pPosold->y;
//						}
//					}
//				}
//			}
//		}
//	}
//	return bHit;
//}


//=============================================================================
// モデルの取得
//=============================================================================
MODEL *GetModel(void)
{
	return &g_aModel[0][0];
}
