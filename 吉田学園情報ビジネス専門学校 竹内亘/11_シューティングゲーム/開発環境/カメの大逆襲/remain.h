//=============================================================================
//
// 残機処理 [remain.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _REMAIN_H_
#define _REMAIN_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_REMAIN (2)				// 最大桁数
#define REMAIN_INTERVAL_SIZE (35)	// スコア間隔

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CRemain : public CScene
{
public:
	CRemain();
	~CRemain();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//void SetScore(int nScore);
	//int GetRemain(void);

	// 静的メンバ関数
	static CRemain * Create(D3DXVECTOR3 pos);
	void AddRemain(int nValue);


private:
	CNumber * m_apNumber[MAX_REMAIN];
	int m_nRemain;
	D3DXVECTOR3	m_pos;			// 位置

};
#endif