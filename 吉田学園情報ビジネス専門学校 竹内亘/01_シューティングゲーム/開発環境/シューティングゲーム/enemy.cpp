//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author :　竹内亘
//
//=============================================================================
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "sound.h"
#include "player.h"
#include "boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(7)								//敵の種類
#define ENEMY_TEXTURE_NAME0	"data/TEXTURE/enemy000.png"		//敵0のテクスチャ名
#define ENEMY_TEXTURE_NAME1	"data/TEXTURE/enemy001.png"		//敵1のテクスチャ名
#define ENEMY_TEXTURE_NAME2	"data/TEXTURE/enemy002.png"		//敵2のテクスチャ名
#define ENEMY_TEXTURE_NAME3	"data/TEXTURE/enemy003.png"		//敵3のテクスチャ名
#define ENEMY_TEXTURE_NAME4 "data/TEXTURE/enemy004.png"		//敵4のテクスチャ名
#define	ENEMY_SIZE			(25)							//敵の大きさ
#define ENEMY_LIFE			(3)								//敵の体力
#define DAMAGE_TIME			(5)								//ダメージ状態の時間

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										//敵の情報
int g_nNumEnemy;												//敵の総数

//=============================================================================
// 敵の初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//敵の情報の初期化
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = ENEMY_LIFE;
		g_aEnemy[nCntEnemy].nCounterAnimEnemy = 0;
		g_aEnemy[nCntEnemy].nPartternAnimEnemy = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_nNumEnemy = 0;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME0, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME1, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME2, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME3, &g_apTextureEnemy[3]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME4, &g_apTextureEnemy[4]);

	//頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵の終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	//テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	//頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 敵の更新処理
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;

	float fKakudo;		//角度用の変数

	//プレイヤーの取得
	Player * pPlayer;
	pPlayer = GetPlayer();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].nCounterAnimEnemy++;

		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy * 4);	//該当の位置まで進める

		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				if (rand() % 300 == 0)
				{
					//SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_ENEMY);

					fKakudo = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);		//角度求める
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(fKakudo) * 5.0f, cosf(fKakudo) * 5.0f, 0.0f), BULLETTYPE_ENEMY);
				}
				break;

			case ENEMYSTATE_DAMEGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					PlaySound(SOUND_LABEL_SE_HIT000);

					//頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}

			if ((g_aEnemy[nCntEnemy].nCounterAnimEnemy % 30) == 0)
			{
				g_aEnemy[nCntEnemy].nPartternAnimEnemy = (g_aEnemy[nCntEnemy].nPartternAnimEnemy + 1) % 2;	//パターンNo.更新

				//テクスチャの座標を更新
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_aEnemy[nCntEnemy].nPartternAnimEnemy), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f + (0.5f * g_aEnemy[nCntEnemy].nPartternAnimEnemy), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.5f * g_aEnemy[nCntEnemy].nPartternAnimEnemy), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_aEnemy[nCntEnemy].nPartternAnimEnemy), 1.0f);
			}

			//頂点バッファをアンロック
			g_pVtxBuffEnemy->Unlock();
		}
	}
}

//=============================================================================
// 敵の描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntEnemy,
				2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//敵が使用されていない
		{
			g_aEnemy[nCntEnemy].pos = pos;

			VERTEX_2D *pVtx;	//頂点情報へのポインタ

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntEnemy * 4);	//該当の位置まで進める

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);

			//頂点バッファをアンロック
			g_pVtxBuffEnemy->Unlock();

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;	//使用している状態
			g_nNumEnemy++;
			break;
		}
	}
}

//=============================================================================
// 敵のダメージ処理
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	int nValue = 0;

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aEnemy[nCntEnemy].bUse = false;
		AddScore(2000);

		g_nNumEnemy--;		//敵の総数を減らす
		if (g_nNumEnemy <= 0)
		{
			//StopSound(SOUND_LABEL_BGM002);
			//SetGameState(GAMESTATE_END);

			//ボスの取得
			Boss * pBoss;
			pBoss = GetBoss();

			SetBoss(D3DXVECTOR3(600, 300, 0.0f), 0);

			//ボスBGM
			//PlaySound(SOUND_LABEL_BGM003);
		}
	}

	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;
		g_aEnemy[nCntEnemy].nCounterState = DAMAGE_TIME;	//ダメージ状態の時間

		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy * 4);	//該当の位置まで進める

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		//頂点バッファをアンロック
		g_pVtxBuffEnemy->Unlock();
	}
}

//=============================================================================
// 敵の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
