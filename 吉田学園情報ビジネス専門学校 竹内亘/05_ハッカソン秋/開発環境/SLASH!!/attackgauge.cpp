//=============================================================================
//
// 攻撃ゲージ処理 [attackgauge.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "attackgauge.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAUGE_SIZE    (30)    // ゲージのサイズ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexAttackGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureAttackGauge = NULL;   // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAttackGauge = NULL;	// 頂点バッファへのポインタ
ATTACKGAUGE             g_AttackGauge;                  // ゲージ

//=============================================================================
// 初期化処理
//=============================================================================
void InitAttackGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_AttackGauge.pos = D3DXVECTOR3(30,30, 0.0f); // 座標を初期化
	g_AttackGauge.col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);           // 色を初期化
	g_AttackGauge.ngauge = 0;                                        // ゲージを初期化

	// 頂点情報の作成
	MakeVertexAttackGauge(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitAttackGauge(void)
{
	// 頂点バッファの破棄
	if (g_pTextureAttackGauge != NULL)
	{
		g_pTextureAttackGauge->Release();
		g_pTextureAttackGauge = NULL;
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffAttackGauge != NULL)
	{
		g_pVtxBuffAttackGauge->Release();
		g_pVtxBuffAttackGauge = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateAttackGauge(void)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffAttackGauge->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y - GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE + g_AttackGauge.ngauge, g_AttackGauge.pos.y - GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y + GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE + g_AttackGauge.ngauge, g_AttackGauge.pos.y + GAUGE_SIZE, g_AttackGauge.pos.z);

	// 頂点バッファをアンロックする
	g_pVtxBuffAttackGauge->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawAttackGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffAttackGauge, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureAttackGauge);

	// ポリゴンの描画
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexAttackGauge(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffAttackGauge,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffAttackGauge->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y - GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y - GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y + GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y + GAUGE_SIZE, g_AttackGauge.pos.z);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_AttackGauge.col;
	pVtx[1].col = g_AttackGauge.col;
	pVtx[2].col = g_AttackGauge.col;
	pVtx[3].col = g_AttackGauge.col;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffAttackGauge->Unlock();
}
//=============================================================================
// ゲージの増加
//=============================================================================
void AddAttackGauge(int gauge)
{
	g_AttackGauge.ngauge += gauge;  // ゲージを増やす
	if (g_AttackGauge.ngauge >= GAUGE_MAX)
	{
		g_AttackGauge.ngauge = GAUGE_MAX;
		Player *pPlayer;
		pPlayer = GetPlayer();
		pPlayer->state = PLAYERSTATE_GAUGE_MAX;
	}
}
//=============================================================================
// ゲージの取得
//=============================================================================
ATTACKGAUGE *GetAttackGauge(void)
{
	return &g_AttackGauge;
}