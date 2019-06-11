//=============================================================================
//
// パーティクルの処理 [particle.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PARTICLE_SIZE (20)				// エフェクトサイズ
#define PARTICLE_LIFE (10)				// エフェクトライフ
#define PARTICLE_RADIUS (15)			// エフェクトの半径

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CParticle : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	CParticle();
	~CParticle();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,int life,int radius);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CParticle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int radius);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nLife;		// 表示時間
	int					m_nRadius;			// 半径
	D3DXCOLOR				m_col;			// 色
};
#endif