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
#include "UIScore.h"

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
	static CScore				*m_pScore[MAX_RANKING];
	int							m_nFadeCnt;
	bool						m_bFade;
	int							m_nCntTimer;
	static LPDIRECT3DTEXTURE9	m_pTexture;
	int							m_nCntCor;
};

#endif