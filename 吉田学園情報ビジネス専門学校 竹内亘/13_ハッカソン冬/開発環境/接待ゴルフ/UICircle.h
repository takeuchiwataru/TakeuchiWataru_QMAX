//=============================================================================
//
// サークル処理 [circle.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _UICIRCLE_H_
#define _UICIRCLE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_CIRCLE			(2)			//サークルの数

//*****************************************************************************
//　前方宣言
//*****************************************************************************
//class CModel;
class CSceneMeshField;

//*********************************************************************
//サークルクラスの定義
//*********************************************************************
class CCircle : public CScene //派生クラス
{
public:
	//モデルの種類
	typedef enum
	{
		CIRCLETEX_NORMAL = 0,	//タイル
		CIRCLETEX_MAX			//テクスチャの総数
	}CIRCLETEX;

	CCircle();
	~CCircle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CCircle *Create(D3DXVECTOR3 pos, float fWidth,float fDepth,D3DXCOLOR col, CIRCLETEX tex, int nSplitX, int nSplitZ);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//メンバ変数
	D3DXVECTOR3					m_pos;						//位置
	D3DXVECTOR3					m_posold;					//前回の位置
	D3DXVECTOR3					m_move;						//移動量
	D3DXVECTOR3					m_rot;						//向き
	D3DXCOLOR					m_col;						//色
	float						m_fWidth, m_fDepth;			//幅 奥行き
	float						m_fMinusWidth[MAX_CIRCLE],
								m_fMinusDepth[MAX_CIRCLE];
	int							m_nSplitX, m_nSplitZ;		//分割数
	CIRCLETEX					m_Type;						//タイプ

	static LPDIRECT3DTEXTURE9	m_pTexture[CIRCLETEX_MAX];	//テクスチャへのポインタ

	CSceneMeshField				*m_pCircle[MAX_CIRCLE];		//サークル本体へのポインタ
public:
};

#endif