//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "effect.h"
#include "sound.h"
#include "life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_TEXTURENAME	"data/TEXTURE/player000.png"		//テクスチャ名
#define MAX_PARTTERN		(10)								//パターンの最大
#define POLYGON_COUNT		(1)									//大きくするとアニメーションが遅くなる
#define POLYGON_X			(600)								//ポリゴンのX座標
#define POLYGON_Y			(600)								//ポリゴンのY座標
#define PLAYER_SIZE			(25)								//プレイヤーの大きさ
#define PLAYER_SPEED		(2)									//プレイヤーの速さ
#define PLAYER_X            (640)								//プレイヤーのX座標
#define PLAYER_Y            (560)								//プレイヤーのX座標

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
//D3DXVECTOR3 g_posPlayer;							//プレイヤーの位置
//D3DXVECTOR3 g_movePlayer;							//プレイヤーの移動量
Player g_player;

//=============================================================================
// プレイヤー初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//プレイヤーの情報の初期化
	g_player.pos = D3DXVECTOR3(PLAYER_X, PLAYER_Y, 0.0f);
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nLife = 3;
	g_player.nCounterState = 0;
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bDisp = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, POLYGON_TEXTURENAME, &g_pTexturePlayer);

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
	pVtx[0].pos = D3DXVECTOR3(POLYGON_X - PLAYER_SIZE, POLYGON_Y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_X + PLAYER_SIZE, POLYGON_Y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POLYGON_X - PLAYER_SIZE, POLYGON_Y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_X + PLAYER_SIZE, POLYGON_Y + PLAYER_SIZE, 0.0f);

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
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMEGE:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_DAMEGE;

			//pVtx += (nCntEnemy * 4);	// 該当の位置まで進める

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
		{
			SetGameState(GAMESTATE_GAMEOVER);

			g_player.state = PLAYERSTATE_END;
		}
		return;
		break;
	}

	if (g_player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//左方向に移動
			if (GetKeyboardPress(DIK_W) == true)
			{//左上に移動
				g_player.move.x += sinf(D3DX_PI * -0.75f) * PLAYER_SPEED;
				g_player.move.y += cosf(D3DX_PI * -0.75f) * PLAYER_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//左下移動
				g_player.move.x += sinf(D3DX_PI * -0.25f) * PLAYER_SPEED;
				g_player.move.y += cosf(D3DX_PI * -0.25f) * PLAYER_SPEED;
			}
			else
			{//左移動
				g_player.move.x -= PLAYER_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//右方向に移動
			if (GetKeyboardPress(DIK_W) == true)
			{//右上移動
				g_player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//右下移動
				g_player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;
			}
			else
			{//右移動
				g_player.move.x += PLAYER_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//上に移動
			g_player.move.y += cosf(D3DX_PI * 1.0f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//下に移動
			g_player.move.y += cosf(D3DX_PI * 0.0f) * PLAYER_SPEED;
		}

		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{//弾を発射
			SetBullet(g_player.pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(-10.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(10.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(D3DX_PI * 0.75f), cosf(D3DX_PI * 0.75f), 0.0f) * 10, BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(D3DX_PI * -0.75f), cosf(D3DX_PI * -0.75f), 0.0f) * 10, BULLETTYPE_PLAYER);
			PlaySound(SOUND_LABEL_SE_SHOT001);
		}

		//else if (GetKeyboardTrigger(DIK_V) == true)
		//{//別パターンの弾を発射

		//}

		if (g_player.pos.x > SCREEN_WIDTH + PLAYER_SIZE)
		{//機体が画面外に出たら逆に
			g_player.pos.x = 0;
		}
		else if (g_player.pos.x < -PLAYER_SIZE)
		{//機体が画面外に出たら逆に
			g_player.pos.x = SCREEN_WIDTH;
		}
		else if (g_player.pos.y < -PLAYER_SIZE)
		{//機体が画面外に出たら逆に
			g_player.pos.y = SCREEN_HEIGHT;
		}
		else if (g_player.pos.y > SCREEN_HEIGHT + PLAYER_SIZE)
		{//機体が画面外に出たら逆に
			g_player.pos.y = 0;
		}

		//位置更新（移動）
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		g_player.move.x += (0.0f - g_player.move.x) * 0.15f;
		g_player.move.y += (0.0f - g_player.move.y) * 0.15f;

		//頂点座標を更新
		pVtx[0].pos.x = g_player.pos.x - PLAYER_SIZE;	// 左上のX座標を設定
		pVtx[0].pos.y = g_player.pos.y - PLAYER_SIZE;	// 左上のY座標を設定
		pVtx[1].pos.x = g_player.pos.x + PLAYER_SIZE;	// 右上のX座標を設定
		pVtx[1].pos.y = g_player.pos.y - PLAYER_SIZE;	// 右上のY座標を設定
		pVtx[2].pos.x = g_player.pos.x - PLAYER_SIZE;	// 左下のX座標を設定
		pVtx[2].pos.y = g_player.pos.y + PLAYER_SIZE;	// 左下のY座標を設定
		pVtx[3].pos.x = g_player.pos.x + PLAYER_SIZE;	// 右下のX座標を設定
		pVtx[3].pos.y = g_player.pos.y + PLAYER_SIZE;	// 右下のY座標を設定

	}
	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
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

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// プレイヤーのダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{
		SetExplosion(g_player.pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION001);
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 60;
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMEGE;
		PlaySound(SOUND_LABEL_SE_HIT002);
		g_player.nCounterState = 5;			//ダメージ状態の時間

		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//pVtx += (nCntEnemy * 4);	// 該当の位置まで進める

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