//=============================================================================
//
// リザルト処理 [result.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CResult
{
public:
	CResult();
	~CResult();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CResult * m_pResult;
};

#endif