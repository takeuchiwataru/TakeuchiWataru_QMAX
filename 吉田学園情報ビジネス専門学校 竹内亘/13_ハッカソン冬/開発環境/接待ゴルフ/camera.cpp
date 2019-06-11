//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "game.h"
#include "camera.h"
#include "input.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "player.h"
#include "ball.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_CAMERA			(3.5f)						//モデル移動量
#define MOVE_SIN_COS_TOP_CAMERA	(0.75f)						//カメラ移動量
#define MOVE_SIN_COS_BOT_CAMERA	(0.25f)						//カメラ移動量

//--------------------------------------------
//カメラクラス コンストラクタ
//--------------------------------------------
CCamera::CCamera()
{
}

//--------------------------------------------
//カメラクラス デストラクタ
//--------------------------------------------
CCamera::~CCamera()
{
}

//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::Init(void)
{
	m_Camera.posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);
	m_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.posU = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_Camera.rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.nCounterAngle = 0;
	fLength = sqrtf(
		//Xの距離を求める　Xの距離の2乗
		(m_Camera.posR.x - m_Camera.posV.x) * (m_Camera.posR.x - m_Camera.posV.x)
		//Zの距離を求める　Zの距離の2乗
		+ (m_Camera.posR.z - m_Camera.posV.z) * (m_Camera.posR.z - m_Camera.posV.z));

	m_State = STATE_NORMAL;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Update(void)
{
#if 1
	//現在のモードを取得
	 CManager::MODE mode = CManager::GetMode();

	 //キーボード情報を取得
	 CInputKeyboard *pInput = CManager::GetInputKeyboard();
	switch (mode)
	{
	case CManager::MODE_GAME:
		CBall *pBall = CGame::GetBall();

		if (m_State == STATE_NORMAL)
		{
			m_Camera.posRDest.x = pBall->GetPos().x - sinf(pBall->GetRot().y) * 30;
			m_Camera.posRDest.y = pBall->GetPos().y - sinf(pBall->GetRot().x) * 30;
			m_Camera.posRDest.z = pBall->GetPos().z - cosf(pBall->GetRot().y) * 30;
			//カメラの距離
			m_Camera.posVDest.x = pBall->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
			m_Camera.posVDest.y = pBall->GetPos().y - sinf(m_Camera.rotCamera.x) * (fLength - 100);
			m_Camera.posVDest.z = pBall->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 100);
			//減速
			m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pBall->GetMove().x;
			m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 8;	//カメラの注視点の上下位置が変わる
			m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pBall->GetMove().z;

			//視点
			m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f) + 25;
			m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) + 25;
			m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);
		}
		else if (m_State == STATE_NORMAL2)
		{
			m_Camera.posRDest.x = pBall->GetPos().x - sinf(pBall->GetRot().y) * 30;
			m_Camera.posRDest.y = pBall->GetPos().y - sinf(pBall->GetRot().x) * 30;
			m_Camera.posRDest.z = pBall->GetPos().z - cosf(pBall->GetRot().y) * 30;
			//カメラの距離
			m_Camera.posVDest.x = pBall->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
			m_Camera.posVDest.y = pBall->GetPos().y - sinf(m_Camera.rotCamera.x) * (fLength - 100);
			m_Camera.posVDest.z = pBall->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 100);
			//減速
			m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pBall->GetMove().x;
			m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 8;	//カメラの注視点の上下位置が変わる
			m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pBall->GetMove().z;

			//視点
			m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f) - 25;
			m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) + 25;
			m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);
		}
		else if (m_State == STATE_FALL)
		{
			//m_Camera.posRDest.x = pBall->GetPos().x - sinf(pBall->GetRot().y) * 30;
			//m_Camera.posRDest.y = 0.0f;
			//m_Camera.posRDest.z = pBall->GetPos().z - cosf(pBall->GetRot().y) * 30;
			////カメラの距離
			//m_Camera.posVDest.x = pBall->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
			//m_Camera.posVDest.y = 1300.0f;
			//m_Camera.posVDest.z = pBall->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 100);
			////減速
			//m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pBall->GetMove().x;
			//m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 20.0f;	//カメラの注視点の上下位置が変わる
			//m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pBall->GetMove().z;

			////視点
			//m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f);
			//m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) - 50;
			//m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);

			m_Camera.posR.x = 0.0f;
			m_Camera.posR.y = 100.0f;	//カメラの注視点の上下位置が変わる
			m_Camera.posR.z = 10590.0f;


			//視点
			m_Camera.posV.x = 0.0f;
			m_Camera.posV.y = 700;
			m_Camera.posV.z = 10360;
		}
		break;
	}
#endif

	//カメラの操作
#if 0
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//移動処理

	//任意のキー←
	if (pInput->GetPress(DIK_LEFT) == true)
	{
		if (pInput->GetPress(DIK_UP) == true)
		{//左奥移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.75f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.75f) * MOVE_CAMERA;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else if (pInput->GetPress(DIK_DOWN) == true)
		{//左手前移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.25f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.25f) * MOVE_CAMERA;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else
		{
			//カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
	}
	//任意のキー→
	else if (pInput->GetPress(DIK_RIGHT) == true)
	{
		if (pInput->GetPress(DIK_UP) == true)
		{//右奥移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y - D3DX_PI * 0.75f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y - D3DX_PI * 0.75f) * MOVE_CAMERA;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else if (pInput->GetPress(DIK_DOWN) == true)
		{//右手前移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y - D3DX_PI * 0.25f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y - D3DX_PI * 0.25f) * MOVE_CAMERA;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else
		{
			//カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x += sinf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
			m_Camera.posV.z += cosf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
	}
	else if (pInput->GetPress(DIK_UP) == true)
	{//奥移動
	 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
		m_Camera.posV.x += sinf(m_Camera.rotCamera.y) * MOVE_CAMERA;
		m_Camera.posV.z += cosf(m_Camera.rotCamera.y) * MOVE_CAMERA;
		//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
	}
	else if (pInput->GetPress(DIK_DOWN) == true)
	{//手前移動
	 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
		m_Camera.posV.x -= sinf(m_Camera.rotCamera.y) * MOVE_CAMERA;
		m_Camera.posV.z -= cosf(m_Camera.rotCamera.y) * MOVE_CAMERA;
		//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
	}
	//任意のキーC
	if (pInput->GetPress(DIK_C) == true)
	{
		m_Camera.rotCamera.y -= 0.05f;
		// -3.14を下回った
		if (m_Camera.rotCamera.y < -D3DX_PI)
		{
			// -3.14を 3.14にする
			m_Camera.rotCamera.y += D3DX_PI * 2.0f;
		}
		m_Camera.posV.x = m_Camera.posR.x + sinf(m_Camera.rotCamera.y + D3DX_PI)* fLength;
		m_Camera.posV.z = m_Camera.posR.z + cosf(m_Camera.rotCamera.y + D3DX_PI)* fLength;

	}
	//任意のキーZ
	if (pInput->GetPress(DIK_Z) == true)
	{
		m_Camera.rotCamera.y += 0.05f;
		// 3.14を上回った
		if (m_Camera.rotCamera.y > D3DX_PI)
		{
			// 3.14を -3.14にする
			m_Camera.rotCamera.y -= D3DX_PI * 2.0f;
		}
		m_Camera.posV.x = m_Camera.posR.x + sinf(m_Camera.rotCamera.y + D3DX_PI)* fLength;
		m_Camera.posV.z = m_Camera.posR.z + cosf(m_Camera.rotCamera.y + D3DX_PI)* fLength;

	}
	//任意のキーQ
	if (pInput->GetPress(DIK_Q) == true)
	{
		m_Camera.rotCamera.y -= 0.03f;
		// -3.14を下回った
		if (m_Camera.rotCamera.y < -D3DX_PI)
		{
			// -3.14を 3.14にする
			m_Camera.rotCamera.y += D3DX_PI * 2.0f;
		}
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y)* fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y)* fLength;

	}
	//任意のキーE
	if (pInput->GetPress(DIK_E) == true)
	{
		m_Camera.rotCamera.y += 0.03f;
		// 3.14を上回った
		if (m_Camera.rotCamera.y > D3DX_PI)
		{
			// 3.14を -3.14にする
			m_Camera.rotCamera.y -= D3DX_PI * 2.0f;
		}
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y)* fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y)* fLength;

	}
	//任意のキーT
	if (pInput->GetPress(DIK_T) == true)
	{
		m_Camera.rotCamera.x += 1.5f;
		m_Camera.posR.y = m_Camera.rotCamera.x;
	}
	//任意のキーB
	if (pInput->GetPress(DIK_B) == true)
	{
		m_Camera.rotCamera.x -= 1.5f;
		m_Camera.posR.y = m_Camera.rotCamera.x;
	}
	//任意のキーY
	if (pInput->GetPress(DIK_Y) == true)
	{
		m_Camera.posV.y += 2.0f;
	}
	//任意のキーN
	if (pInput->GetPress(DIK_N) == true)
	{
		m_Camera.posV.y -= 2.0f;
	}
#endif
#ifdef DEBUG
	CDebugProc::Print(1, "\n [カメラの操作] カメラの向き Z:C 左右 Y:N 上下 / 注視点 Q:E 左右 T:B 上下  \n\n");

	CDebugProc::Print(1, " カメラの視点  : ( %.1f ,%.1f ,%.1f )\n", m_Camera.posV.x, m_Camera.posV.y, m_Camera.posV.z);
	CDebugProc::Print(1, " カメラの注視点: ( %.1f ,%.1f ,%.1f )\n", m_Camera.posR.x, m_Camera.posR.y, m_Camera.posR.z);
	CDebugProc::Print(1, " カメラの向き  : ( %.1f ,%.1f ,%.1f )\n", m_Camera.rotCamera.x, m_Camera.rotCamera.y, m_Camera.rotCamera.z);
#endif

#ifdef  _DEBUG
	CDebugProc::Print(1, " カメラの視点  : ( %.1f ,%.1f ,%.1f )\n", m_Camera.posV.x, m_Camera.posV.y, m_Camera.posV.z);
	CDebugProc::Print(1, " カメラの注視点: ( %.1f ,%.1f ,%.1f )\n", m_Camera.posR.x, m_Camera.posR.y, m_Camera.posR.z);
#endif

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_Camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_Camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_Camera.mtxView,
		&m_Camera.posV,
		&m_Camera.posR,
		&m_Camera.posU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_Camera.mtxView);
}

//=============================================================================
// カメラの取得
//=============================================================================
CCamera::Camera CCamera::GetCamera(void)
{
	return m_Camera;
}

//=============================================================================
// カメラの取得
//=============================================================================
void CCamera::SetState(STATE state)
{
	m_State = state;
}

//=============================================================================
// カメラの取得
//=============================================================================
CCamera::STATE CCamera::GetState(void)
{
	return m_State;
}