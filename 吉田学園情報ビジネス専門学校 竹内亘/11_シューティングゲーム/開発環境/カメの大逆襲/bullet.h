//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HIT_SIZE (30)				// 当たり判定のサイズ
#define BULLET_SIZE (15)			// 弾の大きさ
#define BULLET_LIFE (50)			// 弾のライフ

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CBullet : public CScene2D
{// 派生させる時は : public ～を後ろにつけてやる
public:
	typedef enum
	{// 弾の種類
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PlAYER000,
		BULLETTYPE_ENEMY000,
		BULLETTYPE_MAX
	}BULLETTYPE;

	CBullet();
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE BulletType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE BulletType);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
	D3DXVECTOR3				m_move;			// 移動量
	int						m_nLife;
	BULLETTYPE m_bulletType;				// 弾の種類
};
#endif