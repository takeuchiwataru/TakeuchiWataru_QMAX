//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "sceneX.h"

//========================================
// クラスの定義
//========================================
//=====================
// ブロッククラス
//=====================
class CBullet : public CSceneX
{
public:
	CBullet();								// コンストラクタ
	~CBullet();								// デストラクタ

	HRESULT Init(void);						// プレイヤー初期化処理
	void Uninit(void);						// プレイヤー終了処理
	void Update(void);						// プレイヤー更新処理
	void Draw(void);						// プレイヤー描画処理

	static HRESULT LoadModel(void);				// テクスチャ読み込み
	static void UnloadModel(void);				// テクスチャ解放

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);	// オブジェクトの生成

	D3DXVECTOR3 GetPos(void);						// 位置の取得
	void SetPos(D3DXVECTOR3 pos);					// 位置の設定

	bool Collision(D3DXVECTOR3 *pos, float fRadius);	// 当たり判定
	void CollisonBlock(D3DXVECTOR3 *pos, float fRadius);	// 当たり判定

private:
	static LPD3DXMESH		m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER		m_pBuffMat;			// マテリアル情報へのポインタ
	static DWORD			m_nNumMat;			// マテリアル情報の数
	static LPDIRECT3DTEXTURE9		*m_pTexture;			// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;				// 位置
	D3DXVECTOR3				m_move;				// 移動量
	D3DXVECTOR3				m_rot;				// 向き
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// ブロックの最小値、最大値
	D3DXVECTOR3				m_scale;			// 拡大率
	bool m_bHit;

	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
	int m_nLife;
};

#endif