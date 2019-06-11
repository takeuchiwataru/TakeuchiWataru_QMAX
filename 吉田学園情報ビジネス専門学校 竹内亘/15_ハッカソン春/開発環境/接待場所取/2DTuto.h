//=============================================================================
//
// UIチュートリアル処理 [2DTUTO.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _2DTUTO_H_
#define _2DTUTO_H_

#include "main.h"
#include "scene2D.h"

#define MAX_2DTUTO (1)
//*********************************************************************
//UIチュートリアルクラスの定義
//*********************************************************************
class C2DTUTO : public CScene2D  //派生クラス
{
public:
	C2DTUTO();
	~C2DTUTO();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static C2DTUTO *Create(D3DXVECTOR3 pos,float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_2DTUTO];		// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_2DTUTO];
};
#endif
