//=============================================================================
//
// カメラ処理 [camera.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*********************************************************************
//カメラクラスの定義
//*********************************************************************
class CCamera //基本クラス
{
public:
	typedef enum
	{// プレイヤーの種類
		STATE_NONE = 0,
		STATE_NORMAL,	// 通常状態
		STATE_NORMAL2,	// 通常状態
		STATE_FALL,		// 落下状態
		STATE_MAX		// プレイヤーの種類の総数
	} STATE;

	typedef struct
	{
		D3DXVECTOR3 posV;			//視点
		D3DXVECTOR3 posR;			//注視点
		D3DXVECTOR3 posU;			//上方向ベクトル
		D3DXVECTOR3 posVDest;
		D3DXVECTOR3 posRDest;
		D3DXVECTOR3 rotCamera;		//向き
		D3DXVECTOR3 rotDest;
		D3DXVECTOR3 DiffAngle;
		D3DXMATRIX mtxProjection;	//プロジェクションマトリックス(テレビ)
		D3DXMATRIX mtxView;			//ビューマトリックス(カメラマン)
		int nCounterAngle;			//カメラアングルが変わるカウンター
	}Camera;

	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	Camera GetCamera(void);
	void SetState(STATE state);
	STATE GetState(void);
	//static Camera *Create(void);

	//メンバ変数
private:
	Camera m_Camera;	//カメラの情報
	STATE m_State;		// カメラの状態
	float fLength;
};

#endif