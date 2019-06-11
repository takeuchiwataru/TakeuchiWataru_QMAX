//=============================================================================
//
// アイテム処理 [item.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEMSIZE (25)				// アイテムの大きさ

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CItem : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	typedef enum
	{// アイテムの種類
		ITEMTYPE_000 = 0,	// スコア
		ITEMTYPE_001,		// 2way
		ITEMTYPE_002,		// スピードUP
		ITEMTYPE_003,		// 分身
		ITEMTYPE_MAX,
	}ITEMTYPE;

	CItem();
	~CItem();
	HRESULT Init(D3DXVECTOR3 pos, ITEMTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	ITEMTYPE GetItemType(void);

	// 静的メンバ関数
	static CItem * Create(D3DXVECTOR3 pos, ITEMTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[ITEMTYPE_MAX];	// 共有テクスチャのポインタ

	D3DXVECTOR3				m_pos;			// 位置
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nLife;
	ITEMTYPE				m_nType;		// アイテムの種類
	int						m_nTime;
	//static CScore * m_pScore;

};
#endif
