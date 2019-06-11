//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_ANGEL_VIEW  (45.0f)    // �J�����̉�p
#define CAMERA_MOVE        (15.0f)    // �J�����̈ړ���
#define AROUND_SPEED       (0.02f)    // ��荞�ݑ��x�����l
#define AROUND_TIME        (50)       // ��荞�ݑ҂����ԏ����l

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera;  // �J�����̏��

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // ���݂̒����_��������
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �ړI�̎��_��������
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �ړI�̒����_��������
	g_camera.posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �����镪�̎��_��������
	g_camera.posRAdd = D3DXVECTOR3(0.0f, 100.0f, 0.0f);  // �����镪�̒����_��������
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       // �x�N�g����������
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);        // ���݂̌�����������
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړI�̌�����������
	g_camera.state = CAMERASTATE_NORMAL;                 // �ʏ�̏�Ԃ�
	g_camera.fWaraparoundSpeed = AROUND_SPEED;           // ��荞�ݑ��x��������
	g_camera.nWaraparoundTime = AROUND_TIME;             // ��荞�ݑ҂����Ԃ�������
	g_camera.nCounterTime = 0;                           // �҂����ԃJ�E���^�[��������
	g_camera.posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړI�̎��_���W��������
	g_camera.posRAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړI�̒����_���W��������
	g_camera.fLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // ������������

	// �r���[�|�[�g�̐ݒ�
	g_camera.ViewPort.X = 0;                  // x���W���[
	g_camera.ViewPort.Y = 0;                  // y���W��[
	g_camera.ViewPort.Width = SCREEN_WIDTH;   // x���W�E�[
	g_camera.ViewPort.Height = SCREEN_HEIGHT; // x���W���[
	g_camera.ViewPort.MinZ = 0.0f;            // ��O
	g_camera.ViewPort.MaxZ = 1.0f;            // ����

	if (GetMode() == MODE_RANKING)
	{// �����L���O��ʂ�������
		g_camera.fLength.x = 200;
		g_camera.fLength.y = 30;
		g_camera.fLength.z = 200;
	}
	else if (GetMode() == MODE_TITLE)
	{// �^�C�g����ʂ�������
		g_camera.fLength.x = 200;
		g_camera.fLength.y = 50;
		g_camera.fLength.z = 200;

		g_camera.posR = D3DXVECTOR3(0.0f, 300.0f, 0.0f);       // ���݂̒����_��������
	}
	else if(GetMode() == MODE_GAME)
	{// ����ȊO�̉�ʂ�������
		g_camera.fLength.x = 600;
		g_camera.fLength.y = 300;
		g_camera.fLength.z = 600;
	}
	else if (GetMode() == MODE_TUTORIAL)
	{// ����ȊO�̉�ʂ�������
		g_camera.fLength.x = 200;
		g_camera.fLength.y = 0;
		g_camera.fLength.z = 200;
		g_camera.posR = D3DXVECTOR3(0.0f, 240.0f,800.0f);       // ���݂̒����_��������
	}

	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.y) * g_camera.fLength.y;
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
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
// �f�o�b�N�p�J��������̏���
#if 0
//-----------------
// ���_�ړ�
//-----------------
	if (GetKeyboardPress(DIK_LEFT) == true)
	{// A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{// ������W�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// ������S�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// �����ɉ���������Ă��Ȃ�
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{// D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{// ������W�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// ������S�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// �����ɉ���������Ă��Ȃ�
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{// W�L�[�������ꂽ
		g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_MOVE;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{// S�L�[�������ꂽ
		g_camera.posV.x -= sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z -= cosf(g_camera.rot.y) * CAMERA_MOVE;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	//-----------------
	// ���_����
	//-----------------
	if (GetKeyboardPress(DIK_Z) == true)
	{// Z�L�[�������ꂽ
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y <= -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength.z;

	}
	if (GetKeyboardPress(DIK_C) == true)
	{// C�L�[�������ꂽ
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	//-----------------
	// �����_����
	//-----------------
	if (GetKeyboardPress(DIK_Q) == true)
	{// Q�L�[�������ꂽ
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	if (GetKeyboardPress(DIK_E) == true)
	{// E�L�[�������ꂽ
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	//-----------------
	// �J�������Z�b�g
	//-----------------
	if (GetKeyboardPress(DIK_G) == true)
	{// SPACE�L�[�������ꂽ
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, -250.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 00.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_camera.rot.y = atan2f(g_camera.posV.x - g_camera.posR.x, g_camera.posV.z - g_camera.posR.z);
	}

	//-----------------
	// �����_�㏸���~
	//-----------------
	if (GetKeyboardPress(DIK_T) == true)
	{// T�L�[�������ꂽ
		g_camera.posR.y += 3.5f;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{// B�L�[�������ꂽ
		g_camera.posR.y -= 3.5f;
	}
	//-----------------
	// ���_�㏸���~
	//-----------------
	if (GetKeyboardPress(DIK_Y) == true)
	{// Y�L�[�������ꂽ
		g_camera.posV.y += 3.5f;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{// N�L�[�������ꂽ
		g_camera.posV.y -= 3.5f;
	}

	//------------------------
	// �Y�[���C�� �Y�[���A�E�g
	//------------------------
	if (GetKeyboardPress(DIK_U) == true)
	{// U�L�[�������ꂽ
		if (g_camera.fLength.z >= 60)
		{
			g_camera.fLength.z -= 2.0f;
		}
	}
	if (GetKeyboardPress(DIK_M) == true)
	{// M�L�[�������ꂽ
		if (g_camera.fLength.z <= 350)
		{
			g_camera.fLength.z += 2.0f;
		}
	}
#endif

	if (GetMode() == MODE_TITLE)
	{// �^�C�g����ʂ�������
		g_camera.rot.y += D3DX_PI / 1200;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetMode() == MODE_RANKING)
	{// �����L���O��ʂ�������
		g_camera.rot.y -= D3DX_PI / 1200;
		if (g_camera.rot.y <= -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetMode() == MODE_GAME)
	{// �Q�[����ʂ�������
		Player *pPlayer = GetPlayer();  // �v���C���[�̎擾

		// ���_�ݒ�
		g_camera.posVDest.x = (pPlayer->pos.x + (5.0f * pPlayer->move.x)) - sinf(g_camera.rot.y) * g_camera.fLength.x;  // �ړI�̎��_��ݒ�
		g_camera.posVDest.y = (pPlayer->pos.y + g_camera.posVAdd.y) + cosf(0.0f) * g_camera.fLength.y / 1.7f;           // �ړI�̎��_��ݒ�
		g_camera.posVDest.z = (pPlayer->pos.z + (5.0f * pPlayer->move.z)) - cosf(g_camera.rot.y) * g_camera.fLength.z;  // �ړI�̎��_��ݒ�

		// �����_�ݒ�
		g_camera.posRDest.x = (pPlayer->pos.x + (5.0f * pPlayer->move.x)) + sinf(pPlayer->rot.y + D3DX_PI) * ((pPlayer->move.x * pPlayer->move.x) + ((pPlayer->move.x * pPlayer->move.x))); // �ړI�̒����_��ݒ�
		g_camera.posRDest.y = (pPlayer->pos.y + g_camera.posRAdd.y + 40.0f);                                                                                // �ړI�̒����_��ݒ�
		g_camera.posRDest.z = (pPlayer->pos.z + (5.0f * pPlayer->move.z)) + cosf(pPlayer->rot.y + D3DX_PI) * ((pPlayer->move.z * pPlayer->move.z) + ((pPlayer->move.z * pPlayer->move.z))); // �ړI�̒����_��ݒ�

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.5f; // ���݂̎��_��ݒ�
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.5f; // ���݂̎��_��ݒ�
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.5f; // ���݂̎��_��ݒ�

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.30f; // ���݂̒����_��ݒ�
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.30f; // ���݂̒����_��ݒ�
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.30f; // ���݂̒����_��ݒ�

		if (GetKeyboardPress(DIK_RIGHT) == true ||
			GetJoyPadPress(DIJS_BUTTON_16, 0) == TRUE)
		{// ���A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
			g_camera.rot.y += D3DX_PI / 120;
			if (g_camera.rot.y >= D3DX_PI)
			{
				g_camera.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_LEFT) == true ||
			GetJoyPadPress(DIJS_BUTTON_17, 0) == TRUE)
		{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
			g_camera.rot.y -= D3DX_PI / 120;
			if (g_camera.rot.y <= -D3DX_PI)
			{
				g_camera.rot.y = D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_UP) == true ||
			GetJoyPadPress(DIJS_BUTTON_14, 0) == TRUE)
		{// ���A�i���O�X�e�B�b�N����ɓ|���ꂽ 
			if (g_camera.fLength.y >= 70.0f)
			{// ���_������̒l�܂ŉ������Ă��Ȃ�
				g_camera.fLength.y -= 3.0f;
			}
		}
		else if (GetKeyboardPress(DIK_DOWN) == true ||
			GetJoyPadPress(DIJS_BUTTON_15, 0) == TRUE)
		{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
			if (g_camera.fLength.y <= 320.0f)
			{// ���_������̒l�܂ŏオ���Ă��Ȃ�
				g_camera.fLength.y += 3.0f;
			}
		}
	}
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_camera.ViewPort);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(CAMERA_ANGEL_VIEW),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		50000.0f);

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