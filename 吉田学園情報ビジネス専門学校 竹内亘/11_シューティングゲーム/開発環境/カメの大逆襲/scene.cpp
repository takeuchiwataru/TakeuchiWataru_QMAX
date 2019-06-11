//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : �|���j
//
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScene * CScene::m_apScene[NUM_PRIORITY][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;

			m_nID = nCntScene;			// �������g�̔ԍ��ݒ�
			m_nPriority = nPriority;	// �D�揇�ʂ̐ݒ�
			m_objType = CScene::OBJTYPE_NONE;
			m_nNumAll++;
			break;
		}
	}
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}
//=============================================================================
// �I�u�W�F�N�g�̎�ސݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE ObjType)
{
	m_objType = ObjType;
}
//=============================================================================
// �I�u�W�F�N�g�̎�ގ擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}
//=============================================================================
// 
//=============================================================================
CScene *CScene::GetScene(int nPriority,int nIdx)
{
	return m_apScene[nPriority][nIdx];
}
////=============================================================================
//// 
////=============================================================================
//CScene *CScene::GetScene(void)
//{
//	return;
//}
//=============================================================================
// �S�ĉ��
//=============================================================================
void CScene::ReleseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Uninit();

				delete m_apScene[nCntPriority][nCntScene];
				m_apScene[nCntPriority][nCntScene] = {};
			}
		}
	}
}
//=============================================================================
// �S�čX�V
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}
//=============================================================================
// �S�ĕ`��
//=============================================================================
void CScene::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}
//=============================================================================
// �I�u�W�F�N�g�̔j��
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		//delete[] m_apScene[m_nID];
		//m_apScene[m_nID] = NULL;		// �_��!

		int nID;					// �ۑ��p
		nID = m_nID;				// �ۑ�	// m_nID���s��ɂȂ�O�ɕۑ�����

		int nPriority;				// �D�揇�ʂ̕ۑ��p
		nPriority = m_nPriority;	// �ۑ�

		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}
