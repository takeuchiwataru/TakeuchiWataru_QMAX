//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : �|���j
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT (3)		// ���C�g�̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_light[MAX_LIGHT];			//���C�g�̏��

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	int nCntLight;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;

	// ���C�g���N���A����
	for (nCntLight = 0; nCntLight < 3; nCntLight++)
	{
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

	}
	//ZeroMemory(&g_light[1], sizeof(D3DLIGHT9));
	//ZeroMemory(&g_light[2], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);			// ���K������
	g_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);			// ���K������
	g_light[1].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);			// ���K������
	g_light[2].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light[0]);
	pDevice->SetLight(1, &g_light[1]);
	pDevice->SetLight(2, &g_light[2]);

	// ���C�g��L���ɂ���
	for (nCntLight = 0; nCntLight < 3; nCntLight++)
	{
		pDevice->LightEnable(nCntLight, TRUE);

	}
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}

