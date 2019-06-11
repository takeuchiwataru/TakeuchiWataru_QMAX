//=============================================================================
//
// シーン2D処理 [scene2D.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//シーン2Dクラスの定義
//*********************************************************************
class CScene2D : public CScene //派生クラス
{
public:
	CScene2D();
	~CScene2D();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTUREを割り当てる
	void SetPos(D3DXVECTOR3 pos, float fSpin, float fScale, D3DXCOLOR col);
	void SetRot(float fSpin);
	D3DXVECTOR3 Getpos(void);
	void SetCol(D3DXCOLOR col);

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	float					m_fSpin;				// 回転
	float					m_fWidth, m_fHeight;	// 幅高さ
	float					m_fLength;				// 大きさ
	float					m_fScale;				// 大きさ変更
	D3DXCOLOR				m_Col;
};

#endif