//=============================================================================
//
// オブジェクトBG処理 [objectBG.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

#include "main.h"
#include "scene.h"
#include "sceneObject.h"
#include "shadow.h"
//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CSceneObject;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MATTEX	(20)

//*****************************************************************************
// 構造体
//*****************************************************************************

//*********************************************************************
//プレイヤークラスの定義
//*********************************************************************
class C3DEffect : public CScene //派生クラス
{
public:
	//モデルの種類
	typedef enum
	{
		EFFECTTYPE_BILL000 = 0,	//ビル 0 小
		EFFECTTYPE_BILL001,		//ビル 1 小
		EFFECTTYPE_BILL002,		//ビル 2 小
		EFFECTTYPE_BILL003,		//ビル 3 小
		EFFECTTYPE_FENCE000,	//フェンス
		EFFECTTYPE_TREE000,		//木
		EFFECTTYPE_LEAF000,		//葉
		EFFECTTYPE_TRUCK000,	//トラック
		EFFECTTYPE_BIN000,		//ビン
		EFFECTTYPE_MAX,			//最大数
	}EFFECTTYPE;

	C3DEffect();
	~C3DEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static C3DEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, EFFECTTYPE type,int nLife);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);

private:
	//メンバ変数
	D3DXVECTOR3					m_pos;				//位置
	D3DXVECTOR3					m_posold;			//前回の位置
	D3DXVECTOR3					m_move;				//移動量
	D3DXVECTOR3					m_ModelMove;		//移動の仕方
	D3DXVECTOR3					m_rot;				//向き
	D3DXMATRIX					m_mtxWorld;			//ワールドマトリックス
	EFFECTTYPE					m_Type;				//タイプ

	float						m_fDestAngle;		//角度
	float						m_fDiffAngle;		//差分

	static LPD3DXMESH			m_pMesh[EFFECTTYPE_MAX];			//メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat[EFFECTTYPE_MAX];		//マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture[EFFECTTYPE_MAX];		//テクスチャへのポインタ
	static DWORD				m_nNumMat[EFFECTTYPE_MAX];		//マテリアル情報の数

	int							m_nCount;			// カウンター
	int							m_nLife;			// 消えるまでのライフ
	CShadow						*m_pShadow;			// 影へのポインタ
public:
	CSceneObject				*m_pObject;
};

#endif