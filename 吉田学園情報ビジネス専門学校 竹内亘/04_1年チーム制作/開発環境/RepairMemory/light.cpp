//=========================================================================================================================
//
// ���C�g���� [light.cpp]
// Author : 
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "light.h"
#include "input.h"
#include "game.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_LIGHT		(4)						// ���C�g�̍ő吔

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
D3DLIGHT9 g_Light[MAX_LIGHT];

int		  g_nCntColTimer;
D3DXCOLOR g_color;

//=========================================================================================================================
// ���C�g�̏���������
//=========================================================================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];				// �ݒ�p�����x�N�g��
	int nCntLight;

	g_nCntColTimer = 0;
	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_Light[nCntLight], sizeof(D3DLIGHT9));

		if (nCntLight == 0)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.5f, -0.8f, 0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 1)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.5f, -0.8f, -0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 2)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.5f, -0.8f, 0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 3)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.5f, -0.8f, -0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_Light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=========================================================================================================================
// ���C�g�̏I������
//=========================================================================================================================
void UninitLight(void)
{

}

//=========================================================================================================================
// ���C�g�̍X�V����
//=========================================================================================================================
void UpdateLight(void)
{
	QUESTSTATE pQuestState = GetQuestState();

	if (pQuestState == QUESTSTATE_SEARCH)
	{
		g_nCntColTimer++;

		if (g_nCntColTimer > 10000)
		{
			if (g_color.r > 0.98f)
			{
				g_color.r -= (1.0f - 0.98f) / 5000.0f;
			}
			if (g_color.g > 0.68f)
			{
				g_color.g -= (1.0f - 0.58f) / 5000.0f;
			}
			if (g_color.b > 0.53f)
			{
				g_color.b -= (1.0f - 0.43f) / 5000.0f;
			}
		}
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];				// �ݒ�p�����x�N�g��
	int nCntLight;

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_Light[nCntLight], sizeof(D3DLIGHT9));

		if (nCntLight == 0)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = g_color;

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.5f, -0.8f, 0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 1)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = g_color;

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.5f, -0.8f, -0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 2)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = g_color;

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.5f, -0.8f, 0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 3)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = g_color;

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.5f, -0.8f, -0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_Light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

void SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];				// �ݒ�p�����x�N�g��
	int nCntLight;

	g_nCntColTimer = 0;
	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_Light[nCntLight], sizeof(D3DLIGHT9));

		if (nCntLight == 0)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.5f, -0.8f, 0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 1)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.5f, -0.8f, -0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 2)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.5f, -0.8f, 0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}
		else if (nCntLight == 3)
		{
			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			// ���C�g�̕����̐ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.5f, -0.8f, -0.5f);
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
			g_Light[nCntLight].Direction = vecDir[nCntLight];
		}

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_Light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}