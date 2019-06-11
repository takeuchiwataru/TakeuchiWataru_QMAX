//=============================================================================
//
// ビルボードオブジェクト処理 [billboardObject.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARDOBJECT_H_
#define _BILLBOARDOBJECT_H_

#include "main.h"
#include "billboard.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CScene2D;

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CBillBoardObject : public CSceneBillBoard //派生クラス
{
public:
	typedef enum
	{
		TEXTYPE_TREE = 0,	//通常
		TEXTYPE_TITLE,		//タイトルロゴ
		TEXTYPE_MAX			//テクスチャの総数
	}TEXTYPE;


	CBillBoardObject();
	~CBillBoardObject();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillBoardObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, TEXTYPE TexType);
	static HRESULT Load(void);
	static void UnLoad(void);

	bool CollisionBillboardObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTYPE_MAX];		// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	float						m_fSpin;					// 回転
	float						m_fScale;					// 拡大
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス

	CSceneBillBoard				*m_pBillBoard;

	TEXTYPE					m_TexType;
};
#endif
