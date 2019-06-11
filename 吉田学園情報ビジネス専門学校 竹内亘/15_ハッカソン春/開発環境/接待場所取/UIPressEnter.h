//=============================================================================
//
// UIエンター処理 [UIPressEnter.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIPRESSENTER_H_
#define _UIPRESSENTER_H_

#include "main.h"
#include "scene2D.h"

#define MAX_PRESSENTER (1)

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;

//*********************************************************************
//UIエンタークラスの定義
//*********************************************************************
class CUIPressEnter : public CScene2D  //派生クラス
{
public:
	CUIPressEnter();
	~CUIPressEnter();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIPressEnter *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetItemBool(bool bGetItem);
private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_PRESSENTER];		// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;							// 位置
	D3DXVECTOR3					m_move;							// 移動量
	D3DXVECTOR3					m_posold;						// 前回の位置
	float						m_fWidth, m_fHeight;			// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;					// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_PRESSENTER];	// 2Dポリゴンへのポインタ
	int							m_nItem;						// 獲得数
	int							m_nColorFlash;					// 点滅カウント
	D3DXCOLOR					m_Col;							// 色
	bool						m_bEnter;						// 押されたかどうか状態
	float						m_fScale;						// 拡大縮小量
	int							m_ScaleCounter;					// 拡大縮小のカウンター
};
#endif
