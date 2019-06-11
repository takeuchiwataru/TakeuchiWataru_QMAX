//=============================================================================
//
// 海藻処理 [marineplant.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "marineplant.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "explosion.h"
#include "input.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CMarinePlant::m_apTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CMarinePlant::CMarinePlant():CScene2D(4)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CMarinePlant::~CMarinePlant()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMarinePlant::Init(D3DXVECTOR3 pos)
{
	CScene2D::InitAnim(pos);

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_MAEINAPLANT);

	// 位置の設置
	CScene2D::SetPosition(pos, MARINESIZE, MARINESIZE);

	// 情報の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 3;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CMarinePlant::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CMarinePlant::Update(void)
{
	D3DXVECTOR3 pos;		// 位置

	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// 位置の取得
	pos = CScene2D::GetPosition();

	pos += m_move;
	m_move.y = 1 * 1;

	// 海藻のアニメーション
	m_nCounterAnim++;

	if ((m_nCounterAnim % 30) == 0)
	{// パターンNo.更新
		m_nPatternAnim = (m_nPatternAnim + 1) % 2;

		SetPattern2(m_nPatternAnim);
	}

	// 位置の設置
	CScene2D::SetPosition(pos, MARINESIZE, MARINESIZE);
}
//=============================================================================
// 描画処理
//=============================================================================
void CMarinePlant::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// 敵の生成
//=============================================================================
CMarinePlant * CMarinePlant::Create(D3DXVECTOR3 pos)
{
	CMarinePlant *pMarinePlant = NULL;

	if (pMarinePlant == NULL)
	{
		pMarinePlant = new CMarinePlant;

		if (pMarinePlant != NULL)
		{
			pMarinePlant->Init(pos);
			pMarinePlant->BindTexture(m_apTexture);
		}
	}
	return pMarinePlant;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CMarinePlant::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, MARINE_TEXTURE_000, &m_apTexture);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CMarinePlant::Unload(void)
{
	// テクスチャの破棄
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}
}
