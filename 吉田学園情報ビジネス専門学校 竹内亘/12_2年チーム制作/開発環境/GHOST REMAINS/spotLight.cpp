//=============================================================================
//
// �X�|�b�g���C�g���� [spotLight.cpp]
// Author : ���R���
//
//=============================================================================
#include "spotLight.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "enemy.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
D3DLIGHT9 CSpotLight::m_light[MAX_TITLE_LIGHT] = {};

//=============================================================================
// ���C�g�N���X�̃R���X�g���N�^
//=============================================================================
CSpotLight::CSpotLight()
{
	CManager::GetpSpotLight() = this;

	// �l���N���A
	m_nCntTime = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSpotLight::~CSpotLight()
{
}

//=============================================================================
// �X�|�b�g���C�g�̏���������
//=============================================================================
void CSpotLight::Init(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3			vecDir;

	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// �^�C�g���̎��̐ݒ�
		m_pos = D3DXVECTOR3(-7100.0f, 875.0f, -2750.0f);
	}
	else if (CManager::GetMode() == CManager::MODE_RANKING)
	{// �����L���O�̎��̐ݒ�
		m_pos = D3DXVECTOR3(-7000.0f, 1000.0f, -6600.0f);
	}

	m_pos = D3DXVECTOR3(-7100.0f, 875.0f, -2750.0f);
	m_nCntTime = 0;		// ���C�g�̓_�łɎg��
	m_bLight = true;	// �����Ă��邩�ǂ���

						//=====================================
						// �P��
						//=====================================
						// ���C�g���N���A����
	ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light[0].Type = D3DLIGHT_POINT;

	// ���C�g�����˂���f�B�t���[�Y�F��ݒ�
	m_light[0].Diffuse = D3DXCOLOR(0.7f, 1.0f, 1.0f, 1.0f);

	// �X�y�L�����[�F(�P�����ʂ��o������)??
	m_light[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//����(����������Ȃ������֊ԐړI�ɓ�������̋���)??
	m_light[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �����̈ʒu��ݒ�
	m_light[0].Position = m_pos;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//���K���ɂ���
	m_light[0].Direction = vecDir;

	// �����̗L��������ݒ�
	m_light[0].Range = 300.0f;

	// �悭�킩��񂯂ǊJ���҂̑�����1.0f��ݒ肵�Ă�炵��
	m_light[0].Falloff = 1.0f;

	//���C�g�̋��x(1��2��0.0f�ɂ��邱�ƂŌ������Ȃ����ɂȂ�)
	m_light[0].Attenuation0 = 1.0f;
	m_light[0].Attenuation1 = 0.0f;
	m_light[0].Attenuation2 = 0.0f;

	//�����R�[���i�悭����������ꏊ�j
	m_light[0].Theta = D3DXToRadian(30.0f);

	//�O���R�[���i�኱����������ꏊ�j
	m_light[0].Phi = D3DXToRadian(50.0f);

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_light[0]);

	//=====================================
	// �Q��
	//=====================================
	// ���C�g���N���A����
	ZeroMemory(&m_light[1], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// �^�C�g���̎��̐ݒ�
		m_light[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// �`���[�g���A���̎��̐ݒ�
		m_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// ���U���g�̎��̐ݒ�
		m_light[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// �����L���O�̎��̐ݒ�
		m_light[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[1].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(1, &m_light[1]);

	//=====================================
	// �R��
	//=====================================
	// ���C�g���N���A����
	ZeroMemory(&m_light[2], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// �^�C�g���̎��̐ݒ�
		m_light[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// �`���[�g���A���̎��̐ݒ�
		m_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// ���U���g�̎��̐ݒ�
		m_light[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// �����L���O�̎��̐ݒ�
		m_light[2].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
	}

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[2].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(2, &m_light[2]);

	//=====================================
	// �S��
	//=====================================
	// ���C�g���N���A����
	ZeroMemory(&m_light[3], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light[3].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// �^�C�g���̎��̐ݒ�
		m_light[3].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// �`���[�g���A���̎��̐ݒ�
		m_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// ���U���g�̎��̐ݒ�
		m_light[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// �����L���O�̎��̐ݒ�
		m_light[3].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	}

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[3].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(3, &m_light[3]);

	//=====================================
	// �T��
	//=====================================
	// ���C�g���N���A����
	ZeroMemory(&m_light[4], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light[4].Type = D3DLIGHT_POINT;

	// ���C�g�����˂���f�B�t���[�Y�F��ݒ�
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// �����L���O
		m_light[4].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// �^�C�g��
		m_light[4].Diffuse = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// �`���[�g���A���̎��̐ݒ�
		m_light[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// �X�y�L�����[�F(�P�����ʂ��o������)??
	m_light[4].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//����(����������Ȃ������֊ԐړI�ɓ�������̋���)??
	m_light[4].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �����̈ʒu��ݒ�
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// �����L���O
		m_light[4].Position = D3DXVECTOR3(-6800.0f, 900.0f, -6600.0f);
	}
	else if (CManager::GetMode() == CManager::MODE_TITLE)
	{// �^�C�g��
		m_light[4].Position = D3DXVECTOR3(-6300.0f, 1200.0f, -3400.0f);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// �`���[�g���A��
		m_light[4].Position = D3DXVECTOR3(-5000.0f, 150.0f, -400.0f);
	}

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);				//���K���ɂ���
	m_light[4].Direction = vecDir;

	// �����̗L��������ݒ�
	m_light[4].Range = 500.0f;

	// �悭�킩��񂯂ǊJ���҂̑�����1.0f��ݒ肵�Ă�炵��
	m_light[4].Falloff = 1.0f;

	//���C�g�̋��x(1��2��0.0f�ɂ��邱�ƂŌ������Ȃ����ɂȂ�)
	m_light[4].Attenuation0 = 1.0f;
	m_light[4].Attenuation1 = 0.0f;
	m_light[4].Attenuation2 = 0.0f;

	//�����R�[���i�悭����������ꏊ�j
	m_light[4].Theta = D3DXToRadian(30.0f);

	//�O���R�[���i�኱����������ꏊ�j
	m_light[4].Phi = D3DXToRadian(50.0f);

	// ���C�g��ݒ肷��
	pDevice->SetLight(4, &m_light[4]);

	// 0�`4�̃��C�g��L���ɂ���
	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// �^�C�g���̎��̐ݒ�
		pDevice->LightEnable(0, TRUE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, TRUE);
	}
	if (CManager::GetMode() == CManager::MODE_PRACTICE)
	{// �`���[�g���A���̎��̐ݒ�
		pDevice->LightEnable(0, TRUE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, TRUE);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// ���U���g�̎��̐ݒ�
		pDevice->LightEnable(0, FALSE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, FALSE);
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{// �����L���O�̎��̐ݒ�
		pDevice->LightEnable(0, TRUE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, TRUE);
	}
}

//=============================================================================
// �X�|�b�g���C�g�̏I������
//=============================================================================
void CSpotLight::Uninit(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice(); // �f�o�C�X�̎擾

	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->LightEnable(3, FALSE);
	pDevice->LightEnable(4, FALSE);

	CManager::GetpSpotLight() = NULL;
}

//=============================================================================
// �X�|�b�g���C�g�̍X�V����
//=============================================================================
void CSpotLight::Update(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	if (CManager::GetMode() == CManager::MODE_TITLE)
	{// �^�C�g���̎��̐ݒ�
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
			// ���C�g��L���ɂ���
			pDevice->LightEnable(4, TRUE);
		}
		else
		{
			m_nCntTime--;
			// ���C�g�𖳌��ɂ���
			pDevice->LightEnable(4, FALSE);
		}

		pDevice->SetLight(4, &m_light[4]);
	}
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{// ���U���g�̎��̐ݒ�
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
				// ���C�g��L���ɂ���
				pDevice->LightEnable(1, TRUE);
				pDevice->LightEnable(2, TRUE);
				pDevice->LightEnable(3, TRUE);
			}
			else
			{
				m_nCntTime--;
				// ���C�g�𖳌��ɂ���
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
// �ݒ菈��
//=============================================================================
void CSpotLight::Set(void)
{
	//LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	//D3DXVECTOR3			vecDir;

	////=====================================
	//// �P��
	////=====================================
	//// ���C�g���N���A����
	//ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));

	//// ���C�g�̎�ނ�ݒ�
	//m_light[0].Type = D3DLIGHT_SPOT;

	//// ���C�g�����˂���f�B�t���[�Y�F��ݒ�
	//m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// �X�y�L�����[�F
	//m_light[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////����(���邭�Ȃ�)
	//m_light[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// �����̈ʒu��ݒ�
	//m_light[0].Position = D3DXVECTOR3(400.0f, 300.0f, -400.0f);

	//// ���C�g�̕����̐ݒ�
	//vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//D3DXVec3Normalize(&vecDir, &vecDir);				//���K���ɂ���
	//m_light[0].Direction = vecDir;

	//// �����̗L��������ݒ�
	//m_light[0].Range = 500.0f;

	//// �悭�킩��񂯂ǊJ���҂̑�����1.0f��ݒ肵�Ă�炵��
	//m_light[0].Falloff = 1.0f;

	////���C�g�̋��x 
	//m_light[0].Attenuation0 = 1.0f;
	//m_light[0].Attenuation1 = 0.0f;
	//m_light[0].Attenuation2 = 0.0f;

	////�����R�[���i�悭����������ꏊ�j
	//m_light[0].Theta = D3DXToRadian(50.0f);

	////�O���R�[���i�኱����������ꏊ�j
	//m_light[0].Phi = D3DXToRadian(80.0f);

	//// ���C�g��ݒ肷��
	//pDevice->SetLight(0, &m_light[0]);

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(0, TRUE);

	////=====================================
	//// �Q��
	////=====================================
	//// ���C�g���N���A����
	//ZeroMemory(&m_light[1], sizeof(D3DLIGHT9));

	//// ���C�g�̎�ނ�ݒ�
	//m_light[1].Type = D3DLIGHT_DIRECTIONAL;

	//// ���C�g�̊g�U����ݒ�
	//m_light[1].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);

	//// ���C�g�̕����̐ݒ�
	//vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	//m_light[1].Direction = vecDir;

	//// ���C�g��ݒ肷��
	//pDevice->SetLight(1, &m_light[1]);

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(1, TRUE);

	////=====================================
	//// �R��
	////=====================================
	//// ���C�g���N���A����
	//ZeroMemory(&m_light[2], sizeof(D3DLIGHT9));

	//// ���C�g�̎�ނ�ݒ�
	//m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	//// ���C�g�̊g�U����ݒ�
	//m_light[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);

	//// ���C�g�̕����̐ݒ�
	//vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	//m_light[2].Direction = vecDir;

	//// ���C�g��ݒ肷��
	//pDevice->SetLight(2, &m_light[2]);

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(2, TRUE);

	////=====================================
	//// �S��
	////=====================================
	//// ���C�g���N���A����
	//ZeroMemory(&m_light[3], sizeof(D3DLIGHT9));

	//// ���C�g�̎�ނ�ݒ�
	//m_light[3].Type = D3DLIGHT_DIRECTIONAL;

	//// ���C�g�̊g�U����ݒ�
	//m_light[3].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);

	//// ���C�g�̕����̐ݒ�
	//vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	//m_light[3].Direction = vecDir;

	//// ���C�g��ݒ肷��
	//pDevice->SetLight(3, &m_light[3]);

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(3, TRUE);
}