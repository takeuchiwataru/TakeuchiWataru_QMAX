//=============================================================================
//
// パーティクルの処理 [particle.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "particle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PARTICLE	  "data/TEXTURE/effect000.jpg"		// 読み込むテクスチャファイル名
#define PARTICLE_SIZE  (20)										// ポリゴンのサイズ
#define	MAX_PARTICLE		  (4096)							// パーティクルの最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureParticle = NULL;	 // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	 // 頂点バッファへのポインタ
PARTICLE			    g_aParticle[MAX_PARTICLE];   // パーティクルの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// パーティクルの数だけ繰り返し
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,TEXTURE_PARTICLE,&g_pTextureParticle);

	// 頂点情報の作成
	MakeVertexParticle(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitParticle(void)
{
	// テクスチャの開放
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateParticle(void)
{
	// 頂点情報の作成
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンの描画
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// パーティクルの数だけ繰り返し
		if (g_aParticle[nCntParticle].bUse == true)
		{// パーティクルが使用されている
			g_aParticle[nCntParticle].nLife--;
			g_aParticle[nCntParticle].pos += g_aParticle[nCntParticle].move;

			g_aParticle[nCntParticle].fRadius--;
			g_aParticle[nCntParticle].col.r -= 0.005f;
			g_aParticle[nCntParticle].col.g -= 0.02f;
			g_aParticle[nCntParticle].col.b -= 0.05f;
			g_aParticle[nCntParticle].col.a -= 0.005f;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{// 一定時間経過
				if (g_aParticle[nCntParticle].fRadius <= 0)
				{// 半径がなくなる
					g_aParticle[nCntParticle].bUse = false;
				}
			}

			// 頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);

			// 色情報の更新
			pVtx[0].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[1].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[2].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[3].col = D3DXCOLOR(g_aParticle[nCntParticle].col);

		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxView, mtxTrans;				// 計算用マトリックス

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aParticle[nCntParticle].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aParticle[nCntParticle].mtxWorld._11 = mtxView._11;
		g_aParticle[nCntParticle].mtxWorld._12 = mtxView._21;
		g_aParticle[nCntParticle].mtxWorld._13 = mtxView._31;
		g_aParticle[nCntParticle].mtxWorld._21 = mtxView._12;
		g_aParticle[nCntParticle].mtxWorld._22 = mtxView._22;
		g_aParticle[nCntParticle].mtxWorld._23 = mtxView._32;
		g_aParticle[nCntParticle].mtxWorld._31 = mtxView._13;
		g_aParticle[nCntParticle].mtxWorld._32 = mtxView._23;
		g_aParticle[nCntParticle].mtxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aParticle[nCntParticle].pos.x, g_aParticle[nCntParticle].pos.y, g_aParticle[nCntParticle].pos.z);
		D3DXMatrixMultiply(&g_aParticle[nCntParticle].mtxWorld, &g_aParticle[nCntParticle].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[nCntParticle].mtxWorld);

		// アルファテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);


		// αブレンディングを加算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		if (g_aParticle[nCntParticle].bUse == true)	// パーティクルが使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureParticle);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntParticle,
				2);
		}

		// アルファテストを無効にする
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		// αブレンディングを元に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	VERTEX_3D *pVtx;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// パーティクルの数だけ繰り返し
	 //   // 頂点座標
		//pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		//pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		//pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		//pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);

		pVtx[0].pos = D3DXVECTOR3(-PARTICLE_SIZE, PARTICLE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PARTICLE_SIZE, PARTICLE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-PARTICLE_SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PARTICLE_SIZE, 0.0f, 0.0f);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}

//=============================================================================
// エフェクト設定
//=============================================================================
void SetParticle(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXCOLOR col, float fRadius, int nLife)
{
	// 頂点情報の作成
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// パーティクルの数だけ繰り返し
		if (g_aParticle[nCntParticle].bUse == false)
		{// パーティクルが使用されていない
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].move = move;
			g_aParticle[nCntParticle].col = col;

			// 色情報の設定
			pVtx[0].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[1].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[2].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[3].col = D3DXCOLOR(g_aParticle[nCntParticle].col);

			g_aParticle[nCntParticle].fRadius = fRadius;

			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}