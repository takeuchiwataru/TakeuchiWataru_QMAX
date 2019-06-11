//=============================================================================
//
// 動物の処理 [Animal.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "animal.h"
#include "particle.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ANIMAL_NAME0	"data/MODEL/Animal/neko.x"			// 猫のモデル名
#define ANIMAL_NAME1	"data/MODEL/Animal/inu.x"			// 犬のモデル名
#define ANIMAL_NAME2	"data/MODEL/Animal/karasu.x"        // カラスのモデル名
#define MAX_ANIMAL		(200)
#define MAX_ANIMAL_TYPE   (ANIMALTYPE_MAX)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH		    g_pMeshAnimal[MAX_ANIMAL_TYPE];	         // メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER	    g_pBuffMatAnimal[MAX_ANIMAL_TYPE];	     // マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9* g_pTextureAnimal[MAX_ANIMAL_TYPE];         // テクスチャ情報へのポインタ
DWORD			    g_nNumMatAnimal[MAX_ANIMAL_TYPE] = {};     // マテリアル情報の数
ANIMAL	            g_aAnimal[MAX_ANIMAL_TYPE][MAX_ANIMAL];  // 動物の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitAnimal(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char aXFileName[MAX_ANIMAL_TYPE][64] = { ANIMAL_NAME0,
		ANIMAL_NAME1,
		ANIMAL_NAME2,
	};

	for (int nCntType = 0; nCntType < MAX_ANIMAL_TYPE; nCntType++)
	{// 障害物の種類だけ繰り返し
	 // Xファイルの読み込み
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatAnimal[nCntType],
			NULL,
			&g_nNumMatAnimal[nCntType],
			&g_pMeshAnimal[nCntType]);

		// マテリアル情報からテクスチャを引き出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatAnimal[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatAnimal[nCntType]];
		g_pTextureAnimal[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatAnimal[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatAnimal[nCntType]; nCntMat++)
		{// 頂点数の数だけ繰り返し 
		 // マテリアル情報を読み込む
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// 環境光を初期化する
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// テクスチャ情報を初期化
			g_pTextureAnimal[nCntType][nCntMat] = NULL;

			// テクスチャの情報を読み込む
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// テクスチャのファイル名がある
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureAnimal[nCntType][nCntMat]);
			}
		}

		for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
		{// 障害物の数だけ繰り返し
		 // 障害物情報の初期化
			g_aAnimal[nCntType][nCntAnimal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 座標を初期化
			g_aAnimal[nCntType][nCntAnimal].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 向きをを初期化
			g_aAnimal[nCntType][nCntAnimal].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 移動量をを初期化
			g_aAnimal[nCntType][nCntAnimal].Type = (ANIMALTYPE)nCntType;             // 種類をを初期化
			g_aAnimal[nCntType][nCntAnimal].bUse = false;                            // 使用していない状態にする

			if (nCntAnimal == 0)
			{// 1回目だったら
				int nNumVtx;	 // 頂点数
				DWORD sizeFVF;	 // 頂点フォーマットのサイズ
				BYTE *pVtxBuff;  // 頂点バッファへのポインタ

								 // 最小値の設定
				g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// 頂点数を取得
				nNumVtx = g_pMeshAnimal[nCntType]->GetNumVertices();

				// 頂点フォーマットのサイズを取得
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshAnimal[nCntType]->GetFVF());

				// 頂点バッファをロック
				g_pMeshAnimal[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// モデルの頂点数だけ繰り返し
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

					if (vtx.x < g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.x)
					{// X座標がより小さい
						g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.x = vtx.x;
					}
					if (vtx.y < g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.y)
					{// Y座標がより小さい
						g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.y = vtx.y;
					}
					if (vtx.z < g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.z)
					{// Z座標がより小さい
						g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.z = vtx.z;
					}

					if (vtx.x > g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.x)
					{// X座標がより大きい
						g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.x = vtx.x;
					}
					if (vtx.y > g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.y)
					{// Y座標がより大きい
						g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.y = vtx.y;
					}
					if (vtx.z > g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.z)
					{// Z座標がより大きい
						g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// サイズ分ポインタを進める
				}

				// 頂点バッファをアンロック
				g_pMeshAnimal[nCntType]->UnlockVertexBuffer();
			}
			else
			{// それ以降
				g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle = g_aAnimal[nCntType][nCntAnimal - 1].vtxMaxObstacle;
				g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle = g_aAnimal[nCntType][nCntAnimal - 1].vtxMinObstacle;
			}
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitAnimal(void)
{
	for (int nCntType = 0; nCntType < MAX_ANIMAL_TYPE; nCntType++)
	{
		// メッシュの開放
		if (g_pMeshAnimal[nCntType] != NULL)
		{
			g_pMeshAnimal[nCntType]->Release();
			g_pMeshAnimal[nCntType] = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatAnimal[nCntType] != NULL)
		{
			g_pBuffMatAnimal[nCntType]->Release();
			g_pBuffMatAnimal[nCntType] = NULL;
		}
		// テクスチャの開放
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatAnimal[nCntType]; nCntMat++)
		{
			if (g_pTextureAnimal[nCntType][nCntMat] != NULL)
			{
				g_pTextureAnimal[nCntType][nCntMat]->Release();
				g_pTextureAnimal[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateAnimal(void)
{
	for (int nCntType = 0; nCntType < MAX_ANIMAL_TYPE; nCntType++)
	{// 動物の種類の数だけ繰り返し
		for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
		{// 動物の数だけ繰り返し
			if (g_aAnimal[nCntType][nCntAnimal].bUse == true)
			{// 動物が使用されている
				// 位置を移動
				g_aAnimal[nCntType][nCntAnimal].pos += g_aAnimal[nCntType][nCntAnimal].move;

				// カウンターを加算
				g_aAnimal[nCntType][nCntAnimal].nMoveCounter++;

				if (g_aAnimal[nCntType][nCntAnimal].nMoveCounter >= 120)
				{// カウンターがある程度増えた
					g_aAnimal[nCntType][nCntAnimal].move *= -1;
					g_aAnimal[nCntType][nCntAnimal].DestRot *= -1;
					g_aAnimal[nCntType][nCntAnimal].nMoveCounter = 0;
				}

				// 角度の修正
				g_aAnimal[nCntType][nCntAnimal].DiffRot.y = g_aAnimal[nCntType][nCntAnimal].DestRot.y - g_aAnimal[nCntType][nCntAnimal].rot.y;   // 現在の向きと目的の向きの差分を計算

				if (g_aAnimal[nCntType][nCntAnimal].DiffRot.y > D3DX_PI)
				{// 差分がD3DX_PIを超えた
					g_aAnimal[nCntType][nCntAnimal].DiffRot.y -= D3DX_PI * 2.0f;
				}
				if (g_aAnimal[nCntType][nCntAnimal].DiffRot.y < -D3DX_PI)
				{// 差分が-D3DX_PIを超えた
					g_aAnimal[nCntType][nCntAnimal].DiffRot.y += D3DX_PI * 2.0f;
				}

				g_aAnimal[nCntType][nCntAnimal].rot.y += g_aAnimal[nCntType][nCntAnimal].DiffRot.y * 0.1f;

				if (g_aAnimal[nCntType][nCntAnimal].rot.y > D3DX_PI)
				{// 現在の向きがD3DX_PIを超えた
					g_aAnimal[nCntType][nCntAnimal].rot.y -= D3DX_PI * 2.0f;
				}
				if (g_aAnimal[nCntType][nCntAnimal].rot.y < -D3DX_PI)
				{// 現在の向きが-D3DX_PIを超えた
					g_aAnimal[nCntType][nCntAnimal].rot.y += D3DX_PI * 2.0f;
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawAnimal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nCntType = 0; nCntType< MAX_ANIMAL_TYPE; nCntType++)
	{// 動物の種類の数だけ繰り返し
		for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
		{// 動物の数だけ繰り返し
			if (g_aAnimal[nCntType][nCntAnimal].bUse == true)
			{// 動物が使用されている
			    // ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aAnimal[nCntType][nCntAnimal].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aAnimal[nCntType][nCntAnimal].rot.y, g_aAnimal[nCntType][nCntAnimal].rot.x, g_aAnimal[nCntType][nCntAnimal].rot.z);
				D3DXMatrixMultiply(&g_aAnimal[nCntType][nCntAnimal].mtxWorld, &g_aAnimal[nCntType][nCntAnimal].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aAnimal[nCntType][nCntAnimal].pos.x, g_aAnimal[nCntType][nCntAnimal].pos.y, g_aAnimal[nCntType][nCntAnimal].pos.z);
				D3DXMatrixMultiply(&g_aAnimal[nCntType][nCntAnimal].mtxWorld, &g_aAnimal[nCntType][nCntAnimal].mtxWorld, &mtxTrans);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aAnimal[nCntType][nCntAnimal].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatAnimal[nCntType]->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_nNumMatAnimal[nCntType]; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					pDevice->SetTexture(0, g_pTextureAnimal[nCntType][nCntMat]);

					// モデル(パーツ)の描画
					g_pMeshAnimal[nCntType]->DrawSubset(nCntMat);
				}
				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=============================================================================
// 動物の設定処理
//=============================================================================
void SetAnimal(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, ANIMALTYPE Type)
{
	for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
	{// 障害物の数だけ繰り返し
		if (g_aAnimal[Type][nCntAnimal].bUse == false)
		{// 障害物が使用されていない
		 // 位置・向きの初期設定
			g_aAnimal[Type][nCntAnimal].pos = pos;
			g_aAnimal[Type][nCntAnimal].rot = rot;
			g_aAnimal[Type][nCntAnimal].DestRot = rot;
			g_aAnimal[Type][nCntAnimal].move = move;
			//　影のセット
			//g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);

			g_aAnimal[Type][nCntAnimal].bUse = true;
			break;
		}
	}

}
//=============================================================================
// 動物とシャッターが取れた時の当たり判定
//=============================================================================
void CollisionShutterAnimal(D3DXVECTOR3 pos, D3DXVECTOR3 radius)
{
	for (int nCntType = 0; nCntType < MAX_ANIMAL_TYPE; nCntType++)
	{// 動物の種類の数だけ繰り返し
		for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMAL; nCntAnimal++)
		{// 動物の数だけ繰り返し
			if (g_aAnimal[nCntType][nCntAnimal].bUse == true)
			{// 動物が使用されている
				if (g_aAnimal[nCntType][nCntAnimal].pos.x + g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.x >= pos.x - radius.x && g_aAnimal[nCntType][nCntAnimal].pos.x + g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.x <= pos.x + radius.x
					&& g_aAnimal[nCntType][nCntAnimal].pos.z + g_aAnimal[nCntType][nCntAnimal].vtxMaxObstacle.z >= pos.z - radius.z && g_aAnimal[nCntType][nCntAnimal].pos.z + g_aAnimal[nCntType][nCntAnimal].vtxMinObstacle.z <= pos.z + radius.z)
				{// シャッターの枠の中にいる
					if (g_aAnimal[nCntType][nCntAnimal].Type == ANIMALTYPE_CROW)
					{// 当たっているのがカラスだったら
						AddScore(-10);
						for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
						{
							SetParticle(D3DXVECTOR3(g_aAnimal[nCntType][nCntAnimal].pos.x, g_aAnimal[nCntType][nCntAnimal].pos.y + 20.0f, g_aAnimal[nCntType][nCntAnimal].pos.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f, 1.4f, cosf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f), 60.0f, 180);
						}
					}
					else
					{// それ以外の動物だったら
						AddScore(10);
						for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
						{
							SetParticle(D3DXVECTOR3(g_aAnimal[nCntType][nCntAnimal].pos.x, g_aAnimal[nCntType][nCntAnimal].pos.y + 20.0f, g_aAnimal[nCntType][nCntAnimal].pos.z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f, 1.4f, cosf(rand() % 628 * 0.01f - D3DX_PI) * 2.5f), 60.0f, 180);
						}
					}
				}
			}
		}
	}
}