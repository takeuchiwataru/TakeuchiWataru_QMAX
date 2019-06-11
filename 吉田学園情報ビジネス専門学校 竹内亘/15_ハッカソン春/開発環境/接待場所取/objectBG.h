//=============================================================================
//
// オブジェクトBG処理 [objectBG.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _OBJECTBG_H_
#define _OBJECTBG_H_

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
class CObjectBG : public CScene //派生クラス
{
public:
	//モデルの種類
	typedef enum
	{
		MODELTYPE_BILL000 = 0,	//ビル 0 小
		MODELTYPE_BILL001,		//ビル 1 小
		MODELTYPE_BILL002,		//ビル 2 小
		MODELTYPE_BILL003,		//ビル 3 小
		MODELTYPE_FENCE000,		//フェンス
		MODELTYPE_TREE000,		//木
		MODELTYPE_TRUCK000,		//トラック
		MODELTYPE_FINISH000,	//フィニッシュ
		MODELTYPE_MAX,			//最大数
	}MODELTYPE;
	//移動の種類
	typedef enum
	{
		MOVETYPE_NONE = 0,
		MOVETYPE_NOT,
		MOVETYPE_X_MOVE,
		MOVETYPE_Y_MOVE,
		MOVETYPE_Z_MOVE,
		MOVETYPE_ROTATION_X,
		MOVETYPE_ROTATION_Y,
		MOVETYPE_ROTATION_Z,
		MOVETYPE_HOUSE,
		MOVETYPE_MAX
	}MOVETYPE;

	CObjectBG();
	~CObjectBG();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CObjectBG *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, MODELTYPE type, MOVETYPE nMovetype,int nCollision);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);

	bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private:
	//メンバ変数
	D3DXVECTOR3					m_pos;				//位置
	D3DXVECTOR3					m_posold;			//前回の位置
	D3DXVECTOR3					m_move;				//移動量
	D3DXVECTOR3					m_ModelMove;		//移動の仕方
	D3DXVECTOR3					m_rot;				//向き
	D3DXMATRIX					m_mtxWorld;			//ワールドマトリックス
	MODELTYPE					m_Type;				//タイプ


	float						m_fDestAngle;		//角度
	float						m_fDiffAngle;		//差分
	static LPD3DXMESH			m_pMesh[MODELTYPE_MAX];			//メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat[MODELTYPE_MAX];		//マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9	m_pTexture[MODELTYPE_MAX];		//テクスチャへのポインタ
	static DWORD				m_nNumMat[MODELTYPE_MAX];		//マテリアル情報の数
	int							m_nCount;			// カウンター
	MOVETYPE					m_nMoveType;		// 動きの種類
	int							m_nCollision;		// 当たり判定のONOFF
	CShadow						*m_pShadow;			// 影へのポインタ
public:
	CSceneObject				*m_pObject;

};

#endif