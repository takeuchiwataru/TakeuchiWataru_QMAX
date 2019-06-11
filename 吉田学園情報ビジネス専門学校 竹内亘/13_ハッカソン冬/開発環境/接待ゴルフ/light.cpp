//=============================================================================
//
// ライト処理 [light.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//--------------------------------------------
//ライトクラス コンストラクタ
//--------------------------------------------
CLight::CLight()
{
}

//--------------------------------------------
//ライトクラス デストラクタ
//--------------------------------------------
CLight::~CLight()
{
}
//=============================================================================
// ライトの初期化処理
//=============================================================================
void CLight::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 vecDir;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ライトをクリアする
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));
	}

	// ライトの種類を設定
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_aLight[0].Direction = vecDir;

	// ライトの種類を設定
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
	// ライトの拡散光を設定
	//m_aLight[1].Diffuse = D3DXCOLOR(-0.15f, -0.63f, -0.76f, 1.0f);
	m_aLight[1].Diffuse = D3DXCOLOR(-0.35f, -0.35f, -0.35f, 1.0f);


	// ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);
	m_aLight[1].Direction = vecDir;

	// ライトの種類を設定
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
	// ライトの拡散光を設定
	m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);


	// ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.15f, 0.15f, 0.15f);

	D3DXVec3Normalize(&vecDir, &vecDir);
	m_aLight[2].Direction = vecDir;


	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//０のライトに情報を入れる
		// ライトを設定する
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void CLight::Update(void)
{
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//０のライトに情報を入れる
#ifdef  _DEBUG
		CDebugProc::Print(1, " ライトの方向[%d]  : ( %.1f,%.1f,%.1f )\n", nCntLight, m_aLight[nCntLight].Direction.x
			, m_aLight[nCntLight].Direction.y, m_aLight[nCntLight].Direction.z);
#endif
	}
}

