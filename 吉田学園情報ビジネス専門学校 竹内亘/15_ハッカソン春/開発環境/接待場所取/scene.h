//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_PRIORITY			(8)

//*********************************************************************
//オブジェクトクラスの定義
//*********************************************************************
class CScene //基本クラス
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,		//初期値
		OBJTYPE_SCENE2D,		//シーン2D
		OBJTYPE_SCENE3D,		//シーン3D
		OBJTYPE_MODEL,			//モデル
		OBJTYPE_SHADOW,			//影
		OBJTYPE_SCENEX,			//シーンX
		OBJTYPE_OBJECT,			//オブジェクト
		OBJTYPE_PAUSE,			//ポーズ
		OBJTYPE_BILLBOARD,		//ビルボード
		OBJTYPE_BILLBOARDENEMY,	//ビルボード 敵
		OBJTYPE_BILLBOARDITEM,	//ビルボード アイテム
		OBJTYPE_BILLBOARDOBJECT,//ビルボード オブジェクト
		OBJTYPE_BULLET,			//弾
		OBJTYPE_ENEMY,			//敵
		OBJTYPE_EFFECT,			//エフェクト
		OBJTYPE_EFFECTADD,		//エフェクト(加算合成)
		OBJTYPE_MESHFIELD,		//メッシュフィールド
		OBJTYPE_MESHCYLINDER,	//メッシュシリンダー
		OBJTYPE_FIELD,			//フィールド
		OBJTYPE_BGMODEL,		//背景用モデル
		OBJTYPE_MAX				//最大数
	}OBJTYPE;
	CScene(int nPriority = 3,OBJTYPE ObjType = OBJTYPE_NONE);
	virtual ~CScene();
	virtual HRESULT Init() = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void Setpos(D3DXVECTOR3 pos);				//位置設定
	static int GetNumAll(void);					//総数取得
	static void ReleaseAll(void);				//全てを破棄
	static void UpdateAll(void);				//全てを更新
	static void DrawAll(void);					//全てを描画
	void UninitAll(void);						//死亡フラグが立っているものを破棄
	void SetObjType(OBJTYPE ObjType);			//タイプを設定
	CScene::OBJTYPE GetObjType(void);			//タイプを取得
	void SetPriority(int nPriority);

	static CScene *&GetTop(int nPriority);
	CScene *&GetNext(void) { return m_pNext; }
	bool &GetDeath(void) { return m_pDeath; }

	static void SetbPause(bool bPause);

protected:
	void Release(void);							//フラグを立てる
	CScene *m_pNext;							//次のオブジェクトへのポインタ
private:
	//メンバ変数
	static CScene	*m_pTop[NUM_PRIORITY];		//先頭のオブジェクトへのポインタ
	static CScene	*m_pCur[NUM_PRIORITY];		//現在のオブジェクトへのポインタ
	int				m_nPriority;				//優先順位の番号
	CScene			*m_pPrev;					//前のオブジェクトへのポインタ
	OBJTYPE			m_ObjType;					//種類
	bool			m_bDeath;					//死亡フラグ
	bool			m_pDeath;					//死亡フラグ

	static bool		m_bPause;					//ポーズ
};

#endif