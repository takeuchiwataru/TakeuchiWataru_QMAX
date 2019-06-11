//=============================================================================
//
// UIスタート処理 [UIStart.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UISTART_H_
#define _UISTART_H_

#include "main.h"
#include "scene2D.h"

#define MAX_START (4)

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;

//*********************************************************************
//UIスタートクラスの定義
//*********************************************************************
class CUIStart : public CScene2D  //派生クラス
{
public:
	CUIStart();
	~CUIStart();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIStart *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_START];			// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;							// 位置
	D3DXVECTOR3					m_move;							// 移動量
	D3DXVECTOR3					m_posold;						// 前回の位置
	float						m_fWidth, m_fHeight;			// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;					// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_START];			// 2Dポリゴンへのポインタ
	int							m_nItem;						// 獲得数
	int							m_nColorFlash;					// 点滅カウント
	D3DXCOLOR					m_Col;							// 色
	int							m_nType;						// 現在のタイプ
	bool						m_bCntDown;						// 押されたかどうか状態
	float						m_fScale;						// 拡大縮小量
	int							m_ScaleCounter;					// 拡大縮小のカウンター
};
#endif
