//=============================================================================
//
// �G���� [enemy.cpp]
// Author : �|���j
//
//=============================================================================
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "explosion.h"
#include "input.h"
#include "fade.h"

#include "player.h"
#include "life.h"
#include "sound.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[ENEMYTYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy():CScene2D(4)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	CScene2D::InitAnim(pos);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_ENEMY);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, ENEMYSIZE, ENEMYSIZE);

	// ���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 3;
	m_nType = type;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	//float fAngle;	// �p�x

	float fDiffAngle[2] = {};		// ����
	float fAngle[2] = {};			// �ړI�̊p�x
	float fMoveAngle = 10.0f;	// ���݂̊p�x 

	bool bUse = false;

	// �T�E���h�̎擾
	CSound * pSound = CManager::GetSound();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �ʒu�̎擾
	m_pos = CScene2D::GetPosition();

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
					D3DXVECTOR3 Playerpos;

					int nState;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nState = pPlayer->GetState();

					// �v���C���[�̎擾
					Playerpos = pScene->GetPosition();

					if (nState == pPlayer->PLAYERSTATE_NORMAL)
					{
						if (m_pos.x >= Playerpos.x - ENEMYSIZE && m_pos.x <= Playerpos.x + ENEMYSIZE
							&& m_pos.y <= Playerpos.y + ENEMYSIZE && m_pos.y >= Playerpos.y - ENEMYSIZE)
						{// �v���C���[�ƓG�̓����蔻��

							CExplosion::Create(Playerpos);

							pPlayer->Hit(1);

							//���e�X�g
							pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

							break;
						}
					}
				}
			}
		}
	}

	m_pos += m_move;

	CGame *pGame = NULL;

	CPlayer *pPlayer = NULL;

	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 move2 = GetMove();

	if (m_nType == ENEMYTYPE_TEST)
	{// �`���[�g���A���p�̓G
		m_move.y = 1 * 1.2f;

		D3DXVECTOR3 Playerpos[2];

		Playerpos[0] = pGame->GetPlayer()->GetPos();
		Playerpos[1] = pGame->GetPlayer2()->GetPos();

		fAngle[0] = atan2f(Playerpos[0].x - m_pos.x, Playerpos[0].y - m_pos.y);
		fAngle[1] = atan2f(Playerpos[1].x - m_pos.x, Playerpos[1].y - m_pos.y);

		fDiffAngle[0] = fAngle[0] - fMoveAngle;
		fDiffAngle[1] = fAngle[1] - fMoveAngle;

		if (fDiffAngle[0] > D3DX_PI)
		{
			fDiffAngle[0] -= D3DX_PI * 2.0f;
		}
		else if (fDiffAngle[0] < D3DX_PI)
		{
			fDiffAngle[0] += D3DX_PI * 2.0f;
		}

		fMoveAngle += fDiffAngle[0] * 0.2f;

		if (fDiffAngle[1] > D3DX_PI)
		{
			fDiffAngle[1] -= D3DX_PI * 2.0f;
		}
		else if (fDiffAngle[1] < D3DX_PI)
		{
			fDiffAngle[1] += D3DX_PI * 2.0f;
		}

		fMoveAngle += fDiffAngle[1] * 0.2f;

		if (fMoveAngle > D3DX_PI)
		{
			fMoveAngle -= D3DX_PI * 2.0f;
		}
		else if (fMoveAngle < D3DX_PI)
		{
			fMoveAngle += D3DX_PI * 2.0f;
		}

		move.x += sinf(fAngle[0]) * BALLET_SPEED;
		move.y += cosf(fAngle[0]) * BALLET_SPEED;

		move2.x += sinf(fAngle[1]) * BALLET_SPEED;
		move2.y += cosf(fAngle[1]) * BALLET_SPEED;

		if (rand() % 300 == 0)
		{
			if (m_pos.x >= Playerpos[0].x - 500 && m_pos.x <= Playerpos[0].x + 500
				&& m_pos.y <= Playerpos[0].y + 500 && m_pos.y >= Playerpos[0].y - 500)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(move.x, move.y, 0.0f), CBullet::BULLETTYPE_ENEMY000);
			}
			if (m_pos.x >= Playerpos[1].x - 300 && m_pos.x <= Playerpos[1].x + 300
				&& m_pos.y <= Playerpos[1].y + 300 && m_pos.y >= Playerpos[1].y - 300)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(move2.x, move2.y, 0.0f), CBullet::BULLETTYPE_ENEMY000);
			}
		}
	}

	if (m_pos.y >= 0)
	{
		if (rand() % 300 == 0)
		{
			// �e�̃N���X����
			CBullet::Create(m_pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), CBullet::BULLETTYPE_ENEMY000);
		}
	}

	if (m_nType == ENEMYTYPE_000)
	{// ���i�ړ�
		m_move.y = 1 * 1.2f;
	}
	else if (m_nType == ENEMYTYPE_001)
	{// �΂߈ړ�
		m_move.x = 1 * m_fMoveX;
		m_move.y = 1 * m_fMoveY;

		if (m_pos.x >= 930)
		{
			m_fMoveX = -1.0f;
		}
		else if (m_pos.x <= 260)
		{
			m_fMoveX = 1.0f;
		}
	}
	else if (m_nType == ENEMYTYPE_002)
	{// ���ړ�
		m_move.x = 1 * 2.0f;

		if (m_pos.x > 920)
		{// �E
			bUse = true;
		}
		else if (m_pos.x < 280)
		{// ��
			bUse = true;
		}
	}

	// ��ʂ̔���c
	if (m_pos.y > SCREEN_HEIGHT)
	{// ��
		bUse = true;
	}

	// �G�̃A�j���[�V����
	m_nCounterAnim++;

	if ((m_nCounterAnim % 30) == 0)
	{// �p�^�[��No.�X�V
		m_nPatternAnim = (m_nPatternAnim + 1) % 2;

		SetPattern2(m_nPatternAnim);
	}


	// �ʒu�̐ݒu
	CScene2D::SetPosition(m_pos, ENEMYSIZE, ENEMYSIZE);

	if (bUse == true)
	{// �G�̔j��
		Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �G�̐���
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	CEnemy *pEnemy = NULL;

	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{
			pEnemy->Init(pos, type);
			pEnemy->BindTexture(m_apTexture[type]);
		}
	}
	return pEnemy;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_001, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_002, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_000, &m_apTexture[3]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CEnemy::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < ENEMYTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
////=============================================================================
//// �G�̃_���[�W����
////=============================================================================
//void CEnemy::HitEnemy(int nDamage)
//{
//	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
//
//	// ���_����ݒ�
//	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^
//
//	// �G�̈ʒu
//	CEnemy *pEnemy = NULL;
//
//	if (pEnemy != NULL)
//	{
//		pEnemy->m_nLife -= nDamage;
//
//		if (pEnemy->m_nLife <= 0)
//		{
//			pEnemy->Uninit();
//		}
//		else
//		{
//			pVtxBuff = pEnemy->GetVtxBuff();
//
//			// ���_�o�b�t�@�����b�N
//			pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//
//			// ���_�o�b�t�@���A�����b�N
//			pVtxBuff->Unlock();
//		}
//	}
//}
