//---------------------------------------------------------------------
// チュートリアル処理 [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "tutorial.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "Logo.h"

#include "2DTuto.h"
#include "UIPressEnter.h"
#include "fade.h"
#include "meshField.h"
#include "field.h"

#include "effect.h"
#include "number.h"
#include "UILife.h"
#include "UIItem.h"
#include "UIGauge.h"


#include "fade.h"
#include "Logo.h"
#include "meshField.h"
#include "field.h"
#include "meshOrbit.h"
#include "billboard.h"
#include "billboardObject.h"
#include "player.h"
#include "shadow.h"
#include "effect.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[MAX_TUTORIALBG] = {};
CPlayer		*CTutorial::m_pPlayer = NULL;

//--------------------------------------------
//チュートリアルクラス コンストラクタ
//--------------------------------------------
CTutorial::CTutorial()
{
	m_nType = 0;
}

//--------------------------------------------
//チュートリアルクラス デストラクタ
//--------------------------------------------
CTutorial::~CTutorial()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CTutorial *CTutorial::Create(void)
{
	//チュートリアルのポインタ
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	pTutorial->Init();
	//チュートリアルの情報を返す
	return pTutorial;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//カメラ ライトの初期化
	CManager::GetCamera()->Init();
	CManager::GetLight()->Init();


	//テクスチャやモデルの読み込み
	CLogo::Load();
	CUIPressEnter::Load();
	CField::Load();
	CUIItem::Load();
	CUIGauge::Load();
	CUILife::Load();
	CNumber::Load();
	CEffect::Load();
	C2DTUTO::Load();
	//オブジェクトの生成

	C2DTUTO::Create(D3DXVECTOR3(0, 0, 0), 100, 100);

	//CField::Create(D3DXVECTOR3(-100, 0.1f, 15000), 200, 50300, CField::FIELDTEX_ROADWAY, 1, 300);
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);

	//ゲージを生成
	//CUIGauge::Create(D3DXVECTOR3(1100, 680, 0), 100, 300);
	// プレスエンター
	CUIPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 + 250, 0.0f), 400, 100);


	return S_OK;
}

//=============================================================================
// チュートリアルクラス 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	//テクスチャやモデルの破棄
	CLogo::UnLoad();
	CUIPressEnter::UnLoad();
	CField::UnLoad();
	CUIItem::UnLoad();
	CUIGauge::UnLoad();
	CUILife::UnLoad();
	CNumber::UnLoad();
	CEffect::UnLoad();
	C2DTUTO::UnLoad();

	CScene::ReleaseAll();
}

//=============================================================================
// チュートリアルクラス 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//ジョイパッド情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);

	//切り替え処理
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		//CSound *pSound = CManager::GetSound(1);
	//	pSound->PlaySound(pSound->SOUND_LABEL_SE_SODAFULL);
		CFade::SetFade(CManager::MODE_GAME);
	}

	if (pInput->GetTrigger(DIK_R) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_TITLE);
	}

	CDebugProc::Print(1, " チュートリアル\n");
}

//=============================================================================
// チュートリアルクラス 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}
//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CTutorial::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	return S_OK;
}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CTutorial::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TUTORIALBG; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}