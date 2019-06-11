//=============================================================================
//
// UIライフ処理 [UILife.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UILife.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\life001.png"			//テクスチャのファイル名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUILife::m_pTexture[1] = {};
int							CUILife::m_nLife = 3;
//--------------------------------------------
//UIライフクラス コンストラクタ
//--------------------------------------------
CUILife::CUILife()
{
	m_pos = D3DXVECTOR3(0,0,0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);				// 前回の位置
	m_nLife = 3;
}

//--------------------------------------------
//UIライフクラス デストラクタ
//--------------------------------------------
CUILife::~CUILife()
{
}

//--------------------------------------------
//UIライフの生成
//--------------------------------------------
CUILife *CUILife::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUILife *pScene2D;

	pScene2D = new CUILife;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUILife::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		m_pScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((m_pos.x + (m_fWidth + 25)* nCnt), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
		m_pScene2D[nCnt]->BindTexture(m_pTexture[0]);
		//オブジェクト種類の設定
		m_pScene2D[nCnt]->SetObjType(CScene::OBJTYPE_SCENE2D);
	}

	m_nLife = 3;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUILife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}
	//自分を消す
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUILife::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CUILife::Draw(void)
{
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CUILife::Load(void)
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
void CUILife::UnLoad(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
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
// ライフ取得処理
//=============================================================================
int CUILife::GetnLife(void)
{
	return m_nLife;
}

//=============================================================================
// ライフ加算処理
//=============================================================================
void CUILife::AddLife(int nLife)
{
	m_nLife += nLife;

	if (m_nLife > MAX_LIFE - 1)
	{
		m_nLife = MAX_LIFE - 1;
	}

	m_pScene2D[m_nLife]->SetbDraw(true);
}

//=============================================================================
// ライフ減算処理
//=============================================================================
void CUILife::MinusLife(int nLife)
{
	m_nLife -= nLife;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	m_pScene2D[m_nLife]->SetbDraw(false);
}
