//=============================================================================
//
// ボス処理 [boss.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ENEMY_TEXTURE (2)		// 敵の種類
#define BOSSSIZE (100)				// 敵の大きさ
#define BOSS_LIFE (400)				// ボスの体力

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CBoss : public CEnemy
{// 派生させる時は : public ～を後ろにつけてやる
public:
	typedef enum
	{// 敵の種類
		BOSSTYPE_000 = 0,
		BOSSTYPE_MAX,
	}BOSSTYPE;

	typedef enum
	{// プレイヤーの状態
		BOSSSTATE_NORMAL = 0,	// 通常状態
		BOSSSTATE_DAMEGE,		// ダメージ状態
		BOSSSTATE_MAX,
	}BOSSSTATE;

	CBoss();
	~CBoss();
	HRESULT Init(D3DXVECTOR3 pos, BOSSTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBoss * Create(D3DXVECTOR3 pos, BOSSTYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	void HitBoss(int nDamage);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[BOSSTYPE_MAX];	// 共有テクスチャのポインタ

	D3DXVECTOR3				m_pos;			// 位置
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nLife;
	int						m_nCounterAnim;	// アニメーションカウンター
	int						m_nPatternAnim;	// アニメションパターン
	BOSSTYPE				m_nType;		// 敵の種類
	BOSSSTATE				m_State;		// プレイヤーの状態
	int m_nCounterState;					// 状態管理のカウンター
	float					m_fMoveX = 2.0f;
	float					m_fMoveY = 1.0f;
	int						m_nTime;
};
#endif