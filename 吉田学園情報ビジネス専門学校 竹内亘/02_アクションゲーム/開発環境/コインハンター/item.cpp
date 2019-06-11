//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "score.h"
#include "timer.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ITEM		(3)							// アイテムの種類
#define ITEM_TEXTURE_COIN  "data/TEXTURE/coin000.png"	// テクスチャ名
#define ITEM_TEXTURE_COIN2 "data/TEXTURE/coin001.png"	// テクスチャ名
#define TEX_COIN			(4)							// コインテクスチャアニメーション数
#define TEX_ANIM_SPEED		(8)							// アニメーションスピード

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_TYPE_ITEM] = {};					// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;					// 頂点バッファへのポインタ
Item                    g_aItem[MAX_ITEM];                      // アイテムの情報
int g_nNumCoin;													// コインの総数

//=============================================================================
// アイテムの初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// アイテムの情報の初期化
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  
		g_aItem[nCntItem].nType = ITEMTYPE_COIN;
		g_aItem[nCntItem].nCounterState = 0;
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].fHeight = 0.0f;
		g_aItem[nCntItem].fWidth = 0.0f;
		g_aItem[nCntItem].bUse = false;
		g_nNumCoin = 0;
	}

	//テクスチャの読み込み
	// コイン
	D3DXCreateTextureFromFile(pDevice,ITEM_TEXTURE_COIN,&g_pTextureItem[0]);

	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_COIN2, &g_pTextureItem[1]);


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
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムの終了処理
//=============================================================================
void UninitItem(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_TYPE_ITEM; nCntTex++)
	{
		//テクスチャの開放
		if (g_pTextureItem[nCntTex] != NULL)
		{
			g_pTextureItem[nCntTex]->Release();
			g_pTextureItem[nCntTex] = NULL;
		}

		// 頂点バッファの開放
		if (g_pVtxBuffItem != NULL)
		{
			g_pVtxBuffItem->Release();
			g_pVtxBuffItem = NULL;
		}
	}
}

//=============================================================================
// アイテムの更新処理
//=============================================================================
void UpdateItem(void)
{
	VERTEX_2D *pVtx;

	int nCntItem;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].nCounterAnim++;

		if (g_aItem[nCntItem].bUse == true)
		{// アイテムが使用されている
			if (g_aItem[nCntItem].nCounterAnim % TEX_ANIM_SPEED == 0)
			{
				g_aItem[nCntItem].nPatternAnim = (g_aItem[nCntItem].nPatternAnim + 1) % TEX_COIN;

				//テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aItem[nCntItem].nPatternAnim * 0.25f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f + (g_aItem[nCntItem].nPatternAnim * 0.25f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aItem[nCntItem].nPatternAnim * 0.25f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f + (g_aItem[nCntItem].nPatternAnim * 0.25f), 1.0f);
			}
		}
		pVtx += 4;
	}
	
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムの描画処理
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
	{
		if (g_aItem[nCntItem].bUse == true)
		{// アイテムが使用されている
		 // テクスチャの読み込み
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			// 敵の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}
}

//=============================================================================
// アイテムの設定
//=============================================================================
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight, ITEMTYPE nType)
{
	int nCntItem;
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].fHeight = fHeight;
			g_aItem[nCntItem].fWidth = fWidth;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);

			// 色情報の設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;
			g_nNumCoin++;
			break;
		}
		pVtx +=4 ;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}
//=============================================================================
// アイテムの当たり判定
//=============================================================================
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove,float * fWidth, float * fHeight)
{
	int nCntItem;

	bool bGet = false;		//ゲットしたかどうか

	//アイテムの取得
	Item * pItem;
	pItem = GetItem();

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,pItem++)
	{
		if (pItem->bUse == true)
		{//アイテムが使われている
			if (pPos->x + (*fWidth / 2) > g_aItem[nCntItem].pos.x &&
				pPos->x - (*fWidth / 2) < g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth &&
				pPos->y + (*fHeight / 2) > g_aItem[nCntItem].pos.y  &&
				pPos->y - (*fHeight / 2) < g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight)
			{
				pItem->bUse = false;
				SetExplosion(g_aItem[nCntItem].pos,D3DXVECTOR3(0.0f,5.0f,0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
				PlaySound(SOUND_LABEL_SE_COINOOO);

				if (g_aItem[nCntItem].nType == ITEMTYPE_COIN)
				{
					AddScore(100);
				}

				else if (g_aItem[nCntItem].nType == ITEMTYPE_COIN2)
				{
					AddScore(500);
				}

				g_nNumCoin--;						//コインの総数を減らす
				if(g_nNumCoin <= 0)
				{//0になったら
					StopTimer();
					SetFade(MODE_GAMECLEAR);
				}
			}
		}
	}
	return bGet;
}

//=============================================================================
// アイテムの取得
//=============================================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// アイテムの総数を取得
//=============================================================================
int GetCoin(void)
{
	return g_nNumCoin;
}
