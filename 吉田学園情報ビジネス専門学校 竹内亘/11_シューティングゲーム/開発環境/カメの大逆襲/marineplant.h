//=============================================================================
//
// 海藻処理 [marineplant.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _MARINEPLANT_H_
#define _MARINEPLANT_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MARINESIZE (25)				// 海藻の大きさ

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CMarinePlant : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	CMarinePlant();
	~CMarinePlant();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CMarinePlant * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture;	// 共有テクスチャのポインタ

	D3DXVECTOR3				m_pos;			// 位置
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nLife;
	int						m_nCounterAnim;	// アニメーションカウンター
	int						m_nPatternAnim;	// アニメションパターン

	CScene2D * m_apScene2D;
};
#endif