//=============================================================================
//
// 爆発の処理 [exsplosion.h]
// Author : Yamashita
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//マクロ定義
#define MAX_COUNTER (5)
#define MAX_PATTERN (4)
//#define EXPLOSION_UV_U (1.0f)
//#define EXPLOSION_UV_V (0.25f)

class Manager;

//エクスプロージョンクラス（シーン2D派生）
class CExplosion : public CScene2D
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(D3DXVECTOR3 pos,D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CExplosion *Create(D3DXVECTOR3 pos,D3DXCOLOR col);
	static HRESULT Load(void);						//テクスチャ読み込み
	static void Unload(void);
	
private:
//	D3DXVECTOR3 m_pos;								//位置
	D3DXCOLOR m_col;								//色
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// 頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;

	int m_nCounterAnim;								//アニメーションカウンター
	int m_nPatternAnim;								//アニメーションパターンNO
	D3DXVECTOR3 m_pos;

	
};
#endif
