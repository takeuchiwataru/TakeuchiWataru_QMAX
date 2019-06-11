//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �|���j
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player2.h"
//#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera;	// �J�����̏��
int g_nCount;		// 

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f,40.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fLength = g_camera.posR.z - g_camera.posV.z;
	g_camera.fAngle = g_camera.posV.z - g_camera.posR.z;
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDiff = 0.0f;

	//g_camera.fAngle = 0.0f;
	//g_camera.fIntervel = 200.0f;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	// �v���C���[�̎擾
	Player2 *pPlayer;
	pPlayer = GetPlayer2();

	if (GetMode() == MODE_GAME)
	{
		//�J�����̒Ǐ]
		g_camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 20;
		g_camera.posRDest.y = pPlayer->pos.y + sinf(pPlayer->rot.x) * 20;
		g_camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 20;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = pPlayer->pos.y + sinf(g_camera.rot.x) * g_camera.fLength + 50;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.2f;
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.2f;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.2f;
		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 1.0f;
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.2f;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 1.0f;

		g_camera.posV.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.x = pPlayer->pos.x;
		g_camera.posR.z = pPlayer->pos.z;

		//if (pPlayer->move.x < 0.05f && pPlayer->move.x > -0.05f /*|| pPlayer->move.z < 1.0f && pPlayer->move.z > -1.0f*/)
		//{
		//	g_nCount++;
		//	if (g_nCount >= 60)
		//	{
		//		g_camera.rotDest.y = pPlayer->rot.y + D3DX_PI;
		//		g_camera.rotDiff = g_camera.rotDest.y - g_camera.rot.y;

				if (g_camera.rotDiff > D3DX_PI)
				{
					g_camera.rotDiff -= D3DX_PI * 2.0f;
				}
				if (g_camera.rotDiff < -D3DX_PI)
				{
					g_camera.rotDiff += D3DX_PI * 2.0f;
				}

				g_camera.rot.y += g_camera.rotDiff * 0.05f;

				if (g_camera.rot.y > D3DX_PI)
				{
					g_camera.rotDiff -= D3DX_PI * 2.0f;
				}
				if (g_camera.rot.y < D3DX_PI)
				{
					g_camera.rotDiff += D3DX_PI * 2.0f;
				}
	//		}
	//	}
	//	else
	//	{
	//		g_nCount = 0;
	//	}
	}

	else if (GetMode() == MODE_TITLE)
	{// �E����
		g_camera.rot.y += 0.002f;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	else if (GetMode() == MODE_RANKING)
	{// �E����
		g_camera.rot.y += 0.002f;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	else if (GetMode() == MODE_GAMECLEAR)
	{// ������
		g_camera.rot.y -= 0.002f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	else if (GetMode() == MODE_GAMEOVER)
	{// ������
		g_camera.rot.y -= 0.002f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	// �J�����ړ�
	//if (GetKeyboardPress(DIK_A) == true)
	//{// �������Ɉړ�
	//	g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * 0.5f) * 2.0f;
	//	g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * 0.5f) * 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{// ���O�����Ɉړ�
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{// �E������Ɉړ�
	//		g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * 1.0f) *2.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_D) == true)
	//{// �E�����Ɉړ�
	//	g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 0.5f) * 2.0f;
	//	g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 0.5f) * 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

	//	if (GetKeyboardPress(DIK_W) == true)
	//	{// ���O�����Ɉړ�
	//		g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{// ��������Ɉړ�
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 1.0f) *2.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_W) == true)
	//{// �O�����Ɉړ�
	//	g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//	g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

	//}
	//else if (GetKeyboardPress(DIK_S) == true)
	//{// ������Ɉړ�
	//	g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 1.0f) *2.0f;
	//	g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//}

	//// ���_����
	//if (GetKeyboardPress(DIK_Y) == true)
	//{// ��ړ�
	//	g_camera.posV.y -= cosf(D3DX_PI) * 2.0f;
	//}
	//else if (GetKeyboardPress(DIK_N) == true)
	//{// ���ړ�
	//	g_camera.posV.y += cosf(D3DX_PI) * 2.0f;
	//}
	//else if (GetKeyboardPress(DIK_Z) == true)
	//{// ������
	//	g_camera.rot.y += 0.05f;
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y = -D3DX_PI;
	//	}
	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	//}
	//else if (GetKeyboardPress(DIK_C) == true)
	//{// �E����
	//	g_camera.rot.y -= 0.05f;
	//	if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y = D3DX_PI;
	//	}
	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	//}

	//// �����_����
	//if (GetKeyboardPress(DIK_T) == true)
	//{// ��ړ�
	//	g_camera.posR.y -= cosf(D3DX_PI) * 2.0f;
	//}
	//else if (GetKeyboardPress(DIK_B) == true)
	//{// ���ړ�
	//	g_camera.posR.y += cosf(D3DX_PI) * 2.0f;
	//}
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{// ������
	//	g_camera.rot.y -= 0.05f;
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y = -D3DX_PI;
	//	}
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//}
	//if (GetKeyboardPress(DIK_E) == true)
	//{// �E����
	//	g_camera.rot.y += 0.05f;
	//	if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y = D3DX_PI;
	//	}

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),									// ��p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,				
		10.0f,													// ��O�̈ʒu
		1000.0f);												// ���̈ʒu

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}
//=============================================================================
// �J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}



