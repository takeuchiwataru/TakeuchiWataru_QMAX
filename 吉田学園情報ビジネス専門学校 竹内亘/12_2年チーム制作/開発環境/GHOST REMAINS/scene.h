//=============================================================================
//
// シーン処理 [scene.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define MAX_SCENE		(8)
#define PAUSE_PRIORITY	(MAX_SCENE - 1)				//ポーズの優先順位
#define PAUSE_LENGTH	(75.0f)				//ポーズ上下枠の長さ

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene
{
public://*****************************************************************************
	typedef enum
	{
		DRAW_TYPE_NORMAL = 0,		//通常描画
		DRAW_TYPE_ADD,				//加算合成
		DRAW_TYPE_SUBTRACT,			//減算合成
		DRAW_TYPE_MULTIPLY,			//乗算合成
		DRAW_TYPE_OVERLAY,			//黒無視加算無し
		DRAW_TYPE_ZNORMAL = 10,		//Z無視通常
		DRAW_TYPE_ZADD,				//Z無視加算
		DRAW_TYPE_ZSUBTRACT,		//Z無視減算
		DRAW_TYPE_ZMULTIPLY,		//乗算合成
		DRAW_TYPE_ZOVERLAY,			//黒無視加算無し
		DRAW_TYPE_NO,				//描画しない
		DRAW_TYPE_MAX
	}DRAW_TYPE;
	typedef enum
	{//判定したい全クラス お前誰よ？->俺だよ俺ってやつ
		OBJTYPE_NONE,
		OBJTYPE_DUNGEON, OBJTYPE_MESH,
		OBJTYPE_EFFECT, OBJTYPE_ANIM3D, OBJTYPE_SALE,
		OBJTYPE_BOSS, 
		//モデル//**********************************************
		OBJTYPE_PLAYER, OBJTYPE_ENEMY, OBJTYPE_OBJ,
		//画像//**********************************************
		OBJTYPE_OBJ_NO,	//モデル　判定：(有/無し)
		OBJTYPE_NUMBER,
		OBJTYPE_GOAL, OBJTYPE_SHOP,
		OBJTYPE_MAX
	}OBJTYPE;
	typedef struct
	{//種類ごとのモデル情報保存
		LPD3DXMESH		MeshModel = NULL;		//メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffMatModel = NULL;	//マテリアル情報へのポインタ
		DWORD			nNumMatModel = NULL;	//マテリアルの情報数
	}MODEL_DRAW;
	typedef enum
	{
		/* BG */			TEX_Title, TEX_Select, TEX_TUTORIAL,
		/* 壁 */			TEX_Wall,
		/* 壁 */			TEX_Field,
		/* 炎 */			TEX_Fire,
		/* 柵 */			TEX_Fence,
		/* 岩 */			TEX_Stone,
		/*鉄骨*/			TEX_Steel,
		/*ブロック*/		TEX_Brock, TEX_DBlock, TEX_MBlock,
		/* 槍 */			TEX_Spear,
		/*ボタン*/			TEX_Button,
		/*落石*/			TEX_DropStone,
		/* 影 */			TEX_Shadow,
		/* ロゴ */			TEX_ResaltLogo, TEX_RankingLogo, TEX_RankingRank, TEX_RankingMinute, TEX_RankingSecond, TEX_PressEnter, TEX_Pause, TEX_TutorialLogo,
		/*数字*/			TEX_Number,
		/*ここからモデル用*/TEX_CHAR,
		TEX_MAX
	}TEXTURE;
	CScene::CScene(int nPrioryity = 3);
	~CScene();

	static LPDIRECT3DTEXTURE9	&Load(TEXTURE tex);
	static void	UnLoad(void);
	static void	ReleaseAll(void);
	static void	UpdateAll(void);
	static void	DrawAll(LPDIRECT3DDEVICE9 &pDevice);
	static void	UninitAll(void);
	static void	BreakObject(void);			//オブジェクトの全破壊
	static void	BreakObject(OBJTYPE obj);	//指定したオブジェクトを破壊

	static CScene *GetTop(int nPrioryity);
	//*****************************************************************************
	virtual HRESULT Init(void)					 { return S_OK; };
	virtual void	Uninit(void) { m_bDeath = true; m_ObjType = OBJTYPE_NONE; };
	virtual void	Draw(void)					 {};
	virtual void	Update(void)				 {};
	static int		&GetnCntStart(void)			 { return m_nCntStart; }
	static bool		&GetbPause(void)			 { return m_bPause; }
	static bool		DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice);	//描画準備処理

	CScene *&GetpNext(void) { return m_pNext; }
	CScene *&GetpPrev(void) { return m_pPrev; }
	void	SetObjType(OBJTYPE ObjType)			 { m_ObjType = ObjType; }
	OBJTYPE GetObjType(void)					 { return m_ObjType; }
	LPDIRECT3DTEXTURE9	&GetTexture(int nNumber) { return m_pTexture[nNumber]; }

protected://*****************************************************************************
	void			Release(void);											//解放処理			
private://*****************************************************************************
	//変数宣言//***********************************************************************
	static int		m_nDraw;			//現在の描画方法
	static LPDIRECT3DTEXTURE9	m_pTexture[TEX_MAX];		// テクスチャへのポインタ
	static CScene	*m_pTop[MAX_SCENE];		// 開始位置
	static CScene	*m_pCur[MAX_SCENE];		// 最後尾(カレントの略->現在)
	static int		m_nNumAll[MAX_SCENE];				//Updateのスタート位置
	static int		m_nCntStart;				//Updateのスタート位置
	static bool		m_bPause;					//ポーズの有無

	CScene *m_pNext;				//次
	CScene *m_pPrev;				//前
	int				m_nPriority;	//自分の優先順位
	OBJTYPE			m_ObjType;		//オブジェクトタイプ
	bool			m_bDeath;		//死亡フラグ
};

//==================================================================================================//
//    * テンプレート定義 *
//==================================================================================================//
template<class T> bool SceneCreate(T *&pScene, int nPriority)
{
	pScene = NULL;
	pScene = new T(nPriority);
	if (pScene != NULL) { pScene->Init(); return true; }

	return false;
}
//==================================================================================================//
//    * テンプレート定義 *
//==================================================================================================//
template<class T> bool Create(T *&pScene)
{
	pScene = NULL;
	pScene = new T;
	if (pScene != NULL) { pScene->Init(); return true; }
	//MessageBox(0, "生成できない！", "", MB_OK);

	return false;
}

#endif
