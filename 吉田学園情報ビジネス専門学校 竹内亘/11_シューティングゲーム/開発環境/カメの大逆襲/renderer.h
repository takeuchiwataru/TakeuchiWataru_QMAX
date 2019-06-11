//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//LPDIRECT3DDEVICE9 GetDevice(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
private:
#ifdef _DEBUG
	void DrawFPS(void);
#endif
	// メンバ変数
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	bool m_bPause;							// ポーズ中かどうか
	static CPause *m_pPause;

#ifdef _DEBUG
	LPD3DXFONT				m_pFont;		// フォントへのポインタ
	int						m_nCountFPS;	// FPSカウンタ
#endif

};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif