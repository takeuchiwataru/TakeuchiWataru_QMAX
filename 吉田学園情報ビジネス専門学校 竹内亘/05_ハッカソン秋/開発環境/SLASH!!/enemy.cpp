//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "enemy.h"
#include "attackgauge.h"
#include "particle.h"
#include "input.h"
#include "bullet.h"
#include "player.h"
#include "score.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(4)				// 敵の種類
#define POLYGON_POS_X		(40)			//頂点座標Xの移動量
#define POLYGON_POS_Y		(40)			//頂点座標Yの移動量
#define COUNTER_ANIM_RESET	(2)				//アニメーションカウントリセット
#define TEX_POS_X_INIT		(0.5f)			//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT		(1.0f)			//テクスチャ座標Vの初期位置
#define TEX_LEFT			(0.0f)			//テクスチャ座標U左
#define TEX_RIGHT			(0.5f)			//テクスチャ座標U右
#define TEX_TOP				(0.0f)			//テクスチャ座標V上
#define TEX_BOT				(1.0f)			//テクスチャ座標V下
#define MOVE_ENEMY			(2.0f)			//敵の移動量
#define MOVE_X_ENEMY		(5.0f)			//敵の移動量
#define MOVE_RANDOM_ENEMY	(0.3f)			//敵の移動量

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// 頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										// 敵の情報	
int		g_nYpos = 0;
int		g_nNumEnemy;										    // 敵の総数
float   g_Randam;                                              // ランダム移動に使う
float   g_AngelX;                                              // ランダム移動に使う
float   g_AngelY;                                              // ランダム移動に使う
int     g_randCounter[MAX_ENEMY];                              // ランダム移動に使う
bool    g_randFinish[MAX_ENEMY];
D3DXVECTOR3 MovePosEnemy(0.0f, 0.0f, 0.0f);
float   g_pSpinEnemy = 0.75f;                                 // パーティクルに使用

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].nCntWall = 0;
		g_aEnemy[nCntEnemy].nCunterStop = 0;
		g_aEnemy[nCntEnemy].nRandomMove = 0;
		g_randCounter[nCntEnemy] = 0;
		g_randFinish[nCntEnemy] = false;
	}

	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\enemy000.png",
	&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy001.png",
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy002.png",
		&g_apTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy003.png",
		&g_apTextureEnemy[3]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	int nCntEnemy;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);

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
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	g_nNumEnemy = 0;	//敵の総数をクリア
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		// テクスチャの開放
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	float fMove = 1;
	float fEnemyKakudo;
	float fEnemyMoveX;
	float fEnemyMoveY;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		if (g_aEnemy[nCntEnemy].bUse == true)	//敵が使用中
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
			{//位置の更新
				VERTEX_2D *pVtx;	//頂点情報へのポインタ
									//頂点バッファをロックし頂点データのポインタを取得
				g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
				//pVtx += (nCntEnemy * 4);	//頂点データのポインタを4つ分進める	

				//頂点バッファをアンロックする
				g_pVtxBuffEnemy->Unlock();
				break;
			}
			case ENEMYSTATE_DAMAGE:
			{
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					//位置の更新
					VERTEX_2D *pVtx;	//頂点情報へのポインタ
										//頂点バッファをロックし頂点データのポインタを取得
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += (nCntEnemy * 4);	//頂点データのポインタを4つ分進める	
					//頂点カラー
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//頂点バッファをアンロックする
					g_pVtxBuffEnemy->Unlock();
				}
				break;
			}
			}
			//ジグザグ移動キャラ
			if (g_aEnemy[nCntEnemy].nType == 0)
			{
				//位置更新
				g_aEnemy[nCntEnemy].move.x = 1 * g_aEnemy[nCntEnemy].fMoveEnemyX;
				g_aEnemy[nCntEnemy].move.y = 1 * g_aEnemy[nCntEnemy].fMoveEnemyY;

				//画面外に行かないように
				if (g_aEnemy[nCntEnemy].pos.y > SCREEN_HEIGHT - POLYGON_POS_Y)
				{
					g_aEnemy[nCntEnemy].fMoveEnemyY = -(1.0f);
				}
				else if (g_aEnemy[nCntEnemy].pos.y < 0.0f + POLYGON_POS_Y)
				{
					g_aEnemy[nCntEnemy].fMoveEnemyY = 1.0f;
				}
				if (g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH - POLYGON_POS_X)
				{
					g_aEnemy[nCntEnemy].fMoveEnemyX = -(MOVE_X_ENEMY);
					g_aEnemy[nCntEnemy].nCntWall += 1;
				}
				else if (g_aEnemy[nCntEnemy].pos.x < 0 + POLYGON_POS_X)
				{
					g_aEnemy[nCntEnemy].fMoveEnemyX = MOVE_X_ENEMY;
					g_aEnemy[nCntEnemy].nCntWall += 1;
				}
				if (g_aEnemy[nCntEnemy].nCntWall > 3)
				{
					//プレイヤーの取得
					Player *pPlayer;
					pPlayer = GetPlayer();

					//プレイヤーとの距離を求める
					fEnemyMoveX = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
					fEnemyMoveY = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;
					//角度を求める
					fEnemyKakudo = atan2f(fEnemyMoveX, fEnemyMoveY);

					D3DXVECTOR3 MovePosEnemy(0.0f, 0.0f, 0.0f);
					//移動量を設定
					MovePosEnemy.x += sinf(fEnemyKakudo) * -5.0f;
					MovePosEnemy.y += cosf(fEnemyKakudo) * -5.0f;
					g_aEnemy[nCntEnemy].move = MovePosEnemy;
				}
			}
			//直進(追尾)キャラ
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{
				g_aEnemy[nCntEnemy].move.y = 1 * g_aEnemy[nCntEnemy].fMoveEnemyY;
				//プレイヤーの取得
				Player *pPlayer;
				pPlayer = GetPlayer();

				//プレイヤーとの距離を求める
				fEnemyMoveX = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
				fEnemyMoveY = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;
				//角度を求める
				fEnemyKakudo = atan2f(fEnemyMoveX, fEnemyMoveY);

				D3DXVECTOR3 MovePosEnemy(0.0f, 0.0f, 0.0f);
				//移動量を設定
				MovePosEnemy.x += sinf(fEnemyKakudo) * -5.0f;
				MovePosEnemy.y += cosf(fEnemyKakudo) * -5.0f;
				g_aEnemy[nCntEnemy].move = MovePosEnemy;


			}
			//一時停止キャラ
			else if (g_aEnemy[nCntEnemy].nType == 2)
			{
				g_aEnemy[nCntEnemy].nCunterStop++;
				g_aEnemy[nCntEnemy].move.y = 1 * g_aEnemy[nCntEnemy].fMoveEnemyY;

				//プレイヤーの取得
				Player *pPlayer;
				pPlayer = GetPlayer();

				//プレイヤーとの距離を求める
				fEnemyMoveX = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
				fEnemyMoveY = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;
				//角度を求める
				fEnemyKakudo = atan2f(fEnemyMoveX, fEnemyMoveY);

				D3DXVECTOR3 MovePosEnemy(0.0f, 0.0f, 0.0f);
				//移動量を設定
				MovePosEnemy.x += sinf(fEnemyKakudo) * -5.0f;
				MovePosEnemy.y += cosf(fEnemyKakudo) * -5.0f;
				g_aEnemy[nCntEnemy].move = MovePosEnemy;
				//一時停止
				if (g_aEnemy[nCntEnemy].nCunterStop >= rand() % 60)
				{
					g_aEnemy[nCntEnemy].move.y = 0;
					g_aEnemy[nCntEnemy].move.x = 0;
					if (g_aEnemy[nCntEnemy].nCunterStop >= 120)
					{//動き出す
						g_aEnemy[nCntEnemy].nCunterStop = 0;
					}
				}
			}
			//ランダム移動キャラ
			else if (g_aEnemy[nCntEnemy].nType == 3)
			{
				if(g_aEnemy[nCntEnemy].nRandomCnt >= 120)
				{
					g_aEnemy[nCntEnemy].nRandomCnt = 0;
				}
				if (g_aEnemy[nCntEnemy].nRandomCnt % 60 == 0 && g_randFinish[nCntEnemy] == false)
				{// まだランダム移動する
					g_AngelX = rand() % SCREEN_WIDTH + 0.0f;
					g_AngelY = rand() % SCREEN_HEIGHT + 300.0f;

					Player *pPlayer;
					pPlayer = GetPlayer();

					g_Randam = atan2f(g_AngelX - pPlayer->pos.x, g_AngelY - pPlayer->pos.y);

					if (g_Randam > D3DX_PI)
					{// 角度が円周率の値を超えてしまった
						g_Randam -= D3DX_PI * 2.0f;
					}
					if (g_Randam < -D3DX_PI)
					{// 角度が円周率の値を超えてしまった
						g_Randam += D3DX_PI * 2.0f;
					}
					g_randCounter[nCntEnemy]++;
			
					if (g_randCounter[nCntEnemy] >= rand() % 6 + 4)
					{// ランダム終わり
						g_randFinish[nCntEnemy] = true;
					}
					MovePosEnemy.x = sinf(g_Randam) * 5.0f;
					MovePosEnemy.y = cosf(g_Randam) * 5.0f;
				}
				else if (g_randFinish[nCntEnemy] == true)
				{// もうランダム移動しない
					//プレイヤーの取得
					Player *pPlayer;
					pPlayer = GetPlayer();

					//プレイヤーとの距離を求める
					fEnemyMoveX = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
					fEnemyMoveY = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;
					//角度を求める
					fEnemyKakudo = atan2f(fEnemyMoveX, fEnemyMoveY);
					//移動量を設定
					MovePosEnemy.x = sinf(fEnemyKakudo) * -5.0f;
					MovePosEnemy.y = cosf(fEnemyKakudo) * -5.0f;
					g_aEnemy[nCntEnemy].move = MovePosEnemy;
				}
				g_aEnemy[nCntEnemy].move = MovePosEnemy;
				g_aEnemy[nCntEnemy].nRandomCnt++;
			}
			//画面外に行かないように
			if (g_aEnemy[nCntEnemy].pos.y > SCREEN_HEIGHT - POLYGON_POS_Y)
			{
				g_aEnemy[nCntEnemy].pos.y = SCREEN_HEIGHT - POLYGON_POS_Y;
			}
			if (g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH - POLYGON_POS_X)
			{
				g_aEnemy[nCntEnemy].pos.x = SCREEN_WIDTH - POLYGON_POS_X;
			}
			if (g_aEnemy[nCntEnemy].pos.x < 0 + POLYGON_POS_X)
			{
				g_aEnemy[nCntEnemy].pos.x = 0 + POLYGON_POS_X;
			}

		}

		g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
		g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
		//位置の更新
		VERTEX_2D *pVtx;	//頂点情報へのポインタ
		//頂点バッファをロックし頂点データのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += (nCntEnemy * 4);
		//頂点座標更新
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		//減速
		g_aEnemy[nCntEnemy].move.x += (0.0f - g_aEnemy[nCntEnemy].move.x) * 0.25f;
		g_aEnemy[nCntEnemy].move.y += (0.0f - g_aEnemy[nCntEnemy].move.y) * 0.25f;
		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		if (g_aEnemy[nCntEnemy].bUse == true)	//敵が使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntEnemy),	//開始する頂点のインデックス
				2); //描画するプリミティブ数
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	int nCntEnemy;

	VERTEX_2D *pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし頂点データのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//敵が使用されていない
		{
			g_aEnemy[nCntEnemy].pos = pos;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			//g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = 1;
			g_aEnemy[nCntEnemy].nCntWall = 0;
			g_aEnemy[nCntEnemy].nCunterStop = 0;
			g_aEnemy[nCntEnemy].nRandomMove = 0;
			g_nNumEnemy++;		//敵の総数を加算
			g_randFinish[nCntEnemy] = false;
			g_randCounter[nCntEnemy] = 0;
			break;
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める	
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=============================================================================
// 敵のダメージ処理
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		PlaySound(SOUND_LABEL_SE_BOMB000);
		g_aEnemy[nCntEnemy].bUse = false;
		AddAttackGauge(50);
		Player *pPlayer;
		pPlayer = GetPlayer();
		pPlayer->nCounterGauge += 50;
		for (int nCntParticle = 0; nCntParticle < 90; nCntParticle++)
		{// パーティクル発生
			g_pSpinEnemy += 0.05f;
			D3DXVECTOR3 movePar(0.0f, 0.0f, 0.0f);
			movePar.x = sinf(D3DX_PI * g_pSpinEnemy) * (rand() % 20 * 0.3f);
			movePar.y = cosf(D3DX_PI * g_pSpinEnemy) * (rand() % 20 * 0.3f);
			SetParticle(g_aEnemy[nCntEnemy].pos, movePar, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 30.0f, rand() % 20);
		}
		AddScore(1000);
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;	//どのくらい表示するか		

		VERTEX_2D *pVtx;	//頂点情報へのポインタ
		//頂点バッファをロックし頂点データのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += (nCntEnemy * 4);	//頂点データのポインタを4つ分進める	
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();	
	}
}