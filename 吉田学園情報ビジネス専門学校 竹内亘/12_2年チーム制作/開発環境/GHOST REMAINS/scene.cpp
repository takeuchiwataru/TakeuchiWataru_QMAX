//=============================================================================
//
// �����_�����O���� [renderer.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "SceneModel.h"
#include "Font.h"
#include "motion.h"

#include "2DPolygon.h"
#include "2DGage.h"
#include "3DPolygon.h"

#include "collision.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CScene	*CScene::m_pTop[MAX_SCENE] = {};					// ���݂̕`����
CScene	*CScene::m_pCur[MAX_SCENE] = {};					// ���݂̕`����
int		CScene::m_nNumAll[MAX_SCENE] = {0, 0, 0, 0, 0, 0, 0, 0};	// ������
int		CScene::m_nDraw = 0;					// ���݂̕`����
int		CScene::m_nCntStart = 0;				// ���݂̕`����
bool	CScene::m_bPause = false;				//�|�[�Y�̗L��
LPDIRECT3DTEXTURE9	CScene::m_pTexture[TEX_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPrioryity)
{
	//�O�ɍ��̃I�u�W�F������
	if (m_pCur[nPrioryity] != NULL) { m_pCur[nPrioryity]->GetpNext() = this; }	//�O������
	else							{ m_pTop[nPrioryity] = this; }				//�����擪
	
	//���ɑO�̃I�u�W�F������
	m_pPrev = m_pCur[nPrioryity];
	m_pNext = NULL;

	//���ɂ��̃I�u�W�F������
	m_pCur[nPrioryity] = this;
	m_nPriority = nPrioryity;
	m_nNumAll[nPrioryity]++;

	//���ɂ����ނ���Ȃ��I�u�W�F�^�C�v��
	SetObjType(OBJTYPE_NONE);
	m_bDeath = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene(void) {}

//=============================================================================
// �摜�̓ǂݍ���
//=============================================================================
LPDIRECT3DTEXTURE9	&CScene::Load(TEXTURE tex)
{
	if (tex < TEX_MAX)
	{//�͈͊m�F
		if (m_pTexture[tex] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//�ǂݍ��� 
			case TEX_Title:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TITLE/title.png", &m_pTexture[tex]);		break;
			case TEX_TUTORIAL:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TUTORIAL/tutorial01.png", &m_pTexture[tex]);		break;
			case TEX_Wall:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/DUNGEON/Wall.jpg", &m_pTexture[tex]);	break; 
			case TEX_Field:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/DUNGEON/lava.jpg", &m_pTexture[tex]);	break;
			case TEX_Fence:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/fence.jpg", &m_pTexture[tex]);		break;
			case TEX_Stone:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/998_stone_.jpg", &m_pTexture[tex]);	break;
			case TEX_Steel:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Steel000.jpg", &m_pTexture[tex]);		break; 
			case TEX_Brock:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/brick.jpg", &m_pTexture[tex]);		break;
			case TEX_DBlock:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/stone_1.jpg", &m_pTexture[tex]);		break;
			case TEX_MBlock:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/stone_0.jpg", &m_pTexture[tex]);		break;
			case TEX_Spear:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Spear000.jpg", &m_pTexture[tex]);		break;
			case TEX_Fire:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/GAME/pipo-btleffect024.png", &m_pTexture[tex]);		break;
			case TEX_Button:    D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/button.jpg", &m_pTexture[tex]);		break;
			case TEX_DropStone: D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/DropStone.jpg", &m_pTexture[tex]);	break;
			case TEX_Shadow: D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/GAME/shadow000.jpg", &m_pTexture[tex]);	break;
				
			case TEX_ResaltLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/RESULT/resultlogo.png", &m_pTexture[tex]);			break;
			case TEX_RankingLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/RANKING/rankinglogo.png", &m_pTexture[tex]);		break;
			case TEX_RankingRank:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/RANKING/ranking_rank.png", &m_pTexture[tex]);		break;
			case TEX_RankingMinute:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/minute.png", &m_pTexture[tex]);			break;
			case TEX_RankingSecond:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/second.png", &m_pTexture[tex]);			break;
			case TEX_PressEnter:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/pressenter.png", &m_pTexture[tex]);			break; 
			case TEX_Number:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/number000.png", &m_pTexture[tex]);			break;
			case TEX_Pause:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/pause.png", &m_pTexture[tex]);			break;
			case TEX_TutorialLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TUTORIAL/tutorial.png", &m_pTexture[tex]);			break;
			}
		}
		return m_pTexture[tex];
	}
	return m_pTexture[0];
}
//=============================================================================
// �摜�̉��
//=============================================================================
void	CScene::UnLoad(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{//�S�摜�j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//==================================================================================================//
//    * �S����֐� *
//==================================================================================================//
void CScene::ReleaseAll(void)
{
	CSceneModel::UnLoadModel();	//Model�̍폜
	CCharacter::UnLoad();		//�L�����p�[�c�̍폜
	CMotion::UnLoad();			//���[�V�����̍폜
	CFont::UnLoad();			//�����̏I��
	UnLoad();

	BreakObject();

	//if (CManager::GetCamera() != NULL) { CManager::GetCamera()->Uninit(); }
	//if (CManager::GetLight() != NULL) { CManager::GetLight()->Uninit(); }

}

//=============================================================================
// �X�V����
//=============================================================================
void  CScene::UpdateAll(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;

	//�������\��
	CManager::GetDLog()->Update();
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "������\n ��F%d,  ��F%d,  ��F%d,  �Q�F%d,  �l�F%d,  �ށF%d,  �Z�F%d,  ���F%d\n"
		, m_nNumAll[0], m_nNumAll[1], m_nNumAll[2], m_nNumAll[3], m_nNumAll[4], m_nNumAll[5], m_nNumAll[6], m_nNumAll[7]);

	for (int nCntScene = (m_bPause ? MAX_SCENE - 1 : m_nCntStart); nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
			while (pScene != NULL)
			{//NULL�ɂȂ�܂ŌJ��Ԃ�
				pNext = pScene->GetpNext();	//Update���ɏ�����\�������邩��
				if (!pScene->m_bDeath) { pScene->Update(); }
				pScene = pNext;
			}
	}
	CCollision::CollisionAll();
}
//=============================================================================
// �`�揈��
//=============================================================================
void  CScene::DrawAll(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//Draw���ɏ����邩������Ȃ�����
			pScene->Draw();
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * �I���֐� *
//==================================================================================================//
void	CScene::UninitAll(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pNext = pScene->GetpNext();	//Draw���ɏ����邩������Ȃ�����
			if (pScene->m_bDeath) { pScene->Release(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * �`�揀���֐� *
//==================================================================================================//
bool CScene::DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice)
{
	if (DrawType == DRAW_TYPE_NO) { return true; }

	if (m_nDraw / 10 != DrawType / 10)
	{//���݂�Z�e�X�g�ƕ`����@���Ⴄ�Ȃ�
		if (DrawType >= CScene::DRAW_TYPE_ZNORMAL)
		{// Z�e�X�g����
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		}
		else
		{// Z�e�X�g�n��
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		}
	}
	if (m_nDraw % 10 != DrawType % 10)
	{//���݂̍������@���Ⴄ�Ȃ�
		switch (DrawType % 10)
		{//�ق�Ƃ�3�s���邱�Ƃ�Y��Ă͂����Ȃ�...
		case CScene::DRAW_TYPE_NORMAL:// �ʏ�
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case CScene::DRAW_TYPE_ADD:// ���u�����f�B���O�����Z�����ɐݒ�
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case CScene::DRAW_TYPE_SUBTRACT:// ���Z
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case CScene::DRAW_TYPE_MULTIPLY:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
			break;
		case CScene::DRAW_TYPE_OVERLAY:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		}
	}
	m_nDraw = DrawType;	//�`����@�̑��

	return false;
}
//==================================================================================================//
//    * �����폜�֐� *
//==================================================================================================//
void CScene::Release()
{
	//�O�̂�Ɏ����̎������
	if (m_pPrev != NULL) { m_pPrev->GetpNext() = m_pNext; }	//�⌾��
	else				 { m_pTop[m_nPriority] = m_pNext; }	//�擪���

	//���̂�Ɏ��������������Ƃ�`����
	if (m_pNext != NULL) { m_pNext->GetpPrev() = m_pPrev; }	//���ƑO���Ȃ���
	else				 { m_pCur[m_nPriority] = m_pPrev; } //�Ō�����

	//�����̍폜
	m_nNumAll[m_nPriority]--;
	delete this;
}
//=============================================================================
//	�S�I�u�W�F�N�g��j��
//=============================================================================
void CScene::BreakObject(void)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		while (m_pTop[nCntScene] != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			m_pTop[nCntScene]->Uninit();
			m_pTop[nCntScene]->Release();
		}
	}
}
//=============================================================================
//	�w�肵���I�u�W�F�N�g��j��
//=============================================================================
void CScene::BreakObject(OBJTYPE obj)
{
	CScene *pNext = NULL;
	CScene *pTarget = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//�D�揇�ʕ����
		pNext = m_pTop[nCntScene];
		while (pNext != NULL)
		{//NULL�ɂȂ�܂ŌJ��Ԃ�
			pTarget = pNext;
			pNext = pNext->GetpNext();

			if (pTarget->GetObjType() == obj)
			{//�I�u�W�F�^�C�v�����Ԃ��Ă���Ȃ�폜
				pTarget->Uninit();
				pTarget->SetObjType(OBJTYPE_NONE);
			}
		}
	}
}
//=============================================================================
// �V�[����Ԃ�
//=============================================================================
CScene *CScene::GetTop(int nPrioryity)
{
	return m_pTop[nPrioryity];
}

