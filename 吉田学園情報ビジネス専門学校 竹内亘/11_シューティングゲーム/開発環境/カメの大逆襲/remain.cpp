//=============================================================================
//
// �c�@���� [remain.h]
// Author : �|���j
//
//=============================================================================
#include "remain.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
//int CRemain::m_nRemain = 0;
//CNumber * CRemain::m_apNumber[MAX_REMAIN] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRemain::CRemain()
{
	m_nRemain = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRemain::~CRemain()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CRemain::Init(D3DXVECTOR3 pos)
{
	int nRemain;

	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		m_apNumber[nCount] = new CNumber;

		//m_apNumber[nCount]->Create(D3DXVECTOR3(pos.x + (SCORE_INTERVAL_SIZE * nCount), pos.y, pos.z));// ��
		m_apNumber[nCount]->Init(D3DXVECTOR3(pos.x - (REMAIN_INTERVAL_SIZE * nCount), pos.y, pos.z));
	}

	m_nRemain = 0;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene2D *pScene;

			// Scene�̎擾
			pScene = (CScene2D*)CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;

				// �I�u�W�F�N�g�̎擾
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{// �v���C���[��������
					CPlayer * pPlayer = (CPlayer*)pScene;

					nRemain = pPlayer->GetRemain();

					break;
				}
			}
		}
	}
	
	AddRemain(nRemain);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CRemain::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		m_apNumber[nCount]->Uninit();
	}

	// �I�u�W�F�N�g(�������g)�̔j��
	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CRemain::Update(void)
{
	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		m_apNumber[nCount]->Update();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CRemain::Draw(void)
{
	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}
////=============================================================================
//// �c�@�̐ݒu
////=============================================================================
//void CRemain::SetScore(int nScore)
//{
//	m_nRemain = nScore;
//}
////=============================================================================
//// �c�@�̎擾
////=============================================================================
//int CRemain::GetScore(void)
//{
//	return m_nRemain;
//}
//=============================================================================
// �c�@�̉��Z
//=============================================================================
void CRemain::AddRemain(int nValue)
{
	m_nRemain += nValue;

	int nAnswer = 1;
	int nRemain;

	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		nRemain = m_nRemain % (nAnswer * 10) / nAnswer;
		m_apNumber[nCount]->SetNumber(nRemain);
		nAnswer *= 10;
	}
}
//=============================================================================
// �c�@�̐���
//=============================================================================
CRemain * CRemain::Create(D3DXVECTOR3 pos)
{
	CRemain *pRemain = NULL;

	if (pRemain == NULL)
	{
		pRemain = new CRemain;

		if (pRemain != NULL)
		{
			pRemain->Init(pos);
		}
	}
	return pRemain;
}
