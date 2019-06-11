//=============================================================================
//
// UIフィニッシュ処理 [UIFinish.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIFinish.h"
#include "manager.h"
#include "number.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\Finish02.png"			//テクスチャのファイル名

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIFinish::m_pTexture[MAX_FINISH] = {};

//--------------------------------------------
//UIフィニッシュクラス コンストラクタ
//--------------------------------------------
CUIFinish::CUIFinish()
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
//UIフィニッシュクラス デストラクタ
//--------------------------------------------
CUIFinish::~CUIFinish()
{
}

//--------------------------------------------
//UIフィニッシュの生成
//--------------------------------------------
CUIFinish *CUIFinish::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIFinish *pScene2D;

	pScene2D = new CUIFinish;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUIFinish::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULLを代入
	for (int nCnt = 0; nCnt < MAX_FINISH; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	//生成
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3((m_pos.x), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//ポリゴンの更新
	//m_pScene2D[0]->SetPos(m_pScene2D[0]->Getpos(), 3.0f, 0, D3DXCOLOR(1, 1, 1, 1));
	//オブジェクト種類の設定
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	float fWidth = m_fWidth / 2;
	float fHeight = m_fHeight / 2;

	//値の初期化
	m_bEnter = false;
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pScene2D[0]->SetColor(m_Col);
	m_nColorFlash = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUIFinish::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_FINISH; nCnt++)
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
void CUIFinish::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//ジョイパッド情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();

	m_fScale += 10.0f;
	if (m_fScale > 300)
	{
		m_fScale = 300;
	}

	m_pScene2D[0]->SetScale(m_fScale);

}

//=============================================================================
// 描画処理
//=============================================================================
void CUIFinish::Draw(void)
{
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CUIFinish::Load(void)
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
void CUIFinish::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_FINISH; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
