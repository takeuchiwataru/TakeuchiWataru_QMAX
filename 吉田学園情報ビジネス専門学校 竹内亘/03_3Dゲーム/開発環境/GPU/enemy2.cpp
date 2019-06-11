//=============================================================================
//
// 敵2処理 [enemy2.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "enemy2.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "player2.h"
#include "game.h"
#include "explosion.h"
#include "meshWall.h"
#include "life.h"
#include "model.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME		"data/MODEL/karasu.x"			// モデル名karasu002.x
#define MODEL_NAME1		"data/MODEL/karasu002.x"		// モデル名
#define MAX_MODEL		(256)							// モデル配置の最大数
#define MAX_MODEL_TYPE	(1)								// モデル種類の最大数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshEnemy2[ENEMYTYPE2_MAX];							// メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatEnemy2[ENEMYTYPE2_MAX];						// マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9	g_pTextureEnemy2 = NULL;						// テクスチャへのポインタ
DWORD g_nNumMatEnemy2[ENEMYTYPE2_MAX];								// マテリアル情報の数
ENEMY2 g_aEnemy2[ENEMYTYPE2_MAX][MAX_MODEL];						// モデルの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char cFN[ENEMYTYPE2_MAX][256] = { MODEL_NAME };

	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{// 敵の種類繰り返し

	 // Xファイルの読み込み
		D3DXLoadMeshFromX(cFN[nCntEnemyType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatEnemy2[nCntEnemyType],
			NULL,
			&g_nNumMatEnemy2[nCntEnemyType],
			&g_pMeshEnemy2[nCntEnemyType]);

		int nNumVtex;					// 頂点数
		DWORD sizeFvF;					// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;					// 頂点バッファへのポインタ

		// 敵の初期化
		for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
		{// 敵の数繰り返し
			g_aEnemy2[nCntEnemyType][nCntEnemy2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
			g_aEnemy2[nCntEnemyType][nCntEnemy2].nType = ENEMYTYPE2_NORMAL;
			g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = false;

			// 頂点数を取得
			nNumVtex = g_pMeshEnemy2[nCntEnemyType]->GetNumVertices();

			// 頂点フォーマットのサイズを取得
			sizeFvF = D3DXGetFVFVertexSize(g_pMeshEnemy2[nCntEnemyType]->GetFVF());

			// 頂点バッファをロック
			g_pMeshEnemy2[nCntEnemyType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x >= vtx.x)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x = vtx.x;
				}
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.y >= vtx.y)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.y = vtx.y;
				}
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z >= vtx.z)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z = vtx.z;
				}

				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x <= vtx.x)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x = vtx.x;
				}
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.y <= vtx.y)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.y = vtx.y;
				}
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z <= vtx.z)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z = vtx.z;
				}
				pVtxBuff += sizeFvF;
			}
			// 頂点バッファをアンロック
			g_pMeshEnemy2[nCntEnemyType]->UnlockVertexBuffer();
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy2(void)
{
	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{
		// メッシュの開放
		if (g_pMeshEnemy2[nCntEnemyType] != NULL)
		{
			g_pMeshEnemy2[nCntEnemyType]->Release();
			g_pMeshEnemy2[nCntEnemyType] = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatEnemy2[nCntEnemyType] != NULL)
		{
			g_pBuffMatEnemy2[nCntEnemyType]->Release();
			g_pBuffMatEnemy2[nCntEnemyType] = NULL;
		}
	}

	// テクスチャの破棄
	if (g_pTextureEnemy2 != NULL)
	{
		g_pTextureEnemy2->Release();
		g_pTextureEnemy2 = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy2(void)
{
	// カメラの取得
	Camera *pCamera;
	pCamera = GetCamera();

	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{// 敵の種類繰り返し
		for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
		{// 敵の数繰り返し
			if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == true)
			{// 敵が使われている
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].nType == ENEMYTYPE2_NORMAL)
				{
					{
						if (rand() % 2)
						{
							g_aEnemy2[nCntEnemyType][nCntEnemy2].move.x -= sinf((rand() % 314 * 2) + pCamera->rot.y) * 2;
							g_aEnemy2[nCntEnemyType][nCntEnemy2].move.z -= cosf((rand() % 314 * 2) + pCamera->rot.y) * 2;
						}
					}
				}

				// メッシュウォールの取得
				MeshWall *pMeshWall;
				pMeshWall = GetMeshWall();

				// 壁との当たり判定
				if (g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z > 725)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z = 725;
				}
				else if (g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z < -25)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z = -25;
				}
				else if (g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x > 725)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x = 725;
				}
				else if (g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x < -25)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x = -25;
				}
				else
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].move;
				}

				// 過去の位置を取得
				g_aEnemy2[nCntEnemyType][nCntEnemy2].posOld = g_aEnemy2[nCntEnemyType][nCntEnemy2].pos;

				g_aEnemy2[nCntEnemyType][nCntEnemy2].pos += g_aEnemy2[nCntEnemyType][nCntEnemy2].move;
				g_aEnemy2[nCntEnemyType][nCntEnemy2].move.x += (0.0f - g_aEnemy2[nCntEnemyType][nCntEnemy2].move.x) * 0.2f;
				g_aEnemy2[nCntEnemyType][nCntEnemy2].move.z += (0.0f - g_aEnemy2[nCntEnemyType][nCntEnemy2].move.z) * 0.2f;

				// モデルとの当たり判定
				if (CollisionModel(&g_aEnemy2[nCntEnemyType][nCntEnemy2].pos, &g_aEnemy2[nCntEnemyType][nCntEnemy2].posOld, &g_aEnemy2[nCntEnemyType][nCntEnemy2].move) == true)
				{
					g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = false;			//使用してない
				}
				else
				{
					if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == false)
					{
						g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = true;		//使用してる
					}
				}

				SetPositionShadow(g_aEnemy2[nCntEnemyType][nCntEnemy2].nIdexShadow, g_aEnemy2[nCntEnemyType][nCntEnemy2].pos);

				//// プレイヤーとの当たり判定
				//if (CollisionPlayer(&g_aEnemy2[nCntEnemyType][nCntEnemy2].pos, &g_aEnemy2[nCntEnemyType][nCntEnemy2].posOld, &g_aEnemy2[nCntEnemyType][nCntEnemy2].move) == true)
				//{
				//	g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = false;			//使用してない
				//}
				//else
				//{
				//	if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == false)
				//	{
				//		g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp = true;		//使用してる
				//	}
				//}

			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{// 敵の種類繰り返し
		for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
		{// 敵の数繰り返し
			if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == true)
			{// 敵が使用されている
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy2[nCntEnemyType][nCntEnemy2].rot.y, g_aEnemy2[nCntEnemyType][nCntEnemy2].rot.x, g_aEnemy2[nCntEnemyType][nCntEnemy2].rot.z);
				D3DXMatrixMultiply(&g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld, &g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x, g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.y, g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z);
				D3DXMatrixMultiply(&g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld, &g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld, &mtxTrans);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy2[nCntEnemyType][nCntEnemy2].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatEnemy2[g_aEnemy2[nCntEnemyType][nCntEnemy2].nType]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy2[g_aEnemy2[nCntEnemyType][nCntEnemy2].nType]; nCntMat++)
				{// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャ
					pDevice->SetTexture(0, g_pTextureEnemy2);

					// モデル(パーツ)の描画
					g_pMeshEnemy2[g_aEnemy2[nCntEnemyType][nCntEnemy2].nType]->DrawSubset(nCntMat);

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
void SetEnemy2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE2 nType)
{
	for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
	{
		if (g_aEnemy2[nType][nCntEnemy2].bDisp == false)
		{
			g_aEnemy2[nType][nCntEnemy2].pos = pos;
			g_aEnemy2[nType][nCntEnemy2].rot = D3DXVECTOR3(0, 0, 0);
			g_aEnemy2[nType][nCntEnemy2].nType = nType;
			g_aEnemy2[nType][nCntEnemy2].nIdexShadow = SetShadow(g_aEnemy2[nType][nCntEnemy2].pos, g_aEnemy2[nType][nCntEnemy2].rot);
			g_aEnemy2[nType][nCntEnemy2].bDisp = true;
			break;
		}
	}
}

//=============================================================================
// 敵の当たり判定処理
//=============================================================================
bool CollisionEnemy2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	bool bHit = false;		// 当たったかどうか

	for (int nCntEnemyType = 0; nCntEnemyType < ENEMYTYPE2_MAX; nCntEnemyType++)
	{// 敵の種類繰り返し
		for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_MODEL; nCntEnemy2++)
		{// 敵の数繰り返し
			if (g_aEnemy2[nCntEnemyType][nCntEnemy2].bDisp == true)
			{// 敵が使われている
				if (pPos->x >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x &&
					pPos->x <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x)
				{// Z面の判定
					if (pPosold->z <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z &&
						pPos->z >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z)
					{// 手前の判定
						pPos->z = pPosold->z;
						pMove->z = -20.0f;
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_KARASU);
					}
					else if (pPosold->z >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z) &&
						pPos->z <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z))
					{// 奥の判定
						pPos->z = pPosold->z;
						pMove->z = 20.0f;
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_KARASU);
					}
				}
				if (pPos->z >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.z &&
					pPos->z <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.z + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.z)
				{// X面の判定
					if (pPosold->x >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x &&
						pPos->x <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMaxModel.x)
					{// 右面の判定
						pPos->x = pPosold->x;
						pMove->x = 20.0f;
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_KARASU);

					}
					else if (pPosold->x <= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x) &&
						pPos->x >= g_aEnemy2[nCntEnemyType][nCntEnemy2].pos.x + (g_aEnemy2[nCntEnemyType][nCntEnemy2].VtxMinModel.x))
					{// 左面の判定
						pPos->x = pPosold->x;
						pMove->x = -20.0f;
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_KARASU);
					}
				}
			}		
		}
	}
	return bHit;
}

//=============================================================================
// 敵の取得
//=============================================================================
ENEMY2 *GetEnemy2(void)
{
	return &g_aEnemy2[0][0];
}

