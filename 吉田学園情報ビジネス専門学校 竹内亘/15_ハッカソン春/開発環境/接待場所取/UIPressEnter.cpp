//=============================================================================
//
// UIエンター処理 [UIPressEnter.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIPressEnter.h"
#include "manager.h"
#include "number.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\press_enter.png"			//テクスチャのファイル名

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIPressEnter::m_pTexture[MAX_PRESSENTER] = {};

//--------------------------------------------
//UIエンタークラス コンストラクタ
//--------------------------------------------
CUIPressEnter::CUIPressEnter()
{
	m_pos = D3DXVECTOR3(0,0,0);					// 位置
	m_move = D3DXVECTOR3(0, 0, 0);				// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);			// 前回の位置
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nItem = 0;
	m_bEnter = false;
	m_fScale = 0;
	m_ScaleCounter = 0;
}

//--------------------------------------------
//UIエンタークラス デストラクタ
//--------------------------------------------
CUIPressEnter::~CUIPressEnter()
{
}

//--------------------------------------------
//UIエンターの生成
//--------------------------------------------
CUIPressEnter *CUIPressEnter::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIPressEnter *pScene2D;

	pScene2D = new CUIPressEnter;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUIPressEnter::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULLを代入
	for (int nCnt = 0; nCnt < MAX_PRESSENTER; nCnt++)
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
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nColorFlash = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUIPressEnter::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PRESSENTER; nCnt++)
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
void CUIPressEnter::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//ジョイパッド情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();

	//カウンター加算
	if (m_bEnter == false)
	{
		m_ScaleCounter++;
		if (m_ScaleCounter <= 40)
		{
			m_Col.a -= 0.015f;
		}
		else if (m_ScaleCounter >= 41 && m_ScaleCounter <= 80)
		{
			m_Col.a += 0.025f;
			if (m_Col.a > 1.0f)
			{
				m_Col.a = 1.0f;
			}
		}
		else if (m_ScaleCounter > 80)
		{
			m_ScaleCounter = 0;
		}
		m_pScene2D[0]->SetColor(m_Col);
	}

	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		m_bEnter = true;
		m_Col.r = 1.0f;
		m_Col.g = 1.0f;
		m_Col.b = 1.0f;
		m_Col.a = 1.0f;

		m_pScene2D[0]->SetColor(m_Col);
	}

	if (m_bEnter == true)
	{
		m_nColorFlash++;
		if (m_nColorFlash <= 5)
		{
			m_Col.r = 1.0f;
			m_Col.g = 1.0f;
			m_Col.b = 1.0f;
		}
		else if (m_nColorFlash >= 6 && m_nColorFlash <= 10)
		{
			m_Col.r = 1.0f;
			m_Col.g = 0.0f;
			m_Col.b = 0.0f;
		}
		else if(m_nColorFlash > 10)
		{
			m_nColorFlash = 0;
		}
		m_pScene2D[0]->SetColor(m_Col);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CUIPressEnter::Draw(void)
{
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CUIPressEnter::Load(void)
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
void CUIPressEnter::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PRESSENTER; nCnt++)
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
// エンターの獲得のフラグ設定
//=============================================================================
void CUIPressEnter::SetItemBool(bool bGetItem)
{
	m_bEnter = bGetItem;
}
