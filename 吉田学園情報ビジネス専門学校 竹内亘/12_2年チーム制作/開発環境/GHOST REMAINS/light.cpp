//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{//���g�N���A
	CManager::GetLight() = this;
}
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::~CLight()
{//���g�N���A

}
//=============================================================================
// ���C�g�̏���������
//=============================================================================
void CLight::Init(void)
{
	m_col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_fStrength = 0.0f;
	m_fGoal = 0.0f;
	InitSet();
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CLight::Uninit(void)
{
	CManager::GetLight() = NULL;
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CLight::Update(void)
{
	if (m_fFrame > 0.0f)
	{//���C�g�̏��������K�v
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
// ���������ݒ菈��
//=============================================================================
void CLight::InitSet(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3			vecDir;
	int					nCntLight;
	D3DXCOLOR			WKcol;

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		WKcol = D3DXCOLOR(m_col.r + m_fStrength, m_col.g + m_fStrength, m_col.b + m_fStrength, 1.0f);
		if (WKcol.r > 1.0f) { WKcol.r = 1.0f; }
		if (WKcol.g > 1.0f) { WKcol.g = 1.0f; }
		if (WKcol.b > 1.0f) { WKcol.b = 1.0f; }

		m_light[nCntLight].Diffuse = WKcol;

		// ���C�g�̕����̐ݒ�
		if (nCntLight == 0) { vecDir = D3DXVECTOR3(0.2f, 0.8f, -0.4f); }
		if (nCntLight == 1) { vecDir = D3DXVECTOR3(-0.5f, -0.2f, 0.4f); }
		if (nCntLight == 2) { vecDir = D3DXVECTOR3(0.4f, -0.8f, 1.0f); }

		D3DXVec3Normalize(&vecDir, &vecDir);				//���K���ɂ���
		m_light[nCntLight].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CLight::Set(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3			vecDir;
	int					nCntLight;
	D3DXCOLOR			WKcol;

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g�̊g�U����ݒ�
		WKcol = D3DXCOLOR(m_col.r + m_fStrength, m_col.g + m_fStrength, m_col.b + m_fStrength, 1.0f);
		if (WKcol.r > 1.0f) { WKcol.r = 1.0f; }
		if (WKcol.g > 1.0f) { WKcol.g = 1.0f; }
		if (WKcol.b > 1.0f) { WKcol.b = 1.0f; }

		m_light[nCntLight].Diffuse = WKcol;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);
	}
}
//=============================================================================
// ���̋����ݒ菈��
//=============================================================================
void CLight::SetStrength(float fGoal, float fFrame)
{
	m_fGoal = fGoal; 
	m_fFrame = fFrame * FRAME_SPEED;
}

