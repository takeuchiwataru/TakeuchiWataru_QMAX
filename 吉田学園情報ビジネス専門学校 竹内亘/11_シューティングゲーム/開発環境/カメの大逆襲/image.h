//=============================================================================
//
// 画像処理 [image.cpp]
// Author : 竹内亘
//
//=============================================================================
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// 画像クラスの定義
//*****************************************************************************
class CImage : public CLogo
{
public:
	typedef enum
	{// フレームの種類
		IMAGE_REMAIN000,
		IMAGE_REMAIN001,
		IMAGE_TUTORIAL,
		IMAGE_TUTORIAL002,
		IMAGE_MAX,
	}IMAGE;

	CImage();
	~CImage();
	HRESULT Init(D3DXVECTOR3 pos, IMAGE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CImage * Create(D3DXVECTOR3 pos, IMAGE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[IMAGE_MAX];	// 共有テクスチャのポインタ
	IMAGE m_nType;										// リザルトの種類
};

#endif
