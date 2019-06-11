//=============================================================================
//
// スコア処理 [score.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCORE (8)				// 最大桁数
#define SCORE_INTERVAL_SIZE (35)	// スコア間隔

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore();
	~CScore();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//void SetScore(int nScore);
	int GetScore(void);
	void AddScore(int nValue);

	// 静的メンバ関数
	static CScore * Create(D3DXVECTOR3 pos);

private:
	CNumber * m_apNumber[MAX_SCORE];
	int m_nScore;
	D3DXVECTOR3				m_pos;			// 位置
};
#endif