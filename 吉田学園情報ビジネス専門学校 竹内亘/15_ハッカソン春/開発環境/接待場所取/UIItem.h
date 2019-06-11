//=============================================================================
//
// UIアイテム処理 [UIItem.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIITEM_H_
#define _UIITEM_H_

#include "main.h"
#include "scene2D.h"

#define MAX_ITEM2D (2)
#define MAX_ITEMNUM (3)

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;

//*********************************************************************
//UIアイテムクラスの定義
//*********************************************************************
class CUIItem : public CScene2D  //派生クラス
{
public:
	CUIItem();
	~CUIItem();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIItem *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	void PlusItem(int nAddItem);
	int GetItemNum(void);
	void SetItemBool(bool bGetItem);
private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ITEM2D];		// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_ITEM2D];	// 2Dポリゴンへのポインタ
	CNumber						*m_apNumber[MAX_ITEMNUM];	// 数字へのポインタ
	int							m_nItem;					// 獲得数
	bool						m_bGetItem;					// 取得状態
	float						m_fScale;					// 拡大縮小量
	int							m_ScaleCounter;				// 拡大縮小のカウンター
};
#endif
