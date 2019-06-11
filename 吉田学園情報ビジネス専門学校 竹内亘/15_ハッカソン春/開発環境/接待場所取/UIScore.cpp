//---------------------------------------------------------------------
//	�X�R�A����(score.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "UIScore.h"
#include "number.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//--------------------------------------------
//�X�R�A�N���X �R���X�g���N�^
//--------------------------------------------
CScore::CScore(int nPriority) : CScene(nPriority)
{
}

//--------------------------------------------
//�X�R�A�N���X �f�X�g���N�^
//--------------------------------------------
CScore::~CScore()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CScore *CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScore *pScore;
	pScore = new CScore;
	pScore->m_pos = pos;
	pScore->m_fWidth = fWidth;
	pScore->m_fHeight = fHeight;
	pScore->Init();
	return pScore;
}


//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CScore::Init(void)
{
	CNumber::Load();

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{	//�����̏�����
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3((m_pos.x - (m_fWidth * 1.2f) * nCnt), m_pos.y, m_pos.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fWidth, m_fHeight);
		}
	}
	//�X�R�A������
	m_nScore = 0;
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_SCENE2D);
	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CScore::Uninit(void)
{
	CNumber::UnLoad();

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			if (m_apNumber[nCnt]->GetDeath() == false)
			{
				//�X�R�A��������i���o�[������
				m_apNumber[nCnt]->Uninit();
				m_apNumber[nCnt] = NULL;
			}
		}
	}
	//������j��
	Release();
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CScore::Update(void)
{

}

//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CScore::Draw(void)
{
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// �����̉��Z����
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nAnswer = 0;
	int nDigit = 1;
	//�X�R�A���Z
	m_nScore += nValue;

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//�����̌v�Z
		nAnswer = m_nScore % (nDigit * 10) / nDigit;
		//���̌��̐������Z�b�g
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->SetNumber(nAnswer);
		}
		//���̌���
		nDigit *= 10;
	}
}
//=============================================================================
// ���݂̃X�R�A��Ԃ�
//=============================================================================
int CScore::GetScore()
{
	return m_nScore;
}
//=============================================================================
// �F��ݒ�
//=============================================================================
void CScore::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apNumber[nCnt]->SetColor(col);
	}
}

