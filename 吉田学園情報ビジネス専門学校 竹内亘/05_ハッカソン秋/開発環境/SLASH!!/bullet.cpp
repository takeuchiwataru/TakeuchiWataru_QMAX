//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "main.h"
#include "enemy.h" 
#include "player.h"
#include "effect.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_POS_X			(80)										//頂点座標Xの移動量
#define POLYGON_POS_Y			(120)										//頂点座標Yの移動量
#define EFFECT_COLOR_PLAYER		(D3DXCOLOR (0.3f, 0.8f, 0.8f, 0.6f))	//自機の弾のエフェクトカラー
#define EFFECT_RADIUS_PLAYER	(80.0f)									//エフェクトの半径
#define EFFECT_LIFE_PLAYER		(10)									//エフェクトのライフ
#define EFFECT_RADIUS_ENEMY		(50.0f)									//エフェクトの半径
#define EFFECT_LIFE_ENEMY		(15)									//エフェクトのライフ
#define ENEMY_HIT				(100)									//敵の当たり判定
#define PLAYER_HIT				(10)									//自機の当たり判定
#define BOSS_HIT				(100)									//敵の当たり判定

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾の情報
float g_Keisu = 1;
int g_nCntTimer = 0;
int g_nCntHomingTimer = 0;

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	g_aBullet[0].pos = D3DXVECTOR3(100, 100, 0.0f);
	g_aBullet[0].move = D3DXVECTOR3(0, 0, 0.0f);

	// 弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 40;
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;

		
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\剣.png",
		&g_pTextureBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点バッファをロックし頂点データのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
		
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		//頂点
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	// テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;


	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし頂点データのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//弾が使用されている
		{
			g_aBullet[nCntBullet].pos.y -= g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x -= g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].nLife--;
			//位置の更新
			//頂点座標更新
			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - POLYGON_POS_X;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + POLYGON_POS_X;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - POLYGON_POS_X;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + POLYGON_POS_X;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y;

			//テクスチャ
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//弾のライフが尽きたら爆発
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//自分の弾の場合
				int nCntEnemy;
				Enemy *pEnemy;
				//敵の取得
				pEnemy = GetEnemy();

				Player *pPlayer;
				//プレイヤーの取得
				pPlayer = GetPlayer();

				if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - 40)
				{
					//頂点座標
					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_X, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, 0.0f);

					//テクスチャ
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
					
				}
				if (g_aBullet[nCntBullet].pos.x - 5 < pPlayer->pos.x && g_aBullet[nCntBullet].pos.y < pPlayer->pos.y - 30)
				{
					//頂点座標
					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);


					g_aBullet[nCntBullet].move.y = -10;
				}
					if (g_aBullet[nCntBullet].pos.x < pPlayer->pos.x && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - 40)
				{
					//頂点座標
					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_X, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, 0.0f);

					//テクスチャ
					pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
					
				}

				if (g_aBullet[nCntBullet].pos.y > pPlayer->pos.y + 30)
				{
					g_aBullet[nCntBullet].move.y = 0;
				}

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{//敵の数だけ繰り返す
					if (pEnemy->bUse == true)	//敵が使用されている
					{
						if (pEnemy->pos.x - ENEMY_HIT < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + ENEMY_HIT > g_aBullet[nCntBullet].pos.x
							&& pEnemy->pos.y - ENEMY_HIT < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + ENEMY_HIT > g_aBullet[nCntBullet].pos.y)
						{//敵の範囲内に弾が当たった
							HitEnemy(nCntEnemy, 1);	//1はダメージ
						}
					}
				}
				//エフェクト描画
				SetEffect(g_aBullet[nCntBullet].pos, EFFECT_COLOR_PLAYER, EFFECT_RADIUS_PLAYER, EFFECT_LIFE_PLAYER);
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
	
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	// ポリゴンの描画
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//弾が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBullet),	//開始する頂点のインデックス
				2); //描画するプリミティブ数
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type)
{
	int nCntBullet;

	VERTEX_2D *pVtx;//頂点情報へのポインタ
					//頂点バッファをロックし頂点データのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	if (type == BULLETTYPE_PLAYER)
	{
		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{

			if (g_aBullet[nCntBullet].bUse == false)	//弾が使用されていない
			{
				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;

				//頂点座標
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				
				//頂点カラー
				pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

				g_aBullet[nCntBullet].nLife = 17;

				g_aBullet[nCntBullet].bUse = true;
				break;
			}
			pVtx += 4;	//頂点データのポインタを4つ分進める	
		}
	}
	else if (type == BULLETTYPE_ENEMY)
	{
		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{

			if (g_aBullet[nCntBullet].bUse == false)	//弾が使用されていない
			{

				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;

				//頂点座標
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);

				//頂点カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				g_aBullet[nCntBullet].nLife = 100;

				g_aBullet[nCntBullet].bUse = true;

				break;
			}
			pVtx += 4;	//頂点データのポインタを4つ分進める	
		}
	}
	else if (type == BULLETTYPE_BOSS)
	{
		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{

			if (g_aBullet[nCntBullet].bUse == false)	//弾が使用されていない
			{

				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_BOSS;

				//頂点座標
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);

				//頂点カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				g_aBullet[nCntBullet].nLife = 150;

				g_aBullet[nCntBullet].bUse = true;

				break;
			}
			pVtx += 4;	//頂点データのポインタを4つ分進める	
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
// 弾の取得
//=============================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}