//=============================================================================
//
// メッシュフィールド処理 [meshFiled.h]
// Author :
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//シーンメッシュフィールドクラスの定義
//*********************************************************************
class CSceneMeshField : public CScene //派生クラス
{
public:
	CSceneMeshField();
	~CSceneMeshField();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneMeshField *Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ);
	void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);
	void Setpos(D3DXVECTOR3 pos);
	bool GetHeightbool(D3DXVECTOR3 &pos);			//地面との当たり判定
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTUREを割り当てる

	void SetHeight(D3DXVECTOR3 pos, float fValue, float fRange);	//起伏の設定
	void NormalSet(void);

	//メンバ変数
private:
	float								m_fWidth;						// 幅
	float								m_fDepth;						// 奥行き
	D3DXVECTOR3							m_pos;							// 位置
	D3DXVECTOR3							m_rot;							// 向き
	D3DXVECTOR3							m_move;							// 移動量
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9					m_pTexture = NULL;	 					// テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9				m_pIdxBuffMeshField = NULL;		// インデックスバッファへのポインタ
	D3DXMATRIX							m_mtxWorldMeshField;			// ワールドマトリックス
	int									m_nNumVerTexMeshField;			// 頂点数
	int									m_nNumIndexMeshField;			// インデックス数
	int									m_nNumPolygonMeshField;			// ポリゴン数
	float								m_Height;
	D3DXVECTOR3							m_aNor[100000];
	int									m_nSplitX, m_nSplitZ;			// 分割数
#ifdef  _DEBUG
	int m_nSelectVtx = 0;
#endif
};
#endif
