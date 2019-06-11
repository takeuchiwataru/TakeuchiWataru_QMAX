//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
#include "debugproc.h"

//*********************************************************************
//レンダリングクラスの定義
//*********************************************************************
class CRenderer //基本クラス
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

#ifdef _DEBUG
	void DrawFPS(void);
#endif
	//メンバ変数
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
#endif
};

#endif