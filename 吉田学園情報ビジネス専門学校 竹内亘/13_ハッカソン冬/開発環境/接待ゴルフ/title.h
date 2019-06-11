//=============================================================================
//
// タイトル処理 [title.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"
//#include "score.h"
//#include "gold.h"
//*********************************************************************
//タイトルクラスの定義
//*********************************************************************
class CTitle //基本クラス
{
public:
	CTitle();
	~CTitle();
	static CTitle *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int						m_nCntTimer;

};

#endif