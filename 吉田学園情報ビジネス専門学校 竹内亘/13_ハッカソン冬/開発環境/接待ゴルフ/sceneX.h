//=============================================================================
//
// モデル処理 [sceneX.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//シーンXクラスの定義
//*********************************************************************
class CSceneX : public CScene //派生クラス
{
public:
	typedef struct
	{
		DWORD nNumMat = 0;						//マテリアル情報の数
		D3DXVECTOR3 pos;						//位置
		D3DXVECTOR3 rot;						//向き
		D3DXMATRIX	mtxWorld;					//ワールドマトリックス
		float fShadow;							//影の大きさ
		int nIdxShadow;							//影のインデックス
		int nType;								//モデルの種類
		bool bUse;								//使用しているか
		D3DXVECTOR3 VtxMinModel, VtxMaxModel;	//モデルの最小値、最大値
	} MODEL;

	CSceneX();
	~CSceneX();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	void Setrot(D3DXVECTOR3 rot);
	MODEL *GetModel(void);
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, MODEL **pModel*/);
	void SetModel(D3DXVECTOR3 pos, int nType);
	static CSceneX *Create(D3DXVECTOR3 pos);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture, LPD3DXMESH Mesh, LPD3DXBUFFER Buff);	//TEXTUREを割り当てる

	//メンバ変数
private:
	LPD3DXMESH m_pMeshModel;					//メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMatModel;				//マテリアル情報へのポインタ
	LPDIRECT3DTEXTURE9	m_pTextureModel;		//テクスチャへのポインタ
	DWORD m_nNumMatModel = 0;					//マテリアル情報の数
	MODEL m_aModel;
};


#endif