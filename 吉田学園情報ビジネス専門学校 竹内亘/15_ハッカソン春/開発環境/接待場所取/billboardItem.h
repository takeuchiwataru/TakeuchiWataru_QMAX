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
#include "shadow.h"

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

	CBillBoardItem();
	~CBillBoardItem();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillBoardItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ITEMTEX TexType);
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
	CSceneBillBoard				*m_pBillBoard;				// ビルボードへのポインタ
	CScene2D					*m_pScene2D;				// 2Dポリゴンへのポインタ
	D3DXVECTOR3					m_Scene2DPos;				// 2Dポリゴンの位置
	D3DXVECTOR3					m_Scene2DPosInit;			// 2Dポリゴンの初期位置
	D3DXVECTOR3					m_Scene2DMove;				// 2Dポリゴンの移動量
	D3DXCOLOR					m_Scene2DCol;				// 2Dポリゴンの色
	ITEMTEX						m_TexType;					// テクスチャの種類
	bool						m_bCreate2D;				// 2Dがクリエイトされたかのフラグ
	bool						m_bGetItem;					// アイテム取得状態のフラグ
	CShadow						*m_pShadow;					// 影へのポインタ
};
#endif
