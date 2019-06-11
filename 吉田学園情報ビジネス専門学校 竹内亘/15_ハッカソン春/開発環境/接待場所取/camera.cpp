//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "game.h"
#include "title.h"
#include "camera.h"
#include "input.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "result.h"

#include "player.h"
#include "UIPressEnter.h"
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
	//カメラ値初期化
	m_nCameraCnt = 0;
	m_nImpactCnt = 0;
	m_CameraSideState = CAMERASIDE_NONE;
	m_bPressEnter = false;
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
	m_Camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//カメラとプレイヤーの距離を求める
	m_Camera.DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//現在のモードを取得
	CManager::MODE mode = CManager::GetMode();
	switch (mode)
	{
	case CManager::MODE_TITLE:
		m_Camera.posV = D3DXVECTOR3(38.0f, 60.0f, -231.0f);
		m_Camera.posR = D3DXVECTOR3(38.0f, 50.0f, 68.0f);
		m_Camera.posU = D3DXVECTOR3(0.0, 0.1f, 0.0f);
		break;
	case CManager::MODE_TUTORIAL:
		m_Camera.posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);
		m_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Camera.posU = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		break;
	case CManager::MODE_GAME:
		m_Camera.posV = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
		m_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Camera.posU = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		break;
	case CManager::MODE_RESULT:
		m_Camera.posV = D3DXVECTOR3(0.0f, 180.0f, -145.0f);
		m_Camera.posR = D3DXVECTOR3(0.0f, 50.0f, 155.0f);
		m_Camera.posU = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		break;
	}

	//カメラの注視点と視点の距離を測る
	fLength = sqrtf(
		//Xの距離を求める　Xの距離の2乗
		(m_Camera.posR.x - m_Camera.posV.x) * (m_Camera.posR.x - m_Camera.posV.x)
		//Zの距離を求める　Zの距離の2乗
		+ (m_Camera.posR.z - m_Camera.posV.z) * (m_Camera.posR.z - m_Camera.posV.z));

	//カメラ値初期化
	m_nCameraCnt = 0;
	m_nImpactCnt = 0;
	m_CameraSideState = CAMERASIDE_NONE;
	m_bPressEnter = false;
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
	CPlayer *pPlayer = CGame::GetPlayer();
	//現在のモードを取得
	 CManager::MODE mode = CManager::GetMode();
	 switch (mode)
	 {
	 case CManager::MODE_GAME:

		 m_Camera.posRDest.x = pPlayer->GetPos().x - sinf(pPlayer->GetRot().y) * 30;
		 m_Camera.posRDest.y = pPlayer->GetPos().y - sinf(pPlayer->GetRot().x) * 30;
		 m_Camera.posRDest.z = pPlayer->GetPos().z - cosf(pPlayer->GetRot().y) * 30;
		 //カメラの距離
		 m_Camera.posVDest.x = pPlayer->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
		 m_Camera.posVDest.y = pPlayer->GetPos().y - sinf(m_Camera.rotCamera.x) * (fLength - 100);
		 m_Camera.posVDest.z = pPlayer->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 200);
		 //減速
		 m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pPlayer->GetMove().x;
		 m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 8;	//カメラの注視点の上下位置が変わる
		 m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pPlayer->GetMove().z;

		 //視点
		 m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f);
		 m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) + 19;
		 m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);
		 //カメラをプレイヤーの後ろにする
		 m_Camera.rotDest.y = (pPlayer->GetRot().y + D3DX_PI);
		 //カメラとプレイヤーの距離を求める
		 m_Camera.DiffAngle.y = m_Camera.rotDest.y - m_Camera.rotCamera.y;
		 //角度の設定
		 if (m_Camera.DiffAngle.y > D3DX_PI)
		 {
			 m_Camera.DiffAngle.y -= D3DX_PI* 2.0f;
		 }
		 if (m_Camera.DiffAngle.y < -D3DX_PI)
		 {
			 m_Camera.DiffAngle.y += D3DX_PI* 2.0f;
		 }
		 //徐々に角度を合わせていく 数字は回り込むスピード
		 m_Camera.rotCamera.y += m_Camera.DiffAngle.y * 0.03f;

		 if (m_Camera.rotCamera.y > D3DX_PI)
		 {
			 m_Camera.rotCamera.y -= D3DX_PI* 2.0f;
		 }
		 if (m_Camera.rotCamera.y < -D3DX_PI)
		 {
			 m_Camera.rotCamera.y += D3DX_PI* 2.0f;
		 }
		 break;

	 case CManager::MODE_RESULT:

		 if (m_Camera.posV.x <= CResult::GetBluePos().x && m_Camera.posR.x <= CResult::GetBluePos().x)
		 {
			 m_Camera.posV.x += 5.0f;
			 m_Camera.posR.x += 5.0f;
		 }

		 //キーボード情報を取得
		 CInputKeyboard *pInput = CManager::GetInputKeyboard();


		 //切り替え処理
		 if (pInput->GetTrigger(DIK_RETURN) == true)
		 {
			 m_Camera.posV = D3DXVECTOR3(CResult::GetBluePos().x, 180.0f, -145.0f);
			 m_Camera.posR = D3DXVECTOR3(CResult::GetBluePos().x, 50.0f, 155.0f);
		 }
		 break;
#if 0
	 case CManager::MODE_TUTORIAL:

		 m_Camera.posRDest.x = pPlayer->GetPos().x - sinf(pPlayer->GetRot().y) * 30;
		 m_Camera.posRDest.y = pPlayer->GetPos().y - sinf(pPlayer->GetRot().x) * 30;
		 m_Camera.posRDest.z = pPlayer->GetPos().z - cosf(pPlayer->GetRot().y) * 30;
		 //カメラの距離
		 m_Camera.posVDest.x = pPlayer->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
		 m_Camera.posVDest.y = pPlayer->GetPos().y - sinf(m_Camera.rotCamera.x) * (fLength - 100);
		 m_Camera.posVDest.z = pPlayer->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 100);
		 //減速
		 m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pPlayer->GetMove().x;
		 m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 8;	//カメラの注視点の上下位置が変わる
		 m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pPlayer->GetMove().z;

		 //視点
		 m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f);
		 m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) + 19;
		 m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);
		 //カメラをプレイヤーの後ろにする
		 m_Camera.rotDest.y = (pPlayer->GetRot().y + D3DX_PI);
		 //カメラとプレイヤーの距離を求める
		 m_Camera.DiffAngle.y = m_Camera.rotDest.y - m_Camera.rotCamera.y;
		 //角度の設定
		 if (m_Camera.DiffAngle.y > D3DX_PI)
		 {
			 m_Camera.DiffAngle.y -= D3DX_PI* 2.0f;
		 }
		 if (m_Camera.DiffAngle.y < -D3DX_PI)
		 {
			 m_Camera.DiffAngle.y += D3DX_PI* 2.0f;
		 }
		 //徐々に角度を合わせていく 数字は回り込むスピード
		 m_Camera.rotCamera.y += m_Camera.DiffAngle.y * 0.03f;

		 if (m_Camera.rotCamera.y > D3DX_PI)
		 {
			 m_Camera.rotCamera.y -= D3DX_PI* 2.0f;
		 }
		 if (m_Camera.rotCamera.y < -D3DX_PI)
		 {
			 m_Camera.rotCamera.y += D3DX_PI* 2.0f;
		 }
		 break;

	 case CManager::MODE_TITLE:
		 //カメラ取得
		 CPlayer *pPlayer = CTitle::GetPlayer();
		 if (pPlayer->GetTitleCamera() == CPlayer::TITLECAMERA_SYOUMEN)
		 {
			 m_Camera.posV.y -= 12.0f;
			 if (m_Camera.posV.y < 50)
			 {
				 m_Camera.posV.y = 50;
			 }
		 }
		 else if (pPlayer->GetTitleCamera() == CPlayer::TITLECAMERA_SENAKA)
		 {	 //カメラの距離
			 m_Camera.posRDest.x = pPlayer->GetPos().x - sinf(pPlayer->GetRot().y) * 30;
			 m_Camera.posRDest.y = pPlayer->GetPos().y - sinf(pPlayer->GetRot().x) * 30;
			 m_Camera.posRDest.z = pPlayer->GetPos().z - cosf(pPlayer->GetRot().y) * 30;
			 //カメラの距離
			 m_Camera.posVDest.x = pPlayer->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
			 m_Camera.posVDest.y = pPlayer->GetPos().y - sinf(m_Camera.rotCamera.x) * (fLength - 100);
			 m_Camera.posVDest.z = pPlayer->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 100);
			 //減速
			 m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pPlayer->GetMove().x;
			 m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 8;	//カメラの注視点の上下位置が変わる
			 m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pPlayer->GetMove().z;
			 //視点
			 m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f);
			 m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) + 25;
			 m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);
			 //カメラをプレイヤーの後ろにする
			 m_Camera.rotDest.y = (pPlayer->GetRot().y + D3DX_PI);
			 //カメラとプレイヤーの距離を求める
			 m_Camera.DiffAngle.y = m_Camera.rotDest.y - m_Camera.rotCamera.y;
			 //角度の設定
			 if (m_Camera.DiffAngle.y > D3DX_PI)
			 {
				 m_Camera.DiffAngle.y -= D3DX_PI* 2.0f;
			 }
			 if (m_Camera.DiffAngle.y < -D3DX_PI)
			 {
				 m_Camera.DiffAngle.y += D3DX_PI* 2.0f;
			 }
			 //徐々に角度を合わせていく 数字は回り込むスピード
			 m_Camera.rotCamera.y += m_Camera.DiffAngle.y * 0.03f;

			 if (m_Camera.rotCamera.y > D3DX_PI)
			 {
				 m_Camera.rotCamera.y -= D3DX_PI* 2.0f;
			 }
			 if (m_Camera.rotCamera.y < -D3DX_PI)
			 {
				 m_Camera.rotCamera.y += D3DX_PI* 2.0f;
			 }
		 }
		 else if (pPlayer->GetTitleCamera() == CPlayer::TITLECAMERA_DOWN)
		 {
			 m_nCameraCnt++;
			 if (m_CameraSideState == CAMERASIDE_NONE)
			 {
				 m_CameraSideState = CAMERASIDE_LEFT;

				 m_nCameraCnt = 0;
			 }
			 else if (m_CameraSideState == CAMERASIDE_LEFT)
			 {
				 if (m_nCameraCnt <= 3)
				 {
					 //カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
					 //m_Camera.posR.x += m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
					 m_Camera.posV.x += MOVE_CAMERA * 2;
				 }
				 else if (m_nCameraCnt <= 6)
				 {
					 //カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
					 //m_Camera.posR.x -= m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
					 m_Camera.posV.x -= MOVE_CAMERA * 2;
				 }
				 else if (m_nCameraCnt > 6)
				 {
					 m_CameraSideState = CAMERASIDE_RIGHT;
					 m_nCameraCnt = 0;
					 m_nImpactCnt++;
				 }
			 }
			 else if (m_CameraSideState == CAMERASIDE_RIGHT)
			 {
				 if (m_nCameraCnt <= 3)
				 {
					 //カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
					 //m_Camera.posR.x += m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
					 m_Camera.posV.x -= MOVE_CAMERA * 2;
				 }
				 else if (m_nCameraCnt <= 6)
				 {
					 //カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
					 //m_Camera.posR.x -= m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
					 m_Camera.posV.x += MOVE_CAMERA * 2;
				 }
				 else if (m_nCameraCnt > 6)
				 {
					 m_CameraSideState = CAMERASIDE_LEFT;
					 m_nCameraCnt = 0;
					 m_nImpactCnt++;
				 }
			 }

			 if (m_nImpactCnt == 4)
			 {
				 m_CameraSideState = CAMERASIDE_NONE;
				 m_Camera.posR.y = 80;	//カメラの注視点の上下位置が変わる

				 if (m_bPressEnter == false)
				 {
					 CUIPressEnter::Create(D3DXVECTOR3(650, 600, 0), 300, 100);
					 m_bPressEnter = true;
				 }
			 }
			 else if (m_nImpactCnt < 2)
			 {
				 m_Camera.posR.y += MOVE_CAMERA * 0.7f;
				 m_Camera.posV.z -= MOVE_CAMERA * 5;
			 }
			 else if (m_nImpactCnt < 4)
			 {
				 m_Camera.posV.z += MOVE_CAMERA * 4.5f;
			 }

		 }
		break;
#endif
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
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.75f) * MOVE_CAMERA * 2;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.75f) * MOVE_CAMERA * 2;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else if (pInput->GetPress(DIK_DOWN) == true)
		{//左手前移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.25f) * MOVE_CAMERA * 2;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.25f) * MOVE_CAMERA * 2;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else
		{
			//カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA * 2;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA * 2;
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
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y - D3DX_PI * 0.75f) * MOVE_CAMERA * 2;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y - D3DX_PI * 0.75f) * MOVE_CAMERA * 2;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else if (pInput->GetPress(DIK_DOWN) == true)
		{//右手前移動
		 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y - D3DX_PI * 0.25f) * MOVE_CAMERA * 2;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y - D3DX_PI * 0.25f) * MOVE_CAMERA * 2;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else
		{
			//カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
			m_Camera.posV.x += sinf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA * 2;
			m_Camera.posV.z += cosf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA * 2;
			//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
	}
	else if (pInput->GetPress(DIK_UP) == true)
	{//奥移動
	 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
		m_Camera.posV.x += sinf(m_Camera.rotCamera.y) * MOVE_CAMERA * 2;
		m_Camera.posV.z += cosf(m_Camera.rotCamera.y) * MOVE_CAMERA * 2;
		//カメラの注視点の移動 カメラの位置 + カメラの角度 * カメラの距離
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
	}
	else if (pInput->GetPress(DIK_DOWN) == true)
	{//手前移動
	 //カメラの移動	カメラの移動する角度(カメラの向き + 角度) * 移動量
		m_Camera.posV.x -= sinf(m_Camera.rotCamera.y) * MOVE_CAMERA * 2;
		m_Camera.posV.z -= cosf(m_Camera.rotCamera.y) * MOVE_CAMERA * 2;
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


#ifdef _DEBUG
	CDebugProc::Print(1, "\n [カメラの操作] カメラの向き Z:C 左右 Y:N 上下 / 注視点 Q:E 左右 T:B 上下  \n\n");

	CDebugProc::Print(1, " カメラの視点  : ( %.1f ,%.1f ,%.1f )\n", m_Camera.posV.x, m_Camera.posV.y, m_Camera.posV.z);
	CDebugProc::Print(1, " カメラの注視点: ( %.1f ,%.1f ,%.1f )\n", m_Camera.posR.x, m_Camera.posR.y, m_Camera.posR.z);
	CDebugProc::Print(1, " カメラの向き  : ( %.1f ,%.1f ,%.1f )\n", m_Camera.rotCamera.x, m_Camera.rotCamera.y, m_Camera.rotCamera.z);
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
