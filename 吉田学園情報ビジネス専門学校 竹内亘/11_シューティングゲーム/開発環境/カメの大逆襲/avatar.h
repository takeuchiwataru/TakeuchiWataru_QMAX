//=============================================================================
//
// アバター処理 [avatar.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _AVATAR_H_
#define _AVATAR_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define AVATAR_SIZE (35)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CAvatar : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	typedef enum
	{// プレイヤーの種類
		AVATARTYPE_000 = 0,
		AVATARTYPE_001,
		AVATARTYPE_MAX,
	}AVATARTYPE;

	CAvatar();
	~CAvatar();
	HRESULT Init(D3DXVECTOR3 pos, AVATARTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// 静的メンバ関数
	static CAvatar * Create(D3DXVECTOR3 pos, AVATARTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[AVATARTYPE_MAX];	// 共有テクスチャのポインタ
	AVATARTYPE m_nType;				// アバターの種類
	int m_nSpeed;					// スピード
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
};

#endif
