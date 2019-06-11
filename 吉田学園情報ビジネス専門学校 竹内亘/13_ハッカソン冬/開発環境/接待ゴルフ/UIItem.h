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

#define MAX_ITEM (1)
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
private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[1];				// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_ITEM];
	CNumber						*m_apNumber[MAX_ITEMNUM];	//
	int							m_nItem;
};
#endif
