//=============================================================================
//
// �����֌W���� [Number.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "2DPolygon.h"
#include "Number.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUMBER_UV_X		(10)
#define NUMBER_UV_Y		(1)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//==================================================================================================//
//    * �Z�b�g�֐� *
//==================================================================================================//
void CNumber::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, int nScore, int nDigits, D3DXCOLOR col, STATE state)	//�X�R�A(����)��TEXTURE
{
	m_state = state;
	m_nNumber = nScore;

	if (m_p2D != NULL)
	{//���Ƀ��������g���Ă���Ȃ�
		for (int nCount = 0; nCount < m_nNum2D; nCount++)
		{//����int���폜
			delete m_p2D[nCount];
		}//�{�̍폜
		delete[] m_p2D;
		m_p2D = NULL;
	}
	m_nNum2D = nDigits;
	m_p2D = new C2D*[m_nNum2D];
	if (m_p2D != NULL)
	{//�����ł����I
		int nNumber = m_nNumber;
		for (int nCount = 0; nCount < m_nNum2D; nCount++)
		{//��������]
			m_p2D[nCount] = new C2D;
			m_p2D[nCount]->Init();

			//�Z�b�g����
			if (m_p2D != NULL)
			{//�����ł����I
				m_p2D[nCount]->Set(pos + D3DXVECTOR3(nCount * (fLengthX * -2.0f), 0.0f, 0.0f), fLengthX, flengthY, D3DX_PI, nNumber % 10, NUMBER_UV_X, NUMBER_UV_Y, col);
				m_p2D[nCount]->BindTexture(CScene::Load(CScene::TEX_Number));
			}

			nNumber /= 10;
		}
	}
}
//==================================================================================================//
//    * �Z�b�g�֐� *
//==================================================================================================//
void CNumber::SetNumber(int nScore)
{
	m_nNumber = nScore;
	if (m_p2D != NULL)
	{
		int nNumber = m_nNumber;
		if (m_state == STATE_TIMER) { nNumber /= 60; }
		for (int nCount = 0; nCount < m_nNum2D; nCount++)
		{
			m_p2D[nCount]->SetUV(nNumber % 10, NUMBER_UV_X, NUMBER_UV_Y);
			nNumber /= 10;
		}
	}
}
//==================================================================================================//
//    * �Z�b�g�֐� *
//==================================================================================================//
void CNumber::AddNumber(int nValue)
{
	m_nNumber += nValue;
	SetNumber(m_nNumber);
}
//=============================================================================
// �S�����̐F�ύX����
//=============================================================================
void	CNumber::SetColor(D3DXCOLOR col)
{
	for (int nCount = 0; nCount < m_nNum2D; nCount++)
	{//��������]
		m_p2D[nCount]->SetColor(col);
	}
}
//=============================================================================
// �����̏���������
//=============================================================================
HRESULT  CNumber::Init(void)
{
	m_nNumber = 0;
	m_nNum2D = 0;
	m_p2D = NULL;
	m_state = STATE_MAX;
	m_fCntState = 0.0f;
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CNumber::Uninit(void)
{
	for (int nCount = 0; nCount < m_nNum2D; nCount++)
	{
		m_p2D[nCount]->Uninit();
	}
	delete this;
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CNumber::Update(void)
{
	if (m_state != STATE_MAX)
	{
		switch (m_state)
		{
		case STATE_TIMER:
			if (m_nNumber > 0) { m_nNumber--; }
			SetNumber(m_nNumber);
			break;
		case STATE_RANKING:
			m_fCntState += 1.0f;
			if ((int)m_fCntState % 30 == 0) { SetColor(D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f)); }
			else if ((int)m_fCntState % 15 == 0) { SetColor(D3DXCOLOR(0.0f, 0.1f, 0.0f, 1.0f)); }
			break;
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CNumber::Draw(void)
{
	for (int nCount = 0; nCount < m_nNum2D; nCount++)
	{
		m_p2D[nCount]->Draw();
	}
}
