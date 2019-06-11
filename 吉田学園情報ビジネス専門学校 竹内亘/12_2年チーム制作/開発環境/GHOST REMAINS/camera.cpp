//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ���{��
//
//=============================================================================
#include "camera.h"
#include "mesh.h"
#include "SceneModel.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		DISTANCE		(250)			//�����_�Ǝ��_�̋���
#define		CAMERA_MOVE		(0.8f)			//�J�����̈ړ����x
#define		ROTPOOR_RY		(50)			//�����_�㉺ +��, -��
#define		ROTPOOR_VY		(80)				//�J�����{�� +��, -��
#define		DRAW_ANGLE		(45.0f)				//�J�����{�� +��, -��
#define		DRAW_ANGLEP		(DRAW_ANGLE + 10.0f)				//�J�����{�� +��, -��
#define		DRAW_DISTANCE	(2500.0f * 2500.0f)				//�J�����{�� +��, -��
#define		DRAW_DISTANCE2	(100.0f * 100.0f)				//�J�����{�� +��, -��

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CCamera::Info CCamera::m_info;			//�J�������

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera(){ CManager::GetCamera() = this; }
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera() { }
//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::Init(void)
{
	m_info.pChar = NULL;
	m_info.pMove = NULL;

	m_posV = D3DXVECTOR3(0.0f, 200.0f, 200.0f);				//���_
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.1f);				//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//�i�j�R��(��)
	m_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ړI
	m_rot = D3DXVECTOR3(D3DX_PI * 0.065f, D3DX_PI, 0.0f);	//�p�x
	m_addpos = D3DXVECTOR3(0.0f, ROTPOOR_VY, 0.0f);			//�J�����Ɨ��ړ�
	m_targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ǐ]����J�����̏ꏊ
	m_fDistance = DISTANCE;									//���_�ƒ����_�̋���

	m_fGMagnification = 0.5f;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::Uninit(void)
{
	CManager::GetCamera() = NULL;
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	bool bDrop = false;
	if (CManager::GetPlayer() != NULL)
	{
		if (CManager::GetPlayer()->GetbDrop()) { bDrop = true; }
	}

	if (m_info.state == STATE_GAME)
	{

	}
	else { UpdateScene(); }

	if (m_info.pChar != NULL && m_info.pMove != NULL)
	{//�Ǐ]�̏ꏊ�̍X�V
		CInputKeyboard *pInputKey = CManager::GetInputKey();
		CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//�W���C�p�b�h���l��
		float fPosY = m_posV.y;

		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			if (pInputKey->GetPress(DIK_U)) { m_rot.y += D3DX_PI * 0.0125f; }
			if (pInputKey->GetPress(DIK_O)) { m_rot.y -= D3DX_PI * 0.0125f; }
			if (pInputKey->GetPress(DIK_Y)) { m_rot.x += D3DX_PI * 0.0125f; }
			if (pInputKey->GetPress(DIK_H)) { m_rot.x -= D3DX_PI * 0.0125f; }
			if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
			if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
			if (pInputPad0->GetStickDefeat(1))
			{
				m_rot.y += D3DX_PI * 0.01f * (pInputPad0->GetnStickX(1) * 0.00005f);
				m_rot.x += D3DX_PI * 0.01f * (pInputPad0->GetnStickY(1) * -0.00005f);
			}

			if (m_rot.x > D3DX_PI * 0.3f) { m_rot.x = D3DX_PI * 0.3f; }
			if (m_rot.x < -D3DX_PI * 0.3f) { m_rot.x = -D3DX_PI * 0.3f; }
			if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
			if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
		}

		if (m_pDistance != NULL) { m_fDistance += (m_pDistance[0] - m_fDistance) * 0.05f; }
		m_targetpos += (m_info.pChar[0] - m_targetpos) * 0.08f;

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + m_targetpos + m_addpos;	//����ꏊ + �����ړ���
		//m_posR += D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -30.0f;
		//m_posR +=D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -50.0f;

		//���_�@���� + (�p�x * ����) + �����ړ���
		m_goal = D3DXVECTOR3(
			m_targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),	//X��
			m_targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,		//Y��
			m_targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z��
		m_posV += (m_goal - m_posV) * m_fGMagnification;

		if (bDrop)
		{//�����Ă���Ȃ�
			m_rot.y += (m_fDRot - m_rot.y) * 0.05f;
			m_posV.y = fPosY;
		}
		//m_posV.y = fY;
	}
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Reset(void)
{
	if (m_info.pChar != NULL)
	{//�Ǐ]�̏ꏊ�̍X�V
		if (m_pDistance != NULL) { m_fDistance = m_pDistance[0]; }

		m_targetpos = m_info.pChar[0];
		//if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y < -50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y - 50; }
		//if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y > 50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y + 50; }

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + m_targetpos + m_addpos;	//����ꏊ + �����ړ���

																						//���_�@���� + (�p�x * ����) + �����ړ���
		m_goal = D3DXVECTOR3(
			m_targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),						//X��
			m_targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,									//Y��
			m_targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z��

		m_posV = m_goal;
	}
}
//=============================================================================
// 3D�̕`�揈�������΍􏈗�
//=============================================================================
bool CCamera::DrawCamera(D3DXVECTOR3 &pos, float fLength)
{//�����_���猩�Ĉ��͈͓��Ȃ�`��
	//float fAngle = atan2f(m_posV.x - pos.x, m_posV.z - pos.z) - m_rot.y;

	//if (fAngle > D3DX_PI) { fAngle -= D3DX_PI * 2.0f; }
	//if (fAngle < -D3DX_PI) { fAngle += D3DX_PI * 2.0f; }

	//if (fAngle >= -D3DX_PI * (DRAW_ANGLEP / 180) && fAngle <= +D3DX_PI * (DRAW_ANGLEP / 180))
	//{//�J�����̌����ʂ�Ȃ�
	//	float fDistance = powf(m_posR.x - pos.x, 2) + powf(m_posR.z - pos.z, 2);
	//	if (fDistance < fLength + DRAW_DISTANCE) { return true; }
	//}

	//if (CManager::GetMode() == CManager::MODE_TITLE) { return true; }
	return true;
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	D3DXVECTOR3 WKValue, WKmove;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3	WKlength = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	D3DXVECTOR3	WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	WKposV = m_posV;
	bool bWKJump = false;

	WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -30.0f;
	WKmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nQuake > 0)
	{
		D3DXVECTOR3	WKposV2;
		D3DXVECTOR3	WKrot = m_rot;
		WKrot.x += (float)((rand() % 100) - 50) * (D3DX_PI * (m_fQuake * m_nQuake));
		WKrot.y += (float)((rand() % 100) - 50) * (D3DX_PI * (m_fQuake * m_nQuake));
		WKposV2 = D3DXVECTOR3(
			m_targetpos.x + (sinf(WKrot.y) * m_fDistance) * cosf(WKrot.x),	//X��
			m_targetpos.y + sinf(WKrot.x) * m_fDistance + ROTPOOR_VY,		//Y��
			m_targetpos.z + (cosf(WKrot.y) * m_fDistance) * cosf(WKrot.x));	//Z��
		m_posV += (WKposV2 - m_posV) * m_fGMagnification;
		m_nQuake--;
	}
	int		nCount = 0;
	CMesh::MeshCollisionCeiling(WKposV, WKValue, WKlength);
	CMesh::MeshCollisionWall(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);
	CMesh::MeshCollisionField(WKposV, WKValue, WKmove, WKlength, WKnor, bWKJump);
	WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * 30.0f;
	CSceneObjct::CollisionAll(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(DRAW_ANGLE),	//��p
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		11000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView, &WKposV, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::SetScene(SCENE_TYPE type)
{
	m_info.nCntState = 0;
	m_info.nCntTime = 0;
	m_info.state = STATE_MOVIE;
	m_info.scene = type;
}
//=============================================================================
// �V�[���Đ�����
//=============================================================================
void CCamera::UpdateScene(void)
{
	if (m_info.state == STATE_MOVIE)
	{//�V�[���Đ�
		switch (m_info.scene)
		{
		case SCENE_TYPE_NO:	//�G���[�����p
			Init();
			break;

		case SCENE_TYPE_BOSS:	//�{�X�O
			//Scene_BOSS();
			break;
		}
	}
}
