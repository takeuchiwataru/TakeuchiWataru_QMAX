//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_SIZE (20)				// エフェクトサイズ
#define EFFECT_LIFE (10)				// エフェクトライフ
#define EFFECT_RADIUS (15.0f)			// エフェクトの半径

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CEffect : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	CEffect();
	~CEffect();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEffect * Create(D3DXVECTOR3 pos, D3DXCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nLife;		// 表示時間
	float					m_fRadius;		// 半径
	D3DXCOLOR				m_col;			// 色
};
#endif