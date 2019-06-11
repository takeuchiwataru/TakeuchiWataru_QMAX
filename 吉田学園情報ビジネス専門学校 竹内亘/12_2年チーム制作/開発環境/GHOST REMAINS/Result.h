//=============================================================================
//
// リザルト処理 [Result.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "Game.h"
#include "scene.h"
#include "scene2D.h"

class CNumber;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TIME (2)		// 分、秒
#define MAX_DATA (6)
#define MAX_RANKINGSCORE (5)
#define FILE_NAME ("data//TEXT//Stage.txt")

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CResult
{
public:
	CResult() {};
	~CResult() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);
	int &GetnTime(void) { return m_nTime; }
	int &GetnRankIn(void) { return m_nRankIn; }

	//ステージ配置物の読み込み
	void LoadObject(void);

private:
	static int m_nTime;
	static int m_nRankIn;
	int m_nTimeEnemy;
	int m_nCntEnemy;

};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CResult_UI : public CScene
{
public:
	CResult_UI() {};
	~CResult_UI() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);
	void	Load(void);
	void	Save(void);

private:
	CNumber *m_pNumber[MAX_TIME];
	int m_aData[MAX_DATA];
};

#endif
