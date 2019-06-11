//=============================================================================
//
// 弾の爆発処理 [explosion.cpp]
// Author :竹内亘
//
//=============================================================================
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION			(256)													// 爆発の最大数
#define EXPLOSION_TEXTURE_NAME	"data/TEXTURE/explosion000.png"								// 読み込むテクスチャ名
#define EXPLOSION_ANIM_X		((0.125f * g_aExplosion[nCntExplosion].nPatternAnim))	// 読み込むテクスチャのパターン
#define EXPLOSION_HEIGHT		(30)													// 爆発の高さ
#define EXPLOSION_WIDTH			(30)													// 爆発の幅

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];				//使用しているかどうか

//=============================================================================
// 爆発の初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//爆発の初期化
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(0.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].fHeight = EXPLOSION_HEIGHT;
		g_aExplosion[nCntExplosion].fWidth = EXPLOSION_WIDTH;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURE_NAME, &g_pTextureExplosion);

	//頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,	//確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,						//頂点フォーマット
								D3DPOOL_MANAGED,
								&g_pVtxBuffExplosion,
								NULL);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

		//テクスチャ座標の設定
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;	//頂点データを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 爆発の終了処理
//=============================================================================
void UninitExplosion(void)
{
	//テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//=============================================================================
// 爆発の更新処理
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].nCounterAnim++;

		if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)	//爆発が使用されている
			{
				//パターンNo.を更新
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;

				//テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.0f + EXPLOSION_ANIM_X, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + EXPLOSION_ANIM_X, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + EXPLOSION_ANIM_X, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + EXPLOSION_ANIM_X, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim == 0)
				{
					g_aExplosion[nCntExplosion].bUse = false;	//使用していない状態にする
				}
			}
		}
		pVtx +=  4;	//該当の位置まで進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 爆発の描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	//ポリゴンの描画
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)	//爆発が使用されている
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									4 * nCntExplosion,
									2);
		}
	}
}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col)
{
	int nCntExplosion;

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			VERTEX_2D *pVtx;	//頂点情報へのポインタ

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntExplosion * 4);	//該当の位置まで進める

			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].move = move;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);

			g_aExplosion[nCntExplosion].col = col;

			//頂点カラー
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_aExplosion[nCntExplosion].nPatternAnim = 0;
		
			////テクスチャ座標の設定
			//pVtx[0].tex = D3DXVECTOR2(0.0f + EXPLOSION_ANIM_X, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(0.125f + EXPLOSION_ANIM_X, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f + EXPLOSION_ANIM_X, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(0.125f + EXPLOSION_ANIM_X, 1.0f);
			//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//頂点バッファをアンロック
			g_pVtxBuffExplosion->Unlock();

			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;	//使用している状態
			break;
		}
	}
}