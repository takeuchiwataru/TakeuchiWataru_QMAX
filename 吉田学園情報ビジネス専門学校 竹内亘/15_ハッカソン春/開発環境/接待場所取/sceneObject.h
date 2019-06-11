//=============================================================================
//
// シーンオブジェクト処理 [sceneObject.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//モデルクラスの定義
//*********************************************************************
class CSceneObject
{
public:
	CSceneObject();
	~CSceneObject();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff);	//TEXTUREを割り当てる
	void SetParent(CSceneObject *pModel);
	D3DXMATRIX GetMtxWorld(void);
	void SetMtxWorld(D3DXMATRIX MtxWorld);

	void VtxMinMaxSet(void);

	D3DXVECTOR3 VtxMin(void) { return m_VtxMinModel; }
	D3DXVECTOR3 VtxMax(void) { return m_VtxMaxModel; }

	void Setpos(D3DXVECTOR3 pos);
	void Setrot(D3DXVECTOR3 rot);
	D3DXVECTOR3 Getrot(void);
	D3DXVECTOR3 GetPos(void);

	void SetbShadow(bool bShadow);


	//メンバ変数
private:
	D3DXVECTOR3				m_pos;					//位置
	D3DXVECTOR3				m_rot;					//向き


	LPD3DXMESH				m_pMeshModel;			//メッシュ情報へのポインタ
	LPD3DXBUFFER			m_pBuffMatModel;		//マテリアル情報へのポインタ
	LPDIRECT3DTEXTURE9		*m_pTextureModel;		//テクスチャへのポインタ
	DWORD					m_nNumMatModel = 0;		//マテリアル情報の数
	D3DXVECTOR3				m_VtxMinModel, m_VtxMaxModel;		//モデルの最小値、最大値
	D3DXMATRIX				m_mtxWorld;				//ワールドマトリックス
	CSceneObject			*m_pParent;				//親モデルへのポインタ

	bool					m_bShadow;				//影のフラグ
};


#endif