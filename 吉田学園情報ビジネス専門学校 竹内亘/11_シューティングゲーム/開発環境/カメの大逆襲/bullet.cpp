//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �|���j
//
//=============================================================================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "score.h"
#include "effect.h"
#include "item.h"
#include "player.h"
#include "life.h"
#include "particle.h"

#include "game.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
//CScore * CBullet::m_pScore = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet():CScene2D(3)
{
	m_bulletType = BULLETTYPE_NONE;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE BulletType)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET);

	CScene2D::Init(pos);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, BULLET_SIZE, BULLET_SIZE);

	// ���̏�����
	m_move = move;
	m_nLife = BULLET_LIFE;
	m_bulletType = BulletType;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	//m_pScore = NULL;

	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
 {
	bool bUse = false;

	// �ʒu
	D3DXVECTOR3 pos;

	D3DXCOLOR col;

	// �ʒu�̎擾
	pos = CScene2D::GetPosition();

	// �T�E���h�̎擾
	CSound * pSound = CManager::GetSound();

	// �X�R�A�̎擾
	CScore * pScore = CGame::GetScore();

	//// �v���C���[�̎擾
	//CPlayer * pPlayer = CGame::GetPlayer();

	//// ���C�t�̎擾
	//CLife *pLife = CGame::GetLife();

	pos += m_move;

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, BULLET_SIZE, BULLET_SIZE);

	m_nLife--;
	if (m_nLife <= 0 || pos.y < 0)
	{
		CExplosion::Create(pos);

		bUse = true;
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene2D *pScene;

			// Scene�̎擾
			pScene = (CScene2D*)CScene::GetScene(nCntPriority,nCntScene);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;

				// �I�u�W�F�N�g�̎擾
				objType = pScene->GetObjType();

				if (m_bulletType == BULLETTYPE_PlAYER000 && objType == CScene::OBJTYPE_ENEMY)
				{// �v���C���[�̒e��������
					D3DXVECTOR3 Enemypos;

					// �G�̎擾
					Enemypos = pScene->GetPosition();

					if (pos.x >= Enemypos.x - HIT_SIZE && pos.x <= Enemypos.x + HIT_SIZE
						&& pos.y <= Enemypos.y + HIT_SIZE && pos.y >= Enemypos.y - HIT_SIZE)
					{// �G�ƃv���C���[�̒e�̓����蔻��
						pScore->AddScore(100);

						//CExplosion::Create(Enemypos);
						for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
						{
							CParticle::Create(Enemypos, D3DXVECTOR3(sinf(rand() % 628 / 100.0f) * (rand() % 5 + 1) , cosf(rand() % 628 / 100.0f) * (rand() % 5+ 1), 0.0f), 30, 30);
						}

						pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

						pScene->Uninit();

						bUse = true;

						break;
					}
				}
				else if (m_bulletType == BULLETTYPE_PlAYER000 && objType == CScene::OBJTYPE_BOSS)
				{// �v���C���[�̒e��������
					D3DXVECTOR3 Bosspos;

					CBoss * pBoss = (CBoss*)pScene;

					// �{�X�̎擾
					Bosspos = pScene->GetPosition();

					if (pos.x >= Bosspos.x - 100 && pos.x <= Bosspos.x + 100
						&& pos.y <= Bosspos.y + 100 && pos.y >= Bosspos.y - 100)
					{// �{�X�ƃv���C���[�̒e�̓����蔻��

						pBoss->HitBoss(1);

						bUse = true;

						break;
					}
				}

				else if (m_bulletType == BULLETTYPE_PlAYER000 && objType == CScene::OBJTYPE_MAEINAPLANT)
				{// �v���C���[�̒e
					D3DXVECTOR3 Marinepos;

					// �C���̎擾
					Marinepos = pScene->GetPosition();

					if (pos.x >= Marinepos.x - HIT_SIZE && pos.x <= Marinepos.x + HIT_SIZE
						&& pos.y <= Marinepos.y + HIT_SIZE && pos.y >= Marinepos.y - HIT_SIZE)
					{// �C���ƃv���C���[�̒e�̓����蔻��

						CExplosion::Create(Marinepos);

						pScene->Uninit();

						if (rand() % 3 == 0)
						{// �X�R�A
							CItem::Create(Marinepos, CItem::ITEMTYPE_000);
						}
						else if (rand() % 5 == 0)
						{// 2way
							CItem::Create(Marinepos, CItem::ITEMTYPE_001);
						}
						else if (rand() % 10 == 0)
						{// 2way
							CItem::Create(Marinepos, CItem::ITEMTYPE_001);
						}

						bUse = true;

						break;
					}
				}

				else if (m_bulletType == BULLETTYPE_ENEMY000 && objType == CScene::OBJTYPE_PLAYER)
				{// �G�̒e��������

					 // �ړ��ʂ̍X�V
					D3DXVECTOR3 PlayerPos;

					int nState;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nState = pPlayer->GetState();

					// �v���C���[�̎擾
					PlayerPos = pScene->GetPosition();

					if (nState == pPlayer->PLAYERSTATE_NORMAL)
					{
						if (pos.x >= PlayerPos.x - HIT_SIZE && pos.x <= PlayerPos.x + HIT_SIZE
							&& pos.y <= PlayerPos.y + HIT_SIZE && pos.y >= PlayerPos.y - HIT_SIZE)
						{// �v���C���[�ƓG�̒e�̓����蔻��

							pPlayer->Hit(1);

							pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

							CExplosion::Create(PlayerPos);

							//	pScene->Uninit();

							bUse = true;

							break;
						}
					}
				}

				else if (m_bulletType == BULLETTYPE_ENEMY000 && objType == CScene::OBJTYPE_PLAYER)
				{// �G�̒e��������

					// �ړ��ʂ̍X�V
					D3DXVECTOR3 PlayerPos;

					int nState;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nState = pPlayer->GetState();

					// �v���C���[�̎擾
					PlayerPos = pScene->GetPosition();

					if (nState == pPlayer->PLAYERSTATE_NORMAL)
					{
						if (pos.x >= PlayerPos.x - HIT_SIZE && pos.x <= PlayerPos.x + HIT_SIZE
							&& pos.y <= PlayerPos.y + HIT_SIZE && pos.y >= PlayerPos.y - HIT_SIZE)
						{// �v���C���[�ƓG�̒e�̓����蔻��

							pPlayer->Hit(1);

							//���e�X�g
							pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

							CExplosion::Create(PlayerPos);

							//	pScene->Uninit();

							bUse = true;

							break;
						}
					}
				}

				else if (m_bulletType == BULLETTYPE_ENEMY000 && objType == CScene::OBJTYPE_PLAYER)
				{// �{�X�̒e��������

					// �ړ��ʂ̍X�V
					D3DXVECTOR3 PlayerPos;

					int nState;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nState = pPlayer->GetState();

					// �v���C���[�̎擾
					PlayerPos = pScene->GetPosition();

					if (nState == pPlayer->PLAYERSTATE_NORMAL)
					{
						if (pos.x >= PlayerPos.x - HIT_SIZE && pos.x <= PlayerPos.x + HIT_SIZE
							&& pos.y <= PlayerPos.y + HIT_SIZE && pos.y >= PlayerPos.y - HIT_SIZE)
						{// �v���C���[�ƓG�̒e�̓����蔻��

							pPlayer->Hit(1);

							//���e�X�g
							pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

							CExplosion::Create(PlayerPos);

							//	pScene->Uninit();

							bUse = true;

							break;
						}
					}
				}

			}
		}
	}

	// �G�t�F�N�g�̐���
	CEffect::Create(pos, D3DXCOLOR(0.0f, 0.6f, 0.5f, 1.0f));

	if (bUse == true)
	{// �e�̔j��
		Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �e�̐���
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE BulletType)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		pBullet = new CBullet;

		if (pBullet != NULL)
		{
			pBullet->Init(pos,move,BulletType);
			pBullet->BindTexture(m_pTexture);
		}
	}
	return pBullet;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BULEET_TEXTURE_000, &m_pTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}