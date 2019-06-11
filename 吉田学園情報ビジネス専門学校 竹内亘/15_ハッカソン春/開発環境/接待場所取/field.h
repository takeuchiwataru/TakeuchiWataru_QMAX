//=============================================================================
//
// フィールド処理 [field.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
//class CModel;
class CSceneMeshField;

//*********************************************************************
//プレイヤークラスの定義
//*********************************************************************
class CField : public CScene //派生クラス
{
public:
	//モデルの種類
	typedef enum
	{
		FIELDTEX_NORMAL = 0,	//タイル
		FIELDTEX_ROADWAY,		//車道
		FIELDTEX_FOOTWAY,		//歩道
		FIELDTEX_GARDEN,		//庭
		FIELDTEX_MAX			//テクスチャの総数
	}FIELDTEX;

	CField();
	~CField();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CField *Create(D3DXVECTOR3 pos, float fWidth,float fDepth, FIELDTEX tex, int nSplitX, int nSplitZ);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//メンバ変数
	D3DXVECTOR3					m_pos;					//位置
	D3DXVECTOR3					m_posold;				//前回の位置
	D3DXVECTOR3					m_move;					//移動量
	D3DXVECTOR3					m_rot;					//向き
	float						m_fWidth, m_fDepth;		//幅 奥行き
	int							m_nSplitX, m_nSplitZ;	//分割数
	FIELDTEX					m_Type;					//タイプ

	static LPDIRECT3DTEXTURE9	m_pTexture[FIELDTEX_MAX];		//テクスチャへのポインタ

	CSceneMeshField				*m_pField;			//フィールド本体へのポインタ
public:
};

#endif