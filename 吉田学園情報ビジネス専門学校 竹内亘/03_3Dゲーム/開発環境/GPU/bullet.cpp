//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "bullet.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BB_TEXTURENAME	"data/TEXTURE/bullet000.png"			// テクスチャ名
#define MAX_BULLET	(256)										// 弾の最大数
#define BULLET_POS	(3.0f)										// 弾の位置
#define MAX_POS		(4)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;					// テクスチャへのポインタ
Bullet g_aBullet[MAX_BULLET];								// 弾の情報 
//int g_nIdexShadowBillboard;								// 影の取得をするため
D3DXVECTOR3 aPos[MAX_POS];

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	int nCntBullet;

	// 弾の初期化処理
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 30;
		g_aBullet[nCntBullet].nType = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].vecA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].vecB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].vecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;	
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BB_TEXTURENAME, &g_pTextureBullet);

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BULLET_POS, BULLET_POS, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_POS, BULLET_POS, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_POS, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_POS, 0.0f, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	// テクスチャの解放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	aPos[0] = D3DXVECTOR3(-25, 0.0f, -25);
	aPos[1] = D3DXVECTOR3(-25, 0.0f, 725);
	aPos[2] = D3DXVECTOR3(725, 0.0f, 725);
	aPos[3] = D3DXVECTOR3(725, 0.0f, -25);

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//弾が使用されている
		{
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			SetPositionShadow(g_aBullet[nCntBullet].nIdexShadow,D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y -20,g_aBullet[nCntBullet].pos.z));
			SetEffect(g_aBullet[nCntBullet].pos, 5.0f, 5);

			////一定時間経過
			//g_aBullet[nCntBullet].nLife--;
			//if (g_aBullet[nCntBullet].nLife <= 0)
			//{
			//	//if (g_aBullet[nCntBullet].pos.z > 225)
			//	//{// Z面の奥
			//	//	//爆発の設定
			//	//	//SetExplosion(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//	//	SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			//	//	g_aBullet[nCntBullet].bUse = false;
			//	//	DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
			//	//}
			//	//else if (g_aBullet[nCntBullet].pos.z < -25)
			//	//{// Z面の手前
			//	//	//爆発の設定
			//	//	//SetExplosion(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//	//	SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			//	//	g_aBullet[nCntBullet].bUse = false;
			//	//	DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
			//	//}
			//	//else if (g_aBullet[nCntBullet].pos.x > 225)
			//	//{// X面の右
			//	//	//爆発の設定
			//	//	//SetExplosion(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//	//	SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			//	//	g_aBullet[nCntBullet].bUse = false;
			//	//	DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
			//	//}
			//	//else if (g_aBullet[nCntBullet].pos.x < -25)
			//	//{// X面の左
			//	//	//爆発の設定
			//	//	//SetExplosion(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//	//	SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			//	//	g_aBullet[nCntBullet].bUse = false;
			//	//	DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
			//	//}
			//}

			// 外積の当たり判定
			for (int nCnt = 0; nCnt < MAX_POS; nCnt++)
			{
				g_aBullet[nCntBullet].vecA = aPos[nCnt + 1] - aPos[nCnt];
				g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[nCnt];

				if (((g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecC.x) - (g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecC.z)) < 0)
				{
					SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
					g_aBullet[nCntBullet].bUse = false;
					DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
				}
			}

			//// 内積を利用した反射処理
			//g_aBullet[nCntBullet].vecA = aPos[1] - aPos[0];
			//g_aBullet[nCntBullet].vecB = g_aBullet[nCntBullet].pos - aPos[0];

			//if ((g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecB.x )+ (g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecB.z))
			//{

			//}

			if (g_aBullet[nCntBullet].nType == BULLETTYPE_PLAYER)
			{// プレイヤーの弾
				//敵の取得
				//Enemy * pEnemy;
				//pEnemy = GetEnemy();

				//for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				//	if (pEnemy->bUse == true)
				//	{
				//		{//当たり判定
				//			//if (g_aBullet[nCntBullet].pos.x > pEnemy->aModel[nCntEnemy].pos.x - 250 &&
				//			//	g_aBullet[nCntBullet].pos.x < pEnemy->aModel[nCntEnemy].pos.x + 250 &&
				//			//	g_aBullet[nCntBullet].pos.z < pEnemy->aModel[nCntEnemy].pos.z + 250 &&
				//			//	g_aBullet[nCntBullet].pos.z > pEnemy->aModel[nCntEnemy].pos.z - 250)
				//			if(pEnemy->aModel[nCntEnemy].pos.x > g_aBullet[nCntBullet].pos.x - 50 &&
				//				pEnemy->aModel[nCntEnemy].pos.x < g_aBullet[nCntBullet].pos.x + 50 &&
				//				pEnemy->aModel[nCntEnemy].pos.z < g_aBullet[nCntBullet].pos.z + 50 &&
				//				pEnemy->aModel[nCntEnemy].pos.z > g_aBullet[nCntBullet].pos.z - 50)
				//			{
				//				HitEnemy(nCntEnemy, 1);				//攻撃力
				//				g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
				//				//DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
				//				SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
				//			}
				//		}
				//	}
			}
			pVtx += 4;
		}

		// 頂点バッファをアンロック
		g_pVtxBuffBullet->Unlock();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	int nCntBullet;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxView, mtxTrans;				//計算用マトリックス

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
		g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
		g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
		g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
		g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
		g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
		g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
		g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
		g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBullet);

		// アルファテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBullet[nCntBullet].bUse == true)	// 弾が使用されている
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBullet,
				2);
		}

		// アルファテストを無効にする
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;

			g_aBullet[nCntBullet].rot = rot;

			g_aBullet[nCntBullet].move = move;

			g_aBullet[nCntBullet].nIdexShadow = SetShadow(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			g_aBullet[nCntBullet].bUse = true;			// 使用してる状態
			break;
		}
	}

	return nCntBullet;
}
////=============================================================================
//// ビルボードの位置を設定
////=============================================================================
//void SetPositionBillboard(int nIdexBillboard, D3DXVECTOR3 pos)
//{
//	g_aBillboard[nIdexBillboard].pos = pos;
//}

