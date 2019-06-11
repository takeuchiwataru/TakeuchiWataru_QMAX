//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "particle.h"
#include "bullet.h"
#include "remain.h"
#include "attackgauge.h"
#include "input.h"
#include "reload.h"
#include "game.h"
#include "sound.h"
#include "life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_TEXTURENAME	"data/TEXTURE/player000.png"		//テクスチャ名
#define MAX_PARTTERN		(10)								//パターンの最大
#define	POLYGON_X			(0)									//ポリゴンX座標
#define POLYGON_Y			(0)									//ポリゴンY座標
#define POLYGON_COUNT		(1)									//大きくするとアニメーションが遅くなる
#define PLAYER_SIZE			(50)								//プレイヤーの大きさ
#define PLAYER_SPEED		(2)									//プレイヤーの速さ
#define PLAYER_X            (640)								//プレイヤーのX座標
#define PLAYER_Y            (560)								//プレイヤーのX座標
#define MAX_LIFE			(10)								//ライフ最大表示数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void DecisionPlayer(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTexturePlayer = NULL;    // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// 頂点バッファへのポインタ
Player                  g_player;                   // プレイヤー
int                     g_CounterAttack;            // ゲージアタック
float   g_pSpinPlayer = 0.75f;                       // パーティクルに使用

//=============================================================================
// プレイヤー初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//プレイヤーの情報の初期化
	g_player.pos = D3DXVECTOR3(640,670,0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);
	g_player.state = PLAYERSTATE_APPEAR;
	g_player.nCounterState = 120;
	g_player.nLife = PLAYER_LIFE;
	g_player.nRemain = PLAYER_REMAIN;
	g_player.nSharp = PLAYER_SHARP;
	g_player.nCounterSharp = 0;
	g_player.nCounterGauge = 0;
	g_player.bDisp = true;
	g_CounterAttack = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURENAME, &g_pTexturePlayer);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			//頂点フォーマット
								D3DPOOL_MANAGED,
								&g_pVtxBuffPlayer,
								NULL);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y + PLAYER_SIZE, 0.0f);

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

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// プレイヤー終了処理
//=============================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// プレイヤー更新処理
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{// ある程度出現状態がキープされた
			g_player.state = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_NORMAL:
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case PLAYERSTATE_DAMEGE:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{// 状態カウンターが０になった
			g_player.state = PLAYERSTATE_NORMAL;

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{// 状態カウンターが０になった
			if (g_player.nRemain > 0)
			{// 残機がまだある
				g_player.pos = D3DXVECTOR3(640, 680, 0.0f);
				g_player.state = PLAYERSTATE_APPEAR;
				g_player.nCounterState = 60;
				g_player.nLife = PLAYER_LIFE;
				g_player.nSharp = PLAYER_SHARP;
				g_player.nCounterSharp = 0;
				g_player.nCounterGauge = 0;
				g_player.bDisp = true;
				SetLife(g_player.nLife);

				// 頂点座標の更新
				pVtx[0].pos.x = g_player.pos.x - PLAYER_SIZE;
				pVtx[0].pos.y = g_player.pos.y - PLAYER_SIZE;
				pVtx[1].pos.x = g_player.pos.x + PLAYER_SIZE;
				pVtx[1].pos.y = g_player.pos.y - PLAYER_SIZE;
				pVtx[2].pos.x = g_player.pos.x - PLAYER_SIZE;
				pVtx[2].pos.y = g_player.pos.y + PLAYER_SIZE;
				pVtx[3].pos.x = g_player.pos.x + PLAYER_SIZE;
				pVtx[3].pos.y = g_player.pos.y + PLAYER_SIZE;
			}
			else if (g_player.nRemain <= 0 && g_player.state != PLAYERSTATE_MAX)
			{// 残機がもうない
				SetGameState(GAMESTATE_END);
				g_player.state = PLAYERSTATE_MAX;
			}
		}
		return;
		break;
	case PLAYERSTATE_GAUGE_MAX:

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		if (GetKeyboardPress(DIK_SPACE))
		{// SPACEキーが押され続けている
			g_CounterAttack++;
			if (g_CounterAttack >= 80)
			{
				SetParticle(g_player.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			}
		}
		if (g_CounterAttack >= 80 && GetKeyboardRelease(DIK_SPACE))
		{// ある程度押された後離された
			g_CounterAttack = 0;
			g_player.nCounterGauge = 0;
			ATTACKGAUGE *gauge;
			gauge = GetAttackGauge();
			gauge->ngauge = 0;

			g_player.state = PLAYERSTATE_NORMAL;
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			Enemy *pEnemy;
			pEnemy = GetEnemy();

			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{//敵の数だけ繰り返す
				if (pEnemy->bUse == true)	//敵が使用されている
				{
					HitEnemy(nCntEnemy, 1);
				}
			}
			PlaySound(SOUND_LABEL_SE_KAMINARI);
		}
		else if (g_CounterAttack < 80 && GetKeyboardRelease(DIK_SPACE))
		{
			g_CounterAttack = 0;
		}
		break;
	}

	if (g_player.bDisp == true)
	{
		if (g_player.nSharp > 0)
		{// 切れ味がまだある
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{//切味が0になるまで攻撃
				D3DXVECTOR3 SetPos(g_player.pos.x + 100, g_player.pos.y + 40, g_player.pos.z);
				D3DXVECTOR3 MovePos(10.0f,10.0f,0.0f);
				SetBullet(SetPos,MovePos,BULLETTYPE_PLAYER);
				g_player.nSharp--;
				CutReload(1);
				PlaySound(SOUND_LABEL_SE_ZANGEKI);
			}
		}
		else if (g_player.nSharp <= 0)
		{//0になったら切味を戻す
			g_player.nCounterSharp++;
			if (g_player.nCounterSharp % 30 == 0)
			{
				g_player.nSharp = PLAYER_SHARP;
				g_player.nCounterSharp = 0;
				AddReload();
				PlaySound(SOUND_LABEL_SE_KEN);
			}
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();

	DecisionPlayer();
}

//=============================================================================
// プレイヤー描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	if (g_player.bDisp == true)
	{
		//デバイスを取得する
		pDevice = GetDevice();

		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		if (g_player.state != PLAYERSTATE_APPEAR)
		{// 出現してしばらくたつ
		 // プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
		}
		else if (g_player.state == PLAYERSTATE_APPEAR && g_player.nCounterState % 2 == 0)
		{// 出現して間もない
		 // プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
		}
	}
}
//=============================================================================
// プレイヤーの敵接触判定
//=============================================================================
void DecisionPlayer(void)
{
	Enemy *pEnemy;
	int nCntEnemy;
	// 敵の取得
	pEnemy = GetEnemy();
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 敵の数だけ繰り返し
		if (pEnemy[nCntEnemy].bUse == true)
		{// 敵が使用されている
			if (g_player.pos.x + PLAYER_SIZE > pEnemy[nCntEnemy].pos.x - 40 && g_player.pos.x - PLAYER_SIZE	  < pEnemy[nCntEnemy].pos.x + 40
				&& g_player.pos.y + PLAYER_SIZE	 > pEnemy[nCntEnemy].pos.y - 40 && g_player.pos.y - PLAYER_SIZE < pEnemy[nCntEnemy].pos.y + 40)
			{// プレイヤーが敵に当たる
				if (g_player.bDisp == true)
				{
					HitPlayer(1);
				}
				pEnemy[nCntEnemy].bUse = false;
			}
		}

	}
}
//=============================================================================
// プレイヤーのダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{// ライフが０になったら
		if (g_player.bDisp == true)
		{// プレイヤーが描画状態だったら
			g_player.bDisp = false;
			g_player.nRemain--;
			g_player.state = PLAYERSTATE_DEATH;
			g_player.nCounterState = 60;
			CutRemain();
			for (int nCntParticle = 0; nCntParticle < 90; nCntParticle++)
			{// パーティクル発生
				g_pSpinPlayer += 0.05f;
				D3DXVECTOR3 movePar(0.0f, 0.0f, 0.0f);
				movePar.x = sinf(D3DX_PI * g_pSpinPlayer) * (rand() % 20 * 0.3f);
				movePar.y = cosf(D3DX_PI * g_pSpinPlayer) * (rand() % 20 * 0.3f);
				SetParticle(g_player.pos, movePar, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 30.0f, rand() % 20);
			}
			PlaySound(SOUND_LABEL_SE_BOMB000);
		}
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMEGE;
		g_player.nCounterState = 20;			//ダメージ状態の時間

		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffPlayer->Unlock();
	}
	CutLife(1);
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}