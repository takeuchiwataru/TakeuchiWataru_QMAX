//=============================================================================
//
// ボス処理 [boss.cpp]
// Author :　竹内亘
//
//=============================================================================
#include "boss.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(3)								//ボスの種類
#define ENEMY_TEXTURE_NAME5 "data/TEXTURE/enemy005.png"		//敵5(ボス)のテクスチャ名
#define	BOSS_SIZE			(100)							//ボスの大きさ
#define BOSS_LIFE			(20)							//ボスの体力
#define DAMAGE_TIME			(5)								//ダメージ状態の時間

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureBoss[MAX_TYPE_ENEMY] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;					//頂点バッファへのポインタ
Boss g_aBoss[MAX_ENEMY];										//ボスの情報
int g_nNumBoss;													//ボスの総数
float g_Spin = 0.0f;											//弾の回転0

//=============================================================================
// ボスの初期化処理
//=============================================================================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBoss;

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//ボスの情報の初期化
	for(nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nType = 0;
		g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
		g_aBoss[nCntBoss].nCounterState = 0;
		g_aBoss[nCntBoss].nLife = BOSS_LIFE;
		g_aBoss[nCntBoss].nCounterAnimBoss = 0;
		g_aBoss[nCntBoss].nPartternAnimBoss = 0;
		g_aBoss[nCntBoss].bUse = false;
		g_nNumBoss = 0;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME5, &g_apTextureBoss[0]);

	//頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBoss,
									NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_SIZE, g_aBoss[nCntBoss].pos.y - BOSS_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_SIZE, g_aBoss[nCntBoss].pos.y - BOSS_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_SIZE, g_aBoss[nCntBoss].pos.y + BOSS_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_SIZE, g_aBoss[nCntBoss].pos.y + BOSS_SIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;	//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();
}

//=============================================================================
// ボスの終了処理
//=============================================================================
void UninitBoss(void)
{
	int nCntTex;

	//テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureBoss[nCntTex] != NULL)
		{
			g_apTextureBoss[nCntTex]->Release();
			g_apTextureBoss[nCntTex] = NULL;
		}
	}

	//頂点バッファの開放
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//=============================================================================
// ボスの更新処理
//=============================================================================
void UpdateBoss(void)
{
	int nCntBoss;

	//プレイヤーの取得
	Player * pPlayer;
	pPlayer = GetPlayer();

	for (nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		g_aBoss[nCntBoss].nCounterAnimBoss++;

		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntBoss * 4);	//該当の位置まで進める

		if (g_aBoss[nCntBoss].bUse == true)
		{//ボスが使用されている
			switch (g_aBoss[nCntBoss].state)
			{
			case BOSSSTATE_NORMAL:
				if (rand() % 7 == 0)
				{
					//SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_ENEMY);

					//fKakudo = atan2f(pPlayer->pos.x - g_aBoss[nCntBoss].pos.x, pPlayer->pos.y - g_aBoss[nCntBoss].pos.y);		//角度求める
					//SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(fKakudo) * 5.0f, cosf(fKakudo) * 5.0f, 0.0f), BULLETTYPE_ENEMY);
					
					//回転弾
					g_Spin += 0.1f;		//弾の回転の速さ
					D3DXVECTOR3 SetSpin(g_aBoss[nCntBoss].pos);
					D3DXVECTOR3 MoveSpin(0.0f, 0.0f, 0.0f);
					MoveSpin.x += sinf(D3DX_PI * g_Spin) * 4;
					MoveSpin.y += cosf(D3DX_PI * g_Spin) * 4;
					SetBullet(SetSpin, MoveSpin, BULLETTYPE_ENEMY);
					
				}
				break;

			case BOSSSTATE_DAMEGE:
				g_aBoss[nCntBoss].nCounterState--;

				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{
					g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;

					PlaySound(SOUND_LABEL_SE_HIT000);

					//頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;

			case BOSSSTATE_DEATH:
				g_aBoss[nCntBoss].nCounterState--;

				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{
					SetGameState(GAMESTATE_END);
					g_aBoss[nCntBoss].state = BOSSSTATE_END;
				}
				return;
				break;

			}

			if ((g_aBoss[nCntBoss].nCounterAnimBoss % 30) == 0)
			{
				g_aBoss[nCntBoss].nPartternAnimBoss = (g_aBoss[nCntBoss].nPartternAnimBoss + 1) % 2;	//パターンNo.更新

				//テクスチャの座標を更新
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_aBoss[nCntBoss].nPartternAnimBoss), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f + (0.5f * g_aBoss[nCntBoss].nPartternAnimBoss), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.5f * g_aBoss[nCntBoss].nPartternAnimBoss), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_aBoss[nCntBoss].nPartternAnimBoss), 1.0f);
			}

			//頂点バッファをアンロック
			g_pVtxBuffBoss->Unlock();
		}
	}
}

//=============================================================================
// ボスの描画処理
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for(int nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBoss[g_aBoss[nCntBoss].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBoss,
				2);
		}
	}
}

//=============================================================================
// ボスの設定
//=============================================================================
void SetBoss(D3DXVECTOR3 pos, int nType)
{
	int nCntBoss;

	for(nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)	//ボスが使用されていない
		{
			g_aBoss[nCntBoss].pos = pos;

			VERTEX_2D *pVtx;	//頂点情報へのポインタ

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntBoss * 4);	//該当の位置まで進める

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_SIZE, g_aBoss[nCntBoss].pos.y - BOSS_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_SIZE, g_aBoss[nCntBoss].pos.y - BOSS_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_SIZE, g_aBoss[nCntBoss].pos.y + BOSS_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_SIZE, g_aBoss[nCntBoss].pos.y + BOSS_SIZE, 0.0f);

			//頂点バッファをアンロック
			g_pVtxBuffBoss->Unlock();

			g_aBoss[nCntBoss].nType = nType;
			g_aBoss[nCntBoss].bUse = true;	//使用している状態
			g_nNumBoss++;
			break;
		}
	}
}

//=============================================================================
// ボスのダメージ処理
//=============================================================================
void HitBoss(int nCntBoss, int nDamage)
{
	int nValue = 0;

	g_aBoss[nCntBoss].nLife -= nDamage;

	if (g_aBoss[nCntBoss].nLife <= 0)
	{
		g_aBoss[nCntBoss].state = BOSSSTATE_DEATH;
		SetExplosion(g_aBoss[nCntBoss].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aBoss[nCntBoss].bUse = false;
		AddScore(5000);

		g_nNumBoss--;		//ボスの総数を減らす
		if (g_nNumBoss <= 0)
		{
  			SetGameState(GAMESTATE_GAMECLEAR);
		}
	}

	else
	{
		g_aBoss[nCntBoss].state = BOSSSTATE_DAMEGE;
		g_aBoss[nCntBoss].nCounterState = DAMAGE_TIME;	//ダメージ状態の時間

		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntBoss * 4);	//該当の位置まで進める

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		//頂点バッファをアンロック
		g_pVtxBuffBoss->Unlock();
	}
}

//=============================================================================
// ボスの取得
//=============================================================================
Boss *GetBoss(void)
{
	return &g_aBoss[0];
}
