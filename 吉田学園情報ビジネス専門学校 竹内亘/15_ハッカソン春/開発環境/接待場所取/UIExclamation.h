//=============================================================================
//
// UIエンター処理 [UIExclamation.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIEXCLAMATION_H_
#define _UIEXCLAMATION_H_

#include "main.h"
#include "scene2D.h"

#define MAX_EXCLAMATION (1)

//*********************************************************************
//UIエンタークラスの定義
//*********************************************************************
class CUIExclamation : public CScene2D  //派生クラス
{
public:
	typedef enum
	{
		ENEMYPOS_CENTER = 0,
		ENEMYPOS_RIGHT,
		ENEMYPOS_LEFT,
	}ENEMYPOS;

	CUIExclamation();
	~CUIExclamation();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIExclamation *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, ENEMYPOS type);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetItemBool(bool bGetItem);
private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_EXCLAMATION];	// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;							// 位置
	D3DXVECTOR3					m_move;							// 移動量
	D3DXVECTOR3					m_posold;						// 前回の位置
	float						m_fWidth, m_fHeight;			// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;					// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_EXCLAMATION];	// 2Dポリゴンへのポインタ
	int							m_nItem;						// 獲得数
	int							m_nColorFlash;					// 点滅カウント
	D3DXCOLOR					m_Col;							// 色
	bool						m_bEnter;						// 押されたかどうか状態
	float						m_fScale;						// 拡大縮小量
	int							m_ScaleCounter;					// 拡大縮小のカウンター
	int							m_EnemyCreateCnt;				// 敵の生成までのカウント
	ENEMYPOS					m_EnemyPosType;
};
#endif
