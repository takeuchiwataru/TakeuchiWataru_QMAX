//=============================================================================
//
// UIゲージ処理 [UIGauge.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIGAUGE_H_
#define _UIGAUGE_H_

#include "main.h"
#include "scene2D.h"

#define MAX_GAUGE (3)
//*********************************************************************
//UIゲージクラスの定義
//*********************************************************************
class CUIGauge : public CScene2D  //派生クラス
{
public:
	typedef enum
	{
		GAUGESTATE_NORMAL = 0,	//通常
		GAUGESTATE_MAXGAUGE,	//ゲージが最大
	}GAUGESTATE;

	CUIGauge();
	~CUIGauge();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIGauge *Create(D3DXVECTOR3 pos,float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	static void SetGauge(float fGauge);
	static GAUGESTATE GetGaugeState(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_GAUGE];		// テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTextureLogo;				// LOGOテクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	static float				m_fVtxHeight;				// 頂点の高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_GAUGE];
	static GAUGESTATE			m_State;
};
#endif
