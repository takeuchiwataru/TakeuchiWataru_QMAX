//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �|���j
//
//=============================================================================
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "item.h"
#include "sound.h"
#include "life.h"
#include "remain.h"
#include "fade.h"
#include "score.h"
#include "avatar.h"
#include "boss.h"

#include "game.h"
//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[PLAYERTYPE_MAX] = {};
int CPlayer::m_nNumPlayer = 0;
//CPlayer::PLAYERSTATE CPlayer::m_State = PLAYERSTATE_NORMAL;
//CLife * CPlayer::m_pLife = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer():CScene2D(4)
{
	m_rot = 0.0f;
	m_State = PLAYERSTATE_NORMAL;
	m_ItemState = ITEMSTATE_NORMAL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, PLAYERTYPE type)
{
	CScene2D::Init(pos); 

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYER);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, PLAYER_SIZE, PLAYER_SIZE);

	//m_nLife = 3;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nRemain = PLAYER_REMAIN;
	m_nType = type;
	m_State = PLAYERSTATE_INVICIBLE;
	m_ItemState = ITEMSTATE_NORMAL;
	m_nCounterState = 120;
	m_nNumPs = 1;
	m_nNumPlayer = 2;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �ʒu
	D3DXVECTOR3 pos;

	float fCol = 1.0f;

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h�̎擾
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	// �W���C�p�b�h(XInput)�̎擾
	CXInputJoyPad *pXInputJoyPad = CManager::GetXInputJoyPad();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �T�E���h�̎擾
	CSound * pSound = CManager::GetSound();

	// �ʒu�̎擾
	m_pos = CScene2D::GetPosition();

	// �X�R�A�̎擾
	CScore * pScore = CGame::GetScore();

	switch (m_State)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMEGE:
		m_nCounterState--;
		if (m_nCounterState <= 0)
		{
			m_State = PLAYERSTATE_INVICIBLE;
		}
		break;

	case PLAYERSTATE_DEATH:
		break;

	case PLAYERSTATE_INVICIBLE:
		m_nTime++;
		m_nCounterState++;

		if (m_nCounterState % 10 == 0)
		{
			m_nCounterState = 0;
		}
		if (m_nCounterState < 5)
		{
			fCol = 1.0f;
		}
		else
		{
			fCol = 0.0f;
		}
		if (m_nTime % 120 == 0)
		{
			m_nTime = 0;
		}
		if (m_nTime == 100)
		{
			m_State = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_PS:

		m_nTime++;
		m_rot -= 0.09f;

		if (m_rot > D3DX_PI)
		{// ��]
			m_rot -= D3DX_PI * 2.0f;
		}
		else if (m_rot < -D3DX_PI)
		{
			m_rot += D3DX_PI * 2.0f;
		}

		if (m_nTime % 720 == 0)
		{// ���G
			m_nTime = 0;
		}
		if (m_nTime == 600)
		{// ���G�I��
			m_State = PLAYERSTATE_NORMAL;
			m_rot = 0.0f;
		}

		for (int nCntParticle = 0; nCntParticle < 5; nCntParticle++)
		{// �p�[�e�B�N���̐���
			CParticle::Create(m_pos, D3DXVECTOR3(sinf(rand() % 628 / 100.0f) * (rand() % 7 + 1), cosf(rand() % 628 / 100.0f) * (rand() % 7 + 1), 0.0f), 20, 20);
		}
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

					if (objType == CScene::OBJTYPE_ENEMY)
					{// �G��������
						D3DXVECTOR3 Enemypos;

						// �v���C���[�̎擾
						Enemypos = pScene->GetPosition();

						if (m_pos.x >= Enemypos.x - PLAYER_SIZE && m_pos.x <= Enemypos.x + PLAYER_SIZE
							&& m_pos.y <= Enemypos.y + PLAYER_SIZE && m_pos.y >= Enemypos.y - PLAYER_SIZE)
						{// �v���C���[�ƓG�̓����蔻��

							pScore->AddScore(100);

							for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
							{
								CParticle::Create(Enemypos, D3DXVECTOR3(sinf(rand() % 628 / 100.0f) * (rand() % 5 + 1), cosf(rand() % 628 / 100.0f) * (rand() % 5 + 1), 0.0f), 30, 30);
							}

							pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

							pScene->Uninit();

							break;
						}
					}
					else if (objType == CScene::OBJTYPE_BOSS)
					{// �{�X��������
						D3DXVECTOR3 Bosspos;

						CBoss * pBoss = (CBoss*)pScene;

						// �{�X�̎擾
						Bosspos = pScene->GetPosition();

						if (m_pos.x >= Bosspos.x - PLAYER_SIZE && m_pos.x <= Bosspos.x + PLAYER_SIZE
							&& m_pos.y <= Bosspos.y + PLAYER_SIZE && m_pos.y >= Bosspos.y - PLAYER_SIZE)
						{// �v���C���[�ƓG�̓����蔻��

							pBoss->HitBoss(1);

							break;
						}
					}
				}
			}
		}
		break;
	}

	 //XInput����
	if (m_nType == PLAYERTYPE_000)
	{// �v���C���[1

		// ���X�e�B�b�N
		if (pXInputJoyPad->GetStick(0, 0) == true)
		{
			m_pos.x += sinf(pXInputJoyPad->GetLeftAxiz(0)) * PLAYER_MOVESPEED;
			m_pos.y -= cosf(pXInputJoyPad->GetLeftAxiz(0)) * PLAYER_MOVESPEED;

			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}

		// �\���L�[(XInput)
		if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 0) == true || pInputKeyboard->GetPress(DIK_A) == true)
		{// ������������
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true || pInputKeyboard->GetPress(DIK_W) == true)
			{// �����Ɂ�����������	// ����ړ�
				m_pos.x += sinf(D3DX_PI * -0.75f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * -0.75f) * PLAYER_MOVESPEED;
			}
			else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true || pInputKeyboard->GetPress(DIK_S) == true)
			{// �����Ɂ�����������	// �����ړ�
				m_pos.x += sinf(D3DX_PI * -0.25f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * -0.25f) * PLAYER_MOVESPEED;
			}
			else
			{// ���ړ�
				m_pos.x -= PLAYER_MOVESPEED;
			}
			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 0) == true || pInputKeyboard->GetPress(DIK_D) == true)
		{// ������������
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true || pInputKeyboard->GetPress(DIK_W) == true)
			{// �����Ɂ�����������	// �E��ړ�
				m_pos.x += sinf(D3DX_PI * 0.75f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * 0.75f) * PLAYER_MOVESPEED;
			}
			else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true || pInputKeyboard->GetPress(DIK_S) == true)
			{// �����Ɂ�����������	// �E���ړ�
				m_pos.x += sinf(D3DX_PI * 0.25f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * 0.25f) * PLAYER_MOVESPEED;
			}
			else
			{// �E�ړ�
				m_pos.x += PLAYER_MOVESPEED;
			}
			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true || pInputKeyboard->GetPress(DIK_W) == true)
		{// ������������	// ��ړ�
			m_pos.y -= PLAYER_MOVESPEED;

			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true || pInputKeyboard->GetPress(DIK_S) == true)
		{// ������������	// ���ړ�
			m_pos.y += PLAYER_MOVESPEED;

			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}

		if (pXInputJoyPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{// �e�̔���
			switch (m_ItemState)
			{
			case ITEMSTATE_NORMAL:
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				break;

			case ITEMSTATE_ITEM_2WAY:
				CBullet::Create(D3DXVECTOR3(m_pos.x - PLAYER_BULLET_INTERVAL, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_BULLET_INTERVAL, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				break;

			}
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BABURU);
		}
		if (m_nNumPs == 1)
		{// 1��̂�
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 0) == true || pInputKeyboard->GetPress(DIK_F) == true)
			{// �p�[�t�F�N�g�V�F��
				m_State = PLAYERSTATE_PS;
				m_nNumPs--;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PS);
			}
		}
	}
	else if (m_nType == PLAYERTYPE_001)
	{// �v���C���[2

		// ���X�e�B�b�N
		if (pXInputJoyPad->GetStick(0, 1) == true)
		{
			m_pos.x += sinf(pXInputJoyPad->GetLeftAxiz(1)) * PLAYER_MOVESPEED;
			m_pos.y -= cosf(pXInputJoyPad->GetLeftAxiz(1)) * PLAYER_MOVESPEED;

			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		// �\���L�[
		if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 1) == true || pInputKeyboard->GetPress(DIK_LEFT) == true)
		{// ������������
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 1) == true || pInputKeyboard->GetPress(DIK_UP) == true)
			{// �����Ɂ�����������	// ����ړ�
				m_pos.x += sinf(D3DX_PI * -0.75f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * -0.75f) * PLAYER_MOVESPEED;
			}
			else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 1) == true || pInputKeyboard->GetPress(DIK_DOWN) == true)
			{// �����Ɂ�����������	// �����ړ�
				m_pos.x += sinf(D3DX_PI * -0.25f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * -0.25f) * PLAYER_MOVESPEED;
			}
			else
			{// ���ړ�
				m_pos.x -= PLAYER_MOVESPEED;
			}
			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 1) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{// ������������
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 1) == true || pInputKeyboard->GetPress(DIK_UP) == true)
			{// �����Ɂ�����������	// �E��ړ�
				m_pos.x += sinf(D3DX_PI * 0.75f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * 0.75f) * PLAYER_MOVESPEED;
			}
			else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 1) == true || pInputKeyboard->GetPress(DIK_DOWN) == true)
			{// �����Ɂ�����������	// �E���ړ�
				m_pos.x += sinf(D3DX_PI * 0.25f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * 0.25f) * PLAYER_MOVESPEED;
			}
			else
			{// �E�ړ�
				m_pos.x += PLAYER_MOVESPEED;
			}
			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 1) == true || pInputKeyboard->GetPress(DIK_UP) == true)
		{// ������������	// ��ړ�
			m_pos.y -= PLAYER_MOVESPEED;

			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 1) == true || pInputKeyboard->GetPress(DIK_DOWN) == true)
		{// ������������	// ���ړ�
			m_pos.y += PLAYER_MOVESPEED;

			//�G�t�F�N�g�̐���
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		if (pXInputJoyPad->GetTrigger(XINPUT_GAMEPAD_A, 1) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{// �e�̔���
			switch (m_ItemState)
			{
			case ITEMSTATE_NORMAL:
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				break;

			case ITEMSTATE_ITEM_2WAY:
				CBullet::Create(D3DXVECTOR3(m_pos.x - PLAYER_BULLET_INTERVAL, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_BULLET_INTERVAL, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				break;
			}
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BABURU);
		}
		if (m_nNumPs == 1)
		{// 1��̂�
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 1) == true || pInputKeyboard->GetPress(DIK_M) == true)
			{// �p�[�t�F�N�g�V�F��
				m_State = PLAYERSTATE_PS;
				m_nNumPs--;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PS);
			}
		}
	}

	SetColor(D3DXCOLOR(1.0f,1.0f,1.0f, fCol));

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
	CScene2D::SetPosition(m_pos, PLAYER_SIZE, PLAYER_SIZE);

	// ���_�o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CScene2D::GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - m_rot) * PLAYER_SIZE, m_pos.y + cosf(-D3DX_PI * 0.75f - m_rot) * PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - m_rot) * PLAYER_SIZE, m_pos.y + cosf(D3DX_PI * 0.75f - m_rot) * PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - m_rot) * PLAYER_SIZE, m_pos.y + cosf(-D3DX_PI * 0.25f - m_rot) * PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - m_rot) * PLAYER_SIZE, m_pos.y + cosf(D3DX_PI * 0.25f - m_rot) * PLAYER_SIZE, 0.0f);

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
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
//=============================================================================
// �_���[�W����
//=============================================================================
void CPlayer::Hit(int nDamage)
{
	bool bDeath = false;	// ���񂾂��ǂ���

	// �ۑ�
	int nNumPlayer = m_nNumPlayer;

	// 1P�c�@�̎擾
	CRemain * pRemain = CGame::GetRemain();

	// 2P�c�@�̎擾
	CRemain * pRemain2 = CGame::GetRemain2();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �X�R�A�̎擾
	CScore * pScore = CGame::GetScore();

	m_nRemain -= nDamage;

	if (m_nType == PLAYERTYPE_000)
	{// �v���C���[1
		if (m_nRemain == 0)
		{// �c�@0
			pRemain->AddRemain(-1);

			m_nNumPlayer--;

			bDeath = true;
		}
		else if (m_nRemain >= 1)
		{// �c�@1�ȏ�
			m_State = PLAYERSTATE_INVICIBLE;
			m_ItemState = ITEMSTATE_NORMAL;
			pRemain->AddRemain(-1);

			m_nCounterState = 120;
		}
	}
	else if (m_nType == PLAYERTYPE_001)
	{// �v���C���[2
		if (m_nRemain == 0)
		{// �c�@0
			pRemain2->AddRemain(-1);

			m_nNumPlayer--;

			bDeath = true;
		}
		else if (m_nRemain >= 1)
		{// �c�@1�ȏ�
			m_State = PLAYERSTATE_INVICIBLE;
			m_ItemState = ITEMSTATE_NORMAL;

			pRemain2->AddRemain(-1);

			m_nCounterState = 120;
		}
	}

	if (m_nNumPlayer == 0)
	{// �v���C���[�̐���0�ɂȂ�����

		//�X�R�A�̕ۑ�
		CManager::GetRankingScore(pScore->GetScore());

		pFade->Set(CManager::MODE_RESULT, pFade->FADE_OUT);
	}

	if (bDeath == true)
	{// �v���C���[�����񂾂�
		Uninit();
	}
}
//=============================================================================
// ��Ԃ̎擾
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetState(void)
{
	return m_State;
}
//=============================================================================
// ��ނ̎擾
//=============================================================================
CPlayer::PLAYERTYPE CPlayer::GetType(void)
{
	return m_nType;
}

//=============================================================================
// ��Ԃ̐ݒu
//=============================================================================
void CPlayer::SetItemState(ITEMSTATE itemstate)
{
	m_ItemState = itemstate;
}
//=============================================================================
// �c�@�̎擾
//=============================================================================
int CPlayer::GetRemain(void)
{
	return m_nRemain;
}
//=============================================================================
// �v���C���[�̎擾
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
////=============================================================================
//// �v���C���[�̃^�C�v�擾
////=============================================================================
//CPlayer::PLAYERTYPE CPlayer::GetPlayerType(void)
//{
//	return m_nType;
//}
//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, PLAYERTYPE type)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			pPlayer->Init(pos,type);
			pPlayer->BindTexture(m_apTexture[type]);
		}
	}
	return pPlayer;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
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
void CPlayer::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < PLAYERTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
