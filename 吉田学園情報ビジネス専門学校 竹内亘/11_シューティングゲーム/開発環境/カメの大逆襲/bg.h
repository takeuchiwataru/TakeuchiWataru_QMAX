//=============================================================================
//
// 背景処理 [bg.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_TEXTURE_000	"data/TEXTURE/bg001.png"
#define BG_TEXTURE_001	"data/TEXTURE/bg002.png"
#define BG_TEXTURE_002	"data/TEXTURE/bg000.png"
#define MAX_BG_TEXTURE (3)			// 背景のテクスチャの数
#define MAX_BG (3)					// 背景の最大数
#define BG_POS_X			(0)		// 背景X座標
#define BG_POS_Y			(0)		// 背景Y座標
#define BG_POS_X000		(250)		// ゲーム中の背景X座標1
#define BG_POS_X001		(950)		// ゲーム中の背景X座標2
#define BG_WIDTH (SCREEN_WIDTH)		// 背景の幅
#define BG_HEIGHT (SCREEN_HEIGHT)	// 背景の高さ
#define BG_MOVESPEED_000 (0.0005f)	// 背景1のスライドスピード
#define BG_MOVESPEED_100 (0.0003f)	// 背景2のスライドスピード
#define BG_MOVESPEED_200 (0.0008f)	// 背景3のスライドスピード

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CBg : public CScene
{
public:
	CBg();
	~CBg();
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT InitGame(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBg * Create(D3DXVECTOR3 pos);
	static CBg * Create2(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE];	// 共有テクスチャのポインタ
	CScene2D * m_apScene2D[MAX_BG];
	D3DXVECTOR3				m_move;			// 移動量
	int m_slideSpeed;						// スライドスピード
};
#endif