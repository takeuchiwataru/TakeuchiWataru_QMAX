//=============================================================================
//
// ロゴ処理 [logo.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLELOGO_TEXTURE "data/TEXTURE/title_logo.png"			// タイトルロゴのテクスチャ
#define RESULTLOGO_TEXTURE000 "data/TEXTURE/gameclear.png"	// リザルトロゴ(クリア)のテクスチャ
#define RESULTLOGO_TEXTURE001 "data/TEXTURE/gameover.png"		// リザルトロゴ(オーバー)のテクスチャ
#define TUTORIALLOGO_TEXTURE "data/TEXTURE/tutorial_logo.png"	// チュートリアルロゴのテクスチャ
#define RANKINGLOGO_TEXTURE ""
#define PRESSENTER_TEXTURE "data/TEXTURE/press_enter.png"		// プレスエンターのテクスチャ
#define PRESSENTER_TEXTURE002 "data/TEXTURE/press_enter2.png"		// プレスエンターのテクスチャ
#define PAUSEMAT_TEXTURE	"data/TEXTURE/pause200.png"			// ポーズ台紙のテクスチャ
#define PAUSESELECT_TEXTURE000	"data/TEXTURE/pause101.png"		// CONTINUE
#define PAUSESELECT_TEXTURE001	"data/TEXTURE/pause102.png"		// RETRY
#define PAUSESELECT_TEXTURE002	"data/TEXTURE/pause103.png"		// QUIT
#define FRAME_TEXTURE000 "data/TEXTURE/life_frame.png"			// ライフフレーム
#define FRAME_TEXTURE001 "data/TEXTURE/score_frame.png"			// スコアフレーム
#define IMAGE_TEXTURE000 "data/TEXTURE/remain000.png"			// プレイヤー1の残機
#define IMAGE_TEXTURE001 "data/TEXTURE/remain001.png"			// プレイヤー1の残機
#define IMAGE_TEXTURE002 "data/TEXTURE/tutorial000.png"			// コントローラー説明
#define IMAGE_TEXTURE003 "data/TEXTURE/tutorial001.png"			// PS説明
#define RANKINGRANK_TEXTURE "data/TEXTURE/ranking_rank.png"		// ランキングランク
#define LOGO_SIZE_X (150)
#define LOGO_SIZE_Y (50)
#define TEXTURE_SIZE_X      (400)								// テクスチャを張り付ける幅
#define TEXTURE_SIZE_Y      (150)								// テクスチャを張り付ける高さ
#define PRESSENTER_SIZE_X   (250)								// プレスエンター幅
#define PRESSENTER_SIZE_Y   (50)								// プレスエンター高さ

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CLogo : public CScene
{
public:
	CLogo(int nPriority);
	~CLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos, float fwidth, float fheight);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetColor(D3DXCOLOR col);					// カラーの設置
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);

private:
	LPDIRECT3DTEXTURE9	m_pTexture;						// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ

protected:
	D3DXVECTOR3				m_pos;						// 位置
	D3DXVECTOR3				m_move;						// 移動
	D3DXCOLOR				m_col;						// 色
}; 
//*****************************************************************************
// タイトルロゴクラスの定義
//*****************************************************************************
class CTitleLogo : public CLogo
{
public:
	CTitleLogo();
	~CTitleLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTitleLogo * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
};
//*****************************************************************************
// リザルトクラスロゴクラスの定義
//*****************************************************************************
class CResultLogo : public CLogo
{
public:
	typedef enum
	{// リザルトの種類
		RESULTTYPE_CLEAR,
		RESULTTYPE_OVER,
		RESULTTYPE_MAX,
	}RESULTTYPE;

	CResultLogo();
	~CResultLogo();
	HRESULT Init(D3DXVECTOR3 pos, RESULTTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CResultLogo * Create(D3DXVECTOR3 pos,RESULTTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[RESULTTYPE_MAX];	// 共有テクスチャのポインタ
	RESULTTYPE m_nType;										// リザルトの種類
};
//*****************************************************************************
// チュートリアルロゴクラスの定義
//*****************************************************************************
class CTutorialLogo : public CLogo
{
public:
	CTutorialLogo();
	~CTutorialLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTutorialLogo * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
};
//*****************************************************************************
// ランキングロゴクラスの定義
//*****************************************************************************
class CRankingLogo : public CLogo
{
public:
	CRankingLogo();
	~CRankingLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CRankingLogo * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
};
//*****************************************************************************
// プレスエンタークラスの定義
//*****************************************************************************
class CPressEnter : public CLogo
{
public:
	typedef enum
	{//プレスエンターの状態
		PRESSENTERSTATE_NONE = 0,
		PRESSENTERSTATE_PUSH,
		PRESSENTERSTATE_MAX
	}PRESSENTERSTATE;

	typedef enum
	{//プレスエンター
		PRESSENTER_TITLE = 0,
		PRESSENTER_TUTORIAL,
		PRESSENTER_MAX
	}PRESSENTER;

	CPressEnter();
	~CPressEnter();
	HRESULT Init(D3DXVECTOR3 pos, PRESSENTER type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CPressEnter * Create(D3DXVECTOR3 pos,PRESSENTER type);
	static HRESULT Load(void);
	static void Unload(void);
	static void DispPressEnter(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[PRESSENTER_MAX];				// 共有テクスチャのポインタ
	PRESSENTERSTATE         m_PressEnterState;			// 状態
	PRESSENTER				m_nType;					// 種類
	int                     m_nCounterPressEnter;		// Drawするタイミング管理カウンター
	static bool             m_bDisp;					// 描画するかしないか
};
#endif
