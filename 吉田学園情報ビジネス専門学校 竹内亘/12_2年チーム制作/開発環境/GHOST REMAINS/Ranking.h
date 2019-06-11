//=============================================================================
//
// ランキング処理 [Ranking.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "Game.h"
#include "scene.h"
#include "scene2D.h"

class CNumber;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANKING (5)		// ランキングの最大数
#define MAX_TIME (2)		// 分、秒

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CRanking
{
public:
	CRanking() {};
	~CRanking() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);

	//ステージ配置物の読み込み
	void LoadObject(void);

private:
	float m_fCntState;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CRanking_UI : public CScene
{
public:
	CRanking_UI() {};
	~CRanking_UI() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);

private:
	CNumber *m_apNumber[MAX_RANKING][MAX_TIME];
};

#endif
