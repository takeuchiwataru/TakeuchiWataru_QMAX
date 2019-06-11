//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : �|���j
//
//=============================================================================
#include "item.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "score.h"
#include "input.h"
#include "player.h"
#include "avatar.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CItem::m_apTexture[ITEMTYPE_MAX] = {};
//CScore * CItem::m_pScore = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItem::CItem() :CScene2D(3)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem::~CItem()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CScene2D::Init(pos);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_ITEM);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, ITEMSIZE, ITEMSIZE);

	// ���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 3;
	m_nType = type;
	m_nTime = 0;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CItem::Uninit(void)
{
	//m_pScore = NULL;

	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CItem::Update(void)
{
	bool bUse = false;

	// �ʒu�̎擾
	m_pos = CScene2D::GetPosition();

	// �X�R�A�̎擾
	CScore * pScore = CGame::GetScore();

	// �W���C�p�b�h�̎擾
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	CGame * pGame = NULL;

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
					CPlayer::PLAYERTYPE nType;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nType = pPlayer->GetType();

					D3DXVECTOR3 Playerpos;
					D3DXVECTOR3 Playerpos2;

					// �v���C���[�̎擾
					Playerpos = pScene->GetPosition();

					// �v���C���[�̎擾
					Playerpos2 = pScene->GetPosition();

					if (m_pos.x >= Playerpos.x - ITEMSIZE && m_pos.x <= Playerpos.x + ITEMSIZE
						&& m_pos.y <= Playerpos.y + ITEMSIZE && m_pos.y >= Playerpos.y - ITEMSIZE)
					{// �v���C���[�ƃA�C�e���̓����蔻��

						bUse = true;

						if (m_nType == CItem::ITEMTYPE_000)
						{// �X�R�A
							pScore->AddScore(500);
						}
						else if (m_nType == CItem::ITEMTYPE_001)
						{// 2way
							pPlayer->SetItemState(CPlayer::ITEMSTATE_ITEM_2WAY);
						}
						else if (m_nType == CItem::ITEMTYPE_002)
						{// �X�s�[�hUP
							//pPlayer->SetItemState(CPlayer::ITEMSTATE_SPPED_UP);
						}
						else if (m_nType == CItem::ITEMTYPE_003)
						{// ���g
							if (nType == pPlayer->PLAYERTYPE_000)
							{// �v���C���[1
								CAvatar::Create(Playerpos, CAvatar::AVATARTYPE_000);
							}
							else if (nType == pPlayer->PLAYERTYPE_001)
							{// �v���C���[2
								pPlayer->SetItemState(CPlayer::ITEMSTATE_AVATAR);

								CAvatar::Create(Playerpos2, CAvatar::AVATARTYPE_001);
							}
						}
						break;
					}
				}
			}  
		}
	}
	m_pos += m_move;
	m_nTime++;

	if (m_nTime <= 5)
	{
		m_move.y = -1 * 1.1f;
	}
	else if (m_nTime >= 30)
	{
		m_move.y = 1 * 1.2f;
	}


	// �ʒu�̐ݒu
	CScene2D::SetPosition(m_pos, ITEMSIZE, ITEMSIZE);

	if (bUse == true)
	{// �A�C�e���̔j��
		Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �A�C�e���̎�ގ擾
//=============================================================================
CItem::ITEMTYPE CItem::GetItemType(void)
{
	return m_nType;
}
//=============================================================================
// �A�C�e���̐���
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CItem *pItem = NULL;

	if (pItem == NULL)
	{
		pItem = new CItem;

		if (pItem != NULL)
		{
			pItem->Init(pos,type);
			pItem->BindTexture(m_apTexture[type]);
		}
	}
	return pItem;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CItem::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_001, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_002, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_003, &m_apTexture[3]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CItem::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < ITEMTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
