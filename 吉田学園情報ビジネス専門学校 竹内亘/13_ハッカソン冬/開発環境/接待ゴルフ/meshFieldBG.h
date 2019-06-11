//=============================================================================
//
// メッシュフィールドBG処理 [meshFiledBG.h]
// Author :
//
//=============================================================================
#ifndef _MESHFIELDBG_H_
#define _MESHFIELDBG_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//シーンメッシュフィールドクラスの定義
//*********************************************************************
class CSceneMeshFieldBG : public CScene //派生クラス
{
public:
	typedef struct
	{
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 move;	// 移動量
	} MESHFIELD;

	CSceneMeshFieldBG();
	~CSceneMeshFieldBG();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneMeshFieldBG *Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ);
	void Setpos(D3DXVECTOR3 pos);
	static LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	float GetHeight(D3DXVECTOR3);
	void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);
	void SetHeight(D3DXVECTOR3 pos, float fValue, float fRange);
	void SaveHeight(void);											//ファイルのセーブ
	void LoadHeight(void);											//ファイルのロード
	void NormalSet(void);


	//メンバ変数
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff;					//頂点バッファへのポインタ
	MESHFIELD							m_MeshFiled;				//シーン3D構造体
	LPDIRECT3DTEXTURE9					m_pTexture = NULL;			//テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9				m_pIdxBuffMeshField = NULL;	// インデックスバッファへのポインタ
	D3DXMATRIX							m_mtxWorldMeshField;		// ワールドマトリックス
	int									m_nNumVerTexMeshField;		// 頂点数
	int									m_nNumIndexMeshField;		// インデックス数
	int									m_nNumPolygonMeshField;		// ポリゴン数
	float								m_Height;
	D3DXVECTOR3							m_aNor[100000];
	D3DXVECTOR3							m_Pos;						// 位置
	float								m_fWidth;					// 幅
	float								m_fDepth;					// 奥行き
	int									m_nSplitX, m_nSplitZ;		// 分割数

#ifdef  _DEBUG
	int m_nSelectVtx = 0;
#endif
};
#endif
