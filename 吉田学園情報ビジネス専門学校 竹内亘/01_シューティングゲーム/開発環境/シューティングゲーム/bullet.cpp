//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author :竹内亘
//
//=============================================================================
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "player.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET			(256)								//弾の最大数
#define POLYGON_X			(1200)								//ポリゴンのX座標
#define POLYGON_Y			(350)								//ポリゴンのY座標
#define BULLET_TEXTURENAME	"data/TEXTURE/bullet000.png"		//テクスチャ名
#define BULLET_SIZE			(5)									//弾の大きさ
#define BULLET_SIZE_1		(15)								//弾の大きさ
#define ENEMY_HIT			(30)								//敵の当たり判定
#define BOSS_HIT			(40)								//ボスの当たり判定
#define PLAYER_HIT			(25)								//プレイヤーの当たり判定
#define KEISUU_DATA			(0.3f)								//係数の数字


//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//弾の位置
	D3DXVECTOR3 move;	//弾の移動
	D3DXCOLOR col;		//弾の色
	int nLife;			//弾のライフ
	BULLETTYPE type;	//弾の種類
	bool bUse;
} Bullet;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//使用しているかどうか

//=============================================================================
// 弾の初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//ポリゴン座標の設定
	g_aBullet[0].pos = D3DXVECTOR3(POLYGON_X, POLYGON_Y, 0.0f);
	g_aBullet[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].nLife = 20;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME, &g_pTextureBullet);

	//頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,	//確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,						//頂点フォーマット
								D3DPOOL_MANAGED,
								&g_pVtxBuffBullet,
								NULL);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y +BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 弾の終了処理
//=============================================================================
void UninitBullet(void)
{
	//テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//弾が使用されている
		{
			//エフェクトの設定
			SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].col, 10.0f, 10);
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

			if (g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
			}

			//一定時間経過
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//爆発の設定
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 1.0f,1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)	//プレイヤーの弾
			{
				int nCntEnemy;
				
				//敵の取得
				Enemy *pEnemy;
				pEnemy = GetEnemy();

				//ボスの取得
				Boss *pBoss;
				pBoss = GetBoss();

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{//敵が使用されている
						if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
						{
							if (g_aBullet[nCntBullet].pos.x >  pEnemy->pos.x - ENEMY_HIT
								&& g_aBullet[nCntBullet].pos.x <  pEnemy->pos.x + ENEMY_HIT
								&& g_aBullet[nCntBullet].pos.y <  pEnemy->pos.y + ENEMY_HIT
								&& g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - ENEMY_HIT)
							{
								HitEnemy(nCntEnemy, 1);				//攻撃力
								g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
							}
						}
					}

					else if (pBoss->bUse == true)
					{//ボスが使用されている
						if (g_aBullet[nCntBullet].pos.x >  pBoss->pos.x - BOSS_HIT
							&& g_aBullet[nCntBullet].pos.x <  pBoss->pos.x + BOSS_HIT
							&& g_aBullet[nCntBullet].pos.y <  pBoss->pos.y + BOSS_HIT
							&& g_aBullet[nCntBullet].pos.y > pBoss->pos.y - BOSS_HIT)
						{
							HitBoss(nCntEnemy, 1);				//攻撃力
							g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
						}
					}
				}
				//エフェクトの設定(プレイヤー弾）
				SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].col, 20, 20);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)	//敵の弾
			{
				Player *pPlayer;

				//プレイヤーの取得
				pPlayer = GetPlayer();

				if (pPlayer->bDisp == true)
				{//プレイヤーが使用されている
					if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
					{
						if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - PLAYER_HIT
							&& g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + PLAYER_HIT
							&& g_aBullet[nCntBullet].pos.y <  pPlayer->pos.y + PLAYER_HIT
							&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - PLAYER_HIT)

						{
							HitPlayer(1);						//攻撃力
							g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
						}
					}
				}
			}
		}
		pVtx +=  4;	//該当の位置まで進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 弾の描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	//ポリゴンの描画
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//弾が使用されている
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									4 * nCntBullet,
									2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	int nCntBullet;

	float fDiffAngle;	//差分
	float fDestAngle;	//目的の角度
	float fMoveAngle;	//現在の角度

	fDestAngle = 0;
	fMoveAngle = 0;

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			if (type == BULLETTYPE_PLAYER)
			{
				g_aBullet[nCntBullet].pos = pos;

				VERTEX_2D *pVtx;	//頂点情報へのポインタ

				//頂点バッファをロックし、頂点データへのポインタを取得
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntBullet * 4);	//該当の位置まで進める

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				//頂点バッファをアンロック
				g_pVtxBuffBullet->Unlock();

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
				g_aBullet[nCntBullet].bUse = true;	//使用している状態
				g_aBullet[nCntBullet].nLife = 40;	//使用している状態
				break;
			}
			else if (type == BULLETTYPE_ENEMY)
			{
				fDiffAngle = fDestAngle - fMoveAngle;

				if (fDiffAngle > D3DX_PI)
				{
					fDiffAngle -= D3DX_PI * 2.0f;
				}
				else if (fDiffAngle < D3DX_PI)
				{
					fDiffAngle += D3DX_PI * 2.0f;
				}

				fMoveAngle += fDiffAngle * KEISUU_DATA;

				if (fDiffAngle > D3DX_PI)
				{
					fDiffAngle -= D3DX_PI * 2.0f;
				}
				else if (fDiffAngle < D3DX_PI)
				{
					fDiffAngle += D3DX_PI * 2.0f;
				}

				g_aBullet[nCntBullet].pos = pos;

				VERTEX_2D *pVtx;	//頂点情報へのポインタ

				//頂点バッファをロックし、頂点データへのポインタを取得
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntBullet * 4);	//該当の位置まで進める

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_1, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_1, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_1, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_1, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_1, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_1, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_1, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_1, 0.0f);

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

				//頂点バッファをアンロック
				g_pVtxBuffBullet->Unlock();

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;
				g_aBullet[nCntBullet].bUse = true;	//使用している状態
				g_aBullet[nCntBullet].nLife = 100;	//使用している状態
				break;
			}
		}
	}
}