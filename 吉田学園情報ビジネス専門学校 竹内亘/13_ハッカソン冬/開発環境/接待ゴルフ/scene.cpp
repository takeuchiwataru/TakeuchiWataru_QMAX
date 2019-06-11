//---------------------------------------------------------------------
//	�V�[������(scene.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "scene.h"
#include "debugproc.h"
#include "manager.h"
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
CScene *CScene::m_pTop[NUM_PRIORITY] = {};
CScene *CScene::m_pCur[NUM_PRIORITY] = {};
bool    CScene::m_bPause = false;
//--------------------------------------------
//�V�[���N���X �R���X�g���N�^
//--------------------------------------------
CScene::CScene(int nPriority ,CScene::OBJTYPE ObjType)
{
		//CUR�����Ȃ��Ƃ��������ŏ��ɂȂ�
		if (m_pCur[nPriority] == NULL)
		{
			m_pTop[nPriority] = this;
		}
		else
		{
			//�Ō���̃I�u�W�F�N�g�̎���NULL�̎�
			if (m_pCur[nPriority]->m_pNext == NULL)
			{
				m_pCur[nPriority]->m_pNext = this;
			}
		}
		m_pDeath = false;
		m_pPrev = m_pCur[nPriority];
		m_pNext = NULL;
		m_nPriority = nPriority;
		m_ObjType = ObjType;
		m_pCur[nPriority] = this;
}

//--------------------------------------------
//�V�[���N���X �f�X�g���N�^
//--------------------------------------------
CScene::~CScene()
{

}

void CScene::Setpos(D3DXVECTOR3 pos)
{
}

//--------------------------------------------
//�V�[���̊�{�N���X �V�[���̑������擾
//--------------------------------------------
int CScene::GetNumAll(void)
{
	return 0;
}

//--------------------------------------------
//�S�Ă̊J������
//--------------------------------------------
void CScene::ReleaseAll(void)
{

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_pTop[nCntPri];
		CScene *pNext = NULL;

		while (pScene)	//NULL�`�F�b�N
		{
			//�ꎞ�ۑ�
			pNext = pScene->m_pNext;
			//�j��
			pScene->Uninit();
			//�ꎞ�ۑ�����
			pScene = pNext;
		}
		//TOP�ɖ߂�
		pScene = m_pTop[nCntPri];
		//�t���O�������Ă���I�u�W�F�N�g��j��
		while (pScene)	//NULL�`�F�b�N
		{
			//Update�ŏ������肷��̂Ŏc���Ă���
			CScene *pSceneNext = pScene->m_pNext;
			//�폜����
			if (pScene->m_pDeath == true)
			{
				pScene->UninitAll();
			}
			//���̃I�u�W�F�N�g�̃A�h���X����
			pScene = pSceneNext;
		}
	}
}
//--------------------------------------------
//�S�Ă̍X�V����
//--------------------------------------------
void CScene::UpdateAll(void)
{
	int nPriModelNum = 0;
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	if (pInput->GetTrigger(DIK_P) == true)
	{
		m_bPause = m_bPause ? false : true;
	}

	if (m_bPause == false)
	{
		for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
		{
			CScene *pScene = m_pTop[nCntPri];
			nPriModelNum = 0;
			while (pScene)	//NULL�`�F�b�N
			{
				//Update�ŏ������肷��̂Ŏc���Ă���
				CScene *pSceneNext = pScene->m_pNext;
				//�f�X�`�F�b�N
				if (pScene->m_pDeath == false)
				{
					//�X�V����
					pScene->Update();
				}
				//���̃I�u�W�F�N�g�̃A�h���X����
				pScene = pSceneNext;
				nPriModelNum++;
			}

			//TOP�ɖ߂�
			pScene = m_pTop[nCntPri];
			//�t���O�������Ă���I�u�W�F�N�g��j��
			while (pScene)	//NULL�`�F�b�N
			{
				//Update�ŏ������肷��̂Ŏc���Ă���
				CScene *pSceneNext = pScene->m_pNext;
				//�폜����
				if (pScene->m_pDeath == true)
				{
					pScene->UninitAll();
				}
				//���̃I�u�W�F�N�g�̃A�h���X����
				pScene = pSceneNext;
			}
		}
	}
}
//--------------------------------------------
//�S�Ă̕`�揈��
//--------------------------------------------
void CScene::DrawAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_pTop[nCntPri];

		while (pScene)	//NULL�`�F�b�N
		{
			//Update�ŏ������肷��̂Ŏc���Ă���
			CScene *pSceneNext = pScene->m_pNext;
			//�`�揈��
			pScene->Draw();
			//���̃I�u�W�F�N�g�̃A�h���X����
			pScene = pSceneNext;
		}
	}
}

//--------------------------------------------
//����
//--------------------------------------------
void CScene::UninitAll(void)
{
	//NULL�@�`�F�b�N
		if (this != NULL)
		{
			if (m_pNext != NULL)
			{
				if (m_pPrev != NULL)
				{
					//���̃I�u�W�F�N�g�ւ̃|�C���^������Ƃ��O�̃|�C���^��pNext�Ɏ�����pNext����
					m_pPrev->m_pNext = m_pNext;
					//���̃|�C���^��pPrev�Ɏ�����pPrev����
					m_pNext->m_pPrev = m_pPrev;
				}
				else if (m_pPrev == NULL)
				{
					m_pNext->m_pPrev = NULL;
					//������Top�������玟�̃I�u�W�F�N�g��Top�ɂȂ�
					m_pTop[m_nPriority] = m_pNext;
				}
			}
			else if (m_pNext == NULL)
			{
				if (m_pPrev != NULL)
				{
					//���ւ̃|�C���^���Ȃ����ɂ�NULL������
					m_pPrev->m_pNext = NULL;
					//����NULL�̎��͎������Ō�������玩����j������O�ɍŌ�����㏑��
					m_pCur[m_nPriority] = m_pPrev;
				}
				else if (m_pPrev == NULL)
				{
					m_pCur[m_nPriority] = NULL;
					m_pTop[m_nPriority] = NULL;
				}
			}
			//�j��
			delete this;
		}
}

//--------------------------------------------
//�I�u�W�F�N�g�^�C�v�ݒ菈��
//--------------------------------------------
void CScene::SetObjType(OBJTYPE ObjType)
{
	m_ObjType = ObjType;
}
//--------------------------------------------
//�I�u�W�F�N�g�^�C�v�擾����
//--------------------------------------------
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_ObjType;
}

//--------------------------------------------
//���݂̐擪�A�h���X��Ԃ�����
//--------------------------------------------
CScene *& CScene::GetTop(int nPriority)
{
	return m_pTop[nPriority];
}

//--------------------------------------------
//���S�t���O���ݏ���
//--------------------------------------------
void CScene::Release(void)
{
	m_pDeath = true;
}