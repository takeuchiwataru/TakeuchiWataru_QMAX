//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera
{
public:
	typedef enum
	{//モデルの種類
		STATE_NONE = 0,	//動かせない
		STATE_GAME,		//ゲーム
		STATE_MOVIE,		//ムービー

	}CAMERA_STATE;
	typedef enum
	{//モデルの種類
		VIEW_IGNORE = 0,	//何にも関わらない
		VIEW_FOLLOW,		//追従
		VIEW_WATCH,			//追わずに見るだけ

	}CAMERA_VIEW;
	typedef enum
	{//モデルの種類
		SCENE_VIEW_NORMAL = 0,	//通常通り動く
		SCENE_VIEW_STOP,		//モデルのみ止まる

	}SCENE_VIEW;
	typedef enum
	{//モデルの種類
		SCENE_TYPE_NO = 0,	//戻る　間違えようの対処
		SCENE_TYPE_BOSS,	//ボス前のシーン

	}SCENE_TYPE;
	typedef struct
	{
		CAMERA_STATE	state;		//状態
		CAMERA_VIEW		ViewC;		//見る状態 カメラ
		SCENE_VIEW		ViewS;		//見る状態 カメラ以外(モデル等)
		SCENE_TYPE		scene;			//何のシーンか

		int				nCntState;		//ムービーの進行度
		int				nCntTime;		//シーンのフレーム数記録
		D3DXVECTOR3		*pChar;		//何のキャラを追従するか
		D3DXVECTOR3		*pMove;		//何のキャラを追従するか
	}Info;
	CCamera();
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Reset(void);
	bool DrawCamera(D3DXVECTOR3 &pos, float fLength);
	void SetCamera(void);
	void SetScene(SCENE_TYPE type);
	void UpdateScene(void);
	static Info &GetInfo(void) { return m_info; };

	void SetnQuake(int nQuake, float fQuake) { m_nQuake = nQuake; m_fQuake = fQuake; };
	float *&GetpDistance(void) { return m_pDistance; };
	float &GetfDRot(void) { return m_fDRot; };
	D3DXVECTOR3 &GetRot(void) { return m_rot; };
	D3DXVECTOR3 &GetposR(void) { return m_posR; };

private://*****************************************************************************
	static Info	m_info;

		//変数宣言//***********************************************************************
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;			//注視点
	D3DXVECTOR3 m_vecU;			
	D3DXVECTOR3 m_goal;			//向かう位置
	D3DXVECTOR3 m_targetpos;	//追従する場所
	D3DXVECTOR3 m_rot;			//角度
	D3DXVECTOR3 m_addpos;			//カメラの水平移動分
	float		m_fDistance;		//カメラと注視点の距離
	float		*m_pDistance;		//カメラと注視点の距離の目的値
	float		m_fGMagnification;	//目的にいくまでの倍率
	float		m_fQuake;			//揺れの大きさ
	int			m_nQuake;			//揺れ
	float		m_fDRot;			//落ちた時の目的の角度	

	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
};

#endif
