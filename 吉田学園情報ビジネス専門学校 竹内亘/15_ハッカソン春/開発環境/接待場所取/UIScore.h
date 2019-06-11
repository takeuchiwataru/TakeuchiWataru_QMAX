//=============================================================================
//
// スコア処理 [score.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _UISCORE_H_
#define _UISCORE_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCORE	(6)		// スコアの桁数

//*********************************************************************
//スコアクラスの定義
//*********************************************************************
class CScore : public CScene //派生クラス
{
public:
	CScore(int nPriority = 6);
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		//スコア生成
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore();
	void SetColor(D3DXCOLOR col);

private:
	//メンバ変数
	CNumber			*m_apNumber[MAX_SCORE];
	D3DXVECTOR3		m_pos;
	float			m_fLength;
	float			m_fWidth, m_fHeight;	// 幅高さ

	int				m_nScore;
};

#endif