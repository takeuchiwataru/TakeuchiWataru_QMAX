//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 杉本涼
//
//=============================================================================
#include "camera.h"
#include "mesh.h"
#include "SceneModel.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		DISTANCE		(250)			//注視点と視点の距離
#define		CAMERA_MOVE		(0.8f)			//カメラの移動速度
#define		ROTPOOR_RY		(50)			//注視点上下 +下, -上
#define		ROTPOOR_VY		(80)				//カメラ本体 +上, -下
#define		DRAW_ANGLE		(45.0f)				//カメラ本体 +上, -下
#define		DRAW_ANGLEP		(DRAW_ANGLE + 10.0f)				//カメラ本体 +上, -下
#define		DRAW_DISTANCE	(2500.0f * 2500.0f)				//カメラ本体 +上, -下
#define		DRAW_DISTANCE2	(100.0f * 100.0f)				//カメラ本体 +上, -下

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CCamera::Info CCamera::m_info;			//カメラ情報

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera(){ CManager::GetCamera() = this; }
//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera() { }
//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::Init(void)
{
	m_info.pChar = NULL;
	m_info.pMove = NULL;

	m_posV = D3DXVECTOR3(0.0f, 200.0f, 200.0f);				//視点
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.1f);				//注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//ナニコレ(笑)
	m_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//目的
	m_rot = D3DXVECTOR3(D3DX_PI * 0.065f, D3DX_PI, 0.0f);	//角度
	m_addpos = D3DXVECTOR3(0.0f, ROTPOOR_VY, 0.0f);			//カメラ独立移動
	m_targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//追従するカメラの場所
	m_fDistance = DISTANCE;									//視点と注視点の距離

	m_fGMagnification = 0.5f;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
	CManager::GetCamera() = NULL;
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Update(void)
{
	bool bDrop = false;
	if (CManager::GetPlayer() != NULL)
	{
		if (CManager::GetPlayer()->GetbDrop()) { bDrop = true; }
	}

	if (m_info.state == STATE_GAME)
	{

	}
	else { UpdateScene(); }

	if (m_info.pChar != NULL && m_info.pMove != NULL)
	{//追従の場所の更新
		CInputKeyboard *pInputKey = CManager::GetInputKey();
		CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
		float fPosY = m_posV.y;

		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			if (pInputKey->GetPress(DIK_U)) { m_rot.y += D3DX_PI * 0.0125f; }
			if (pInputKey->GetPress(DIK_O)) { m_rot.y -= D3DX_PI * 0.0125f; }
			if (pInputKey->GetPress(DIK_Y)) { m_rot.x += D3DX_PI * 0.0125f; }
			if (pInputKey->GetPress(DIK_H)) { m_rot.x -= D3DX_PI * 0.0125f; }
			if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
			if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
			if (pInputPad0->GetStickDefeat(1))
			{
				m_rot.y += D3DX_PI * 0.01f * (pInputPad0->GetnStickX(1) * 0.00005f);
				m_rot.x += D3DX_PI * 0.01f * (pInputPad0->GetnStickY(1) * -0.00005f);
			}

			if (m_rot.x > D3DX_PI * 0.3f) { m_rot.x = D3DX_PI * 0.3f; }
			if (m_rot.x < -D3DX_PI * 0.3f) { m_rot.x = -D3DX_PI * 0.3f; }
			if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
			if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
		}

		if (m_pDistance != NULL) { m_fDistance += (m_pDistance[0] - m_fDistance) * 0.05f; }
		m_targetpos += (m_info.pChar[0] - m_targetpos) * 0.08f;

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + m_targetpos + m_addpos;	//見る場所 + 水平移動分
		//m_posR += D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -30.0f;
		//m_posR +=D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -50.0f;

		//視点　自分 + (角度 * 距離) + 水平移動分
		m_goal = D3DXVECTOR3(
			m_targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),	//X軸
			m_targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,		//Y軸
			m_targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z軸
		m_posV += (m_goal - m_posV) * m_fGMagnification;

		if (bDrop)
		{//落ちているなら
			m_rot.y += (m_fDRot - m_rot.y) * 0.05f;
			m_posV.y = fPosY;
		}
		//m_posV.y = fY;
	}
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Reset(void)
{
	if (m_info.pChar != NULL)
	{//追従の場所の更新
		if (m_pDistance != NULL) { m_fDistance = m_pDistance[0]; }

		m_targetpos = m_info.pChar[0];
		//if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y < -50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y - 50; }
		//if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y > 50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y + 50; }

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + m_targetpos + m_addpos;	//見る場所 + 水平移動分

																						//視点　自分 + (角度 * 距離) + 水平移動分
		m_goal = D3DXVECTOR3(
			m_targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),						//X軸
			m_targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,									//Y軸
			m_targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z軸

		m_posV = m_goal;
	}
}
//=============================================================================
// 3Dの描画処理落ち対策処理
//=============================================================================
bool CCamera::DrawCamera(D3DXVECTOR3 &pos, float fLength)
{//注視点から見て一定範囲内なら描画
	//float fAngle = atan2f(m_posV.x - pos.x, m_posV.z - pos.z) - m_rot.y;

	//if (fAngle > D3DX_PI) { fAngle -= D3DX_PI * 2.0f; }
	//if (fAngle < -D3DX_PI) { fAngle += D3DX_PI * 2.0f; }

	//if (fAngle >= -D3DX_PI * (DRAW_ANGLEP / 180) && fAngle <= +D3DX_PI * (DRAW_ANGLEP / 180))
	//{//カメラの向き通りなら
	//	float fDistance = powf(m_posR.x - pos.x, 2) + powf(m_posR.z - pos.z, 2);
	//	if (fDistance < fLength + DRAW_DISTANCE) { return true; }
	//}

	//if (CManager::GetMode() == CManager::MODE_TITLE) { return true; }
	return true;
}
//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	D3DXVECTOR3 WKValue, WKmove;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXVECTOR3	WKlength = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	D3DXVECTOR3	WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	WKposV = m_posV;
	bool bWKJump = false;

	WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -30.0f;
	WKmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nQuake > 0)
	{
		D3DXVECTOR3	WKposV2;
		D3DXVECTOR3	WKrot = m_rot;
		WKrot.x += (float)((rand() % 100) - 50) * (D3DX_PI * (m_fQuake * m_nQuake));
		WKrot.y += (float)((rand() % 100) - 50) * (D3DX_PI * (m_fQuake * m_nQuake));
		WKposV2 = D3DXVECTOR3(
			m_targetpos.x + (sinf(WKrot.y) * m_fDistance) * cosf(WKrot.x),	//X軸
			m_targetpos.y + sinf(WKrot.x) * m_fDistance + ROTPOOR_VY,		//Y軸
			m_targetpos.z + (cosf(WKrot.y) * m_fDistance) * cosf(WKrot.x));	//Z軸
		m_posV += (WKposV2 - m_posV) * m_fGMagnification;
		m_nQuake--;
	}
	int		nCount = 0;
	CMesh::MeshCollisionCeiling(WKposV, WKValue, WKlength);
	CMesh::MeshCollisionWall(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);
	CMesh::MeshCollisionField(WKposV, WKValue, WKmove, WKlength, WKnor, bWKJump);
	WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * 30.0f;
	CSceneObjct::CollisionAll(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(DRAW_ANGLE),	//画角
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		11000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView, &WKposV, &m_posR, &m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::SetScene(SCENE_TYPE type)
{
	m_info.nCntState = 0;
	m_info.nCntTime = 0;
	m_info.state = STATE_MOVIE;
	m_info.scene = type;
}
//=============================================================================
// シーン再生処理
//=============================================================================
void CCamera::UpdateScene(void)
{
	if (m_info.state == STATE_MOVIE)
	{//シーン再生
		switch (m_info.scene)
		{
		case SCENE_TYPE_NO:	//エラー処理用
			Init();
			break;

		case SCENE_TYPE_BOSS:	//ボス前
			//Scene_BOSS();
			break;
		}
	}
}
