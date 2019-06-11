//=============================================================================
//
// UIビックリ処理 [UIExclamation.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIExclamation.h"
#include "manager.h"
#include "number.h"
#include "fade.h"
#include "enemy.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\Exclamation.png"			//テクスチャのファイル名

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
#define UI_TIMERNORMAL	(10)
#define UI_TIMERRED		(20)

#define ENEMYCREATE_TIMER (120)

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIExclamation::m_pTexture[MAX_EXCLAMATION] = {};

//--------------------------------------------
//UIビックリクラス コンストラクタ
//--------------------------------------------
CUIExclamation::CUIExclamation()
{
	m_pos = D3DXVECTOR3(0,0,0);					// 位置
	m_move = D3DXVECTOR3(0, 0, 0);				// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);			// 前回の位置
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nItem = 0;
	m_bEnter = false;
	m_fScale = 0;
	m_nColorFlash = 0;
	m_ScaleCounter = 0;
	m_EnemyCreateCnt = 0;
	m_EnemyPosType = ENEMYPOS_CENTER;
}

//--------------------------------------------
//UIビックリクラス デストラクタ
//--------------------------------------------
CUIExclamation::~CUIExclamation()
{
}

//--------------------------------------------
//UIビックリの生成
//--------------------------------------------
CUIExclamation *CUIExclamation::Create(D3DXVECTOR3 pos,float fWidth, float fHeight, ENEMYPOS type)
{
	CUIExclamation *pScene2D;

	pScene2D = new CUIExclamation;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->m_EnemyPosType = type;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUIExclamation::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULLを代入
	for (int nCnt = 0; nCnt < MAX_EXCLAMATION; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	//生成
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3((m_pos.x), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//オブジェクト種類の設定
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	float fWidth = m_fWidth / 2;
	float fHeight = m_fHeight / 2;

	//値の初期化
	m_bEnter = false;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_ScaleCounter = 0;
	m_nColorFlash = 0;
	m_EnemyCreateCnt = 0;


	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);

	pSound->PlaySound(pSound->SOUND_LABEL_SE_WARNING);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUIExclamation::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_EXCLAMATION; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			if (m_pScene2D[nCnt]->GetDeath() == false)
			{
				m_pScene2D[nCnt]->Uninit();

				m_pScene2D[nCnt] = NULL;
			}
		}
	}

	//自分を消す(プレイヤーを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUIExclamation::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//ジョイパッド情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();

	//カウンター加算
	m_nColorFlash++;
	if (m_nColorFlash <= UI_TIMERNORMAL)
	{
		m_Col.r = 1.0f;
		m_Col.g = 1.0f;
		m_Col.b = 0.0f;
	}
	else if (m_nColorFlash >= UI_TIMERNORMAL + 1 && m_nColorFlash <= UI_TIMERRED)
	{
		m_Col.g = 0.0f;
		m_Col.b = 0.0f;
	}
	else if (m_nColorFlash > UI_TIMERRED)
	{
		m_nColorFlash = 0;
	}
	m_pScene2D[0]->SetColor(m_Col);

	//敵の生成
	m_EnemyCreateCnt++;
	if (m_EnemyCreateCnt > ENEMYCREATE_TIMER)
	{
		//プレイヤーを取得
		CPlayer *pPlayer = CGame::GetPlayer();

		switch (m_EnemyPosType)
		{
		case ENEMYPOS_CENTER:
			CEnemy::Create(D3DXVECTOR3(pPlayer->GetPos().x, 0, pPlayer->GetPos().z - 200), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);
			break;
		case ENEMYPOS_RIGHT:
			CEnemy::Create(D3DXVECTOR3(pPlayer->GetPos().x + 70, 0, pPlayer->GetPos().z - 200), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);
			break;
		case ENEMYPOS_LEFT:
			CEnemy::Create(D3DXVECTOR3(pPlayer->GetPos().x - 70, 0, pPlayer->GetPos().z - 200), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);
			break;
		}
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CUIExclamation::Draw(void)
{
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CUIExclamation::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CUIExclamation::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_EXCLAMATION; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ビックリの獲得のフラグ設定
//=============================================================================
void CUIExclamation::SetItemBool(bool bGetItem)
{
	m_bEnter = bGetItem;
}
