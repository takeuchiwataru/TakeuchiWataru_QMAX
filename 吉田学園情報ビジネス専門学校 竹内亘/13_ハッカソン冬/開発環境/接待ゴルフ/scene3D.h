//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//シーン3Dクラスの定義
//*********************************************************************
class CScene3D : public CScene //派生クラス
{
public:
	typedef struct
	{

	}POLYGON;

	CScene3D();
	~CScene3D();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CScene3D *Create(D3DXVECTOR3 pos,float fWidth,float fDepth);
	//static LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	float GetHeight(D3DXVECTOR3);
	//メンバ変数
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuffPolygon = NULL;	//頂点バッファへのポインタ
	POLYGON								m_Polygon;					//シーン3D構造体
	LPDIRECT3DTEXTURE9					m_pTexturePolygon = NULL;	//テクスチャへのポインタ
	float								m_Height;

	D3DXVECTOR3							m_pos;							//位置
	D3DXVECTOR3							m_rot;							//向き
	D3DXMATRIX							m_mtxWorld;						//ワールドマトリックス
	float								m_fWidth, m_fDepth;				//幅　奥行き

	//D3DXVECTOR3							m_aNor[4];
	//D3DXVECTOR3							m_aPos[4];
	//D3DXVECTOR3							m_aVec[4];
};

#endif
