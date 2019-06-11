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
	m_nNumLight = 0;
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

	//現在のモードを取得
	CManager::MODE mode = CManager::GetMode();
	switch (mode)
	{
	case CManager::MODE_TITLE:
		// ライトの種類を設定
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.22f, -0.87f, -0.44f);
		//vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[0].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.15f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[1].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-0.15f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[2].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.15f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[3].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[4].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.0f, 0.0f, -0.15f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[4].Direction = vecDir;
		break;
	case CManager::MODE_TUTORIAL:
		// ライトの種類を設定
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-0.2f, -0.9f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[0].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.3f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[1].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[2].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[3].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[4].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-1.3f, 0.0f, -1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[4].Direction = vecDir;
		break;

	case CManager::MODE_GAME:
		// ライトの種類を設定
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-0.2f, -0.9f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[0].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.3f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[1].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[2].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[3].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[4].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-1.3f, 0.0f, -1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[4].Direction = vecDir;
		break;
	case CManager::MODE_RESULT:
		// ライトの種類を設定
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.22f, -0.87f, -0.44f);
		//vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[0].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.15f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[1].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-0.15f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[2].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.15f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[3].Direction = vecDir;
		// ライトの種類を設定
		m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散光を設定
		m_aLight[4].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.0f, 0.0f, -0.15f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[4].Direction = vecDir;
		break;
	}

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//０のライトに情報を入れる
		// ライトを設定する
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
	//初期値を設定
	m_nNumLight = 0;
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
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

#ifdef  _DEBUG
	//ライト切り替え
	if (pInput->GetTrigger(DIK_NUMPAD7) == true)
	{
		m_nNumLight -= 1;
		if (m_nNumLight < 0)
		{
			m_nNumLight = MAX_LIGHT - 1;
		}
	}
	if (pInput->GetTrigger(DIK_NUMPAD9) == true)
	{
		m_nNumLight += 1;
		if (m_nNumLight > MAX_LIGHT - 1)
		{
			m_nNumLight = 0;
		}
	}

	//ライトを移動
	if (pInput->GetPress(DIK_NUMPAD8) == true)
	{
		m_aLight[m_nNumLight].Direction.x += 0.03f;
	}
	if (pInput->GetPress(DIK_NUMPAD2) == true)
	{
		m_aLight[m_nNumLight].Direction.x -= 0.03f;
	}
	if (pInput->GetPress(DIK_NUMPAD4) == true)
	{
		m_aLight[m_nNumLight].Direction.z += 0.03f;
	}
	if (pInput->GetPress(DIK_NUMPAD6) == true)
	{
		m_aLight[m_nNumLight].Direction.z -= 0.03f;
	}

	CDebugProc::Print(1, " 選択中のLight  [%d] \n", m_nNumLight);

	CDebugProc::Print(1, " ライトの方向   [%d]  : ( %.1f, %.1f, %.1f )\n", m_nNumLight, m_aLight[m_nNumLight].Direction.x
			, m_aLight[m_nNumLight].Direction.y, m_aLight[m_nNumLight].Direction.z);
	CDebugProc::Print(1, " ライトの色     [%d]  : ( %.2f, %.2f, %.2f, %.2f )\n", m_nNumLight,
		m_aLight[m_nNumLight].Diffuse.r, m_aLight[m_nNumLight].Diffuse.g, m_aLight[m_nNumLight].Diffuse.b, m_aLight[m_nNumLight].Diffuse.a);


	// ライトを設定する
	pDevice->SetLight(m_nNumLight, &m_aLight[m_nNumLight]);
	// ライトを有効にする
	pDevice->LightEnable(m_nNumLight, TRUE);
#endif
}

