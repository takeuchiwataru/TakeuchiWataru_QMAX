//=============================================================================
//
// 弾の処理 [bullet.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "billboard.h"

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CBullet : public CSceneBillBoard //派生クラス
{
public:
	typedef enum
	{
		BULLETTYPE_NONE = 0,	//プレイヤー状態
		BULLETTYPE_MAX			//状態の総数
	}BULLETTYPE;

	typedef struct
	{
		D3DXVECTOR3 pos;					// 位置
		D3DXVECTOR3 move;					// 移動量
		D3DXVECTOR3 posold;					// 前回の位置
		D3DXCOLOR col;						// 色
		D3DXMATRIX	mtrxWorldBullet;		// ワールドマトリックス
		float fRadius;						// 半径(大きさ)
		float fHeght;						// 高さ
		float fWidth;						// 幅
		int nLife;							// 寿命
		D3DXVECTOR3 VtxMin, VtxMax;			//プレイヤーの最小値、最大値
	} BULLET;

	CBullet();
	~CBullet();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos ,D3DXVECTOR3 move);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;		//頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャへのポインタ
	BULLET m_Bullet;
};
#endif
