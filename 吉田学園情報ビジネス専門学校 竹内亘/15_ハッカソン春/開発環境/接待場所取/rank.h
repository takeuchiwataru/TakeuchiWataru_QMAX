//=============================================================================
//
// ランク処理 [Rank.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _RANK_H_
#define _RANK_H_

#include "main.h"
#include "scene2D.h"

#define MAX_2DRANK (1)
#define MAX_RANKTEX (5)

//*********************************************************************
//UIライフクラスの定義
//*********************************************************************
class CRank : public CScene2D  //派生クラス
{
public:
	CRank();
	~CRank();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRank *Create(D3DXVECTOR3 pos,float fWidth, float fHeight,int nType);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetColor(D3DXCOLOR col);
private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_RANKTEX];	// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_2DRANK];
	D3DXCOLOR					m_Col;
	int							m_nType;
};
#endif
