//=============================================================================
//
// ビルボードの処理 [billboard.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CSceneBillBoard : public CScene //派生クラス
{
public:
	typedef struct
	{
	//	float fRadius;						// 半径(大きさ)
	//	float fHeight;						// 高さ
	//	float fWidth;						// 幅
	//	int nIdxShadow;						// 影のインデックス
	//	int nType;							// タイプ
	} BILLBOARD;

	CSceneBillBoard();
	~CSceneBillBoard();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	void Set(float fWidth, float fHeight);
	void SetBillboard(D3DXVECTOR3 pos, float fHeight, float fWidth, int nType);
	static CSceneBillBoard *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTUREを割り当てる
	D3DXVECTOR3 GetPos(void);

private:
	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			//頂点バッファへのポインタ
	BILLBOARD				m_aBillboard;
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;						// ポリゴンの位置
	float					m_fWidth, m_fHeight;			//幅,高さ
	D3DXMATRIX				m_mtrxWorld;		// ワールドマトリックス

};

#endif