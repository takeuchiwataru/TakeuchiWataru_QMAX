//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ENEMY_TEXTURE (2)		// 敵の種類
#define ENEMYSIZE (25)				// 敵の大きさ
#define BALLET_SPEED (10)			// 敵の弾のスピード

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CEnemy : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	typedef enum
	{// 敵の種類
		ENEMYTYPE_000 = 0,
		ENEMYTYPE_001,
		ENEMYTYPE_002,
		ENEMYTYPE_TEST,
		ENEMYTYPE_MAX,
	}ENEMYTYPE;

	CEnemy();
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, ENEMYTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEnemy * Create(D3DXVECTOR3 pos, ENEMYTYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	//static void HitEnemy(int nDamage);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMYTYPE_MAX];	// 共有テクスチャのポインタ

	D3DXVECTOR3				m_pos;			// 位置
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nLife;
	int						m_nCounterAnim;	// アニメーションカウンター
	int						m_nPatternAnim;	// アニメションパターン
	ENEMYTYPE               m_nType;		// 敵の種類
	float					m_fMoveX = 1.5f;
	float					m_fMoveY = 1.0f;
};
#endif