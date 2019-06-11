//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "particle.h"
#include "item.h"
#include "score.h"
#include "life.h"
#include "attackgauge.h"
#include "reload.h"
#include "bullet.h"
#include "enemy.h"
#include "effect.h"
#include "remain.h"
#include "result.h"
#include "rankingscore.h"
#include "fade.h"
#include "pause.h"
#include "pauselogo.h"
#include "pauseselect.h"
#include "input.h"
#include "sound.h"

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;   // �Q�[���̏��
int       g_nCounterGameState;            // �Q�[���̏�ԊǗ��J�E���^�[
int       g_GameCounter;                  // �Q�[���̐i�s�J�E���^�[
bool      g_bPuase;                       // �|�[�Y�����ǂ���
int       g_randSetEnemy;                 // �G�̃Z�b�g����^�C�~���O
int       g_randEnemyType;                // �Z�b�g����G�̎��
int       g_randEnemyPosX;                // �Z�b�g����G�̍��W(X)
int       g_randSetItem;                 // �A�C�e���̃Z�b�g����^�C�~���O
int       g_randItemType;                // �Z�b�g����A�C�e���̎��
int       g_randItem;                // �Z�b�g����A�C�e���̍��W(X)

//=============================================================================
// �Q�[����ʏ���������
//=============================================================================
void InitGame(void)
{
	// �w�i����������
	InitBG01();

	// �X�R�A����������
	InitScore();

	// �v���C���[����������
	InitPlayer();

	// �p�[�e�B�N������������
	InitParticle();

	// �A�C�e������������
	InitItem();

	// �e����������
	InitBullet();

	// �G����������
	InitEnemy();
	
	// �G�t�F�N�g����������
	InitEffect();

	// �U���Q�[�W����������
	InitAttackGauge();

	Player *pPlayer;
	pPlayer = GetPlayer();

	// ���C�t����������
	InitLife();
	SetLife(pPlayer->nLife);

	// �c�@����������
	InitRemain();
	SetRemain(pPlayer->nRemain);

	// �؂ꖡ����������
	InitReload();
	SetReload(pPlayer->nSharp);

	// �|�[�Y����������
	InitPause();

	// �|�[�Y���S����������
	InitPauseLogo();

	// �|�[�Y���ڏ���������
	InitPauseSelect();

	g_GameCounter = 0;
	g_GameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPuase = false;
	g_randSetEnemy = 250;
	g_randSetItem = 500;
}
//=============================================================================
// �Q�[����ʏI������
//=============================================================================
void UninitGame(void)
{
	// �w�i�I������
	UninitBG01();

	// �X�R�A�I������
	UninitScore();

	// �v���C���[�I������
	UninitPlayer();

	// �p�[�e�B�N���I������
	UninitParticle();

	// �A�C�e���I������
	UninitItem();

	// ���C�t�I������
	UninitLife();

	// �U���Q�[�W�I������
	UninitAttackGauge();

	// �c�@�I������
	UninitRemain();

	// �؂ꖡ�I������
	UninitReload();

	// �G�t�F�N�g�I������
	UninitEffect();

	// �e�I������
	UninitBullet();

	// �G�I������
	UninitEnemy();

	// �|�[�Y�I������
	UninitPause();

	// �|�[�Y���S�I������
	UninitPauseLogo();

	// �|�[�Y���ڏI������
	UninitPauseSelect();
}
//=============================================================================
// �Q�[����ʍX�V����
//=============================================================================
void UpdateGame(void)
{
	g_GameCounter++;
	FADE fade;
	fade = GetFade();

	if (GetKeyboardTrigger(DIK_P) && fade == FADE_NONE)
	{// �|�[�YON/OFF
		g_bPuase = g_bPuase ? false : true;
	}

	if (g_bPuase == false)
	{// �|�[�YOFF
		// �G�̔z�u�ݒ�
		GameScene();

		// �w�i�X�V����
		UpdateBG01();

		// �v���C���[�X�V����
		UpdatePlayer();

		// �X�R�A�X�V����
		UpdateScore();

		// �p�[�e�B�N���X�V����
		UpdateParticle();

		// �A�C�e���X�V����
		UpdateItem();

		// ���C�t�X�V����
		UpdateLife();

		// �c�@�X�V����
		UpdateRemain();

		// �؂ꖡ�X�V����
		UpdateReload();

		// �U���Q�[�W�X�V����
		UpdateAttackGauge();

		// �G�t�F�N�g�X�V����
		UpdateEffect();

		// �e�X�V����
		UpdateBullet();

		// �G�X�V����
		UpdateEnemy();

		switch (g_GameState)
		{
		case GAMESTATE_NORMAL:  // �ʏ���
			break;

		case GAMESTATE_END:     //�I�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{// ��莞�Ԃ�������
				g_GameState = GAMESTATE_NONE;
				SetRankingScore(GetScore());
				SetFade(MODE_RESULT);
			}
			break;
		}
	}
	else
	{
		// �|�[�Y�X�V����
		UpdatePause();

		// �|�[�Y���S�X�V����
		UpdatePauseLogo();

		// �|�[�Y���ڍX�V����
		UpdatePauseSelect();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// ENTER�L�[�������ꂽ
			RESTART restart;
			restart = GetRestart();

			switch (restart)
			{
			case RESTART_CONTINUE:  // �Q�[���ĊJ
				break;
			case RESTART_RETRY:     // �Q�[����蒼��
				SetFade(MODE_GAME);
				return; // ����ȏ�Q�[����Update���Ȃ�
				break;
			case RESTART_QUIT:      // �^�C�g���J��
				SetFade(MODE_TITLE);
				return; // ����ȏ�Q�[����Update���Ȃ�
				break;
			}
			g_bPuase = g_bPuase ? false : true; // �|�[�Y�͉���
		}
	}
}
//=============================================================================
// �Q�[����ʕ`�揈��
//=============================================================================
void DrawGame(void)
{
	// �w�i�`�揈��
	DrawBG01();

	// �p�[�e�B�N���`�揈��
	DrawParticle();

	// �A�C�e���`�揈��
	DrawItem();

	// �v���C���[�`�揈��
	DrawPlayer();

	// �e�`�揈��
	DrawBullet();

	// �G�`�揈��
	DrawEnemy();

	// �X�R�A�`�揈��
	DrawScore();
	
	// ���C�t�`�揈��
	DrawLife();

	// �c�@�`�揈��
	DrawRemain();

	// �U���Q�[�W�`�揈��
	DrawAttackGauge();

	// �؂ꖡ�`�揈��
	DrawReload();

	// �G�t�F�N�g�`�揈��
	DrawEffect();

	if (g_bPuase == true)
	{// �|�[�Y���Ȃ�
		// �|�[�Y�`�揈��
		DrawPause();

		// �|�[�Y���S�`�揈��
		DrawPauseLogo();

		// �|�[�Y���ڕ`�揈��
		DrawPauseSelect();
	}
}
//=============================================================================
// �Q�[����ʐݒ菈��
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	g_nCounterGameState = 0;
}
//=============================================================================
// �Q�[����ʎ擾����
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}
//=============================================================================
// �Q�[����ʃV�[���쐬
//=============================================================================
void GameScene(void)
{
	if (g_GameCounter >= 120)
	{// ������x���Ԃ������Ă���
		D3DXVECTOR3 EnemyPos(0.0f, -60.0f, 0.0f);
		if (rand() % g_randSetEnemy <= 2)
		{
			EnemyPos.x = rand() % 200 + 500.0f;
			g_randEnemyType = rand() % 4;
			SetEnemy(EnemyPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_randEnemyType);
		}
		if (rand()% g_randSetItem == 0)
		{
			D3DXVECTOR3 ItemPos(600, -60.0f, 0.0f);
			g_randItemType = rand() % 3;
			SetItem(ItemPos, g_randItemType, D3DXVECTOR3(0.0f, 10.0f, 0.0f));
		}
	}
	if (g_GameCounter % 2500 == 0)
	{
		if (g_randSetEnemy >= 5)
		{
			g_randSetEnemy -= 20;
		}
	}
}