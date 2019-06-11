//=============================================================================
//
// スポットライト処理 [spotLight.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "spotLight.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "enemy.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
D3DLIGHT9 CSpotLight::m_light[MAX_TITLE_LIGHT] = {};

//=============================================================================
// ライトクラスのコンストラクタ
//=============================================================================
CSpotLight::CSpotLight()
{
	CManager::GetpSpotLight() = this;

	// 値をクリア
	m_nCntTime = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSpotLight::~CSpotLight()
{
}

//=============================================================================
// スポットライトの初期化処理
//=============================================================================
void CSpotLight::Init(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXVECTOR3			vecDir;

	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// タイトルの時の設定
		m_pos = D3DXVECTOR3(-7100.0f, 875.0f, -2750.0f);
	}
	else if (CManager::GetMode() == CManager::MODE_RANKING)
	{// ランキングの時の設定
		m_pos = D3DXVECTOR3(-7000.0f, 1000.0f, -6600.0f);
	}

	m_pos = D3DXVECTOR3(-7100.0f, 875.0f, -2750.0f);
	m_nCntTime = 0;		// ライトの点滅に使う
	m_bLight = true;	// 光っているかどうか

						//=====================================
						// １つ目
						//=====================================
						// ライトをクリアする
	ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	m_light[0].Type = D3DLIGHT_POINT;

	// ライトが放射するディフューズ色を設定
	m_light[0].Diffuse = D3DXCOLOR(0.7f, 1.0f, 1.0f, 1.0f);

	// スペキュラー色(輝く効果を出す反射)??
	m_light[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//環境光(光が当たらない部分へ間接的に当たる光の強さ)??
	m_light[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 光源の位置を設定
	m_light[0].Position = m_pos;

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//正規化にする
	m_light[0].Direction = vecDir;

	// 光源の有効距離を設定
	m_light[0].Range = 300.0f;

	// よくわからんけど開発者の多くは1.0fを設定してるらしい
	m_light[0].Falloff = 1.0f;

	//ライトの強度(1と2を0.0fにすることで減衰しない光になる)
	m_light[0].Attenuation0 = 1.0f;
	m_light[0].Attenuation1 = 0.0f;
	m_light[0].Attenuation2 = 0.0f;

	//内部コーン（よく光が当たる場所）
	m_light[0].Theta = D3DXToRadian(30.0f);

	//外部コーン（若干光が当たる場所）
	m_light[0].Phi = D3DXToRadian(50.0f);

	// ライトを設定する
	pDevice->SetLight(0, &m_light[0]);

	//=====================================
	// ２つ目
	//=====================================
	// ライトをクリアする
	ZeroMemory(&m_light[1], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// タイトルの時の設定
		m_light[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// チュートリアルの時の設定
		m_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// リザルトの時の設定
		m_light[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// ランキングの時の設定
		m_light[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[1].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(1, &m_light[1]);

	//=====================================
	// ３つ目
	//=====================================
	// ライトをクリアする
	ZeroMemory(&m_light[2], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// タイトルの時の設定
		m_light[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// チュートリアルの時の設定
		m_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// リザルトの時の設定
		m_light[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// ランキングの時の設定
		m_light[2].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
	}

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[2].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(2, &m_light[2]);

	//=====================================
	// ４つ目
	//=====================================
	// ライトをクリアする
	ZeroMemory(&m_light[3], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	m_light[3].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// タイトルの時の設定
		m_light[3].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// チュートリアルの時の設定
		m_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// リザルトの時の設定
		m_light[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// ランキングの時の設定
		m_light[3].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[3].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(3, &m_light[3]);

	//=====================================
	// ５つ目
	//=====================================
	// ライトをクリアする
	ZeroMemory(&m_light[4], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	m_light[4].Type = D3DLIGHT_POINT;

	// ライトが放射するディフューズ色を設定
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// ランキング
		m_light[4].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// タイトル
		m_light[4].Diffuse = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// チュートリアルの時の設定
		m_light[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// スペキュラー色(輝く効果を出す反射)??
	m_light[4].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//環境光(光が当たらない部分へ間接的に当たる光の強さ)??
	m_light[4].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 光源の位置を設定
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// ランキング
		m_light[4].Position = D3DXVECTOR3(-6800.0f, 900.0f, -6600.0f);
	}
	else if (CManager::GetMode() == CManager::MODE_TITLE)
	{// タイトル
		m_light[4].Position = D3DXVECTOR3(-6300.0f, 1200.0f, -3400.0f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// チュートリアル
		m_light[4].Position = D3DXVECTOR3(-5000.0f, 150.0f, -400.0f);
	}

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);				//正規化にする
	m_light[4].Direction = vecDir;

	// 光源の有効距離を設定
	m_light[4].Range = 500.0f;

	// よくわからんけど開発者の多くは1.0fを設定してるらしい
	m_light[4].Falloff = 1.0f;

	//ライトの強度(1と2を0.0fにすることで減衰しない光になる)
	m_light[4].Attenuation0 = 1.0f;
	m_light[4].Attenuation1 = 0.0f;
	m_light[4].Attenuation2 = 0.0f;

	//内部コーン（よく光が当たる場所）
	m_light[4].Theta = D3DXToRadian(30.0f);

	//外部コーン（若干光が当たる場所）
	m_light[4].Phi = D3DXToRadian(50.0f);

	// ライトを設定する
	pDevice->SetLight(4, &m_light[4]);

	// 0～4のライトを有効にする
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// タイトルの時の設定
		pDevice->LightEnable(0, TRUE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, TRUE);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// チュートリアルの時の設定
		pDevice->LightEnable(0, TRUE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, TRUE);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// リザルトの時の設定
		pDevice->LightEnable(0, FALSE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, FALSE);
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// ランキングの時の設定
		pDevice->LightEnable(0, TRUE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, TRUE);
	}
}

//=============================================================================
// スポットライトの終了処理
//=============================================================================
void CSpotLight::Uninit(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice(); // デバイスの取得

	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->LightEnable(3, FALSE);
	pDevice->LightEnable(4, FALSE);

	CManager::GetpSpotLight() = NULL;
}

//=============================================================================
// スポットライトの更新処理
//=============================================================================
void CSpotLight::Update(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// タイトルの時の設定
		if (m_nCntTime > rand() % 60)
		{
			m_bLight = false;
		}
		else if (m_nCntTime < 0)
		{
			m_bLight = true;
		}

		if (m_bLight == true)
		{
			m_nCntTime++;
			// ライトを有効にする
			pDevice->LightEnable(4, TRUE);
		}
		else
		{
			m_nCntTime--;
			// ライトを無効にする
			pDevice->LightEnable(4, FALSE);
		}

		pDevice->SetLight(4, &m_light[4]);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// リザルトの時の設定
		if (m_nCountLighting <= 1)
		{
			if (m_nCntTime > 50)
			{
				m_bLight = false;

			}
			else if (m_nCntTime < 0)
			{
				m_bLight = true;
				m_nCountLighting++;
			}

			if (m_bLight == true)
			{
				m_nCntTime++;
				// ライトを有効にする
				pDevice->LightEnable(1, TRUE);
				pDevice->LightEnable(2, TRUE);
				pDevice->LightEnable(3, TRUE);
			}
			else
			{
				m_nCntTime--;
				// ライトを無効にする
				pDevice->LightEnable(1, FALSE);
				pDevice->LightEnable(2, FALSE);
				pDevice->LightEnable(3, FALSE);
			}

			pDevice->SetLight(1, &m_light[1]);
			pDevice->SetLight(2, &m_light[2]);
			pDevice->SetLight(3, &m_light[3]);
		}
	}

}

//=============================================================================
// 設定処理
//=============================================================================
void CSpotLight::Set(void)
{
	//LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	//D3DXVECTOR3			vecDir;

	////=====================================
	//// １つ目
	////=====================================
	//// ライトをクリアする
	//ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));

	//// ライトの種類を設定
	//m_light[0].Type = D3DLIGHT_SPOT;

	//// ライトが放射するディフューズ色を設定
	//m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// スペキュラー色
	//m_light[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////環境光(明るくなる)
	//m_light[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// 光源の位置を設定
	//m_light[0].Position = D3DXVECTOR3(400.0f, 300.0f, -400.0f);

	//// ライトの方向の設定
	//vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//D3DXVec3Normalize(&vecDir, &vecDir);				//正規化にする
	//m_light[0].Direction = vecDir;

	//// 光源の有効距離を設定
	//m_light[0].Range = 500.0f;

	//// よくわからんけど開発者の多くは1.0fを設定してるらしい
	//m_light[0].Falloff = 1.0f;

	////ライトの強度 
	//m_light[0].Attenuation0 = 1.0f;
	//m_light[0].Attenuation1 = 0.0f;
	//m_light[0].Attenuation2 = 0.0f;

	////内部コーン（よく光が当たる場所）
	//m_light[0].Theta = D3DXToRadian(50.0f);

	////外部コーン（若干光が当たる場所）
	//m_light[0].Phi = D3DXToRadian(80.0f);

	//// ライトを設定する
	//pDevice->SetLight(0, &m_light[0]);

	//// ライトを有効にする
	//pDevice->LightEnable(0, TRUE);

	////=====================================
	//// ２つ目
	////=====================================
	//// ライトをクリアする
	//ZeroMemory(&m_light[1], sizeof(D3DLIGHT9));

	//// ライトの種類を設定
	//m_light[1].Type = D3DLIGHT_DIRECTIONAL;

	//// ライトの拡散光を設定
	//m_light[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);

	//// ライトの方向の設定
	//vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	//m_light[1].Direction = vecDir;

	//// ライトを設定する
	//pDevice->SetLight(1, &m_light[1]);

	//// ライトを有効にする
	//pDevice->LightEnable(1, TRUE);

	////=====================================
	//// ３つ目
	////=====================================
	//// ライトをクリアする
	//ZeroMemory(&m_light[2], sizeof(D3DLIGHT9));

	//// ライトの種類を設定
	//m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	//// ライトの拡散光を設定
	//m_light[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);

	//// ライトの方向の設定
	//vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	//m_light[2].Direction = vecDir;

	//// ライトを設定する
	//pDevice->SetLight(2, &m_light[2]);

	//// ライトを有効にする
	//pDevice->LightEnable(2, TRUE);

	////=====================================
	//// ４つ目
	////=====================================
	//// ライトをクリアする
	//ZeroMemory(&m_light[3], sizeof(D3DLIGHT9));

	//// ライトの種類を設定
	//m_light[3].Type = D3DLIGHT_DIRECTIONAL;

	//// ライトの拡散光を設定
	//m_light[3].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);

	//// ライトの方向の設定
	//vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	//m_light[3].Direction = vecDir;

	//// ライトを設定する
	//pDevice->SetLight(3, &m_light[3]);

	//// ライトを有効にする
	//pDevice->LightEnable(3, TRUE);
}