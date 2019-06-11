//=============================================================================
//
// タイトル処理 [title.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"

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
	static CPlayer *GetPlayer(void);

private:
	static CPlayer			*m_pPlayer;
	int						m_nCntTimer;
};

#endif