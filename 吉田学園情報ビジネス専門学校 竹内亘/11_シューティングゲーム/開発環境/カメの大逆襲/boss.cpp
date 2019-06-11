//=============================================================================
//
// �{�X���� [boss.cpp]
// Author : �|���j
//
//=============================================================================
#include "boss.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "explosion.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "player.h"
#include "life.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CBoss::m_apTexture[BOSSTYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBoss::CBoss()
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBoss::~CBoss()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CBoss::Init(D3DXVECTOR3 pos, BOSSTYPE type)
{
	CScene2D::InitAnim(pos);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BOSS);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, BOSSSIZE, BOSSSIZE);

	// ���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = BOSS_LIFE;
	m_nType = type;
	m_State = BOSSSTATE_NORMAL;
	m_nTime = 0;
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CBoss::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CBoss::Update(void)
{
	bool bUse = false;

	float fDiffAngle[2] = {};		// ����
	float fAngle[2] = {};			// �ړI�̊p�x
	float fMoveAngle = 10.0f;		// ���݂̊p�x 

	switch (m_State)
	{
	case BOSSSTATE_NORMAL:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case BOSSSTATE_DAMEGE:
		m_nCounterState++;

		if (m_nCounterState % 10 == 0)
		{
			m_nCounterState = 0;
		}
		if (m_nCounterState < 5)
		{
			SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_State = BOSSSTATE_NORMAL;
		}
		break;
	}

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
						if (m_pos.x >= Playerpos.x - 80 && m_pos.x <= Playerpos.x + 80
							&& m_pos.y <= Playerpos.y + 80 && m_pos.y >= Playerpos.y - 80)
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

	m_move.y = 1 * 1.2f;

	if (m_pos.y >= SCREEN_HEIGHT / 2.0f - 100)
	{
		m_move.y = 0;
		m_move.x = 1 * m_fMoveX;

		if (m_pos.x >= 850)
		{
			m_fMoveX = -1.0f;
		}
		else if (m_pos.x <= 330)
		{
			m_fMoveX = 1.0f;
		}
	}

	CGame *pGame = NULL;

	CPlayer *pPlayer = NULL;

	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 move2 = GetMove();

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

	if (m_pos.y >= 0)
	{
		if (rand() % 300 == 0)
		{
			if (m_pos.x >= Playerpos[0].x - 500 && m_pos.x <= Playerpos[0].x + 500
				&& m_pos.y <= Playerpos[0].y + 500 && m_pos.y >= Playerpos[0].y - 500)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(move.x, move.y, 0.0f), CBullet::BULLETTYPE_ENEMY000);
			}
			if (m_pos.x >= Playerpos[1].x - 500 && m_pos.x <= Playerpos[1].x + 500
				&& m_pos.y <= Playerpos[1].y + 500 && m_pos.y >= Playerpos[1].y - 500)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(move2.x, move2.y, 0.0f), CBullet::BULLETTYPE_ENEMY000);
			}
		}
	}
	//if (rand() % 100 == 0)
	//{
	//	// �e�̃N���X����
	//	CBullet::Create(m_pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), CBullet::BULLETTYPE_ENEMY000);
	//}


	// �G�̃A�j���[�V����
	m_nCounterAnim++;

	if ((m_nCounterAnim % 30) == 0)
	{// �p�^�[��No.�X�V
		m_nPatternAnim = (m_nPatternAnim + 1) % 2;

		SetPattern2(m_nPatternAnim);
	}

	// �ʒu�̐ݒu
	CScene2D::SetPosition(m_pos, BOSSSIZE, BOSSSIZE);

	if (bUse == true)
	{// �G�̔j��
		Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBoss::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �G�̐���
//=============================================================================
CBoss * CBoss::Create(D3DXVECTOR3 pos, BOSSTYPE type)
{
	CBoss *pBoss = NULL;

	if (pBoss == NULL)
	{
		pBoss = new CBoss;

		if (pBoss != NULL)
		{
			pBoss->Init(pos, type);
			pBoss->BindTexture(m_apTexture[type]);
		}
	}
	return pBoss;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBoss::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BOSS_TEXTURE_000, &m_apTexture[0]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CBoss::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < BOSSTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
//=============================================================================
// �{�X�̃_���[�W����
//=============================================================================
void CBoss::HitBoss(int nDamage)
{
	bool bUse = false;

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �X�R�A�̎擾
	CScore * pScore = CGame::GetScore();

 	m_nLife -= nDamage;

	m_State = BOSSSTATE_DAMEGE;

	if (m_nLife == 0)
	{// ���C�t0
		pScore->AddScore(5000);

		bUse = true;

		// �X�R�A�̕ۑ�
		CManager::GetRankingScore(pScore->GetScore());

		pFade->Set(CManager::MODE_RESULT2, pFade->FADE_OUT);
	}
	else
	{
		m_State = BOSSSTATE_DAMEGE;
	}

	if (bUse == true)
	{// �{�X�����񂾂�
		Uninit();
	}
}
