//=============================================================================
//
// フェード処理 [fade.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
//*****************************************************************************
//　前方宣言
//*****************************************************************************

//*********************************************************************
//フェードクラスの定義
//*********************************************************************
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// 何もしていない状態
		FADE_IN,			// フェードイン状態
		FADE_OUT,			// フェードアウト状態
		FADE_MAX
	} FADE;

	CFade(int nPriority = 7);
	~CFade();
	static CFade *Create(CManager::MODE modeNext);
	void Init(CManager::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetFade(CManager::MODE modeNext);
	static FADE GetFade(void);
	static void SetFadeINOUT(FADE fade, bool bNextMode);

	//メンバ変数
private:
	static LPDIRECT3DTEXTURE9				m_pTextureFade;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9			m_pVtxBuffFade;		// 頂点バッファへのポインタ
	static FADE								m_fade;				// フェード状態
	static CManager::MODE					m_modeNext;			// 次のモード
	static D3DXCOLOR						m_color;			// フェード色
	static bool								m_bNextMode;
};

#endif