//---------------------------------------------------------------------
//	�^�C������(UITime.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "UITime.h"
#include "number.h"
#include "manager.h"
#include "fade.h"
#include "game.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INIT_TIME		(150)

//--------------------------------------------
//�^�C���N���X �R���X�g���N�^
//--------------------------------------------
CTime::CTime(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_fLength = 0;
	m_nTime = 0;
	m_nTimerCnt = 0;
	m_nFadeCnt = 0;
	m_nColorFlash = 0;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
}

//--------------------------------------------
//�^�C���N���X �f�X�g���N�^
//--------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CTime *CTime::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTime *pTime;
	pTime = new CTime;
	pTime->m_pos = pos;
	pTime->m_fWidth = fWidth;
	pTime->m_fHeight = fHeight;
	pTime->Init();
	return pTime;
}


//=============================================================================
// �^�C���̏���������
//=============================================================================
HRESULT CTime::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{	//�����̏�����
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3((m_pos.x - (m_fWidth * 1.2f) * nCnt), m_pos.y, m_pos.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fWidth, m_fHeight);
		}
	}
	//�^�C��������
	m_nTime = INIT_TIME;
	m_nTimerCnt = 0;
	m_nFadeCnt = 0;
	m_nColorFlash = 0;

	AddTime(0);
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_SCENE2D);
	return S_OK;
}

//=============================================================================
// �^�C���̏I������
//=============================================================================
void CTime::Uninit(void)
{
	//������j��
	Release();
}

//=============================================================================
// �^�C���̍X�V����
//=============================================================================
void CTime::Update(void)
{
	//�v���C���[���擾
	CPlayer *pPlayer = CGame::GetPlayer();

	float AlphaCol = 1.0f;

	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		//10�b�ȉ�
		if (m_nTime <= 10)
		{	//5�b�ȉ�
			if (m_nTime <= 5)
			{
				m_nColorFlash++;
				if (m_nColorFlash <= 8)
				{
					AlphaCol = 0.0f;
				}
				if (m_nColorFlash >= 16)
				{
					m_nColorFlash = 0;
				}
			}
			SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, AlphaCol));
		}

		//�N���A��Ԃ܂��̓X�^�[�g�O�Ȃ玞�Ԃ��~�߂�
		if (pPlayer->GetPlayerState() != CPlayer::PLAYERSTATE_GAMECLEAR)
		{
			if (m_nTime > 0)
			{	//�J�E���g���Z
				m_nTimerCnt++;
				if (m_nTimerCnt >= 60)
				{	//�J�E���g������
					m_nTimerCnt = 0;
					//���ۂ̒l������
					m_nTime -= 1;
					//�X�V���邾��
					AddTime(0);
				}
			}
			else if (m_nTime <= 0)
			{
				//�������Ԃ�0��
				m_nTime = 0;
				//�t�F�[�h�܂ł̃J�E���g
				m_nFadeCnt++;
				if (m_nFadeCnt >= 120)
				{
					CFade::SetFade(CManager::MODE_RESULT);
				}
			}

		}
	}
}

//=============================================================================
// �^�C���̕`�揈��
//=============================================================================
void CTime::Draw(void)
{

}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;
}

//=============================================================================
// �����̉��Z����
//=============================================================================
void CTime::AddTime(int nValue)
{
	int nAnswer = 0;
	int nDigit = 1;
	//�^�C�����Z
	m_nTime += nValue;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		//�����̌v�Z
		nAnswer = m_nTime % (nDigit * 10) / nDigit;
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
// ���݂̃^�C����Ԃ�
//=============================================================================
int CTime::GetTime()
{
	return m_nTime;
}
//=============================================================================
// �F��ݒ�
//=============================================================================
void CTime::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt]->SetColor(col);
	}
}

