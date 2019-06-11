//=============================================================================
//
// プレスエンター処理 [press.h]
// Author :  竹内亘
//
//=============================================================================
#ifndef _PRESS_H_
#define _PRESS_H_

#include "main.h"
#include "scene2D.h"

#define MAX_2DLOGO (1)
#define MAX_TEX (1)

//*********************************************************************
// クラスの定義
//*********************************************************************
class CPress : public CScene2D  //派生クラス
{
public:
	CPress();
	~CPress();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPress *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEX];		// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_2DLOGO];
	D3DXCOLOR				m_col;							// 色
	int m_nTime;
	float m_fColor;

};
#endif
