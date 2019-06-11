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

	// ���C�g�̎�ނ�ݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_aLight[0].Direction = vecDir;

	// ���C�g�̎�ނ�ݒ�
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
	// ���C�g�̊g�U����ݒ�
	//m_aLight[1].Diffuse = D3DXCOLOR(-0.15f, -0.63f, -0.76f, 1.0f);
	m_aLight[1].Diffuse = D3DXCOLOR(-0.35f, -0.35f, -0.35f, 1.0f);


	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);

	D3DXVec3Normalize(&vecDir, &vecDir);
	m_aLight[1].Direction = vecDir;

	// ���C�g�̎�ނ�ݒ�
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
	// ���C�g�̊g�U����ݒ�
	m_aLight[2].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);


	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.15f, 0.15f, 0.15f);

	D3DXVec3Normalize(&vecDir, &vecDir);
	m_aLight[2].Direction = vecDir;


	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//�O�̃��C�g�ɏ�������
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
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
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//�O�̃��C�g�ɏ�������
#ifdef  _DEBUG
		CDebugProc::Print(1, " ���C�g�̕���[%d]  : ( %.1f,%.1f,%.1f )\n", nCntLight, m_aLight[nCntLight].Direction.x
			, m_aLight[nCntLight].Direction.y, m_aLight[nCntLight].Direction.z);
#endif
	}
}

