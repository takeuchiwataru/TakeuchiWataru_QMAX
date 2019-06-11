//=============================================================================
//
// デバッグプロシージャ処理 [debugproc.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"
//#include "varargs.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_CHAR	(20480)
//*********************************************************************
//ライトクラスの定義
//*********************************************************************
class CDebugProc //基本クラス
{
public:
	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);
	void Update(void);
	static void Print(int Num, char *fmt, ...);
	static void Draw(void);
	//メンバ変数
private:
	static LPD3DXFONT	m_pFont;			// フォントへのポインタ
	static char			m_aStr[MAX_CHAR];
};

#endif
