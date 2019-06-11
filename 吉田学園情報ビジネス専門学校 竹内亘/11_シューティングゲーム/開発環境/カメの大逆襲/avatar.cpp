//=============================================================================
//
// �A�o�^�[���� [avatar.cpp]
// Author : �|���j
//
//=============================================================================
#include "avatar.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "item.h"
#include "sound.h"
#include "life.h"
#include "remain.h"
#include "fade.h"
#include "player.h"

#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CAvatar::m_apTexture[AVATARTYPE_MAX] = {};
//CAvatar::PLAYERSTATE CAvatar::m_State = PLAYERSTATE_NORMAL;
//CLife * CAvatar::m_pLife = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAvatar::CAvatar() :CScene2D(2)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CAvatar::~CAvatar()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CAvatar::Init(D3DXVECTOR3 pos, AVATARTYPE type)
{
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_AVATAR);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, AVATAR_SIZE, AVATAR_SIZE);

	m_nType = type;
	m_nSpeed = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	////m_nLife = 3;
	//m_nRemain = PLAYER_REMAIN;
	//m_State = PLAYERSTATE_INVICIBLE;
	//m_ItemState = ITEMSTATE_NORMAL;
	//m_nCounterState = 120;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CAvatar::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CAvatar::Update(void)
{
	float fDiffAngle = 0;		// ����
	float fAngle = 0;			// �ړI�̊p�x
	float fMoveAngle = 10.0f;	// ���݂̊p�x 

	float fDiffAngle2 = 0;		// ����
	float fAngle2 = 0;			// �ړI�̊p�x
	float fMoveAngle2 = 10.0f;	// ���݂̊p�x 

	D3DXVECTOR3 move = CScene2D::GetMove();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h�̎擾
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	CGame * pGame = NULL;

	// �ʒu�̎擾
	m_pos = CScene2D::GetPosition();

	//for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	//	{
	//		CScene2D *pScene;

	//		// Scene�̎擾
	//		pScene = (CScene2D*)CScene::GetScene(nCntPriority, nCntScene);

	//		if (pScene != NULL)
	//		{
	//			CScene::OBJTYPE objType;

	//			// �I�u�W�F�N�g�̎擾
	//			objType = pScene->GetObjType();

	//			if (objType == CScene::OBJTYPE_PLAYER)
	//			{// �v���C���[��������
	//				CPlayer::PLAYERTYPE nType;

	//				CPlayer * pPlayer = (CPlayer*)pScene;
	//				nType = pPlayer->GetType();

	//				if (nType == pPlayer->PLAYERTYPE_000)
	//				{// �v���C���[1
	//					D3DXVECTOR3 Playerpos;

	//					// �v���C���[�̎擾
	//					Playerpos = pGame->GetPlayer()->GetPos();

	//					fAngle = atan2f(Playerpos.x - m_pos.x, Playerpos.y - m_pos.y);

	//					fDiffAngle = fAngle - fMoveAngle;

	//					if (fDiffAngle > D3DX_PI)
	//					{
	//						fDiffAngle -= D3DX_PI * 2.0f;
	//					}
	//					else if (fDiffAngle < D3DX_PI)
	//					{
	//						fDiffAngle += D3DX_PI * 2.0f;
	//					}

	//					fMoveAngle += fDiffAngle * 0.2f;

	//					if (fMoveAngle > D3DX_PI)
	//					{
	//						fMoveAngle -= D3DX_PI * 2.0f;
	//					}
	//					else if (fMoveAngle < D3DX_PI)
	//					{
	//						fMoveAngle += D3DX_PI * 2.0f;
	//					}
	//					move.x += sinf(fAngle) * 3;
	//					move.y += cosf(fAngle) * 3;
	//				}
	//				else if (nType == pPlayer->PLAYERTYPE_001)
	//				{// �v���C���[2
	//					D3DXVECTOR3 Playerpos2;

	//					// �v���C���[�̎擾
	//					Playerpos2 = pGame->GetPlayer2()->GetPos();

	//					fAngle = atan2f(Playerpos2.x - m_pos.x, Playerpos2.y - m_pos.y);

	//					fDiffAngle = fAngle - fMoveAngle;

	//					if (fDiffAngle > D3DX_PI)
	//					{
	//						fDiffAngle -= D3DX_PI * 2.0f;
	//					}
	//					else if (fDiffAngle < D3DX_PI)
	//					{
	//						fDiffAngle += D3DX_PI * 2.0f;
	//					}

	//					fMoveAngle += fDiffAngle * 0.2f;

	//					if (fMoveAngle > D3DX_PI)
	//					{
	//						fMoveAngle -= D3DX_PI * 2.0f;
	//					}
	//					else if (fMoveAngle < D3DX_PI)
	//					{
	//						fMoveAngle += D3DX_PI * 2.0f;
	//					}
	//					move.x += sinf(fAngle) * 3;
	//					move.y += cosf(fAngle) * 3;
	//				}
	//			}
	//		}
	//	}
	//}

	D3DXVECTOR3 Playerpos;
	D3DXVECTOR3 Playerpos2;

	Playerpos = pGame->GetPlayer()->GetPos();
	Playerpos2 = pGame->GetPlayer2()->GetPos();

	fAngle = atan2f(Playerpos.x - m_pos.x, Playerpos.y - m_pos.y);
	fAngle = atan2f(Playerpos2.x - m_pos.x, Playerpos2.y - m_pos.y);

	fDiffAngle = fAngle - fMoveAngle;

	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	else if (fDiffAngle < D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 0.2f;

	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	else if (fMoveAngle < D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}
	move.x += sinf(fAngle) * 3;
	move.y += cosf(fAngle) * 3;


	fAngle2 = atan2f(Playerpos2.x - m_pos.x, Playerpos2.y - m_pos.y);
	fDiffAngle2 = fAngle2 - fMoveAngle2;

	if (fDiffAngle2 > D3DX_PI)
	{
		fDiffAngle2 -= D3DX_PI * 2.0f;
	}
	else if (fDiffAngle2 < D3DX_PI)
	{
		fDiffAngle2 += D3DX_PI * 2.0f;
	}

	fMoveAngle2 += fDiffAngle2 * 0.2f;

	if (fMoveAngle2 > D3DX_PI)
	{
		fMoveAngle2 -= D3DX_PI * 2.0f;
	}
	else if (fMoveAngle2 < D3DX_PI)
	{
		fMoveAngle2 += D3DX_PI * 2.0f;
	}

	move.x += sinf(fAngle2) * 3;
	move.y += cosf(fAngle2) * 3;

	m_pos += move;

	// ��ʂ̔��艡
	if (m_pos.x > 920)
	{// �E
		m_pos.x = 920;
	}
	else if (m_pos.x < 280)
	{// ��
		m_pos.x = 280;
	}

	// ��ʂ̔���c
	if (m_pos.y > SCREEN_HEIGHT)
	{// ��
		m_pos.y = SCREEN_HEIGHT;
	}
	else if (m_pos.y < 0)
	{// ��
		m_pos.y = 0;
	}

	// �ʒu�̐ݒu
	CScene2D::SetPosition(m_pos, AVATAR_SIZE, AVATAR_SIZE);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CAvatar::Draw(void)
{
	CManager manager;	//�C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	pVtxBuff = CScene2D::GetVtxBuff();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_apTexture[m_nType]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
////=============================================================================
//// �_���[�W����
////=============================================================================
//void CAvatar::Hit(int nDamage)
//{
//	bool bDeath = false;	// ���񂾂��ǂ���
//
//							// 1P�c�@�̎擾
//	CRemain * pRemain = CGame::GetRemain();
//
//	// 2P�c�@�̎擾
//	CRemain * pRemain2 = CGame::GetRemain2();
//
//	// �t�F�[�h�̎擾
//	CFade *pFade = CManager::GetFade();
//
//	m_nRemain -= nDamage;
//
//	if (m_nType == PLAYERTYPE_000)
//	{// �v���C���[1
//		if (m_nRemain == 0)
//		{// �c�@0
//			pRemain->AddRemain(-1);
//
//			bDeath = true;
//		}
//		else if (m_nRemain >= 1)
//		{// �c�@1�ȏ�
//			m_State = PLAYERSTATE_INVICIBLE;
//			m_ItemState = ITEMSTATE_NORMAL;
//			pRemain->AddRemain(-1);
//
//			m_nCounterState = 120;
//		}
//	}
//	else if (m_nType == PLAYERTYPE_001)
//	{// �v���C���[2
//		if (m_nRemain == 0)
//		{// �c�@0
//			pRemain2->AddRemain(-1);
//
//			bDeath = true;
//		}
//		else if (m_nRemain >= 1)
//		{// �c�@1�ȏ�
//			m_State = PLAYERSTATE_INVICIBLE;
//			m_ItemState = ITEMSTATE_NORMAL;
//
//			pRemain2->AddRemain(-1);
//
//			m_nCounterState = 120;
//		}
//	}
//
//	if (m_nType == PLAYERTYPE_000 && m_nType == PLAYERTYPE_001)
//	{
//		if (bDeath == true)
//		{
//			pFade->Set(CManager::MODE_RESULT, pFade->FADE_OUT);
//		}
//	}
//
//	if (bDeath == true)
//	{// �v���C���[�����񂾂�
//		Uninit();
//	}
//}
////=============================================================================
//// ��Ԃ̎擾
////=============================================================================
//CAvatar::PLAYERSTATE CAvatar::GetState(void)
//{
//	return m_State;
//}
////=============================================================================
//// ��Ԃ̐ݒu
////=============================================================================
//void CAvatar::SetItemState(ITEMSTATE itemstate)
//{
//	m_ItemState = itemstate;
//}
////=============================================================================
//// �c�@�̎擾
////=============================================================================
//int CAvatar::GetRemain(void)
//{
//	return m_nRemain;
//}
////=============================================================================
//// �v���C���[�̃^�C�v�擾
////=============================================================================
//CAvatar::AVATARTYPE CAvatar::GetPlayerType(void)
//{
//	return m_nType;
//}
//=============================================================================
// �v���C���[�̐���
//=============================================================================
CAvatar * CAvatar::Create(D3DXVECTOR3 pos, AVATARTYPE type)
{
	CAvatar *pAvater = NULL;

	if (pAvater == NULL)
	{
		pAvater = new CAvatar;

		if (pAvater != NULL)
		{
			pAvater->Init(pos, type);
			pAvater->BindTexture(m_apTexture[type]);
		}
	}
	return pAvater;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CAvatar::Load(void)
{
	CManager manager;	// �C���X�^���X

						// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE_000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE_001, &m_apTexture[1]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CAvatar::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < AVATARTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
