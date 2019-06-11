#pragma once
//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PRIORITY		(0)
#define MAX_SWITCH			(4)
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneModel : public CScene
{
public:
	typedef enum
	{
		//ルーム　周囲
		MODEL_FENCE,	//柵
		MODEL_STEEL,	//鉄骨
		//ルーム　中心
		MODEL_STONE,	//岩
		MODEL_STEEL_B,	//鉄骨塊
		//ロード
		MODEL_BOX,		//木箱
		MODEL_STONE_S,	//小岩
		//エントランス
		
		MODEL_BROCK,	//ブロック
		MODEL_MFIELD,	//移動床
		MODEL_MFIELD2,	//移動床2
		MODEL_DFIELD,	//落ちる床
		MODEL_SPEAR,	//槍
		MODEL_BUTTON,		//ボタン
		MODEL_BUTTONFLOR,	//ボタン床
		MODEL_DROP_STONE,	//落石
		MODEL_GOAL,		//ゴール
		MODEL_WARP,		//ボタン
		MODEL_NOLOOK,	//ボタン

		MODEL_MAX
	}MODEL;
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_FADE,
		STATE_FADEIN,
		STATE_FADEOUT,
		STATE_MAX
	}STATE;
	CSceneModel(int nPrioryity = MODEL_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CSceneModel() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, DRAW_TYPE DrawType, bool bHit);
	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	static void	LoadModel(MODEL model, LPDIRECT3DTEXTURE9 &tex);					//モデルの生成
	static void UnLoadModel(void);				//Model解放
	static void GetLength(MODEL model, D3DXVECTOR3 &length);
	static float GetHeight(MODEL model);

	D3DXVECTOR3			&GetPosition(void)				{ return m_pos; }
	D3DXVECTOR3			&GetRotation(void)				{ return m_rot; }
	void		BindTexture(LPDIRECT3DTEXTURE9 pTex)	{ m_pTex = pTex; }
	MODEL				&GetModel(void)					{ return m_Model; }
	CScene::DRAW_TYPE	&GetDrawType(void)				{ return m_DrawType; }


protected://*****************************************************************************
	//モデル//*********************************************************************
	static MODEL_DRAW *m_Model_Draw[MODEL_MAX];					//モデルへのポインタ


	//変数宣言//***********************************************************************
	//D3DXMATRIX			m_mtxWorld;			//ワールドマトリックス
	D3DXCOLOR			&GetColor(void)		{ return m_col; }
	LPDIRECT3DTEXTURE9	&GetTexture(void)	{ return m_pTex; }
	STATE				&GetState(void)		{ return m_state; }
	float				&GetfCntState(void) { return m_fCntState; }

private://*****************************************************************************
	//変数宣言//***********************************************************************
	D3DXVECTOR3			m_pos;				//位置
	D3DXVECTOR3			m_rot;				//向き
	D3DXCOLOR			m_col;				//色
	LPDIRECT3DTEXTURE9	m_pTex;				//画像
	MODEL				m_Model;			//モデル
	CScene::DRAW_TYPE	m_DrawType;			// 描画する方法(加算合成など)
	STATE				m_state;			//使用方法
	float				m_fCntState;		//STATE管理用
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneObjct : public CSceneModel
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		USE_MAX
	}USE;
	CSceneObjct(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) { SetObjType(OBJTYPE_OBJ); };
	~CSceneObjct() {};

	HRESULT	Init(void);
	void	Update(void);
	void	Draw(void);
	void	DropUninit(void);
	void	DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky);		//アイテムドロップ関数
	bool	DropExplosion(void);										//爆発ドロップ
	void	CSceneObjct::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL model, bool bHit, USE use, D3DXVECTOR3 speed, float fPlusRot, int nReturn, int nStop, int nCntReturn, int nNumber);

	static void SetObjField(void);
	static CScene	*CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
		   CScene	*Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	static void	CollisionAllR(void);
	void		CollisionR(CScene *pScene);
	static void	InitSwitch(bool bMode);

	USE		*GetUse(void) { return &m_use; }
	D3DXVECTOR3		&GetPosold(void) { return m_posold; }
	D3DXVECTOR3		&GetRotOld(void) { return m_rotold; }
	D3DXVECTOR3		&GetMove(void) { return m_move; }
private://*****************************************************************************
		//変数宣言//***********************************************************************
	static bool m_bSwitch[MAX_SWITCH];	//スイッチ
	USE m_use;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_rotold;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3	m_speed;
	float		m_fPlusRot;
	int			m_nReturn;
	int			m_nCntReturn;
	int			m_nStop;
	int			m_nCntStop;
	int			m_nNumber;
};

#endif
