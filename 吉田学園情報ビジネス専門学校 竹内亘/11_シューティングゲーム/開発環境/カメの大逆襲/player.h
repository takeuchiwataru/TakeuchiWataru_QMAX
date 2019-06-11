//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_MOVESPEED (7.0f)		// プレイヤーの移動スピード
#define PLAYER_SIZE (50)			// プレイヤーの大きさ
#define PLAYER_BULLET_INTERVAL (10)	// 2wayになった時の間隔
#define PLAYER_REMAIN (3)			// プレイヤー残機
#define MAX_JOYPAD (2)				// 最大コントローラー

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CPlayer : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	typedef enum
	{// プレイヤーの種類
		PLAYERTYPE_000 = 0,
		PLAYERTYPE_001,
		PLAYERTYPE_MAX,
	}PLAYERTYPE;
	
	typedef enum
	{// プレイヤーの状態
		PLAYERSTATE_NORMAL = 0,	// 通常状態
		PLAYERSTATE_DAMEGE,		// ダメージ状態
		PLAYERSTATE_DEATH,		// 死亡状態
		PLAYERSTATE_PS,			// パーフェクトシェル状態
		PLAYERSTATE_INVICIBLE,	// 無敵
		PLAYERSTATE_MAX,
	}PLAYERSTATE;

	typedef enum
	{// アイテムを取ったプレイヤー状態
		ITEMSTATE_NORMAL = 0,	// 通常状態
		ITEMSTATE_ITEM_2WAY,	// 2wayアイテムを取った状態
		ITEMSTATE_AVATAR,		// 分身
		ITEMSTATE_SPPED_UP,		// スピードUP
		ITEMSTATE_MAX,
	}ITEMSTATE;

	CPlayer();
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, PLAYERTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	PLAYERSTATE GetState(void);
	PLAYERTYPE GetType(void);
	void SetItemState(ITEMSTATE itemstate);		// アイテムを取った状態の設置
	int GetRemain(void);
	D3DXVECTOR3 GetPos(void);
	//PLAYERTYPE GetPlayerType(void);

	// 静的メンバ関数
	static CPlayer * Create(D3DXVECTOR3 pos, PLAYERTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[PLAYERTYPE_MAX];	// 共有テクスチャのポインタ
	float					m_rot;
	D3DXVECTOR3 m_pos;				// 位置
	int m_nRemain;					// 残機
	//int m_nLife;					// ライフ
	//int m_nRemainAll;				// 残機合計
	int m_nSpeed;					// スピード
	PLAYERTYPE m_nType;				// プレイヤーの種類
	PLAYERSTATE m_State;			// プレイヤーの状態
	ITEMSTATE m_ItemState;			// アイテムを取ったプレイヤー状態
	int m_nCounterState;			// 状態管理のカウンター
	int m_nTime;					//
	int m_nNumPs;					// PS使用回数
	static int m_nNumPlayer;		// プレイヤー人数
};
#endif