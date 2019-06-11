//=============================================================================
//
// オブジェクト2D処理 [scene2D.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_TEXTURE_000 "data/TEXTURE/player000.png"			// プレイヤー1のテクスチャ
#define PLAYER_TEXTURE_001 "data/TEXTURE/player001.png"			// プレイヤー2のテクスチャ
#define BULEET_TEXTURE_000	"data/TEXTURE/baburu.png"			// 弾のテクスチャ
#define EXPLOSION_TEXTURE_000 "data/TEXTURE/explosion000.png"	// 爆発のテクスチャ
#define ENEMY_TEXTURE_000	"data/TEXTURE/enemy000.png"			// 敵1のテクスチャ
#define ENEMY_TEXTURE_001	"data/TEXTURE/enemy001.png"			// 敵2のテクスチャ
#define ENEMY_TEXTURE_002	"data/TEXTURE/enemy002.png"			// 敵3のテクスチャ
#define BOSS_TEXTURE_000	"data/TEXTURE/boss000.png"			// ボス1のテクスチャ
#define ITEM_TEXTURE_000	"data/TEXTURE/item000.png"			// アイテム1のテクスチャ
#define ITEM_TEXTURE_001	"data/TEXTURE/item0011.png"			// アイテム2のテクスチャ
#define ITEM_TEXTURE_002	"data/TEXTURE/item002.png"			// アイテム3のテクスチャ
#define ITEM_TEXTURE_003	"data/TEXTURE/item003.png"			// アイテム4のテクスチャ
#define MARINE_TEXTURE_000	"data/TEXTURE/marineplant.png"		// 海藻のテクスチャ
#define EFFECT_TEXTURE_000 "data/TEXTURE/effect000.jpg"			// エフェクトのテクスチャ
#define PARTICLE_TEXTURE_000 "data/TEXTURE/effect000.jpg"		// エフェクトのテクスチャ
#define TITLELOGO_TEXTURE "data/TEXTURE/title_logo.png"			// タイトルロゴのテクスチャ
#define RESULTLOGO_TEXTURE "data/TEXTURE/result_logo.png"		// リザルトロゴのテクスチャ
#define POLIGON_SIZE	(30)									// ポリゴンのサイズ

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene2D : public CScene
{// 派生させる時は : public ～を後ろにつけてやる
public:
	CScene2D(int nPriority);
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT InitAnim(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos,float fwidth,float fheight);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetExplosion(int nPatternAnim);				// 爆発アニメーション設置
	void SetPattern2(int nPatternAnim);					// 2パターンのアニメーション設置(敵...)
	void SetEffect(float fRadius);						// エフェクトの設置
	void SetParticle(int nRadius, D3DXVECTOR3 pos);	// パーティクルの設置
	void SetColor(D3DXCOLOR col);						// カラーの設置
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);

	//// 静的メンバ関数
	//static CScene2D * Create(D3DXVECTOR3 pos);	// 使ってない

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;			// 位置
	D3DXVECTOR3				m_move;			// 移動
	D3DXCOLOR				m_col;			// 色 
	float					m_rot;
	float					m_fLength;
	float					m_fAdd;
};
#endif