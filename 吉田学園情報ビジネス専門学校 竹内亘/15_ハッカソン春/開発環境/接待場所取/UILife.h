//=============================================================================
//
// UIライフ処理 [UILife.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UILIFE_H_
#define _UILIFE_H_

#include "main.h"
#include "scene2D.h"

#define MAX_LIFE (3)
//*********************************************************************
//UIライフクラスの定義
//*********************************************************************
class CUILife : public CScene2D  //派生クラス
{
public:
	CUILife();
	~CUILife();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUILife *Create(D3DXVECTOR3 pos,float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	static int GetnLife(void);
	void AddLife(int nLife);
	void MinusLife(int nLife);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[1];				// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_LIFE];
	static int					m_nLife;
};
#endif
