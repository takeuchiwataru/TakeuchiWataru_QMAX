//=============================================================================
//
// アイテム(モデルver)処理 [item2.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "item2.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "score.h"
#include "fade.h"
#include "timer.h"
#include "game.h"
#include "particle.h"
//#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME "data/MODEL/gomi.x"		// モデル名
#define MODEL_NAME2 "data/MODEL/PB.x"		// モデル名
#define MODEL_NAME3 "data/MODEL/kan.x"		// モデル名
#define MODEL_NAME4 "data/MODEL/book.x"		// モデル名
#define MOVE_SPEED (2.0f)					// アイテムの動くスピード
#define MAX_ITEM (256)						// アイテムの最大数
#define MAX_ITEMTYPE (4)					// アイテムの種類数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshItem2[ITEMTYPE2_MAX] = {};		// メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatItem2[ITEMTYPE2_MAX] = {};	// マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9 g_pTextureItem2 = NULL;			// テクスチャへのポインタ
DWORD g_nNumMatItem2[ITEMTYPE2_MAX];				// マテリアル情報の数
//D3DXVECTOR3 g_VtxMinModel, g_VtxMaxModel;			// アイテムの最小値,最大値
//D3DXVECTOR3 g_posModel;							// 位置
//D3DXVECTOR3 g_rotModel;							// 向き
//D3DXMATRIX g_mtxWorldModel;						// ワールドマトリックス
ITEM2 g_aItem2[ITEMTYPE2_MAX][MAX_ITEM];							// アイテムの情報
//int g_nIdexShadow;								// 影の取得をするため
int g_nNumItem;										// アイテムの総数

//=============================================================================
// 初期化処理
//=============================================================================
void InitItem2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	char cFN[ITEMTYPE2_MAX][256] = { MODEL_NAME , MODEL_NAME2, MODEL_NAME3,MODEL_NAME4};

	for (int nCntItemType = 0; nCntItemType < ITEMTYPE2_MAX; nCntItemType++)
	{// アイテムの種類繰り返し

		// Xファイルの読み込み
		D3DXLoadMeshFromX(cFN[nCntItemType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatItem2[nCntItemType],
			NULL,
			&g_nNumMatItem2[nCntItemType],
			&g_pMeshItem2[nCntItemType]);

		// 当たり判定に必要
		int nNumVtx;		// 頂点数
		DWORD sizeFVF;		// 頂点フォーマットのサイズ
		BYTE * pVtxBuff;	// 頂点バッファへのポインタ

		//アイテムの初期化
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{// アイテムの数繰り返し
			g_aItem2[nCntItemType][nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem2[nCntItemType][nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem2[nCntItemType][nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem2[nCntItemType][nCntItem].VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
			g_aItem2[nCntItemType][nCntItem].VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
			g_aItem2[nCntItemType][nCntItem].nType = ITEMTYPE2_GOMI;
			//g_aItem2[nCntItemType][nCntItem].nNumItem = MAX_ITEM;
			g_aItem2[nCntItemType][nCntItem].bUse = false;
			g_nNumItem = 0;

			// 頂点数を取得
			nNumVtx = g_pMeshItem2[nCntItemType]->GetNumVertices();

			// 頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem2[nCntItemType]->GetFVF());

			// 頂点バッファをロック
			g_pMeshItem2[nCntItemType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				if (g_aItem2[nCntItemType][nCntItem].VtxMinModel.x >= vtx.x)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMinModel.x = vtx.x;
				}
				if (g_aItem2[nCntItemType][nCntItem].VtxMinModel.y >= vtx.y)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMinModel.y = vtx.y;
				}
				if (g_aItem2[nCntItemType][nCntItem].VtxMinModel.z >= vtx.z)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMinModel.z = vtx.z;
				}

				if (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x <= vtx.x)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x = vtx.x;
				}
				if (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.y <= vtx.y)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMaxModel.y = vtx.y;
				}
				if (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z <= vtx.z)
				{
					g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff += sizeFVF;
			}

			// 頂点バッファをロック
			g_pMeshItem2[nCntItemType]->UnlockVertexBuffer();
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem2(void)
{
	for (int nCntItemType = 0; nCntItemType < ITEMTYPE2_MAX; nCntItemType++)
	{
		// メッシュの開放
		if (g_pMeshItem2[nCntItemType] != NULL)
		{
			g_pMeshItem2[nCntItemType]->Release();
			g_pMeshItem2[nCntItemType] = NULL;
		}

		// マテリアルの開放
		if (g_pBuffMatItem2[nCntItemType] != NULL)
		{
			g_pBuffMatItem2[nCntItemType]->Release();
			g_pBuffMatItem2[nCntItemType] = NULL;
		}

		// テクスチャの解放
		if (g_pTextureItem2 != NULL)
		{
			g_pTextureItem2->Release();
			g_pTextureItem2 = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem2(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nCntItemType = 0; nCntItemType < ITEMTYPE2_MAX; nCntItemType++)
	{// アイテムの種類繰り返し
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{// アイテムの数繰り返し
			if (g_aItem2[nCntItemType][nCntItem].bUse == true)
			{// アイテムが使われている

				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aItem2[nCntItemType][nCntItem].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aItem2[nCntItemType][nCntItem].rot.y, g_aItem2[nCntItemType][nCntItem].rot.x, g_aItem2[nCntItemType][nCntItem].rot.z);
				D3DXMatrixMultiply(&g_aItem2[nCntItemType][nCntItem].mtxWorld, &g_aItem2[nCntItemType][nCntItem].mtxWorld, &mtxRot);

				// 移動を反映
				D3DXMatrixTranslation(&mtxTrans, g_aItem2[nCntItemType][nCntItem].pos.x, g_aItem2[nCntItemType][nCntItem].pos.y, g_aItem2[nCntItemType][nCntItem].pos.z);
				D3DXMatrixMultiply(&g_aItem2[nCntItemType][nCntItem].mtxWorld, &g_aItem2[nCntItemType][nCntItem].mtxWorld, &mtxTrans);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aItem2[nCntItemType][nCntItem].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatItem2[g_aItem2[nCntItemType][nCntItem].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_nNumMatItem2[g_aItem2[nCntItemType][nCntItem].nType]; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					pDevice->SetTexture(0, NULL);

					// モデル(パーツ)の描画
					g_pMeshItem2[g_aItem2[nCntItemType][nCntItem].nType]->DrawSubset(nCntMat);
				}

				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// アイテムの設定
//=============================================================================
void SetItem2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, ITEMTYPE2 nType)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem2[nType][nCntItem].bUse == false)
		{
			g_aItem2[nType][nCntItem].pos = pos;
			g_aItem2[nType][nCntItem].rot = rot;
			g_aItem2[nType][nCntItem].move = move;
			g_aItem2[nType][nCntItem].nType = nType;
			g_aItem2[nType][nCntItem].bUse = true;
			break;
		}
	}
}

//=============================================================================
// アイテムの当たり判定
//=============================================================================
bool CollisionItem2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	bool bGet = false;		//ゲットしたかどうか

	for (int nCntItemType = 0; nCntItemType < ITEMTYPE2_MAX; nCntItemType++)
	{// アイテムの種類繰り返し
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{
			if (g_aItem2[nCntItemType][nCntItem].bUse == true)
			{// アイテムが使われている
				if (pPos->x >= g_aItem2[nCntItemType][nCntItem].pos.x + g_aItem2[nCntItemType][nCntItem].VtxMinModel.x &&
					pPos->x <= g_aItem2[nCntItemType][nCntItem].pos.x + g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x)
				{// Z面の判定
					if (pPosold->z <= g_aItem2[nCntItemType][nCntItem].pos.z + g_aItem2[nCntItemType][nCntItem].VtxMinModel.z &&
						pPos->z >= g_aItem2[nCntItemType][nCntItem].pos.z + g_aItem2[nCntItemType][nCntItem].VtxMinModel.z)
					{// 手前の判定
						bGet = true;
						g_aItem2[nCntItemType][nCntItem].bUse = false;
						SetParticle(g_aItem2[nCntItemType][nCntItem].pos, g_aItem2[nCntItemType][nCntItem].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);

						// アイテム別のスコア
						if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_GOMI)
						{// アイテム1
							AddScore(1000);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_BOOK)
						{// 本
							AddScore(600);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_PB)
						{// PB
							AddScore(100);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_KAN)
						{// 缶
							AddScore(200);
						}
						pPos->z = pPosold->z;
					}
					else if (pPosold->z >= g_aItem2[nCntItemType][nCntItem].pos.z + (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z) &&
						pPos->z <= g_aItem2[nCntItemType][nCntItem].pos.z + (g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z))
					{// 奥の判定
						bGet = true;
						g_aItem2[nCntItemType][nCntItem].bUse = false;
						SetParticle(g_aItem2[nCntItemType][nCntItem].pos, g_aItem2[nCntItemType][nCntItem].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);

						// アイテム別のスコア
						if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_GOMI)
						{// アイテム1
							AddScore(1000);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_BOOK)
						{// 本
							AddScore(600);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_PB)
						{// PB
							AddScore(100);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_KAN)
						{// 缶
							AddScore(200);
						}
						pPos->z = pPosold->z;
					}
				}
				if (pPos->z >= g_aItem2[nCntItemType][nCntItem].pos.z + g_aItem2[nCntItemType][nCntItem].VtxMinModel.z &&
					pPos->z <= g_aItem2[nCntItemType][nCntItem].pos.z + g_aItem2[nCntItemType][nCntItem].VtxMaxModel.z)
				{// X面の判定
					if (pPosold->x >= g_aItem2[nCntItemType][nCntItem].pos.x + g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x &&
						pPos->x <= g_aItem2[nCntItemType][nCntItem].pos.x + g_aItem2[nCntItemType][nCntItem].VtxMaxModel.x)
					{// 右面の判定
						bGet = true;
						g_aItem2[nCntItemType][nCntItem].bUse = false;
						SetParticle(g_aItem2[nCntItemType][nCntItem].pos, g_aItem2[nCntItemType][nCntItem].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);

						// アイテム別のスコア
						if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_GOMI)
						{// アイテム1
							AddScore(1000);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_BOOK)
						{// 本
							AddScore(600);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_PB)
						{// PB
							AddScore(100);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_KAN)
						{// 缶
							AddScore(200);
						}
						pPos->x = pPosold->x;
					}
					else if (pPosold->x <= g_aItem2[nCntItemType][nCntItem].pos.x + (g_aItem2[nCntItemType][nCntItem].VtxMinModel.x) &&
						pPos->x >= g_aItem2[nCntItemType][nCntItem].pos.x + (g_aItem2[nCntItemType][nCntItem].VtxMinModel.x))
					{// 左面の判定
						bGet = true;
						g_aItem2[nCntItemType][nCntItem].bUse = false;
						SetParticle(g_aItem2[nCntItemType][nCntItem].pos, g_aItem2[nCntItemType][nCntItem].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);

						// アイテム別のスコア
						if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_GOMI)
						{// アイテム1
							AddScore(1000);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_BOOK)
						{// 本
							AddScore(600);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_PB)
						{// PB
							AddScore(100);
						}
						else if (g_aItem2[nCntItemType][nCntItem].nType == ITEMTYPE2_KAN)
						{// 缶
							AddScore(200);
						}
						pPos->x = pPosold->x;
					}
				}
				g_nNumItem--;	// アイテムの数を減らす
				if (g_nNumItem <= 0)
				{// アイテムの数が0になったら
					SetGameState(GAMESTATE_GAMECLEAR);
					//SetFade(MODE_GAMECLEAR);
				}
			}
		}
	}
	return bGet;
}

//=============================================================================
// アイテムの取得
//=============================================================================
ITEM2 *GetItem2(void)
{
	return &g_aItem2[0][0];
}

//=============================================================================
// アイテムの総数を取得
//=============================================================================
int GetITEM(void)
{
	return g_nNumItem;
}


