//=============================================================================
//
// 爆発の処理 [explosion.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CExplosion : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	CExplosion();
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CExplosion * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nCounterAnim;	// アニメーションカウンター
	int						m_nPatternAnim;	// アニメションパターン
};
#endif