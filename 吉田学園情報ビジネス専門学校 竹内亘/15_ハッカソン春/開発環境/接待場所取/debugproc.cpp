//=============================================================================
//
// デバッグ処理 [light.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[MAX_CHAR] = {};

//--------------------------------------------
//デバッグクラス コンストラクタ
//--------------------------------------------
CDebugProc::CDebugProc()
{
}

//--------------------------------------------
//デバッグクラス デストラクタ
//--------------------------------------------
CDebugProc::~CDebugProc()
{
}
//=============================================================================
// デバッグの初期化処理
//=============================================================================
void CDebugProc::Init(void)
{
#ifdef _DEBUG

	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif
}

//=============================================================================
// デバッグの終了処理
//=============================================================================
void CDebugProc::Uninit(void)
{
#ifdef _DEBUG

	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif
}

//=============================================================================
// デバッグの更新処理
//=============================================================================
void CDebugProc::Update(void)
{
}

//=============================================================================
// プリント関数
//=============================================================================
void CDebugProc::Print(int Num, char * fmt, ...)
{
#ifdef _DEBUG
	// *fmt 任意の数の文字列が格納されている
	va_list list;
	char text[MAX_CHAR];
	text[0] = '\0';
	va_start(list, fmt);
	//テキストの書き込み
	vsprintf(text,fmt,list);

	if (Num == 1)
	{
		// 大事　後ろにつなげる
		strcat(&m_aStr[0], &text[0]);
	}
	else if (Num == 0)
	{
		// 上書き
		wsprintf(&m_aStr[0], &text[0]);
	}
	va_end(list);
#endif
}

//=============================================================================
// 描画処理	関数
//=============================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// テキスト描画
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
#endif

}

