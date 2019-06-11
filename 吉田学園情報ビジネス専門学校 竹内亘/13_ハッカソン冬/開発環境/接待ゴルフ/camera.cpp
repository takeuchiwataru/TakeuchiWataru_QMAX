//=============================================================================
//
// �J�������� [camera.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "game.h"
#include "camera.h"
#include "input.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "player.h"
#include "ball.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_CAMERA			(3.5f)						//���f���ړ���
#define MOVE_SIN_COS_TOP_CAMERA	(0.75f)						//�J�����ړ���
#define MOVE_SIN_COS_BOT_CAMERA	(0.25f)						//�J�����ړ���

//--------------------------------------------
//�J�����N���X �R���X�g���N�^
//--------------------------------------------
CCamera::CCamera()
{
}

//--------------------------------------------
//�J�����N���X �f�X�g���N�^
//--------------------------------------------
CCamera::~CCamera()
{
}

//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::Init(void)
{
	m_Camera.posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);
	m_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.posU = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_Camera.rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.nCounterAngle = 0;
	fLength = sqrtf(
		//X�̋��������߂�@X�̋�����2��
		(m_Camera.posR.x - m_Camera.posV.x) * (m_Camera.posR.x - m_Camera.posV.x)
		//Z�̋��������߂�@Z�̋�����2��
		+ (m_Camera.posR.z - m_Camera.posV.z) * (m_Camera.posR.z - m_Camera.posV.z));

	m_State = STATE_NORMAL;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Update(void)
{
#if 1
	//���݂̃��[�h���擾
	 CManager::MODE mode = CManager::GetMode();

	 //�L�[�{�[�h�����擾
	 CInputKeyboard *pInput = CManager::GetInputKeyboard();
	switch (mode)
	{
	case CManager::MODE_GAME:
		CBall *pBall = CGame::GetBall();

		if (m_State == STATE_NORMAL)
		{
			m_Camera.posRDest.x = pBall->GetPos().x - sinf(pBall->GetRot().y) * 30;
			m_Camera.posRDest.y = pBall->GetPos().y - sinf(pBall->GetRot().x) * 30;
			m_Camera.posRDest.z = pBall->GetPos().z - cosf(pBall->GetRot().y) * 30;
			//�J�����̋���
			m_Camera.posVDest.x = pBall->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
			m_Camera.posVDest.y = pBall->GetPos().y - sinf(m_Camera.rotCamera.x) * (fLength - 100);
			m_Camera.posVDest.z = pBall->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 100);
			//����
			m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pBall->GetMove().x;
			m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 8;	//�J�����̒����_�̏㉺�ʒu���ς��
			m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pBall->GetMove().z;

			//���_
			m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f) + 25;
			m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) + 25;
			m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);
		}
		else if (m_State == STATE_NORMAL2)
		{
			m_Camera.posRDest.x = pBall->GetPos().x - sinf(pBall->GetRot().y) * 30;
			m_Camera.posRDest.y = pBall->GetPos().y - sinf(pBall->GetRot().x) * 30;
			m_Camera.posRDest.z = pBall->GetPos().z - cosf(pBall->GetRot().y) * 30;
			//�J�����̋���
			m_Camera.posVDest.x = pBall->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
			m_Camera.posVDest.y = pBall->GetPos().y - sinf(m_Camera.rotCamera.x) * (fLength - 100);
			m_Camera.posVDest.z = pBall->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 100);
			//����
			m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pBall->GetMove().x;
			m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 8;	//�J�����̒����_�̏㉺�ʒu���ς��
			m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pBall->GetMove().z;

			//���_
			m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f) - 25;
			m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) + 25;
			m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);
		}
		else if (m_State == STATE_FALL)
		{
			//m_Camera.posRDest.x = pBall->GetPos().x - sinf(pBall->GetRot().y) * 30;
			//m_Camera.posRDest.y = 0.0f;
			//m_Camera.posRDest.z = pBall->GetPos().z - cosf(pBall->GetRot().y) * 30;
			////�J�����̋���
			//m_Camera.posVDest.x = pBall->GetPos().x - sinf(m_Camera.rotCamera.y) * (fLength - 100);
			//m_Camera.posVDest.y = 1300.0f;
			//m_Camera.posVDest.z = pBall->GetPos().z - cosf(m_Camera.rotCamera.y) * (fLength - 100);
			////����
			//m_Camera.posR.x += (m_Camera.posRDest.x - m_Camera.posR.x) * 0.2f + pBall->GetMove().x;
			//m_Camera.posR.y += (m_Camera.posRDest.y - m_Camera.posR.y) * 0.2f + 20.0f;	//�J�����̒����_�̏㉺�ʒu���ς��
			//m_Camera.posR.z += (m_Camera.posRDest.z - m_Camera.posR.z) * 0.2f + pBall->GetMove().z;

			////���_
			//m_Camera.posV.x += ((m_Camera.posVDest.x - m_Camera.posV.x) * 0.2f);
			//m_Camera.posV.y += ((m_Camera.posVDest.y - m_Camera.posV.y) * 0.2f) - 50;
			//m_Camera.posV.z += ((m_Camera.posVDest.z - m_Camera.posV.z) * 0.2f);

			m_Camera.posR.x = 0.0f;
			m_Camera.posR.y = 100.0f;	//�J�����̒����_�̏㉺�ʒu���ς��
			m_Camera.posR.z = 10590.0f;


			//���_
			m_Camera.posV.x = 0.0f;
			m_Camera.posV.y = 700;
			m_Camera.posV.z = 10360;
		}
		break;
	}
#endif

	//�J�����̑���
#if 0
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�ړ�����

	//�C�ӂ̃L�[��
	if (pInput->GetPress(DIK_LEFT) == true)
	{
		if (pInput->GetPress(DIK_UP) == true)
		{//�����ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.75f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.75f) * MOVE_CAMERA;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else if (pInput->GetPress(DIK_DOWN) == true)
		{//����O�ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.25f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.25f) * MOVE_CAMERA;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else
		{
			//�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
	}
	//�C�ӂ̃L�[��
	else if (pInput->GetPress(DIK_RIGHT) == true)
	{
		if (pInput->GetPress(DIK_UP) == true)
		{//�E���ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y - D3DX_PI * 0.75f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y - D3DX_PI * 0.75f) * MOVE_CAMERA;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else if (pInput->GetPress(DIK_DOWN) == true)
		{//�E��O�ړ�
		 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_Camera.posV.x -= sinf(m_Camera.rotCamera.y - D3DX_PI * 0.25f) * MOVE_CAMERA;
			m_Camera.posV.z -= cosf(m_Camera.rotCamera.y - D3DX_PI * 0.25f) * MOVE_CAMERA;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
		else
		{
			//�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_Camera.posV.x += sinf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
			m_Camera.posV.z += cosf(m_Camera.rotCamera.y + D3DX_PI * 0.5f) * MOVE_CAMERA;
			//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
			m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
			m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
		}
	}
	else if (pInput->GetPress(DIK_UP) == true)
	{//���ړ�
	 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
		m_Camera.posV.x += sinf(m_Camera.rotCamera.y) * MOVE_CAMERA;
		m_Camera.posV.z += cosf(m_Camera.rotCamera.y) * MOVE_CAMERA;
		//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
	}
	else if (pInput->GetPress(DIK_DOWN) == true)
	{//��O�ړ�
	 //�J�����̈ړ�	�J�����̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
		m_Camera.posV.x -= sinf(m_Camera.rotCamera.y) * MOVE_CAMERA;
		m_Camera.posV.z -= cosf(m_Camera.rotCamera.y) * MOVE_CAMERA;
		//�J�����̒����_�̈ړ� �J�����̈ʒu + �J�����̊p�x * �J�����̋���
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y) * fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y) * fLength;
	}
	//�C�ӂ̃L�[C
	if (pInput->GetPress(DIK_C) == true)
	{
		m_Camera.rotCamera.y -= 0.05f;
		// -3.14���������
		if (m_Camera.rotCamera.y < -D3DX_PI)
		{
			// -3.14�� 3.14�ɂ���
			m_Camera.rotCamera.y += D3DX_PI * 2.0f;
		}
		m_Camera.posV.x = m_Camera.posR.x + sinf(m_Camera.rotCamera.y + D3DX_PI)* fLength;
		m_Camera.posV.z = m_Camera.posR.z + cosf(m_Camera.rotCamera.y + D3DX_PI)* fLength;

	}
	//�C�ӂ̃L�[Z
	if (pInput->GetPress(DIK_Z) == true)
	{
		m_Camera.rotCamera.y += 0.05f;
		// 3.14��������
		if (m_Camera.rotCamera.y > D3DX_PI)
		{
			// 3.14�� -3.14�ɂ���
			m_Camera.rotCamera.y -= D3DX_PI * 2.0f;
		}
		m_Camera.posV.x = m_Camera.posR.x + sinf(m_Camera.rotCamera.y + D3DX_PI)* fLength;
		m_Camera.posV.z = m_Camera.posR.z + cosf(m_Camera.rotCamera.y + D3DX_PI)* fLength;

	}
	//�C�ӂ̃L�[Q
	if (pInput->GetPress(DIK_Q) == true)
	{
		m_Camera.rotCamera.y -= 0.03f;
		// -3.14���������
		if (m_Camera.rotCamera.y < -D3DX_PI)
		{
			// -3.14�� 3.14�ɂ���
			m_Camera.rotCamera.y += D3DX_PI * 2.0f;
		}
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y)* fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y)* fLength;

	}
	//�C�ӂ̃L�[E
	if (pInput->GetPress(DIK_E) == true)
	{
		m_Camera.rotCamera.y += 0.03f;
		// 3.14��������
		if (m_Camera.rotCamera.y > D3DX_PI)
		{
			// 3.14�� -3.14�ɂ���
			m_Camera.rotCamera.y -= D3DX_PI * 2.0f;
		}
		m_Camera.posR.x = m_Camera.posV.x + sinf(m_Camera.rotCamera.y)* fLength;
		m_Camera.posR.z = m_Camera.posV.z + cosf(m_Camera.rotCamera.y)* fLength;

	}
	//�C�ӂ̃L�[T
	if (pInput->GetPress(DIK_T) == true)
	{
		m_Camera.rotCamera.x += 1.5f;
		m_Camera.posR.y = m_Camera.rotCamera.x;
	}
	//�C�ӂ̃L�[B
	if (pInput->GetPress(DIK_B) == true)
	{
		m_Camera.rotCamera.x -= 1.5f;
		m_Camera.posR.y = m_Camera.rotCamera.x;
	}
	//�C�ӂ̃L�[Y
	if (pInput->GetPress(DIK_Y) == true)
	{
		m_Camera.posV.y += 2.0f;
	}
	//�C�ӂ̃L�[N
	if (pInput->GetPress(DIK_N) == true)
	{
		m_Camera.posV.y -= 2.0f;
	}
#endif
#ifdef DEBUG
	CDebugProc::Print(1, "\n [�J�����̑���] �J�����̌��� Z:C ���E Y:N �㉺ / �����_ Q:E ���E T:B �㉺  \n\n");

	CDebugProc::Print(1, " �J�����̎��_  : ( %.1f ,%.1f ,%.1f )\n", m_Camera.posV.x, m_Camera.posV.y, m_Camera.posV.z);
	CDebugProc::Print(1, " �J�����̒����_: ( %.1f ,%.1f ,%.1f )\n", m_Camera.posR.x, m_Camera.posR.y, m_Camera.posR.z);
	CDebugProc::Print(1, " �J�����̌���  : ( %.1f ,%.1f ,%.1f )\n", m_Camera.rotCamera.x, m_Camera.rotCamera.y, m_Camera.rotCamera.z);
#endif

#ifdef  _DEBUG
	CDebugProc::Print(1, " �J�����̎��_  : ( %.1f ,%.1f ,%.1f )\n", m_Camera.posV.x, m_Camera.posV.y, m_Camera.posV.z);
	CDebugProc::Print(1, " �J�����̒����_: ( %.1f ,%.1f ,%.1f )\n", m_Camera.posR.x, m_Camera.posR.y, m_Camera.posR.z);
#endif

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_Camera.mtxView,
		&m_Camera.posV,
		&m_Camera.posR,
		&m_Camera.posU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_Camera.mtxView);
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CCamera::Camera CCamera::GetCamera(void)
{
	return m_Camera;
}

//=============================================================================
// �J�����̎擾
//=============================================================================
void CCamera::SetState(STATE state)
{
	m_State = state;
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CCamera::STATE CCamera::GetState(void)
{
	return m_State;
}