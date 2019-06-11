//=============================================================================
//
// メッシュフィールド処理 [meshFiled.h]
// Author :
//
//=============================================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_X				(100)								// ポリゴンの数（X）
#define POLYGON_Z				(1)								// ポリゴンの数（Z）

//*********************************************************************
//シーンメッシュフィールドクラスの定義
//*********************************************************************
class CMeshOrbit : public CScene //派生クラス
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 move;	// 移動量
	} MESHFIELD;

	CMeshOrbit();
	~CMeshOrbit();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshOrbit *Create(D3DXVECTOR3 pos);
	void Setpos(D3DXVECTOR3 pos);
	void SetMtxParent(D3DXMATRIX *pMtx);
	void MakeVertexMeshOrbit(LPDIRECT3DDEVICE9 pDevice);
	static HRESULT Load(void);
	static void UnLoad(void);

	//メンバ変数
private:
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				//頂点バッファへのポインタ
	MESHFIELD							m_MeshOrbit;			//シーン3D構造体
	static LPDIRECT3DTEXTURE9			m_pTexture;				//テクスチャへのポインタ
	D3DXMATRIX							m_mtxWorld;				// ワールドマトリックス
	int									m_nNumVerTex;			// 頂点数
	int									m_nNumPolygon;			// ポリゴン数

	int		m_nCntAlpha;
	int		m_nLife;
	int		m_nAlphaMinus;
	float	m_fAlpha;

	D3DXMATRIX							*m_pMtxParent;										//親のマトリックスへのポインタ
	D3DXVECTOR3							m_aPosVertex[(POLYGON_X + 1) * (POLYGON_Z + 1)];	//算出した頂点座標
	D3DXVECTOR3							m_offSet[2];										//両端のオフセット
};
#endif
