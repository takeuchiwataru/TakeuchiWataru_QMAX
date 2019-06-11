//=============================================================================
//
// ビルボードアイテム処理 [billboardItem.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARDITEM_H_
#define _BILLBOARDITEM_H_

#include "main.h"
#include "billboard.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CScene2D;

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CBillBoardItem : public CSceneBillBoard //派生クラス
{
public:
	typedef enum
	{
		ITEMTEX_NORMAL = 0,	//通常
		ITEMTEX_MAX			//テクスチャの総数
	}ITEMTEX;

	typedef enum
	{
		ITEMMOVE_NONE = 0,
		ITEMMOVE_X,				//移動X軸
		ITEMMOVE_Z,				//移動Z軸
		ITEMMOVE_MAX			//状態の総数
	}ITEMMOVE;

	CBillBoardItem();
	~CBillBoardItem();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillBoardItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ITEMTEX TexType, ITEMMOVE moveType);
	static HRESULT Load(void);
	static void UnLoad(void);

	bool CollisionBillboardItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[ITEMTEX_MAX];	// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	float						m_fSpin;					// 回転
	float						m_fScale;					// 拡大
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス

	CSceneBillBoard				*m_pBillBoard;
	CScene2D					*m_pScene2D;

	D3DXVECTOR3					m_Scene2DPos;
	D3DXVECTOR3					m_Scene2DPosInit;
	D3DXVECTOR3					m_Scene2DMove;
	D3DXCOLOR					m_Scene2DCol;


	ITEMTEX						m_TexType;
	ITEMMOVE					m_moveType;
	bool						m_bCreate2D;
	bool						m_bGetItem;
};
#endif
