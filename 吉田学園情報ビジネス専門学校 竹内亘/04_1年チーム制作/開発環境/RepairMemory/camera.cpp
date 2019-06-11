//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "camera.h"
#include "input.h"
#include "game.h"
#include "xplayer.h"
#include "xenemy.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define CAMERA_POS_MOVE		(2.0f)								// �J�����ړ���
#define CAMERA_ROT_MOVE		(0.02f)								// �J������]��
#define CAMERA_ROT_AUTOMOVE	(0.0015f)							// �J����������]��
#define CAMERA_RESETSPEED	(0.08f)								// �J�������Z�b�g���x

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
Camera						g_Camera;			// �J�����̏��
float						g_fCameraDiff;
int							g_nCntCameraTimer;
float						g_fPlayerrotold;

//=========================================================================================================================
// �J�����̏���������
//=========================================================================================================================
void InitCamera(void)
{
	// �����l�ݒ�
	g_Camera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���_
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;				// �����_
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// �x�N�g��
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	g_Camera.fDistance = g_Camera.posV.z - g_Camera.posR.z;		// ����
	g_Camera.fResetRot = 0.0f;									// ���Z�b�g����
	g_Camera.fResetRotDest = 0.0f;								// �ڕW���Z�b�g����
	g_Camera.bReset = false;									// ���Z�b�g
	g_Camera.type = CAMERATYPE_NONE;							// ���

	g_fCameraDiff = 0.0f;
	g_nCntCameraTimer = 0;
	g_fPlayerrotold = 0.0f;
}

//=========================================================================================================================
// �J�����̏I������
//=========================================================================================================================
void UninitCamera(void)
{

}

//=========================================================================================================================
// �J�����̍X�V����
//=========================================================================================================================
void UpdateCamera(void)
{
	QUESTSTATE pQuestState = GetQuestState();
	XPLAYER *pXPlayer = GetXPlayer();
	float fDiff = 0.0f, fcof = 0.0f;
/*
	XPLAYER *pXPlayer = GetXPlayer();
	float fDiff = 0.0f, fcof = 0.0f;

	DIMOUSESTATE2 pMouse = GetMousePointer();

	//g_Camera.posR.x = g_Camera.posR.x + pMouse.lX;
	//g_Camera.posR.y = g_Camera.posR.y - pMouse.lY;
	
	// 
	if (GetKeyboardPress(DIK_R) == true)
	{
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		fDiff = (pXPlayer->rot.y - g_Camera.rot.y + D3DX_PI);

		if (fDiff > D3DX_PI)
		{
			fDiff -= D3DX_PI * 2.0f;
		}
		if (fDiff < -D3DX_PI)
		{
			fDiff += D3DX_PI * 2.0f;
		}

		g_Camera.rot.y += fDiff * 0.1f;

		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}
	}
	
	// �J�����Ǐ]
	if (pXPlayer->move.x > 0.7f || pXPlayer->move.x < -0.7f || pXPlayer->move.z > 0.7f || pXPlayer->move.z < -0.7f)
	{// �ړ���
		g_Camera.posRDest.x = pXPlayer->pos.x - sinf(pXPlayer->rot.y) * 40.0f;
		g_Camera.posRDest.y = pXPlayer->pos.y;
		g_Camera.posRDest.z = pXPlayer->pos.z - cosf(pXPlayer->rot.y) * 40.0f;
		g_Camera.posVDest.x = pXPlayer->pos.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posVDest.y = pXPlayer->pos.y;
		g_Camera.posVDest.z = pXPlayer->pos.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

		if (g_fPlayerrotold != pXPlayer->rot.y)
		{
			g_nCntCameraTimer = 0;
		}

		if (g_nCntCameraTimer < 30)
		{
			g_nCntCameraTimer++;
		}
		
		fcof = 0.1f + (float)(g_nCntCameraTimer * 0.001f);
	}
	else
	{// ��~��
		g_Camera.posRDest.x = pXPlayer->pos.x - sinf(pXPlayer->rot.y);
		g_Camera.posRDest.y = pXPlayer->pos.y;
		g_Camera.posRDest.z = pXPlayer->pos.z - cosf(pXPlayer->rot.y);
		g_Camera.posVDest.x = pXPlayer->pos.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posVDest.y = pXPlayer->pos.y;
		g_Camera.posVDest.z = pXPlayer->pos.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

		g_nCntCameraTimer = 0;

		fcof = 0.03f;
	}
	
	g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * fcof;
	g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * fcof;
	g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * fcof;
	g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * fcof;

	//g_fPlayerrotold = pXPlayer->rot.y;

	//SetBillboardNormalEffect(g_Camera.posR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(2.0f, 2.0f, 0.0f));
*/

	DIMOUSESTATE2 pMouse = GetMousePointer();
	DIJOYSTATE pStick = GetStick();

	switch (g_Camera.type)
	{
	case CAMERATYPE_NONE:
			break;
	case CAMERATYPE_TITLE:

		g_Camera.rot.y -= CAMERA_ROT_AUTOMOVE;
		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

		break;
	case CAMERATYPE_GAME_SEARCH:
	{
		if (pQuestState != QUESTSTATE_MISSTION && pQuestState != QUESTSTATE_REPORT && pQuestState != QUESTSTATE_CLEAR)
		{
			if ((GetKeyboardTrigger(DIK_R) == true || GetButtonTrigger(6) == true))
			{// �J�������Z�b�g
				if (g_Camera.bReset == false)
				{// �g�p���Ă��Ȃ��ꍇ
					fDiff = (pXPlayer->rot.y - g_Camera.rot.y + D3DX_PI);
					g_Camera.fResetRot = pXPlayer->rot.y;
					g_Camera.fResetRotDest = fDiff + g_Camera.rot.y;
					// �l����
					if (g_Camera.fResetRotDest > D3DX_PI)
					{
						g_Camera.fResetRotDest -= D3DX_PI * 2.0f;
					}
					if (g_Camera.fResetRotDest < -D3DX_PI)
					{
						g_Camera.fResetRotDest += D3DX_PI * 2.0f;
					}

					g_Camera.bReset = true;
				}
			}

			if (g_Camera.bReset == true)
			{// �g�p���Ă���ꍇ
				fDiff = (g_Camera.fResetRot - g_Camera.rot.y + D3DX_PI);
				if (fDiff > D3DX_PI)
				{
					fDiff -= D3DX_PI * 2.0f;
				}
				if (fDiff < -D3DX_PI)
				{
					fDiff += D3DX_PI * 2.0f;
				}

				g_Camera.rot.y += fDiff * CAMERA_RESETSPEED;
				if (g_Camera.rot.y > D3DX_PI)
				{
					g_Camera.rot.y -= D3DX_PI * 2.0f;
				}
				if (g_Camera.rot.y < -D3DX_PI)
				{
					g_Camera.rot.y += D3DX_PI * 2.0f;
				}

				// ���_����
				if (pXPlayer->move.x > 0.7f || pXPlayer->move.x < -0.7f || pXPlayer->move.z > 0.7f || pXPlayer->move.z < -0.7f)
				{// �ړ���
					g_Camera.posVDest.x = pXPlayer->pos.x + g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
					g_Camera.posVDest.z = pXPlayer->pos.z + g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
				}
				else
				{// ��~��
					g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
					g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
				}

				if (g_Camera.rot.y > g_Camera.fResetRotDest - 0.05f && g_Camera.rot.y < g_Camera.fResetRotDest + 0.05f)
				{// �l����
					g_Camera.rot.y = g_Camera.fResetRotDest;
					g_Camera.bReset = false;
				}
			}

			// ���_��]
			if ((GetKeyboardPress(DIK_Q) == true || GetButtonPress(4) == true || pStick.lZ < -100))
			{
				g_Camera.rot.y -= CAMERA_ROT_MOVE;
				g_Camera.posVDest.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
				g_Camera.posVDest.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
			}
			if ((GetKeyboardPress(DIK_E) == true || GetButtonPress(5) == true || pStick.lZ > 100))
			{
				g_Camera.rot.y += CAMERA_ROT_MOVE;
				g_Camera.posVDest.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
				g_Camera.posVDest.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
			}

			// �J�����Ǐ]
			if (pXPlayer->move.x > 0.7f || pXPlayer->move.x < -0.7f || pXPlayer->move.z > 0.7f || pXPlayer->move.z < -0.7f)
			{// �ړ���
				g_Camera.posRDest.x = pXPlayer->pos.x - sinf(pXPlayer->rot.y) * 40.0f;
				g_Camera.posRDest.y = pXPlayer->pos.y;
				g_Camera.posRDest.z = pXPlayer->pos.z - cosf(pXPlayer->rot.y) * 40.0f;
				g_Camera.posVDest.x = pXPlayer->pos.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
				g_Camera.posVDest.y = pXPlayer->pos.y;
				g_Camera.posVDest.z = pXPlayer->pos.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

				if (g_nCntCameraTimer < 30)
				{
					g_nCntCameraTimer++;
				}

				fcof = 0.1f + (float)(g_nCntCameraTimer * 0.001f);
			}
			else
			{// ��~��
				g_Camera.posRDest.x = pXPlayer->pos.x - sinf(pXPlayer->rot.y);
				g_Camera.posRDest.y = pXPlayer->pos.y;
				g_Camera.posRDest.z = pXPlayer->pos.z - cosf(pXPlayer->rot.y);
				g_Camera.posVDest.x = pXPlayer->pos.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
				g_Camera.posVDest.y = pXPlayer->pos.y;
				g_Camera.posVDest.z = pXPlayer->pos.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

				g_nCntCameraTimer = 0;

				fcof = 0.03f;
			}

			// �l���
			g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * fcof;
			g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * fcof;
			g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * fcof;
			g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * fcof;
		}

#if 0
		// �J�����ړ�
		if (GetKeyboardPress(DIK_W) == true)
		{// �Oa
			g_Camera.posV.x += sinf(D3DX_PI * 0.0f + g_Camera.rot.y) * CAMERA_POS_MOVE * 10;
			g_Camera.posV.z += cosf(D3DX_PI * 0.0f + g_Camera.rot.y) * CAMERA_POS_MOVE * 10;
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{// ���
			g_Camera.posV.x -= sinf(D3DX_PI * 0.0f + g_Camera.rot.y) * CAMERA_POS_MOVE;
			g_Camera.posV.z -= cosf(D3DX_PI * 0.0f + g_Camera.rot.y) * CAMERA_POS_MOVE;
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{// ��
			g_Camera.posV.x -= sinf(D3DX_PI * 0.5f + g_Camera.rot.y) * CAMERA_POS_MOVE;
			g_Camera.posV.z -= cosf(D3DX_PI * 0.5f + g_Camera.rot.y) * CAMERA_POS_MOVE;
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;
		}
		if (GetKeyboardPress(DIK_D) == true)
		{// �E
			g_Camera.posV.x += sinf(D3DX_PI * 0.5f + g_Camera.rot.y) * CAMERA_POS_MOVE;
			g_Camera.posV.z += cosf(D3DX_PI * 0.5f + g_Camera.rot.y) * CAMERA_POS_MOVE;
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;
		}
#endif

/*		// �����_�ʒu�ύX
		if (pMouse.lY < 0)
		{// Y���W
			g_Camera.posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 1.0f);
		}
		if (pMouse.lY > 0)
		{// Y���W
			g_Camera.posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 1.0f);
		}
		if (pMouse.lX < 0)
		{// �����_
			g_Camera.rot.y += (pMouse.lX / 200.0f);
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;
		}
		if (pMouse.lX > 0)
		{// �����_
			g_Camera.rot.y += (pMouse.lX / 200.0f);
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;
		}

		if (pMouse.lZ > 0)
		{// Y���W:;:
			g_Camera.posV.y += (pMouse.lZ / 1.0f);
		}
		if (pMouse.lZ < 0)
		{// Y���W
			g_Camera.posV.y += (pMouse.lZ / 1.0f);
		}*/
	}
		break;
	case CAMERATYPE_RESULT:
		break;
	case CAMERATYPE_RANKING:
		
		g_Camera.rot.y += CAMERA_ROT_AUTOMOVE;
		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

		break;
	}

	if (g_Camera.rot.y > D3DX_PI)
	{
		g_Camera.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Camera.rot.y < -D3DX_PI)
	{
		g_Camera.rot.y += D3DX_PI * 2.0f;
	}
}

//=========================================================================================================================
// �J�����̐ݒ菈��
//=========================================================================================================================
void SetUpCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		15000.0f
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH
	(
		&g_Camera.mtxView,
		&g_Camera.posV,
		&g_Camera.posR,
		&g_Camera.vecU
	);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

//=========================================================================================================================
// �J�����̎擾����
//=========================================================================================================================
Camera *GetCamera(void)
{
	return &g_Camera;
}

//=========================================================================================================================
// �J�����̐ݒ菈��
//=========================================================================================================================
void SetCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 rot, float fDistance, CAMERATYPE type)
{
	g_Camera.posV = posV;										// ���_
	g_Camera.posVDest = posV;									// ���_
	g_Camera.posR = posR;										// �����_
	g_Camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����_
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// �x�N�g��
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);											// ����
	g_Camera.fDistance = fDistance;								// ����
	g_Camera.type = type;										// ���

	g_fCameraDiff = 0.0f;
	g_nCntCameraTimer = 0;
	g_fPlayerrotold = 0.0f;
}