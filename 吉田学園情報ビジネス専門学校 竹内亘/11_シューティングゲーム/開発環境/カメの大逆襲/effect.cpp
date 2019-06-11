//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect():CScene2D(2)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_EFFECT);

	CScene2D::Init(pos);

	// 位置の設置
	CScene2D::SetPosition(pos, 10, 10);

	// 情報の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = EFFECT_LIFE;
	m_fRadius = EFFECT_RADIUS;
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	CScene2D::SetColor(m_col);

	CScene2D::SetEffect(m_fRadius);

	m_fRadius -= 2.0f;

	m_nLife--;

	if (m_nLife <= 0 ||m_fRadius == 10)
	{
  		Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
// エフェクトの生成
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos,D3DXCOLOR col)
{
	CEffect *pEffect = NULL;

	if (pEffect == NULL)
	{
		pEffect = new CEffect;

		if (pEffect != NULL)
		{
			pEffect->Init(pos);
			pEffect->m_col = col;
			pEffect->BindTexture(m_pTexture);
		}
	}
	return pEffect;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CEffect::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEXTURE_000, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CEffect::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}