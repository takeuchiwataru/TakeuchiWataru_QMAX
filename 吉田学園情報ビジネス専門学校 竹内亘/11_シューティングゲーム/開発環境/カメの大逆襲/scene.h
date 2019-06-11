//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCENE		(3000)									// ポリゴン最大数
#define NUM_PRIORITY	(8)										// 優先順位の最大数

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene
{
public:
	typedef enum 
	{// オブジェクトの種類
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		// プレイヤー
		OBJTYPE_ENEMY,		// 敵
		OBJTYPE_BOSS,		// ボス
		OBJTYPE_BULLET,		// 弾
		OBJTYPE_EXPLOSION,	// 爆発
		OBJTYPE_LIFE,		// ライフ
		OBJTYPE_EFFECT,		// エフェクト
		OBJTYPE_PARTICLE,	// パーティクル
		OBJTYPE_ITEM,		// アイテム
		OBJTYPE_MAEINAPLANT,// 海藻
		OBJTYPE_TITLELOGO,	// タイトルロゴ
		OBJTYPE_RESULTLOGO,	// リザルトロゴ
		OBJTYPE_TUTORIAL,	// チュートリアルロゴ
		OBJTYPE_PRESSENTER,	// プレスエンター
		OBJTYPE_PAUSEMAT,	// ポーズ台紙
		OBJTYPE_PAUSESELECT,// ポーズ項目
		OBJTYPE_FRAME,		// フレーム
		OBJTYPE_IMAGE,		// 画像
		OBJTYPE_AVATAR,		// 分身
		OBJTYPE_RANKINGRANK,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual	HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual	void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	
	void SetObjType(OBJTYPE ObjType);
	OBJTYPE GetObjType(void);
	static CScene * GetScene(int nPriority,int nIdx);
	//static CScene * GetScene(void);

	// 静的メンバ関数
	static void ReleseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

protected:
	void Release(void);

private:
	static CScene *m_apScene[NUM_PRIORITY][MAX_SCENE];
	static int m_nNumAll;
	int m_nID;			// 自分自身の番号
	OBJTYPE m_objType;	// オブジェクトの種類
	int m_nPriority;	// 優先順位の番号
};
#endif