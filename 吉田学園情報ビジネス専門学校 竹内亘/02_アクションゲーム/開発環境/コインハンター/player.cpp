//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "item.h"
#include "sound.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"

//#include "bullet.h"
//#include "explosion.h"
//#include "effect.h"
//#include "life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_TEXTURENAME	"data/TEXTURE/player000.png"		//テクスチャ名 
#define MAX_PARTTERN		(10)								//パターンの最大
#define	POLYGON_X			(0)									//ポリゴンX座標
#define POLYGON_Y			(0)									//ポリゴンY座標
#define POLYGON_COUNT		(1)									//大きくするとアニメーションが遅くなる
#define PLAYER_SIZE			(35)								//プレイヤーの大きさ
#define PLAYER_SPEED		(1)									//プレイヤーの速さ
#define PLAYER_X            (640)								//プレイヤーのX座標
#define PLAYER_Y            (560)								//プレイヤーのX座標
#define MAX_LIFE			(10)								//ライフ最大表示数
#define PLAYER_LIFE			(3)									//プレイヤーライフ
#define PLAYER_REMAIN		(3)									//プレイヤーの残機
#define PLAYER_SHARP		(5)									//プレイヤーの剣の切味
#define PLAYER_JUMPPOWER	(15)								//ジャンプ力
#define PLAYER_TEX			(4)									//半分分のテクスチャ
#define TEX_MOVE			(8)									//テクスチャの動くスピード
#define PLAYER_WIDTH		(20)								//プレイヤーの幅
#define	PLAYER_HEIGHT		(45)								//プレイヤーの高さ


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
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
	g_player.pos = D3DXVECTOR3(50,680,0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nCounterAnim = 0;
	g_player.nPatternAnim = 0;
	g_player.nDirectionMove = 0;
	g_player.col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);
	g_player.state = PLAYERSTATE_NORMALL;
	g_player.nCounterState = 0;
	g_player.fHeight = PLAYER_HEIGHT;
	g_player.fWidth = PLAYER_WIDTH;
	//g_player.nLife = PLAYER_LIFE;
	//g_player.Remain = PLAYER_REMAIN;
	//g_player.nSharp = PLAYER_SHARP;
	//g_player.nCounterSharp = 0;
	//g_player.nCounterGauge = 0;
	g_player.bDisp = true;
	g_player.bJump = false;
	g_player.pBlock = NULL;

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
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + 0, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

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
	g_player.nCounterAnim++;

	g_player.posold = g_player.pos;   // 前回の位置を保存

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//switch (g_player.state)
	//{
	//case PLAYERSTATE_NORMALL:
	//	break;

	//case PLAYERSTATE_DEATH:
	//	g_player.nCounterState--;

	//	if (g_player.pos.y < SCREEN_HEIGHT + PLAYER_SIZE)
	//	{
	//		SetGameState(GAMESTATE_GAMEOVER);
	//		g_player.state = PLAYERSTATE_END;
	//	}
	//	return;
	//	break;
	//}
	
	if (g_player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
		{//左方向に移動
			g_player.move.x -= PLAYER_SPEED;

			if (g_player.nDirectionMove == 0)
			{//左向きから右向きに
				g_player.nDirectionMove = 1;
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim = 0;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
		{//右方向に移動
			g_player.move.x += PLAYER_SPEED;

			if (g_player.nDirectionMove == 1)
			{//右向きから左向きに
				g_player.nDirectionMove = 0;
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim = 0;
			}
		}
	}

	//画面の横をループさせる
	if (g_player.pos.x > SCREEN_WIDTH + PLAYER_SIZE)
	{//プレイヤーが画面外に出たら逆に
		g_player.pos.x = 0;
	}
	else if (g_player.pos.x < -PLAYER_SIZE)
	{//プレイヤーが画面外に出たら逆に
		g_player.pos.x = SCREEN_WIDTH;
	}

	////フェードの取得
	//FADE *fade;
	//fade = GetFade();

	//if (g_player.pos.y < SCREEN_HEIGHT + PLAYER_SIZE)
	//{//プレイヤーが落ちたら
	//	SetFade(MODE_GAMEOVER);
	//}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//スペースキーが押された
		if (g_player.bJump == false)
		{
			g_player.bJump = true;					//ジャンプを使用してる
			g_player.move.y -= PLAYER_JUMPPOWER;	//ジャンプ力
			PlaySound(SOUND_LABEL_SE_JUMP000);
		}
	}

	if (g_player.bJump == false)
	{//ジャンプを使用してない
		if (g_player.move.x >= 1.0f || g_player.move.x <= -1.0f)
		{//移動してる
			g_player.nCounterAnim++;
			if ((g_player.nCounterAnim % 7) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PLAYER_TEX;
			}
		}

		else if (g_player.move.x <= 1.0f && g_player.move.x >= -1.0f)
		{//移動してない
			if (g_player.nPatternAnim % 2 != 0)
			{
				g_player.nCounterAnim++;
				if ((g_player.nCounterAnim % 7) == 0)
				{
					g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PLAYER_TEX;
				}
			}
		}
	}
	else if (g_player.bJump == true)
	{//ジャンプしてる
		if(g_player.nPatternAnim % 2 == 0)
		{
			g_player.nCounterAnim++;
			if ((g_player.nCounterAnim % 7) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PLAYER_TEX;
			}

		}
	}

	g_player.move.y += 0.5f;				//重力加算加算
	g_player.pos.x += g_player.move.x;		//横移動
	g_player.pos.y += g_player.move.y;		//落下

	//ブロックとの当たり判定
	if (CollisionBlock(&g_player.pos, &g_player.posold, &g_player.move, &g_player.fWidth, &g_player.fHeight, &g_player.pBlock) == true)
	{
		g_player.bJump = false;			//使用してない
	}
	else
	{
		if (g_player.bJump == false)
		{
			g_player.bJump = false;		//使用してる
		}
	}

	//アイテムとの当たり判定
	if (CollisionItem(&g_player.pos, &g_player.posold, &g_player.move, &g_player.fWidth, &g_player.fHeight) == true)
	{
		g_player.bDisp = false;			//使用してない
	}
	else
	{
		if (g_player.bDisp == false)
		{
			g_player.bDisp = true;		//使用してる
		}
	}


	//位置更新（移動）
	g_player.pos.x += g_player.move.x;
	g_player.move.x += (0.0f - g_player.move.x) * 0.40f;

	//if (g_player.pos.y >= 680)
	//{//応急処置で使える
	//	g_player.pos.y = 680;
	//	g_player.move.y = 0.0f;
	//	g_player.bJump = false;
	//}

	//g_player.pos.y += g_player.move.y;
	//g_player.move.y += (0.0f - g_player.move.y) * 0.15f;

	//頂点座標を更新
	//pVtx[0].pos.x = g_player.pos.x - PLAYER_SIZE;	// 左上のX座標を設定
	//pVtx[0].pos.y = g_player.pos.y - PLAYER_SIZE;	// 左上のY座標を設定
	//pVtx[1].pos.x = g_player.pos.x + PLAYER_SIZE;	// 右上のX座標を設定
	//pVtx[1].pos.y = g_player.pos.y - PLAYER_SIZE;	// 右上のY座標を設定
	//pVtx[2].pos.x = g_player.pos.x - PLAYER_SIZE;	// 左下のX座標を設定
	//pVtx[2].pos.y = g_player.pos.y + PLAYER_SIZE;	// 左下のY座標を設定
	//pVtx[3].pos.x = g_player.pos.x + PLAYER_SIZE;	// 右下のX座標を設定
	//pVtx[3].pos.y = g_player.pos.y + PLAYER_SIZE;	// 右下のY座標を設定

	//if (g_player.pBlock != NULL)
	//{
	//	if (g_player.pBlock->nType == BLOCKTYPE_BERUTOKONBEA)
	//	{
	//		//プレイヤーの位置更新
	//	}
	//}

	//頂点座標を更新
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + 0, 0.0f);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((g_player.nPatternAnim % PLAYER_TEX)* 0.25f), 0.0f + (g_player.nDirectionMove * 0.5f));
	pVtx[1].tex = D3DXVECTOR2(0.25f + ((g_player.nPatternAnim % PLAYER_TEX)* 0.25f), 0.0f + (g_player.nDirectionMove * 0.5f));
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((g_player.nPatternAnim % PLAYER_TEX)* 0.25f), 0.5f + (g_player.nDirectionMove * 0.5f));
	pVtx[3].tex = D3DXVECTOR2(0.25f + ((g_player.nPatternAnim % PLAYER_TEX)* 0.25f), 0.5f + (g_player.nDirectionMove * 0.5f));

	pVtx += 4;	//頂点データを４つ分進める

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

////=============================================================================
//// プレイヤーのダメージ処理
////=============================================================================
//void HitPlayer(int nDamage)
//{
//	g_player.nLife -= nDamage;
//
//	if (g_player.nLife <= 0)
//	{
//		//SetExplosion(g_player.pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
//		g_player.bDisp = false;
//		g_player.state = PLAYERSTATE_DEATH;
//		g_player.nCounterState = 60;
//	}
//
//	else
//	{
//		g_player.state = PLAYERSTATE_DAMEGE;
//		g_player.nCounterState = 5;			//ダメージ状態の時間
//
//		VERTEX_2D *pVtx;	//頂点情報へのポインタ
//
//		//頂点バッファをロックし、頂点データへのポインタを取得
//		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
//
//		//pVtx += (nCntEnemy * 4);	// 該当の位置まで進める
//
//		//頂点カラー
//		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//
//		//頂点バッファをアンロック
//		g_pVtxBuffPlayer->Unlock();
//	}
//	//CutLife(1);
//}
//
//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}