//=============================================================================
//
// ライト処理 [light.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{//中身クリア
	CManager::GetLight() = this;
}
//=============================================================================
// コンストラクタ
//=============================================================================
CLight::~CLight()
{//中身クリア

}
//=============================================================================
// ライトの初期化処理
//=============================================================================
void CLight::Init(void)
{
	m_col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_fStrength = 0.0f;
	m_fGoal = 0.0f;
	InitSet();
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void CLight::Uninit(void)
{
	CManager::GetLight() = NULL;
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void CLight::Update(void)
{
	if (m_fFrame > 0.0f)
	{//ライトの初期化が必要
		m_fFrame -= 1.0f;
		if (m_fFrame <= 0.0f)
		{
			m_fFrame = 0.0f;
			m_fGoal = 0.0f;
		}
	}
	m_col.r += (0.5f - m_col.r) * 0.1f / FRAME_SPEED;
	m_col.g += (0.5f - m_col.g) * 0.1f / FRAME_SPEED;
	m_col.b += (0.5f - m_col.b) * 0.1f / FRAME_SPEED;
	m_fStrength += (m_fGoal - m_fStrength) * 0.1f / FRAME_SPEED;

	if (CManager::GetInputKey()->GetTrigger(DIK_L)) { SetStrength(0.5f, 30); }
	if (CManager::GetInputKey()->GetTrigger(DIK_K)) { m_col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f); }
}
//=============================================================================
// 初期化時設定処理
//=============================================================================
void CLight::InitSet(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXVECTOR3			vecDir;
	int					nCntLight;
	D3DXCOLOR			WKcol;

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ライトをクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		WKcol = D3DXCOLOR(m_col.r + m_fStrength, m_col.g + m_fStrength, m_col.b + m_fStrength, 1.0f);
		if (WKcol.r > 1.0f) { WKcol.r = 1.0f; }
		if (WKcol.g > 1.0f) { WKcol.g = 1.0f; }
		if (WKcol.b > 1.0f) { WKcol.b = 1.0f; }

		m_light[nCntLight].Diffuse = WKcol;

		// ライトの方向の設定
		if (nCntLight == 0) { vecDir = D3DXVECTOR3(0.2f, 0.8f, -0.4f); }
		if (nCntLight == 1) { vecDir = D3DXVECTOR3(-0.5f, -0.2f, 0.4f); }
		if (nCntLight == 2) { vecDir = D3DXVECTOR3(0.4f, -0.8f, 1.0f); }

		D3DXVec3Normalize(&vecDir, &vecDir);				//正規化にする
		m_light[nCntLight].Direction = vecDir;

		// ライトを設定する
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}
//=============================================================================
// 設定処理
//=============================================================================
void CLight::Set(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXVECTOR3			vecDir;
	int					nCntLight;
	D3DXCOLOR			WKcol;

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ライトの拡散光を設定
		WKcol = D3DXCOLOR(m_col.r + m_fStrength, m_col.g + m_fStrength, m_col.b + m_fStrength, 1.0f);
		if (WKcol.r > 1.0f) { WKcol.r = 1.0f; }
		if (WKcol.g > 1.0f) { WKcol.g = 1.0f; }
		if (WKcol.b > 1.0f) { WKcol.b = 1.0f; }

		m_light[nCntLight].Diffuse = WKcol;

		// ライトを設定する
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);
	}
}
//=============================================================================
// 光の強さ設定処理
//=============================================================================
void CLight::SetStrength(float fGoal, float fFrame)
{
	m_fGoal = fGoal; 
	m_fFrame = fFrame * FRAME_SPEED;
}

