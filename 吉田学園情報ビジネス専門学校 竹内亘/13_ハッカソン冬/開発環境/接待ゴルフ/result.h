//=============================================================================
//
// リザルト処理 [result.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"

//*********************************************************************
//リザルトクラスの定義
//*********************************************************************
class CResult //基本クラス
{
public:
	CResult();
	~CResult();
	static CResult *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//メンバ変数
private:
	int						m_nCntTimer;
};

#endif