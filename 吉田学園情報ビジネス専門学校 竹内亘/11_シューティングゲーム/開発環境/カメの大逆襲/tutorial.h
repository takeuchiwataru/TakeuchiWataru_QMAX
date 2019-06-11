//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CTutorial
{
public:
	CTutorial();
	~CTutorial();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CScore * m_pScore;
	static CPlayer * m_pPlayer[2];
	static CRemain * m_pRemain[2];


};

#endif