//---------------------------------------------------------------------
//	プレイヤー処理(player.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "player.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "fade.h"
#include "scene3D.h"
#include "meshField.h"
#include "model.h"
#include "objectBG.h"
#include "billboardEnemy.h"
#include "billboardItem.h"
#include "effect.h"
#include "UIGauge.h"
#include "UITime.h"
#include "UILife.h"
#include "UIItem.h"
#include "UIPressEnter.h"
#include "UIFinish.h"
#include "UIStart.h"
#include "bullet.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FILE_NAME						("data\\TEXT\\PlayerMotion.txt")
#define MOVE_PLAYER						(7.0f)		//移動量
#define MOVE_PLAYER_DASH				(3.0f)		//ダッシュ時の加算移動量
#define FIELD_SIZE						(100.0f)	//フィールドの大きさ

#define TIMER_JUMP						(60)		//ゴール時のジャンプまでのタイマー
#define RUN_FRAME						(2.0f)		//走っているときのフレームを割る値
#define APPEAR_FRAME					(15)		//無敵時間

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
CPlayer::PLAYERSTATE		CPlayer::m_State = CPlayer::PLAYERSTATE_NONE;
D3DXVECTOR3					CPlayer::m_pos = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3					CPlayer::m_rot = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3					CPlayer::m_move = D3DXVECTOR3(0, 0, 0);

LPD3DXMESH					CPlayer::m_pMeshModel[MAX_PARTS] = {};
LPD3DXBUFFER				CPlayer::m_pBuffMatModel[MAX_PARTS] = {};
LPDIRECT3DTEXTURE9			CPlayer::m_pTextureModel[MAX_PARTS] = {};
DWORD						CPlayer::m_nNumMatModel[MAX_PARTS] = {};


//--------------------------------------------
//グローバル変数
//--------------------------------------------
int g_nNumModel;
char g_aFileNameModel[MAX_PARTS][256];

//--------------------------------------------
//プレイヤークラス コンストラクタ
//--------------------------------------------
CPlayer::CPlayer() : CScene(6, CScene::OBJTYPE_SCENEX)
{
	m_bJump = false;
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_move = D3DXVECTOR3(0, 0, 0);					//移動量
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	m_State = PLAYERSTATE_NONE;						//状態
	m_nGameEndCnt = 0;								//カウント
	m_nJumpEndTimer = 0;
	m_nStartTimer = 0;
	m_nCntTumble = 0;
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_pMeshModel[nCnt] = NULL;
		m_pBuffMatModel[nCnt] = NULL;
		m_pTextureModel[nCnt] = NULL;
		m_nNumMatModel[nCnt] = NULL;
		m_apModel[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_pKeyInfo[nCnt] = NULL;		//キー情報へのポインタ
	}

	m_nKey = 0;							//現在のキーナンバー
	m_nCountFlame = 0;					//フレーム数
	m_nCntTimer = 0;
	m_nCntAppear = 0;
	m_MotionState = MOTIONSTATE_NEUTRAL;
	m_DashState = DASHSTATE_NORMAL;
	m_bFinish = false;
	m_bStart = false;
	m_bMotionEnd = false;
}

//--------------------------------------------
//プレイヤークラス デストラクタ
//--------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	//プレイヤーポインタ
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	//プレイヤーの初期化
	pPlayer->Init();
	//初期値が入った後
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->m_fDestAngle = rot.y;
	//プレイヤーの情報を返す
	return pPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_SCENEX);

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_pMeshModel[nCnt] = NULL;
		m_pBuffMatModel[nCnt] = NULL;
		m_pTextureModel[nCnt] = NULL;
		m_nNumMatModel[nCnt] = NULL;
		m_apModel[nCnt] = NULL;
		g_aFileNameModel[nCnt][0] = '\0';
	}

	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_pKeyInfo[nCnt] = NULL;		//キー情報へのポインタ
	}

	//m_rot = D3DXVECTOR3(0, D3DX_PI * 1.0f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	//m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;							//プレイヤーの向き
	m_bJump = false;							//ジャンプの状態
	m_bFinish = false;							//ゴールフラグ
	m_bStart = false;							//スタートフラグ
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		//頂点バッファへのポインタ
	m_State = PLAYERSTATE_NEUTRAL;				//最初のモーションの状態
	m_nGameEndCnt = 0;							//ゲーム終了までのカウント
	m_nJumpEndTimer = 0;						//ゲームが終わるまでジャンプするタイマー
	m_nStartTimer = 0;							//スタート時に少し待ってスタートするタイマー
	m_nCntTumble = 0;							//回転の数を数える
	m_nCntAppear = 0;

	//モーション用変数
	m_nKey = 0;			//現在のキー
	m_nCountFlame = 0;	//現在のフレーム
	m_nMotionType = 0;	//現在のモーションタイプ
	m_nOldMotion = 0;	//前のモーション
	m_nCntTimer = 0;	//タイトルカメラの状態
	m_TitleCamState = TITLECAMERA_NORMAL;
	//プレイヤー情報の読み込み
	FileLoad();
	//モーションの状態
	m_MotionState = MOTIONSTATE_NEUTRAL;
	m_DashState = DASHSTATE_NORMAL;

	m_effectCol = D3DXCOLOR(0, 0, 0, 1);
	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		//if (m_apModel[nCnt] != NULL)
		//{
		//	m_apModel[nCnt]->Uninit();
		//	delete m_apModel[nCnt];
		//	m_apModel[nCnt] = NULL;
		//}
	}

	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		if (m_pKeyInfo[nCnt] != NULL)
		{
			m_pKeyInfo[nCnt] = NULL;		//キー情報へのポインタ
		}
	}

	UnLoad();

	//自分を消す(プレイヤーを破棄)
	Release();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CPlayer::Update(void)
{
#if 1
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//ジョイパッド情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//現在のモードを取得
	CManager::MODE mode = CManager::GetMode();
	//カメラ取得
	CCamera *pCamera = CManager::GetCamera();
	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(2);

	//エフェクト用関数
	D3DXVECTOR3 RotRand;
	D3DXVECTOR3 PosRand;
	D3DXVECTOR3 effectmove;

	//前回の位置を保存
	m_posold = m_pos;

	switch (mode)
	{
	case CManager::MODE_TITLE:
		break;
	case CManager::MODE_TUTORIAL:
		break;
	case CManager::MODE_GAME:
#if 1
		if (m_State == PLAYERSTATE_NEUTRAL)
		{
			if (m_bStart == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_START00);
				CUIStart::Create(D3DXVECTOR3(630, 300, 0), 50, 0);
				m_bStart = true;
			}
			//CUIFinish::Create(D3DXVECTOR3(630, 300, 0), 300, 0);
			//モーション切り替え
			m_nMotionType = 0;
			//スタートタイマー加算
			m_nStartTimer++;
			if (m_nStartTimer > 190)
			{
				m_State = PLAYERSTATE_NORMAL;
				m_MotionState = MOTIONSTATE_RUN;
			}
		}

		if (m_State == PLAYERSTATE_NORMAL || m_State == PLAYERSTATE_APPEAR)
		{

			if (m_State == PLAYERSTATE_APPEAR)
			{
				m_nCntAppear++;
				if (m_nCntAppear > APPEAR_FRAME)
				{
					m_State = PLAYERSTATE_NORMAL;
					m_nCntAppear = 0;
				}
			}

			if (m_bJump == false && m_MotionState == MOTIONSTATE_RUN)
			{
				//モーション切り替え
				m_nMotionType = 1;
				m_MotionState = MOTIONSTATE_RUN;
			}
			//自動移動
			m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * MOVE_PLAYER;
			m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * MOVE_PLAYER;
			//m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);

			//任意のキーA
			if (pInput->GetPress(DIK_A) == true || pInputJoypad->GetPress(CInputJoypad::STICK_L_LEFT) == true)
			{
				//モーション切り替え
				if (m_bJump == false)
				{
					if (m_MotionState != MOTIONSTATE_TUMBLE && m_MotionState != MOTIONSTATE_JET)
					{
						m_nMotionType = 1;
						m_MotionState = MOTIONSTATE_RUN;
					}
				}
				//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
				m_move.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MOVE_PLAYER * 0.5f;
				m_move.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MOVE_PLAYER * 0.5f;;
				//m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f);
			}
			//任意のキーD
			else if (pInput->GetPress(DIK_D) == true || pInputJoypad->GetPress(CInputJoypad::STICK_L_RIGHT) == true)
			{
				//モーション切り替え
				if (m_bJump == false)
				{
					if (m_MotionState != MOTIONSTATE_TUMBLE && m_MotionState != MOTIONSTATE_JET)
					{
						m_nMotionType = 1;
						m_MotionState = MOTIONSTATE_RUN;
					}
				}
				//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
				m_move.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MOVE_PLAYER * 0.5f;;
				m_move.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MOVE_PLAYER * 0.5f;;
				//m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f);
			}

			//任意のキーW
			//if (pInput->GetPress(DIK_W) == true && m_MotionState == MOTIONSTATE_RUN
			//	|| pInput->GetPress(DIK_W) == true && m_MotionState == MOTIONSTATE_JUMP
			//	|| pInputJoypad->GetPress(CInputJoypad::STICK_L_UP) == true && m_MotionState == MOTIONSTATE_RUN
			//	|| pInputJoypad->GetPress(CInputJoypad::STICK_L_UP) == true && m_MotionState == MOTIONSTATE_JUMP)
			//{	//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			//	m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * MOVE_PLAYER_DASH;
			//	m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * MOVE_PLAYER_DASH;
			//	m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);
			//	//m_State = PLAYERSTATE_DASH;
			//	m_DashState = DASHSTATE_DASH;
			//	//CUIGauge::SetGauge(2);
			//}
			//else if (pInput->GetRelease(DIK_W) == true || pInputJoypad->GetPress(CInputJoypad::STICK_L_UP) != true)
			//{
			//	//m_State = PLAYERSTATE_NORMAL;
			//	m_DashState = DASHSTATE_NORMAL;
			//}

			//ジャンプ
			//if (pInput->GetTrigger(DIK_SPACE) == true && m_bJump == false && m_MotionState == MOTIONSTATE_RUN
			//	|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && m_bJump == false && m_MotionState == MOTIONSTATE_RUN)
			//{
			//	pSound->PlaySound(pSound->SOUND_LABEL_SE_JUMP);

			//	m_move.y += 10.0f;
			//	//ジャンプフラグをtrueに
			//	m_bJump = true;

			//	//モーション切り替え
			//	m_nCountFlame = 0;
			//	m_nMotionType = 2;
			//	m_nKey = 0;
			//	m_MotionState = MOTIONSTATE_JUMP;
			//	//CUIGauge::SetGauge(50);
			//}

			//if (pInput->GetTrigger(DIK_RETURN) == true && m_MotionState == MOTIONSTATE_RUN
			//	|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_B) == true && m_MotionState == MOTIONSTATE_RUN)
			//{
			//	//モーション切り替え
			//	m_nCountFlame = 0;
			//	m_nMotionType = 4;
			//	m_nKey = 0;
			//	m_MotionState = MOTIONSTATE_TUMBLE;
			//	//CUIGauge::SetGauge(100);
			//	pSound->PlaySound(pSound->SOUND_LABEL_SE_TUMBLE);
			//}

			//if (pInput->GetTrigger(DIK_S) == true && m_MotionState == MOTIONSTATE_RUN && CUIGauge::GetGaugeState() == CUIGauge::GAUGESTATE_MAXGAUGE
			//	|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_Y) == true && m_MotionState == MOTIONSTATE_RUN && CUIGauge::GetGaugeState() == CUIGauge::GAUGESTATE_MAXGAUGE)
			//{
			//	//モーション切り替え
			//	m_nCountFlame = 0;
			//	m_nMotionType = 7;
			//	m_nKey = 0;
			//	m_MotionState = MOTIONSTATE_JET;
			//	m_State = PLAYERSTATE_NORMAL;
			//	m_DashState = DASHSTATE_NORMAL;
			//}

			//ゲージを使い切ったとき
		/*	if (CUIGauge::GetGaugeState() == CUIGauge::GAUGESTATE_NORMAL &&  m_MotionState == MOTIONSTATE_JET)
			{

				m_MotionState = MOTIONSTATE_RUN;
			}*/

#ifdef  _DEBUG
			//if (pInput->GetTrigger(DIK_T) == true)
			//{
			//	//モーション切り替え
			//	m_nCountFlame = 0;
			//	m_nMotionType = 5;
			//	m_nKey = 0;
			//	m_bMotionEnd = false;
			//	m_MotionState = MOTIONSTATE_DAMAGE;
			//}
			//if (pInput->GetTrigger(DIK_Y) == true)
			//{
			//	//モーション切り替え
			//	m_nCountFlame = 0;
			//	m_nMotionType = 6;
			//	m_nKey = 0;
			//	m_bMotionEnd = false;
			//	m_MotionState = MOTIONSTATE_GETUP;
			//}
#endif

			if (pInput->GetTrigger(DIK_SPACE) == true)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_THROW);

				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z + 30.0f),
					D3DXVECTOR3(0, 0, 30),
					50);
			}

			if (m_bJump == false && m_MotionState == MOTIONSTATE_TUMBLE)
			{
				//自動移動
				m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * 5.0f;
				m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * 5.0f;
			}
			if (m_bJump == false && m_MotionState == MOTIONSTATE_JET)
			{
				//自動移動
				m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * 15.0f;
				m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * 15.0f;
			}
	}
#endif
		break;
	}

#if 0
	//任意のキーA
	if (pInput->GetPress(DIK_A) == true || pInputJoypad->GetPress(CInputJoypad::STICK_L_LEFT) == true)
	{
		//モーション切り替え
		if (m_bJump == false)
		{
			if (m_MotionState != MOTIONSTATE_TUMBLE && m_MotionState != MOTIONSTATE_JET)
			{
				m_nMotionType = 1;
				m_MotionState = MOTIONSTATE_RUN;
			}
		}
		//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
		m_move.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MOVE_PLAYER * 0.5f;
		m_move.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MOVE_PLAYER * 0.5f;;
	}
	//任意のキーD
	else if (pInput->GetPress(DIK_D) == true || pInputJoypad->GetPress(CInputJoypad::STICK_L_RIGHT) == true)
	{
		//モーション切り替え
		if (m_bJump == false)
		{
			if (m_MotionState != MOTIONSTATE_TUMBLE && m_MotionState != MOTIONSTATE_JET)
			{
				m_nMotionType = 1;
				m_MotionState = MOTIONSTATE_RUN;
			}
		}
		//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
		m_move.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MOVE_PLAYER * 0.5f;;
		m_move.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MOVE_PLAYER * 0.5f;;
	}
#endif


#if 0

	//任意のキーA
	if (pInput->GetPress(DIK_A) == true)
	{
		//モーション切り替え
		if (m_bJump == false)
		{
			m_nMotionType = 1;
			m_MotionState = MOTIONSTATE_RUN;
		}

		if (pInput->GetPress(DIK_W) == true)
		{//左上移動
		 //モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_move.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f) * MOVE_PLAYER;
			m_move.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f) * MOVE_PLAYER;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f);
		}
		else if (pInput->GetPress(DIK_S) == true)
		{//左下移動
		 //モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_move.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f) * MOVE_PLAYER;
			m_move.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f) * MOVE_PLAYER;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f);
		}
		else
		{	//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_move.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MOVE_PLAYER;
			m_move.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MOVE_PLAYER;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f);
		}
	}
	//任意のキーD
	else if (pInput->GetPress(DIK_D) == true)
	{
		//モーション切り替え
		if (m_bJump == false)
		{
			m_nMotionType = 1;
			m_MotionState = MOTIONSTATE_RUN;
		}

		if (pInput->GetPress(DIK_W) == true)
		{//右上移動
		 //モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_move.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f) * MOVE_PLAYER;
			m_move.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f) * MOVE_PLAYER;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f);
		}
		else if (pInput->GetPress(DIK_S) == true)
		{//右下移動
		 //モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_move.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f) * MOVE_PLAYER;
			m_move.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f) * MOVE_PLAYER;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f);
		}
		else
		{	//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_move.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MOVE_PLAYER;
			m_move.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MOVE_PLAYER;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f);
		}
	}
	//任意のキーW
	else if (pInput->GetPress(DIK_W) == true)
	{	//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
		m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * MOVE_PLAYER;
		m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * MOVE_PLAYER;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);
		//モーション切り替え
		if (m_bJump == false)
		{
			m_nMotionType = 1;
			m_MotionState = MOTIONSTATE_RUN;
		}

	}
	//任意のキーS
	else if (pInput->GetPress(DIK_S) == true)
	{
		//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
		m_move.x -= sinf(pCamera->GetCamera().rotCamera.y) * MOVE_PLAYER;
		m_move.z -= cosf(pCamera->GetCamera().rotCamera.y) * MOVE_PLAYER;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.0f);
		//モーション切り替え
		if (m_bJump == false)
		{
			m_nMotionType = 1;
			m_MotionState = MOTIONSTATE_RUN;
		}
	}
	else
	{
		//移動していない ジャンプしていない　ニュートラル状態
		if (m_bJump == false)
		{
			//モーション切り替え
			m_nMotionType = 0;
			m_MotionState = MOTIONSTATE_NEUTRAL;
		}
	}
#endif

	//向きの慣性
	m_fDiffAngle = m_fDestAngle - m_rot.y;
	//角度の設定
	if (m_fDiffAngle > D3DX_PI)
	{
		m_fDiffAngle -= D3DX_PI* 2.0f;
	}
	if (m_fDiffAngle < -D3DX_PI)
	{
		m_fDiffAngle += D3DX_PI* 2.0f;
	}
	m_rot.y += m_fDiffAngle * 0.1f;
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI* 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI* 2.0f;
	}

	//重力
	//m_move.y -= cosf(D3DX_PI * 0) * 0.7f;

	//減速
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;
	//位置更新
	m_pos += m_move;

	if (m_pos.x > 500.0f)
	{
		m_pos.x = 500;
	}
	else if (m_pos.x < -500.0f)
	{
		m_pos.x = -500;
	}

	//モーション更新
	UpdateMotion();

	//地面との当たり判定
	CollisitionGround();
	// オブジェクトの当たり判定
	CollisitionObject3D(&m_pos, &m_posold, &m_move);
	// 敵 ビルボードの当たり判定
	CollisitionBillBoardEnemy(&m_pos, &m_posold, &m_move);
	// アイテム ビルボードの当たり判定
	CollisitionBillBoardItem(&m_pos, &m_posold, &m_move);

#ifdef  _DEBUG
	CDebugProc::Print(1, " プレイヤーの位置  : ( %.1f ,%.1f ,%.1f )\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print(1, " Numキー  : (%d)\n", m_nKey);
	CDebugProc::Print(1, " m_nCountFlame  : (%d)\n", m_nCountFlame);
	CDebugProc::Print(1, " m_nMotionType  : (%d)\n", m_nMotionType);
	CDebugProc::Print(1, " m_MotionState  : (%d)\n", m_MotionState);
	CDebugProc::Print(1, " m_bMotionEnd   : (%s)\n", m_bMotionEnd ? "true" : "false");

#endif

#if 1

	if (pInput->GetPress(DIK_0) == true && pInput->GetPress(DIK_1) == true)
	{
		m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * 50.0f;
		m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * 50.0f;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);
	}

	//終了処理
	if (m_pos.z > 30000.0f)
	{
		if (m_nMotionType != 0)
		{
			//モーション切り替え
			m_nMotionType = 0;
		}

		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			if (m_bFinish == false)
			{
				m_bFinish = true;
				CUIFinish::Create(D3DXVECTOR3(630, 300, 0), 300, 0);
			}

			//CLEAR状態へ
			m_State = PLAYERSTATE_GAMECLEAR;
			//カウント加算
			m_nGameEndCnt++;

			if (m_nGameEndCnt > 180)
			{
				CFade::SetFade(CManager::MODE_RESULT);
			}
		}
	}

#endif
#endif
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//影の描画処理
	D3DXMATRIX	mtxShadow;
	D3DXPLANE	planeField;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, normal;

	CLight *pLight = CManager::GetLight();

	//減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ライトを無効にする
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);
	//ライトの設定
	VecLight = D3DXVECTOR4(0.0f, 1.0f, -1.0f, 0.0f);
	//影の位置設定
	pos = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	//法線の設定
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//平面を作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//影マトリックスの設定
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
	//ワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->m_bShadow = true;
			m_apModel[nCnt]->Draw();
		}
	}

	//レンダーステイトを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->m_bShadow = false;
			m_apModel[nCnt]->Draw();
		}
	}
}

//=============================================================================
// プレイヤーの位置設定
//=============================================================================
void CPlayer::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	return S_OK;
}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CPlayer::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		// メッシュの開放
		if (m_pMeshModel[nCnt] != NULL)
		{
			m_pMeshModel[nCnt]->Release();
			m_pMeshModel[nCnt] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMatModel[nCnt] != NULL)
		{
			m_pBuffMatModel[nCnt]->Release();
			m_pBuffMatModel[nCnt] = NULL;
		}

		//テクスチャの破棄
		if (m_pTextureModel[nCnt] != NULL)
		{
			m_pTextureModel[nCnt]->Release();
			m_pTextureModel[nCnt] = NULL;
		}
	}
}

//=============================================================================
// プレイヤーのダメージ
//=============================================================================
void CPlayer::HitDamage(int nDamage)
{

}
//=============================================================================
// プレイヤーの位置
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// プレイヤーの回転
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// プレイヤーの移動
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//=============================================================================
//	プレイヤーのモーションの状態を取得
//=============================================================================
CPlayer::MOTIONSTATE CPlayer::GetMotionState(void)
{
	return m_MotionState;
}

//=============================================================================
//	プレイヤーのモーションの状態を設定
//=============================================================================
void CPlayer::SetMotionState(MOTIONSTATE MotionState)
{
	//モーション切り替え
	m_nCountFlame = 0;
	m_nKey = 0;
	m_bMotionEnd = false;
	m_MotionState = MotionState;
	m_nMotionType = (int)MotionState;

	if (m_MotionState == MOTIONSTATE_DAMAGE)
	{
		m_State = PLAYERSTATE_DAMAGE;
	}
}

//=============================================================================
//	プレイヤーの状態を取得
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetPlayerState(void)
{
	return m_State;
}

//=============================================================================
//	プレイヤーのパーツ情報を取得
//=============================================================================
CModel *CPlayer::GetapModel(int nIdx)
{
	return m_apModel[nIdx];
}

//=============================================================================
//	床の当たり判定
//=============================================================================
void CPlayer::CollisitionGround(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(3);

	//ジャンプをfalseに
	//m_bJump = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがメッシュだったら
			if (pScene->GetObjType() == OBJTYPE_MESHFIELD)
			{
				//プレイヤーのHightを入れる
				if (((CSceneMeshField*)pScene)->GetHeightbool(m_pos))
				{
					//ジャンプしていない状態にする
					m_bJump = false;
					//落ちたときにmoveを初期化する
					m_move.y = 0.0f;
				}
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}

//=============================================================================
//	オブジェクトの当たり判定
//=============================================================================
void CPlayer::CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(3);

	//変数宣言
	bool bLand = false;

	//bLandの初期化処理
	m_bLand = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがオブジェクトだったら
			if (pScene->GetObjType() == OBJTYPE_BGMODEL)
			{
				//オブジェクトのあたる判定
				bLand = ((CObjectBG*)pScene)->CollisionObject(pPos, pPosOld, pMove);
				//着地を共有する
				if (bLand)
				{
					m_bJump = false;
					m_bLand = bLand;
				}
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}

//=============================================================================
//	敵ビルボードの当たり判定
//=============================================================================
void CPlayer::CollisitionBillBoardEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(5);

	//変数宣言
	bool bLand = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがオブジェクトだったら
			if (pScene->GetObjType() == OBJTYPE_BILLBOARDENEMY)
			{
				//オブジェクトのあたる判定
				bLand = ((CBillBoardEnemy*)pScene)->CollisionBillboardEnemy(pPos, pPosOld, pMove);
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}

}

//=============================================================================
//	アイテムビルボードの当たり判定
//=============================================================================
void CPlayer::CollisitionBillBoardItem(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(5);

	//変数宣言
	bool bLand = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがオブジェクトだったら
			if (pScene->GetObjType() == OBJTYPE_BILLBOARDITEM)
			{
				//オブジェクトのあたる判定
				bLand = ((CBillBoardItem*)pScene)->CollisionBillboardItem(pPos, pPosOld, pMove);
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}

}


//=============================================================================
// プレイヤーのモーション
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	//サウンド情報を取得
	//CSound *pSound = CManager::GetSound();
	CSound *pSound = CManager::GetSound(2);

	//モーション
	KEY *pKey, *pNextKey;
	float fRateMotion;
	float fDiffMotion;
	float fPlusData;
	float fMinusData;
	float fPlusPos;
	float fMinusPos;

	D3DXVECTOR3 rotmotion;
	D3DXVECTOR3 posmotion;
	D3DXVECTOR3 BodyRot;

	//エフェクト用関数
	D3DXVECTOR3 RotRand;
	D3DXVECTOR3 PosRand;
	D3DXVECTOR3 effectmove;

#if 1

	//キーが最大数を上回らないように
	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
	}

	//モーション更新
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_apModel[nCntParts] != NULL)
		{
			//現在のキーを取得
			pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
			//次のキーを取得
			pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];
			//走り状態の時はモーションのフレームを減らす
			if (m_DashState == DASHSTATE_DASH && m_MotionState == MOTIONSTATE_RUN)
			{
				//現在のキーから次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
				fRateMotion = (float)m_nCountFlame / (float)(m_pKeyInfo[m_nMotionType][m_nKey].nFrame / 2.0f);
			}
			else
			{
				//現在のキーから次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
				fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;
			}
			//ROT

			if (nCntParts == 0)
			{
				fPlusData = pNextKey->frotX + pKey->frotX;
				fMinusData = pNextKey->frotX - pKey->frotX;
				fPlusPos;
				fMinusPos;

				//値を出す(絶対値)
				fPlusData = abs(fPlusData);
				fMinusData = abs(fMinusData);
				//差分小さいほう
				if (fPlusData < fMinusData)
				{	//現在のキーと次のキーの各要素の差分を算出
					fDiffMotion = pNextKey->frotX + pKey->frotX;
					//相対値を差分を使って各要素の値を算出
					rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);
				}
				else
				{	//現在のキーと次のキーの各要素の差分を算出
					fDiffMotion = pNextKey->frotX - pKey->frotX;
					//相対値を差分を使って各要素の値を算出
					rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);
				}

				fPlusData = pNextKey->frotY + pKey->frotY;
				fMinusData = pNextKey->frotY - pKey->frotY;
				//値を出す(絶対値)
				fPlusData = abs(fPlusData);
				fMinusData = abs(fMinusData);
				//差分小さいほう
				if (fPlusData < fMinusData)
				{	//現在のキーと次のキーの各要素の差分を算出
					fDiffMotion = pNextKey->frotY + pKey->frotY;
					//相対値を差分を使って各要素の値を算出
					rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
				}
				else
				{	//現在のキーと次のキーの各要素の差分を算出
					fDiffMotion = pNextKey->frotY - pKey->frotY;
					//相対値を差分を使って各要素の値を算出
					rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
				}

				fPlusData = pNextKey->frotZ + pKey->frotZ;
				fMinusData = pNextKey->frotZ - pKey->frotZ;
				//値を出す(絶対値)
				fPlusData = abs(fPlusData);
				fMinusData = abs(fMinusData);
				//差分小さいほう
				if (fPlusData < fMinusData)
				{	//現在のキーと次のキーの各要素の差分を算出
					fDiffMotion = pNextKey->frotZ + pKey->frotZ;
					//相対値を差分を使って各要素の値を算出
					rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
				}
				else
				{	//現在のキーと次のキーの各要素の差分を算出
					fDiffMotion = pNextKey->frotZ - pKey->frotZ;
					//相対値を差分を使って各要素の値を算出
					rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
				}

				//POS
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//相対値を差分を使って各要素の値を算出
				posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);
				//POS
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//相対値を差分を使って各要素の値を算出
				posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);
				//POS
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//相対値を差分を使って各要素の値を算出
				posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);
			}
			else
			{
				//ROT
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotX - pKey->frotX;
				//相対値を差分を使って各要素の値を算出
				rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);
				//POS
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//相対値を差分を使って各要素の値を算出
				posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);

				//ROT
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotY - pKey->frotY;
				//相対値を差分を使って各要素の値を算出
				rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
				//POS
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//相対値を差分を使って各要素の値を算出
				posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);

				//ROT
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotZ - pKey->frotZ;
				//相対値を差分を使って各要素の値を算出
				rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
				//POS
				//現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//相対値を差分を使って各要素の値を算出
				posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);
			}
			//パーツを動かす
			m_apModel[nCntParts]->Setrot(rotmotion);
			//オフセットの位置を設定
			m_apModel[nCntParts]->Setpos(D3DXVECTOR3(m_OffSetPos[nCntParts].x + posmotion.x,
				m_OffSetPos[nCntParts].y + posmotion.y,
				m_OffSetPos[nCntParts].z + posmotion.z));
		}
	}

	//ループの判定
	switch (m_aMotionInfo[m_nMotionType].bLoop)
	{
	case true:
		//ループする
		//フレームを進める
		m_nCountFlame++;

		RotRand.x = (float)(rand() % 100);
		RotRand.y = (float)(rand() % 100);
		effectmove.x = sinf(RotRand.y + 1) * 0.5f;
		effectmove.y = sinf(RotRand.y + 1) * 0.1f;
		effectmove.z = RotRand.x * -0.05f;

		m_effectCol = D3DXCOLOR(1, 1, 1, 1);

		//キーの更新
		//if (m_State == PLAYERSTATE_DASH)
		if (m_DashState == DASHSTATE_DASH)
		{
			if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame / 2.0f)
			{
				if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
				{
					//音の再生
					if (m_MotionState == MOTIONSTATE_RUN && m_nKey == 3)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_FOOTSTEP);
					//	CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), effectmove, m_effectCol,
					//		30, 30, 1, 50, CEffect::EFFECTTEX_SMOKE);
					}
					m_nKey = 0;
				}
				else
				{
					//音の再生
					if (m_MotionState == MOTIONSTATE_RUN && m_nKey == 1)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_FOOTSTEP);

					//	CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), effectmove, m_effectCol,
					//		30, 30, 1, 50, CEffect::EFFECTTEX_SMOKE);
					}
					m_nKey += 1;
				}
				m_nCountFlame = 0;
			}
		}
		else
		{
			if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
			{
				if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
				{
					//音の再生
					if (m_MotionState == MOTIONSTATE_RUN && m_nKey == 3)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_FOOTSTEP);

					//	CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), effectmove, m_effectCol,
					//		30, 30, 1, 50, CEffect::EFFECTTEX_SMOKE);
					}
					//キーの初期化
					m_nKey = 0;
				}
				else
				{
					//音の再生
					if (m_MotionState == MOTIONSTATE_RUN && m_nKey == 1)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_FOOTSTEP);

					//	CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), effectmove, m_effectCol,
					//		30, 30, 1, 50, CEffect::EFFECTTEX_SMOKE);
					}

					if (m_MotionState == MOTIONSTATE_JET)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_SODAKAIHOU);
						m_State = PLAYERSTATE_APPEAR;
					}
					//キーの更新
					m_nKey += 1;
				}
				m_nCountFlame = 0;
			}
		}

		break;
	case false:
		//ループしない
		if (m_aMotionInfo[m_nMotionType].nNumKey - 1 > m_nKey)
		{//フレームを進める
			m_nCountFlame++;
		}
		else if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
		{
			m_bMotionEnd = true;
			if (m_MotionState == MOTIONSTATE_JUMP && m_bJump == false)
			{
				m_MotionState = MOTIONSTATE_RUN;
				m_nKey = 0;
			}
			else if (m_MotionState == MOTIONSTATE_TUMBLE)
			{
				//回転が二回以下だったら
				if (m_nCntTumble < 2)
				{
					m_MotionState = MOTIONSTATE_TUMBLE;
					m_nKey = 1;
					m_nCntTumble++;
				}
				else if(m_nCntTumble > 1)
				{//2回転したとき
					m_MotionState = MOTIONSTATE_RUN;
					m_nKey = 0;
					m_nCntTumble = 0;
					m_State = PLAYERSTATE_APPEAR;
				}
			}

			if (m_MotionState == MOTIONSTATE_DAMAGE)
			{
				//現在のモードを取得
				CManager::MODE mode = CManager::GetMode();
				if (mode == CManager::MODE_GAME)
				{
					CUILife *pLife = CGame::GetUILife();
					//ライフが尽きたときゲームをリトライ
					if (pLife->GetnLife() == 0 && CFade::GetFade() == CFade::FADE_NONE)
					{
						CFade::SetFade(CManager::MODE_GAME);
					}
					else if(pLife->GetnLife() != 0)
					{
						//モーション切り替え
						m_nCountFlame = 0;
						m_nMotionType = 6;
						m_nKey = 0;
						m_bMotionEnd = false;
						m_MotionState = MOTIONSTATE_GETUP;
					}
				}
				else
				{
					//モーション切り替え
					m_nCountFlame = 0;
					m_nMotionType = 6;
					m_nKey = 0;
					m_bMotionEnd = false;
					m_MotionState = MOTIONSTATE_GETUP;
				}
			}
			else if (m_MotionState == MOTIONSTATE_GETUP)
			{
				//モーション切り替え
				m_nCountFlame = 0;
				m_nMotionType = 1;
				m_nKey = 0;
				m_bMotionEnd = false;
				m_MotionState = MOTIONSTATE_RUN;
				m_State = PLAYERSTATE_APPEAR;
			}
		}
		//キ	ーの更新
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{
			if (m_aMotionInfo[m_nMotionType].nNumKey > m_nKey)
			{
				m_nKey += 1;
			}
			m_nCountFlame = 0;
		}

		break;
	}

#endif
}

//=============================================================================
// ファイル読み込み
//=============================================================================
void CPlayer::FileLoad(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

	D3DXVECTOR3 ParentPos;	//親の位置情報を取得
#if 1
	//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME, "r");
	//NULLチェック
	if (pFile != NULL)
	{
		for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("NUM_MODEL = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				g_nNumModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り戻す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("MODEL_FILENAME = ");

						//文字列を設定
						strcpy(aStr, pStrcur);

						//必要な文字列の最後の文字までの文字数を数える
						int nNullNum = PopString(pStrcur, &aStr[0]);

						//文字列を取り戻す
						strcpy(aStr, pStrcur);

						//最後の文字にNULL文字を入れる
						aStr[nNullNum - 1] = '\0';

						//対象の文字列から抜き出し
						strcpy(&g_aFileNameModel[nCntModel][0], aStr);

						// Xファイルの読み込み
						D3DXLoadMeshFromX(&g_aFileNameModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMatModel[nCntModel],
							NULL,
							&m_nNumMatModel[nCntModel],
							&m_pMeshModel[nCntModel]);
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}


			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "CHARACTERSET", 12) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("NUM_PARTS = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_nNumParts = atoi(pStrcur);
					}
					if (memcmp(pStrcur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);

							//INDEXを読み込み
							if (memcmp(pStrcur, "INDEX = ", strlen("INDEX = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("INDEX = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列抜き出し
								nIndex = atoi(pStrcur);
							}
							//PARENTを読み込み
							if (memcmp(pStrcur, "PARENT = ", strlen("PARENT = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("PARENT = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列抜き出し
								m_aIndexParent[nIndex] = atoi(pStrcur);
							}
							//POSを読み込み
							if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("POS = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposX = (float)atof(pStrcur);
								//文字数分進める
								pStrcur += nWord;

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposY = (float)atof(pStrcur);
								//文字数分進める
								pStrcur += nWord;

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposZ = (float)atof(pStrcur);

							}
							//ROTを読み込み
							if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("ROT = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotX = (float)atof(pStrcur);

								//文字数分進める
								pStrcur += nWord;
								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotY = (float)atof(pStrcur);

								//文字数分進める
								pStrcur += nWord;
								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								//rotFile[nIndex].z = (float)atof(pStrcur);
								m_aKayOffset[nIndex].frotZ = (float)atof(pStrcur);


							}
							//パーツセット終了
							else if (memcmp(pStrcur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{

								//モデルを生成	オフセット設定
								m_apModel[nIndex] = CModel::Create(
									D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
										m_pos.y + m_aKayOffset[nIndex].fposY,
										m_pos.z + m_aKayOffset[nIndex].fposZ),
									D3DXVECTOR3(m_rot.x + m_aKayOffset[nIndex].frotX,
										m_rot.y + m_aKayOffset[nIndex].frotY,
										m_rot.z + m_aKayOffset[nIndex].frotZ));

								//posを代入
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//モデルを割り当て
								m_apModel[nIndex]->BindModel(m_nNumMatModel[nIndex], m_pMeshModel[nIndex], m_pBuffMatModel[nIndex]);

								if (m_aIndexParent[nIndex] == -1)
								{
									//モデルの親を指定
									m_apModel[nIndex]->SetParent(NULL);
								}
								else
								{
									//モデルの親を指定
									m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
								}

								break;
							}
						}
					}
					//キャラクターセット終了
					else if (memcmp(pStrcur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{
						break;
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}

			//モーション読み込み
			if (memcmp(pStrcur, "MOTIONSET", strlen("MOTIONSET")) == 0)
			{
				//頭出し
				pStrcur += strlen("MOTIONSET");

				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);

					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("LOOP = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						switch (atoi(pStrcur))
						{
						case 0:
							//文字列抜き出し
							m_aMotionInfo[nCntMotion].bLoop = false;
							break;
						case 1:
							//文字列抜き出し
							m_aMotionInfo[nCntMotion].bLoop = true;
							break;
						}
						//文字列の先頭を設定
						pStrcur = ReadLine(pFile, &aLine[0]);
					}

					if (memcmp(pStrcur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("NUM_KEY = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_aMotionInfo[nCntMotion].nNumKey = atoi(pStrcur);

						//文字列の先頭を設定
						pStrcur = ReadLine(pFile, &aLine[0]);
						//文字列を取り出す
						strcpy(aStr, pStrcur);
					}

					//キーの設定
					for (int nCntKey = 0; nCntKey < m_aMotionInfo[nCntMotion].nNumKey;)
					{
						if (memcmp(pStrcur, "KEYSET", strlen("KEYSET")) == 0)
						{
							//頭出し
							pStrcur += strlen("KEYSET");
							//文字列の先頭を設定
							strcpy(aStr, pStrcur);
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);

							if (memcmp(pStrcur, "FRAME = ", strlen("FRAME = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("FRAME = ");

								m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].nFrame = atoi(pStrcur);

								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列の先頭を設定
								pStrcur = ReadLine(pFile, &aLine[0]);
							}

							//パーツ分回す
							for (int nCntParts = 0; nCntParts < m_nNumParts;)
							{
								if (memcmp(pStrcur, "KEY", strlen("KEY")) == 0)
								{
									//文字列の先頭を設定
									pStrcur = ReadLine(pFile, &aLine[0]);

									if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
									{
										//頭出し
										pStrcur += strlen("POS = ");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.X代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposX = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Y代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposY = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Z代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposZ = (float)atof(pStrcur);
										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									//ROTを読み込み
									if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
									{
										//頭出し
										pStrcur += strlen("ROT = ");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotX
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotX = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotY
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotY = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotZ
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotZ = (float)atof(pStrcur);

										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "END_KEY", strlen("END_KEY")) == 0)
									{
										//頭出し
										pStrcur += strlen("END_KEY");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);
										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
										//パーツのカウントを進める
										nCntParts++;
									}
								}
								else
								{
									//文字列の先頭を設定
									pStrcur = ReadLine(pFile, &aLine[0]);
								}
							}
							if (memcmp(pStrcur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{
								//文字列の先頭を設定
								pStrcur = ReadLine(pFile, &aLine[0]);
								//カウントを進める
								nCntKey++;
							}
						}
						else
						{
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);
						}

					}
					if (memcmp(pStrcur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{
						//モーションの情報をセット
						m_pKeyInfo[nCntMotion] = &m_aMotionInfo[nCntMotion].aKayInfo[0];
						break;
					}
				}
			}
			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	else
	{	//ファイルが開けなかった
		printf("ファイルが開けませんでした\n");
	}
	//ファイルを閉じる
	fclose(pFile);
#endif

}

//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CPlayer::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char * CPlayer::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CPlayer::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}

//=============================================================================
//　タイトルのカメラの状態を取得
//=============================================================================
CPlayer::TITLECAMERA CPlayer::GetTitleCamera()
{
	return m_TitleCamState;
}
