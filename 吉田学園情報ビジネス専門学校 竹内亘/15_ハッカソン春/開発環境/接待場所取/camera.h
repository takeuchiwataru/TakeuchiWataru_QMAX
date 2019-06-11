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

	typedef enum
	{
		CAMERASIDE_NONE = 0,		// 初期
		CAMERASIDE_LEFT,			// 左
		CAMERASIDE_RIGHT,			// 右
		CAMERASIDE_MAX
	}CAMERASIDE;

	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	Camera GetCamera(void);

	//メンバ変数
private:
	Camera		m_Camera;			//カメラの情報
	float		fLength;			//距離
	CAMERASIDE	m_CameraSideState;	//カメラの右左
	int			m_nCameraCnt;		//カメラのカウント
	int			m_nImpactCnt;		//カメラのカウント
	bool		m_bPressEnter;		//フラグ
};

#endif