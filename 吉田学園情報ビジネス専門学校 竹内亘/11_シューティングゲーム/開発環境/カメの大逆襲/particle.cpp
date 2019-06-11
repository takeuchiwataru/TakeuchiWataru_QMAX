//=============================================================================
//
// パーティクルの処理 [particle.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "particle.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CParticle::CParticle():CScene2D(2)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CParticle::~CParticle()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int radius)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PARTICLE);

	CScene2D::Init(pos);

	// 位置の設置
	CScene2D::SetPosition(pos, 10, 10);

	// 情報の初期化
	m_move = move;
	m_nLife = life;
	m_nRadius = radius;
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CParticle::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CParticle::Update(void)
{
	m_nLife--;

	m_nRadius -= m_nRadius / m_nLife;

	// 位置の取得
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	pos -= m_move;

	CScene2D::SetColor(m_col);

	CScene2D::SetParticle(m_nRadius,pos);

	if (m_nLife <= 0 || m_nRadius == 10)
	{
		Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CParticle::Draw(void)
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
// パーティクルの生成
//=============================================================================
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int radius)
{
	CParticle *pParticle = NULL;

	if (pParticle == NULL)
	{
		pParticle = new CParticle;

		if (pParticle != NULL)
		{
			pParticle->Init(pos,move,life,radius);
			//pParticle->m_col = col;
			pParticle->BindTexture(m_pTexture);
		}
	}
	return pParticle;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CParticle::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_000, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CParticle::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}