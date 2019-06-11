//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"
//#include "bg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TUTORIALBG			(3)			//背景の数

//*********************************************************************
//チュートリアルクラスの定義
//*********************************************************************
class CTutorial //基本クラス
{
public:
	CTutorial();
	~CTutorial();
	static CTutorial *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	//メンバ変数
private:
	int							m_nType;
	//CBg							*pBg;
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TUTORIALBG];			// テクスチャポインタ
};

#endif