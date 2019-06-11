//=============================================================================
//
// ランキングスコア処理 [rankingscore.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANKINGSCORE (8)		// 最大桁数
#define SCORE_INTERVAL_SIZE_X (80)	// スコア間隔X
#define SCORE_INTERVAL_SIZE_Y (110)	// スコア間隔Y
#define MAX_RANKING (5)				// ランキング分

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CRankingScore : public CScene
{
public:
	typedef enum
	{//ランキングスコアの状態
		RANKINGSCORESTATE_NONE = 0, // 更新されていない状態
		RANKINGSCORESTATE_UPDATE,   // 更新された状態
		RANKINGSCORESTATE_MAX
	}RANKINGSCORESTATE;

	CRankingScore();
	~CRankingScore();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetRankingScore(int nScore);

	// 静的メンバ関数
	static CRankingScore * Create(D3DXVECTOR3 pos);

private:
	static CNumber * m_apNumber[MAX_RANKINGSCORE][MAX_RANKING];
	int m_nRankingScore;					// スコア
	D3DXVECTOR3				m_pos;			// 位置

	D3DXCOLOR m_aCol[MAX_RANKING];			// 色
	RANKINGSCORESTATE m_State[MAX_RANKING];	// 状態
	int m_CounterCol;						// 色を切り替えるタイミング


};
#endif