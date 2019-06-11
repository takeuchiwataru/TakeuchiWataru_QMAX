////=============================================================================
////
//// ライフ処理 [life.h]
//// Author : 竹内亘
////
////=============================================================================
//#ifndef _LIFE_H_
//#define _LIFE_H_
//
//#include "main.h"
//#include "scene.h"
//#include "polygon.h"
//
////*****************************************************************************
//// マクロ定義
////*****************************************************************************
//#define MAX_LIFE (3)				// 最大ライフ数
//#define LIFE_INTERVAL_SIZE (45)		// スコア間隔
//
////*****************************************************************************
//// クラスの定義
////*****************************************************************************
//class CLife : public CScene
//{
//public:
//	CLife();
//	~CLife();
//	HRESULT Init(D3DXVECTOR3 pos);
//	void Uninit(void);
//	void Update(void);
//	void Draw(void);
//	void SetLife(int life);
//	int GetLife(void);
//	void CutLife(int cut);
//
//	// 静的メンバ関数
//	static CLife * Create(D3DXVECTOR3 pos);
//
//private:
//	static CPolygon * m_apLife[MAX_LIFE];
//	int m_nLife;
//	//D3DXVECTOR3				m_pos;			// 位置
//};
//
//#endif