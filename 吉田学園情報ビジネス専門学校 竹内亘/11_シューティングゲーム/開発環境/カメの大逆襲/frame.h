//=============================================================================
//
// フレーム処理 [logo.cpp]
// Author : 竹内亘
//
//=============================================================================
#ifndef _FRAME_H_
#define _FRAME_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// フレームクラスの定義
//*****************************************************************************
class CFrame : public CLogo
{
public:
	typedef enum
	{// フレームの種類
		FRAME_LIFE,
		FRAME_SCORE,
		FRAME_MAX,
	}FRAME;

	CFrame();
	~CFrame();
	HRESULT Init(D3DXVECTOR3 pos, FRAME type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CFrame * Create(D3DXVECTOR3 pos, FRAME type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[FRAME_MAX];	// 共有テクスチャのポインタ
	FRAME m_nType;										// リザルトの種類
};

#endif
