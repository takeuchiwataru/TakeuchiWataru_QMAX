//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "bullet.h"
#include "life.h"
#include "remain.h"
#include "reload.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ITEM		(3)						    // アイテムの種類
#define ITEM_TEXTURE_NAME0  "data/TEXTURE/item000.png"  // 読み込む敵のテクスチャファイル名[0番目]
#define ITEM_TEXTURE_NAME1  "data/TEXTURE/item001.png"  // 読み込む敵のテクスチャファイル名[1番目]
#define ITEM_TEXTURE_NAME2  "data/TEXTURE/item002.png"  // 読み込む敵のテクスチャファイル名[2番目]

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureItem[MAX_TYPE_ITEM] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;					// 頂点バッファへのポインタ
ITEM                    g_aItem[MAX_ITEM];                      // アイテムの情報             

//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// アイテムの情報の初期化
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// アイテムの数だけ繰り返し
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // アイテムの座標を初期化
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // アイテムの座標を初期化
		g_aItem[nCntItem].nType = 0;                             // アイテムの種類を初期化
		g_aItem[nCntItem].nCounterState = 0;                     // アイテムの状態カウンターを初期化
		g_aItem[nCntItem].bUse = false;                          // アイテムは使用していない状態にする
	}

    // テクスチャの読み込み(3つ分)
	// １体目
	D3DXCreateTextureFromFile(pDevice,
		ITEM_TEXTURE_NAME0,
		&g_apTextureItem[0]);
	// ２体目
	D3DXCreateTextureFromFile(pDevice,
		ITEM_TEXTURE_NAME1,
		&g_apTextureItem[1]);
	// ３体目
	D3DXCreateTextureFromFile(pDevice,
		ITEM_TEXTURE_NAME2,
		&g_apTextureItem[2]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// アイテムの数だけ繰り返し
	 // 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);

		// 頂点テクスチャ
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
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

	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_ITEM; nCntTex++)
	{// 敵のテクスチャファイル数だけ繰り返し
		if (g_apTextureItem[nCntTex] != NULL)
		{
			g_apTextureItem[nCntTex]->Release();
			g_apTextureItem[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// アイテムの数だけ繰り返し
		if (g_aItem[nCntItem].bUse == true)
		{// アイテムが使用されている

			Bullet *pBullet;
			pBullet = GetBullet();
			Player *pPlayer;
			pPlayer = GetPlayer();

			g_aItem[nCntItem].move.x = sinf(atan2f(pPlayer->pos.x - g_aItem[nCntItem].pos.x, pPlayer->pos.y - g_aItem[nCntItem].pos.y)) * 2.0f;
			g_aItem[nCntItem].move.y = cosf(atan2f(pPlayer->pos.x - g_aItem[nCntItem].pos.x, pPlayer->pos.y - g_aItem[nCntItem].pos.y)) * 2.0f;

			g_aItem[nCntItem].pos += g_aItem[nCntItem].move;

			for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
			{
				if (pBullet->bUse == true)
				{// 弾が使用されていたら
					if (g_aItem[nCntItem].pos.x > pBullet->pos.x - 30 && g_aItem[nCntItem].pos.x < pBullet->pos.x + 30
						&& g_aItem[nCntItem].pos.y > pBullet->pos.y - 30 && g_aItem[nCntItem].pos.y < pBullet->pos.y + 30)
					{// アイテムが斬撃にあたった
						switch (g_aItem[nCntItem].nType)
						{
						case 0:
							pPlayer->nSharp = 5;
							PlaySound(SOUND_LABEL_SE_KENMA);
							AddReload();
							break;
						case 1:
							pPlayer->nLife++;
							PlaySound(SOUND_LABEL_SE_LIFEKAIHUKU);
							AddLife(1);
							break;
						case 2:
							pPlayer->nRemain++;
							PlaySound(SOUND_LABEL_SE_ZANKIKAIHUKU);
							AddRemain();
							break;
						}
						g_aItem[nCntItem].bUse = false;

						if (g_aItem[nCntItem].pos.x > pPlayer->pos.x - 30 && g_aItem[nCntItem].pos.x < pPlayer->pos.x + 30
							&& g_aItem[nCntItem].pos.y > pPlayer->pos.y - 30 && g_aItem[nCntItem].pos.y < pPlayer->pos.y + 30)
						{
							g_aItem[nCntItem].bUse = false;
						}
					}
				}
			}
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// 敵の数だけ繰り返し
		if (g_aItem[nCntItem].bUse == true)
		{// 敵が使用されている
		 // テクスチャの読み込み
			pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].nType]);

			// 敵の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move)
{
	int nCntItem;
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// 敵の数だけ繰り返し
		if (g_aItem[nCntItem].bUse == false)
		{// 敵が使用されている
			g_aItem[nCntItem].pos = pos;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);

			// 色情報の設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}