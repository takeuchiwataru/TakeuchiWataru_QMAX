//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "Game.h"
#include "motion.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include "sound.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
bool CEnemy::m_bBGM = false;
bool CEnemy::m_bWarp = false;
bool CEnemy::m_bLook = false;

//==================================================================================================//
//    * �G�l�~�[�̃Z�b�g�֐� *
//==================================================================================================//
void CEnemy::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type)	//�Q�[�W�Z�b�g����
{
	CCharacter::Set(pos, rot, type);
	BindDrawType(CScene::DRAW_TYPE_NORMAL);

}
//=============================================================================
// �G�l�~�[�̏���������
//=============================================================================
HRESULT  CEnemy::Init(void)
{
	m_bBGM = false;
	m_bWarp = false;
	m_bLook = false;
	CCharacter::Init();
	GetfSpeed() *= 0.35f;
	m_fCntState = 0.0f;
	m_fAppear = 0.0f;
	
	m_fWarp = 0.0f;
	SetObjType(CScene::OBJTYPE_ENEMY);
	if (CManager::GetMode() == CManager::MODE_GAME) { GetfCola() = 0.0f; m_bUse = false; }
	else { GetfCola() = 1.0f; m_bUse = true; }
	return S_OK;
}
//=============================================================================
// �G�l�~�[�̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
	D3DXVECTOR3 &m_pos = Getpos();
	float	fMoveX = 0.0f, fMoveZ = 0.0f;	//�ړ������v�Z�p
	bool bMove = false;
	float &fRot = GetfRot();
	m_fCntState += D3DX_PI * 0.0025f;

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (m_bUse)
		{//�o����
			if (GetfCola() < 1.0f) { GetfCola() += 0.05f; }

			if (m_fAppear < 90) 
			{//�o���������Ȃ�
				m_fAppear++;
				if (m_fAppear == 1) { CManager::GetSound()->Play(CSound::LABEL_SE_ENEMY); }
				if (m_fAppear == 90) 
				{//�J������߂�
					CCamera::GetInfo().pChar = &CManager::GetPlayer()->Getpos();
					CCamera::GetInfo().pMove = &CManager::GetPlayer()->Getposold();
				}
			}
			else if (CManager::GetGame()->GetState() == CGame::STATE_NONE)
			{
				D3DXVECTOR3 &pPos = CManager::GetPlayer()->Getpos();
				float fDistance;
				float fRand = (rand() % 10) * D3DX_PI * 0.005f + D3DX_PI - D3DX_PI * 0.025f;
				float fHeart = 0.0f;
				bMove = true;
				fRot = atan2f(pPos.x - m_pos.x, pPos.z - m_pos.z) + D3DX_PI;	//�ړ������v�Z
				m_pos.y += (pPos.y - m_pos.y) * 0.05f;
				GetfSpeed() += 0.000025f;
				if (GetfSpeed() > 3.0f * 0.6f) { GetfSpeed() = 3.0f * 0.6f; }
				fDistance = powf(m_pos.x - pPos.x, 2) + powf(m_pos.z - pPos.z, 2);
				if (fDistance < 150.0f * 150.0f) { fHeart += 5.0f; }
				if (fDistance < 200.0f * 200.0f) { fHeart += 5.0f; }
				if (fDistance < 300.0f * 300.0f) { fHeart += 5.0f; }
				if (fDistance < 400.0f * 400.0f) { fHeart += 3.0f; }

				if (!m_bBGM && fDistance < 400.0f * 400.0f)
				{
					CManager::GetSound()->Play(CSound::LABEL_ESCAPE);
					m_bBGM = true;
				}
				else if (m_bBGM && fDistance > 400.0f * 400.0f)
				{
					CManager::GetSound()->Stop(CSound::LABEL_ESCAPE);
					m_bBGM = false;
				}

				if (m_bWarp)
				{
					if ((m_fWarp > 180.0f && fDistance > 600.0f * 600.0f))
					{ //NORMAL�Ȃ�
						m_pos = pPos + D3DXVECTOR3(sinf(fRot + fRand), 0.0f, cosf(fRot + fRand)) * 500.0f;
						GetfCola() = 0.0f;
						m_fWarp = 0.0f;
					}
					else if (m_fWarp > 600.0f && fDistance > 250.0f * 250.0f)
					{
						m_pos = pPos + D3DXVECTOR3(sinf(fRot + fRand), 0.0f, cosf(fRot + fRand)) * 350.0f;
						GetfCola() = 0.0f;
						m_fWarp = 0.0f;
					}
					else { m_fWarp += 1.0f; }
				}

				if (m_bLook)
				{
					if (fDistance > 200.0f * 200.0f)
					{//HARD�Ȃ�
						GetfCola() -= 0.1f;
						if (GetfCola() < 0.0f) { GetfCola() = 0.0f; }
					}
				}

				CManager::GetPlayer()->GetfHeart() += fHeart;
			}
		}
		else
		{
			D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
			if (m_pos.x + 1000.0f > pos.x && m_pos.x - 1000.0f < pos.x &&
				m_pos.z + 1000.0f > pos.z && m_pos.z - 1000.0f < pos.z)
			{//�͈͓��Ȃ�
				D3DXVECTOR3 &pPos = CManager::GetPlayer()->Getpos();

				CCamera::GetInfo().pChar = &Getpos();
				CCamera::GetInfo().pMove = &Getposold();
				CManager::GetPlayer()->GetfStop() = 90.0f;
				Getrot().y = CManager::GetCamera()->GetRot().y + D3DX_PI;	//�ړ������v�Z
				fRot = Getrot().y;
				m_bUse = true;
			}
		}
	}
	else if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		m_fCntState += D3DX_PI * 0.003f;

	}
	else if (CManager::GetMode() == CManager::MODE_RANKING)
	{// �����L���O�̎�
		m_fCntState += D3DX_PI * 0.0050f;

	}
	CCharacter::Update(bMove);

}
//=============================================================================
// �G�l�~�[�̕`�揈��
//=============================================================================
void	CEnemy::Draw(void)
{
	D3DXVECTOR3 &m_pos = Getpos();

	//�o�����Ă��Ȃ��Ȃ�`�悵�Ȃ�
	if (!m_bUse) { return; }

	if (CManager::GetMode() == CManager::MODE_GAME || CManager::GetMode() == CManager::MODE_RANKING || CManager::GetMode() == CManager::MODE_RESULT)
	{
		m_pos.y += cosf(m_fCntState) * 30.0f;
		m_pos.y += 30.0f;
		CCharacter::Draw();
		m_pos.y -= cosf(m_fCntState) * 30.0f;
		m_pos.y -= 30.0f;
	}
	else if (CManager::GetMode() == CManager::MODE_TITLE)
	{
		m_pos.y -= cosf(m_fCntState) * 35.0f;
		m_pos.y -= 35.0f;
		CCharacter::Draw();
		m_pos.y += cosf(m_fCntState) * 35.0f;
		m_pos.y += 35.0f;
	}
}
