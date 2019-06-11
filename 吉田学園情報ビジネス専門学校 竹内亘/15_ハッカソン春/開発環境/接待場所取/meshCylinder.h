//=============================================================================
//
// メッシュシリンダー処理 [meshCylinderBG.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class CSceneMeshCylinder : public CScene //派生クラス
{
public:
	//モデルの種類
	typedef enum
	{
		CYLINDERTYPE_INWARD = 0,		//内向き
		CYLINDERTYPE_OUTWARD,			//外向き
		CYLINDERTYPE_MAX				//総数
	}CYLINDERTYPE;

	CSceneMeshCylinder();
	~CSceneMeshCylinder();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneMeshCylinder *Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ, CYLINDERTYPE typeInOut);
	void Setpos(D3DXVECTOR3 pos);

	void SetRot(D3DXVECTOR3 rot);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTUREを割り当てる
	//メンバ変数
private:
	float								m_fWidth;					// 幅
	float								m_fDepth;					// 奥行き
	D3DXVECTOR3							m_pos;						// 位置
	D3DXVECTOR3							m_rot;						// 向き
	D3DXVECTOR3							m_move;						// 移動量
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;			// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9					m_pTexture = NULL;	 		// テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9				m_pIdxBuff = NULL;			// インデックスバッファへのポインタ
	D3DXMATRIX							m_mtxWorld;					// ワールドマトリックス
	int									m_nNumVerTex;				// 頂点数
	int									m_nNumIndex;				// インデックス数
	int									m_nNumPolygon;				// ポリゴン数
	float								m_Height;					// 高さ
	D3DXVECTOR3							m_aNor[100000];				// 法線
	int									m_nSplitX, m_nSplitY;		// 分割数
	CYLINDERTYPE						m_TypeInOut;				// 内向き外向き
};
#endif
