//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "sound.h"
#include "timer.h"
#include "pause.h"
#include "life.h"
#include "ranking.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_X			(300)				//�G��X���W
#define ENEMY_Y			(100)				//�G��Y���W

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[���̏��
int g_nCounterGameState;					//��ԊǗ��J�E���^�[
bool g_bPause;

//=============================================================================
// �Q�[������������
//=============================================================================
void InitGame(void)
{
	//�w�i����������
	InitBG();

	//�w�i����������
	InitBG2();

	//�v���C���[����������
	InitPlayer();

	//�e�̔��ˏ���������
	InitBullet();

	//�����̏���������
	InitExplosion();

	//�G�̏���������
	InitEnemy();

	//1���
	SetEnemy(D3DXVECTOR3(ENEMY_X, ENEMY_Y, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 200, ENEMY_Y, 0.0f), 1);			
	SetEnemy(D3DXVECTOR3(ENEMY_X + 400, ENEMY_Y, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 600, ENEMY_Y, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 800, ENEMY_Y, 0.0f), 4);

	//2���
	SetEnemy(D3DXVECTOR3(ENEMY_X - 100, ENEMY_Y + 100, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 100, ENEMY_Y + 100, 0.0f), 1);	
	SetEnemy(D3DXVECTOR3(ENEMY_X + 300, ENEMY_Y + 100, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 500, ENEMY_Y + 100, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 700, ENEMY_Y + 100, 0.0f), 4);

	//3���
	SetEnemy(D3DXVECTOR3(ENEMY_X, ENEMY_Y + 200, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 200, ENEMY_Y + 200, 0.0f), 1);	
	SetEnemy(D3DXVECTOR3(ENEMY_X + 400, ENEMY_Y + 200, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 600, ENEMY_Y + 200, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 800, ENEMY_Y + 200, 0.0f), 4);

	//4���
	SetEnemy(D3DXVECTOR3(ENEMY_X - 100, ENEMY_Y + 300, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 100, ENEMY_Y + 300, 0.0f), 1);	
	SetEnemy(D3DXVECTOR3(ENEMY_X + 300, ENEMY_Y + 300, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 500, ENEMY_Y + 300, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(ENEMY_X + 700, ENEMY_Y + 300, 0.0f), 4);

	//�{�X�̏���������
	InitBoss();

	//�X�R�A�̏���������
	InitScore();

	//�^�C�}�[�̏���������
	InitTimer();

	//���C�t�̏���������
	InitLife();

	//�G�t�F�N�g�̏���������
	InitEffect();

	PlaySound(SOUND_LABEL_BGM002);

	g_gameState = GAMESTATE_NORMALL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;

	//�|�[�Y�̏���������
	InitPause();

	g_bPause = false;
}

//=============================================================================
// �Q�[���I������
//=============================================================================
void UninitGame(void)
{
	//�w�i�I������
	UninitBG();

	//�w�i�I������
	UninitBG2();

	//�v���C���[�I������
	UninitPlayer();

	//�e�̔��ˏI������
	UninitBullet();

	//�����̏I������
	UninitExplosion();

	//�G�̏I������
	UninitEnemy();

	//�{�X�̏I������
	UninitBoss();

	//�X�R�A�̏I������
	UninitScore();

	//�^�C�}�[�̏I������
	UninitTimer();

	//���C�t�̏I������
	UninitLife();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�|�[�Y�̏I������
	UninitPause();

}

//=============================================================================
// �Q�[���X�V����
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�YON/OFF
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		//�w�i�X�V����
		UpdateBG();

		//�w�i�X�V����
		UpdateBG2();

		//�e�̔��ˍX�V����
		UpdateBullet();

		//�����̍X�V����
		UpdateExplosion();

		//�v���C���[�X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�{�X�̍X�V����
		UpdateBoss();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�^�C�}�[�̍X�V����
		UpdateTimer();

		//���C�t�̍X�V����
		UpdateLife();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMALL:
		break;

	case GAMESTATE_GAMECLEAR:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			//��ʂ̐ݒ�
			SetFade(MODE_CLEAR);
		}
		break;

	case GAMESTATE_GAMEOVER:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			//��ʂ̐ݒ�
			SetFade(MODE_OVER);
		}
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			StopSound(SOUND_LABEL_BGM002);

			//��ʂ̐ݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//=============================================================================
// �Q�[���`�揈��
//=============================================================================
void DrawGame(void)
{
	//�w�i�`�揈��
	DrawBG();

	//�w�i�`�揈��
	DrawBG2();

	//�v���C���[�`�揈��
	DrawPlayer();

	//�e�̔��˕`�揈��
	DrawBullet();

	//�����̕`�揈��
	DrawExplosion();

	//�G�̕`�揈��
	DrawEnemy();

	//�{�X�̕`�揈��
	DrawBoss();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�^�C�}�[�̕`�揈��
	DrawTimer();

	//���C�t�̕`�揈��
	DrawLife();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	if (g_bPause == true)
	{//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//=============================================================================
// �Q�[����Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
// �Q�[����Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

