//=============================================================================
//
// ナンバー処理 [number.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
//#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_SIZE (20.0f)
#define RANKINGNUMBER_SIZE (50.0f)
#define SCORE_TEXTURE "data/TEXTURE/number003.png"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT InitRanking(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	// 静的メンバ関数
	static CNumber * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// 位置
};
#endif