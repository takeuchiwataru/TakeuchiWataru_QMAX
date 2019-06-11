//=============================================================================
//
// ゲームオーバー処理 [gameover.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"

//*********************************************************************
//チュートリアルクラスの定義
//*********************************************************************
class CGameover //基本クラス
{
public:
	CGameover();
	~CGameover();
	static CGameover *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//メンバ変数
private:
	int						m_nCntTimer;

};

#endif