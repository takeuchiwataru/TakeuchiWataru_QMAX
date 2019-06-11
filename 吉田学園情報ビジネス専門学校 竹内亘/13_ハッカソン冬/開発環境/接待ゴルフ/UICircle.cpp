//---------------------------------------------------------------------
//	�T�[�N������(Circle.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "UICircle.h"
#include "meshField.h"
#include "fade.h"
#include "game.h"
#include "ball.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define TEXTURE_NAME001		"data\\TEXTURE\\ROAD002.jpg"	// �n�ʂ̃e�N�X�`����
#define TEXTURE_NAME002		"data\\TEXTURE\\Circle000.png"	// �n�ʂ̃e�N�X�`����
//#define TEXTURE_NAME003		"data\\TEXTURE\\Circle004.jpg"	// �n�ʂ̃e�N�X�`����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CCircle::m_pTexture[CIRCLETEX_MAX] = {};

//--------------------------------------------
//�T�[�N���N���X �R���X�g���N�^
//--------------------------------------------
CCircle::CCircle() : CScene(3, CScene::OBJTYPE_FIELD)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//�ʒu
	m_posold = D3DXVECTOR3(0, 0, 0);				//�O��̈ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);					//����
	m_col = D3DXCOLOR(1, 1, 1, 1);					//�F
	m_Type = CCircle::CIRCLETEX_NORMAL;
	m_fDepth = 0;
	m_fWidth = 0;
	m_fMinusWidth[MAX_CIRCLE] = { 0 };
	m_fMinusDepth[MAX_CIRCLE] = { 0 };
	m_nSplitX = 1;
	m_nSplitZ = 1;

}

//--------------------------------------------
//�T�[�N���N���X �f�X�g���N�^
//--------------------------------------------
CCircle::~CCircle()
{
}

//--------------------------------------------
//�T�[�N���̐���
//--------------------------------------------
CCircle *CCircle::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, D3DXCOLOR col, CIRCLETEX tex, int nSplitX, int nSplitZ)
{
	//�T�[�N���|�C���^
	CCircle *pObjectBG;
	pObjectBG = new CCircle;
	//�^�C�v�̐ݒ�
	pObjectBG->m_Type = tex;

	//�����l���������� pos���
	pObjectBG->m_pos = pos;
	pObjectBG->m_fDepth = fDepth;
	pObjectBG->m_fWidth = fWidth;
	pObjectBG->m_nSplitX = nSplitX;
	pObjectBG->m_nSplitZ = nSplitZ;

	//�T�[�N���̏�����
	pObjectBG->Init();

	//�T�[�N���̏���Ԃ�
	return pObjectBG;
}

//=============================================================================
// �T�[�N���̏���������
//=============================================================================
HRESULT CCircle::Init(void)
{
	//�T�[�N����ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_FIELD);

	m_move = D3DXVECTOR3(0, 0, 0);
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

												//���f���𐶐�	�I�t�Z�b�g�ݒ�
	m_pCircle[0] = CSceneMeshField::Create(m_pos, m_fWidth, m_fDepth, m_nSplitX, m_nSplitZ);
	//�e�N�X�`�������蓖��
	m_pCircle[0]->BindTexture(m_pTexture[m_Type]);
	//�F�����蓖��
	m_pCircle[0]->SetColor(D3DXCOLOR(1, 1, 0, 0.7f));

	//���f���𐶐�	�I�t�Z�b�g�ݒ�
	m_pCircle[1] = CSceneMeshField::Create(D3DXVECTOR3(m_pos.x + m_fWidth / 4, m_pos.y + 0.2f, m_pos.z - m_fDepth / 4),
		m_fWidth / 2, m_fDepth / 2, m_nSplitX, m_nSplitZ);
	//�e�N�X�`�������蓖��
	m_pCircle[1]->BindTexture(m_pTexture[m_Type]);
	//�F�����蓖��
	m_pCircle[1]->SetColor(D3DXCOLOR(1, 0, 0, 0.7f));

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		m_fMinusWidth[nCnt] = 0;
		m_fMinusDepth[nCnt] = 0;
	}
	return S_OK;
}

//=============================================================================
// �T�[�N���̏I������
//=============================================================================
void CCircle::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (m_pCircle[nCnt] != NULL)
		{
			m_pCircle[nCnt]->Uninit();
			m_pCircle[nCnt] = NULL;
		}
	}

	//����������(�T�[�N����j��)
	Release();
}

//=============================================================================
// �T�[�N���̍X�V����
//=============================================================================
void CCircle::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	//�J�������擾
	CBall *pBall = CGame::GetBall();

	//�J�������擾
	CCamera *pCamera = CGame::GetCamera();

	// �v���C���[�̏�Ԃ��擾
	CCamera::STATE CameraState;
	CameraState = pCamera->GetState();

	if (CameraState == CCamera::STATE_FALL)
	{

		m_fMinusWidth[0] += 1.7f;
		m_fMinusDepth[0] += 1.7f;
		m_fMinusWidth[1] += 1.0f;
		m_fMinusDepth[1] += 1.0f;

		//�傫���~
		if (m_pCircle[0] != NULL)
		{
			//0�ȉ��ɂȂ�Ȃ��悤��
			if (m_fMinusWidth[0] > 300.0f)
			{
				m_fMinusWidth[0] = 300.0f;
			}
			m_pCircle[0]->SetWidthDepth(m_fWidth - m_fMinusWidth[0], m_fDepth - m_fMinusDepth[0]);
			m_pCircle[0]->Setpos(D3DXVECTOR3(pBall->GetPos().x + m_fMinusWidth[0] / 2 - 150.0f,m_pos.y, pBall->GetPos().z - m_fMinusDepth[0] / 2 + 150.0f));
		}
		//�������~
		if (m_pCircle[1] != NULL)
		{
			//0�ȉ��ɂȂ�Ȃ��悤��
			if (m_fMinusWidth[1] > 150.0f)
			{
				m_fMinusWidth[1] = 150.0f;
			}
			m_pCircle[1]->SetWidthDepth((m_fWidth / 2) - m_fMinusWidth[1], (m_fDepth / 2) - m_fMinusDepth[1]);
			m_pCircle[1]->Setpos(D3DXVECTOR3((pBall->GetPos().x + m_fWidth / 4) + m_fMinusWidth[1] / 2 - 150.0f, m_pos.y + 0.2f, (pBall->GetPos().z - m_fDepth / 4) - m_fMinusDepth[1] / 2 + 150.0f));
		}
	}

	if (pBall->GetTryTimer() > 300)
	{
		Init();
	}
}

//=============================================================================
// �T�[�N���̕`�揈��
//=============================================================================
void CCircle::Draw(void)
{
	//�J�������擾
	CCamera *pCamera = CGame::GetCamera();

	// �v���C���[�̏�Ԃ��擾
	CCamera::STATE CameraState;
	CameraState = pCamera->GetState();

	if (CameraState == CCamera::STATE_FALL)
	{
		//�f�o�C�X���擾
		CRenderer *pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


		for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
		{
			if (m_pCircle[nCnt] != NULL)
			{
			//	m_pCircle[nCnt]->Draw();
			}
		}
		//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// �T�[�N���̈ʒu�ݒ�
//=============================================================================
void CCircle::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CCircle::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME002, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CCircle::UnLoad(void)
{
	for (int nCnt = 0; nCnt < CIRCLETEX_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
