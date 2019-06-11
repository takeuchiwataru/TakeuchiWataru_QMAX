//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"
//#include "score.h"
//#include "gold.h"
//#include "polygon.h"
//#include "rank.h"
//#include "rankinglogo.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScore;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANKING			(5)							//ランキングの数

//*********************************************************************
//タイトルクラスの定義
//*********************************************************************
class CRanking //基本クラス
{
public:
	CRanking();
	~CRanking();
	static CRanking *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//メンバ変数
private:
	//static CGold				*m_pGold;
	int							m_nFadeCnt;
	int							m_nCntTimer;
	static LPDIRECT3DTEXTURE9	m_pTexture;
	//CRank						*m_Rank;
	//CRankingLogo				*m_Logo;
	int							m_nCntCor;

	static CScore				*m_apScore[MAX_RANKING];	// 亘追加
};

#endif