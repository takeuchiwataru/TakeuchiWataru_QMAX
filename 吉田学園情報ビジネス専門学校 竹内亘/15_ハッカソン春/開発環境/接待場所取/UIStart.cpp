//=============================================================================
//
// UIスタート処理 [UIStart.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIStart.h"
#include "manager.h"
#include "number.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\Countdown00.png"			//テクスチャのファイル名
#define TEXTURENAME001			 "data\\TEXTURE\\UI\\Countdown01.png"			//テクスチャのファイル名
#define TEXTURENAME002			 "data\\TEXTURE\\UI\\Countdown02.png"			//テクスチャのファイル名
#define TEXTURENAME003			 "data\\TEXTURE\\UI\\Countdown03.png"			//テクスチャのファイル名

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIStart::m_pTexture[MAX_START] = {};

//--------------------------------------------
//UIスタートクラス コンストラクタ
//--------------------------------------------
CUIStart::CUIStart()
{
	m_pos = D3DXVECTOR3(0,0,0);					// 位置
	m_move = D3DXVECTOR3(0, 0, 0);				// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);			// 前回の位置
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nItem = 0;
	m_bCntDown = false;
	m_fScale = 0;
	m_ScaleCounter = 0;
	m_nType = 0;
}

//--------------------------------------------
//UIスタートクラス デストラクタ
//--------------------------------------------
CUIStart::~CUIStart()
{
}

//--------------------------------------------
//UIスタートの生成
//--------------------------------------------
CUIStart *CUIStart::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIStart *pScene2D;

	pScene2D = new CUIStart;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUIStart::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULLを代入
	for (int nCnt = 0; nCnt < MAX_START; nCnt++)
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
	m_bCntDown = false;
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pScene2D[0]->SetColor(m_Col);
	m_nColorFlash = 0;
	m_nType = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUIStart::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_START; nCnt++)
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
void CUIStart::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//ジョイパッド情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//サウンド
	CSound *pSound = CManager::GetSound(0);

	if (m_bCntDown == true)
	{
		if (m_nType < MAX_START)
		{
			m_pScene2D[0]->BindTexture(m_pTexture[m_nType]);
			if (m_nType < 3)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_START00);
			}
			else if (m_nType == 3)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_START01);
			}
			m_bCntDown = false;
		}
	}

	//大きさ変化
	m_fScale += 5.0f;
	//透明度上げ
	if (m_fScale > 200 && m_fScale <= 250)
	{
		//カウンター加算
		if (m_bCntDown == false)
		{
			m_Col.a -= 0.1f;
		}
	}
	//大きさ最大
	if (m_fScale > 300)
	{
		m_fScale = 300;
		if (m_nType < 3)
		{
			m_bCntDown = true;
		}
		if (m_nType < MAX_START - 1)
		{
			m_nType += 1;
			m_fScale = 0;
			m_Col.a = 1.0f;
		}
	}
	//色・大きさ更新
	m_pScene2D[0]->SetColor(m_Col);
	m_pScene2D[0]->SetScale(m_fScale);
}

//=============================================================================
// 描画処理
//=============================================================================
void CUIStart::Draw(void)
{
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CUIStart::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME002, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME003, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CUIStart::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_START; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
