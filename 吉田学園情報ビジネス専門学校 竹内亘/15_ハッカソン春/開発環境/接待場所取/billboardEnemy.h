//=============================================================================
//
// ビルボードの敵処理 [billboardEnemy.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARDENEMY_H_
#define _BILLBOARDENEMY_H_

#include "main.h"
#include "billboard.h"

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CBillBoardEnemy : public CSceneBillBoard //派生クラス
{
public:
	typedef enum
	{
		ENEMYTEX_HUMAN000 = 0,	//人間
		ENEMYTEX_MAX			//テクスチャの総数
	}ENEMYTEX;

	typedef enum
	{
		ENEMYMOVE_NONE = 0,
		ENEMYMOVE_X,			//移動X軸
		ENEMYMOVE_Z,			//移動Z軸
		ENEMYMOVE_MAX			//状態の総数
	}ENEMYMOVE;

	CBillBoardEnemy();
	~CBillBoardEnemy();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillBoardEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ENEMYTEX TexType, ENEMYMOVE moveType);
	static HRESULT Load(void);
	static void UnLoad(void);

	bool CollisionBillboardEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[ENEMYTEX_MAX];	// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;	//幅 高さ
	D3DXMATRIX					m_mtrxWorld;			// ワールドマトリックス
	CSceneBillBoard				*m_pBillBoard;

	ENEMYTEX					m_TexType;
	ENEMYMOVE					m_moveType;
};
#endif
