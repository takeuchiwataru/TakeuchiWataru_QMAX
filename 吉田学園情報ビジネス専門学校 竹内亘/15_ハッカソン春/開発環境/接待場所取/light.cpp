//=============================================================================
//
// ���C�g���� [light.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//--------------------------------------------
//���C�g�N���X �R���X�g���N�^
//--------------------------------------------
CLight::CLight()
{
	m_nNumLight = 0;
}

//--------------------------------------------
//���C�g�N���X �f�X�g���N�^
//--------------------------------------------
CLight::~CLight()
{
}
//=============================================================================
// ���C�g�̏���������
//=============================================================================
void CLight::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 vecDir;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));
	}

	//���݂̃��[�h���擾
	CManager::MODE mode = CManager::GetMode();
	switch (mode)
	{
	case CManager::MODE_TITLE:
		// ���C�g�̎�ނ�ݒ�
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.22f, -0.87f, -0.44f);
		//vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[0].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.15f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[1].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-0.15f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[2].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.15f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[3].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[4].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.0f, 0.0f, -0.15f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[4].Direction = vecDir;
		break;
	case CManager::MODE_TUTORIAL:
		// ���C�g�̎�ނ�ݒ�
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-0.2f, -0.9f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[0].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.3f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[1].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[2].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[3].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[4].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-1.3f, 0.0f, -1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[4].Direction = vecDir;
		break;

	case CManager::MODE_GAME:
		// ���C�g�̎�ނ�ݒ�
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-0.2f, -0.9f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[0].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.3f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[1].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[2].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[3].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[4].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-1.3f, 0.0f, -1.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[4].Direction = vecDir;
		break;
	case CManager::MODE_RESULT:
		// ���C�g�̎�ނ�ݒ�
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.22f, -0.87f, -0.44f);
		//vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[0].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.15f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[1].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-0.15f, 0.0f, 0.0f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[2].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.15f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[3].Direction = vecDir;
		// ���C�g�̎�ނ�ݒ�
		m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;
		// ���C�g�̊g�U����ݒ�
		m_aLight[4].Diffuse = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.0f, 0.0f, -0.15f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[4].Direction = vecDir;
		break;
	}

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//�O�̃��C�g�ɏ�������
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
	//�����l��ݒ�
	m_nNumLight = 0;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CLight::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

#ifdef  _DEBUG
	//���C�g�؂�ւ�
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

	//���C�g���ړ�
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

	CDebugProc::Print(1, " �I�𒆂�Light  [%d] \n", m_nNumLight);

	CDebugProc::Print(1, " ���C�g�̕���   [%d]  : ( %.1f, %.1f, %.1f )\n", m_nNumLight, m_aLight[m_nNumLight].Direction.x
			, m_aLight[m_nNumLight].Direction.y, m_aLight[m_nNumLight].Direction.z);
	CDebugProc::Print(1, " ���C�g�̐F     [%d]  : ( %.2f, %.2f, %.2f, %.2f )\n", m_nNumLight,
		m_aLight[m_nNumLight].Diffuse.r, m_aLight[m_nNumLight].Diffuse.g, m_aLight[m_nNumLight].Diffuse.b, m_aLight[m_nNumLight].Diffuse.a);


	// ���C�g��ݒ肷��
	pDevice->SetLight(m_nNumLight, &m_aLight[m_nNumLight]);
	// ���C�g��L���ɂ���
	pDevice->LightEnable(m_nNumLight, TRUE);
#endif
}

