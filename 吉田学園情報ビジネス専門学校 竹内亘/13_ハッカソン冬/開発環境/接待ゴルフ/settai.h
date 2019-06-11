//=============================================================================
//
// タイトルロゴの処理 [titleLogo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _SETTAI_H_
#define _SETTAI_H_

#include "main.h"
#include "gameLogo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SETTAI_LOGO_NAME		"data/TEXTURE/接待しろ.png"		// リザルトロゴのテクスチャ名

//=========================
// チュートリアルロゴクラス
//=========================
class CSettai : public CGameLogo
{
public:
	CSettai();															// コンストラクタ
	~CSettai();															// デストラクタ

	static HRESULT Load(void);													// テクスチャ読み込み
	static void Unload(void);													// テクスチャ解放

	static CSettai *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);															// チュートリアルロゴ初期化処理
	void Uninit(void);															// チュートリアルロゴ終了処理
	void Update(void);															// チュートリアルロゴ更新処理
	void Draw(void);															// チュートリアルロゴ描x画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif