//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "player2.h"
#include "model.h"
#include "enemy2.h"
#include "shadow.h"
#include "billboard.h"
#include "bullet.h"
#include "meshField.h"
#include "meshWall.h"
#include "explosion.h"
#include "effect.h"
#include "frame.h"
#include "score.h"
#include "timer.h"
#include "pause.h"
#include "pauselogo.h"
#include "pauseselect.h"
#include "particle.h"
#include "item2.h"
#include "life.h"
#include "sound.h"
//#include "polygon.h"
//#include "player.h"
//#include "enemy.h"
//#include "wall.h"
//#include "item.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[���̏��
int g_nCounterGameState;					//��ԊǗ��J�E���^�[
bool g_bPause;								//�|�[�Y�����ǂ���

//=============================================================================
// �Q�[������������
//=============================================================================
void InitGame(void)
{
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//// �|���S���̏���������
	//InitPolygon();

	// ���b�V���t�B�[���h�̏���������
	InitmeshField();

	//// ���b�V���t�B�[���h2�̏���������
	//InitMeshField2();

	// �e�̏���������
	InitShadow();

	//// �v���C���[�̏���������
	//InitPlayer();

	// �v���C���[(�e�q�֌W�Ȃ�)�̏���������
	InitPlayer2();

	// ���f���̏���������
	InitModel();
	SetModel(D3DXVECTOR3(715.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH);
	SetModel(D3DXVECTOR3(715.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH);
	SetModel(D3DXVECTOR3(-15.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),MODELTYPE_BENCH2);
	SetModel(D3DXVECTOR3(-15.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH2);

	SetModel(D3DXVECTOR3(400.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA);
	SetModel(D3DXVECTOR3(540.0f, 0.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA2);
	SetModel(D3DXVECTOR3(100.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA2);

	SetModel(D3DXVECTOR3(100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),MODELTYPE_BURANKO);
	SetModel(D3DXVECTOR3(170.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BURANKO);
	SetModel(D3DXVECTOR3(500.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_SLIDE);
	SetModel(D3DXVECTOR3(300.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_JG);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_SEESAW);

	//// �G�̏���������
	//InitEnemy();
	//SetEnemy(D3DXVECTOR3(0.0f,0.0f,150.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f),ENEMYTYPE_NORMALL);
	//SetEnemy(D3DXVECTOR3(100.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_NORMALL);
	//SetEnemy(D3DXVECTOR3(200.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_NORMALL);

	// �G(�e�q�֌W�Ȃ�)�̏���������
	InitEnemy2();
	SetEnemy2(D3DXVECTOR3(50.0f, 0.0f, 150.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(250.0f, 0.0f, 150.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(450.0f, 0.0f, 150.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(50.0f, 0.0f, 400.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(300.0f, 0.0f, 400.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);
	SetEnemy2(D3DXVECTOR3(600.0f, 0.0f, 400.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), ENEMYTYPE2_NORMAL);

	//// �ǂ̏���������
	//InitWall();
	//SetWall(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	//SetWall(D3DXVECTOR3(-50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	// ���b�V���E�H�[���̏���������
	InitMeshWall(0, D3DXVECTOR3(-25.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	InitMeshWall(1, D3DXVECTOR3(-25.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	InitMeshWall(2, D3DXVECTOR3(725.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	InitMeshWall(3, D3DXVECTOR3(725.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	// �r���{�[�h�̏���������
	InitBillboard();
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, 10.0f));
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(100.0f, 0.0f, 650.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, 500.0f));
	SetBillboard(D3DXVECTOR3(250.0f, 0.0f, 250.0f));
	SetBillboard(D3DXVECTOR3(300.0f, 0.0f, 650.0f));
	SetBillboard(D3DXVECTOR3(350.0f, 0.0f, 500.0f));
	SetBillboard(D3DXVECTOR3(400.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(450.0f, 0.0f, 560.0f));
	SetBillboard(D3DXVECTOR3(500.0f, 0.0f, 100.0f));
	SetBillboard(D3DXVECTOR3(500.0f, 0.0f, 10.0f));
	SetBillboard(D3DXVECTOR3(550.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(600.0f, 0.0f, 600.0f));
	SetBillboard(D3DXVECTOR3(650.0f, 0.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(700.0f, 0.0f, 340.0f));

	// �e�̏���������
	InitBullet();

	// �����̏���������
	InitExplosion();

	// �G�t�F�N�g�̏���������
	InitEffect();

	// �t���[���̏���������
	InitFrame();

	// �X�R�A�̏���������
	InitScore();

	// �^�C�}�[�̏���������
	InitTimer();

	// �|�[�Y�̏���������
	InitPause();

	// �|�[�Y���S����������
	InitPauseLogo();

	// �|�[�Y���ڏ���������
	InitPauseSelect();

	// �p�[�e�B�N���̏���������
	InitParticle();

	//// �A�C�e���̏���������
	//InitItem();
	////SetItem(D3DXVECTOR3(80.0f, 0.0f, 30.0f),20,20, ITEMTYPE_COIN);

	// �A�C�e��(���f��ver)�̏���������
	InitItem2();
	SetItem2(D3DXVECTOR3(100.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_GOMI);
	SetItem2(D3DXVECTOR3(580.0f, 0.0f, 430.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_GOMI);

	SetItem2(D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_BOOK);
	SetItem2(D3DXVECTOR3(150.0f, 0.0f, 430.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_BOOK);
	SetItem2(D3DXVECTOR3(610.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_BOOK);

	SetItem2(D3DXVECTOR3(200.0f, 0.0f, 190.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(300.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(700.0f, 0.0f, 45.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(500.0f, 0.0f, 670.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(320.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);
	SetItem2(D3DXVECTOR3(60.0f, 0.0f, 680.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_PB);

	SetItem2(D3DXVECTOR3(100.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);
	SetItem2(D3DXVECTOR3(620.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);
	SetItem2(D3DXVECTOR3(500.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);
	SetItem2(D3DXVECTOR3(350.0f, 0.0f, 490.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);
	SetItem2(D3DXVECTOR3(20.0f, 0.0f, 30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE2_KAN);

	// ���C�t�̏���������
	InitLife();

	//Player *pPlayer;
	//pPlayer = GetPlayer();
	//SetLife(pPlayer->nLife);

	// �v���C���[�̎擾
	Player2 *pPlayer;
	pPlayer = GetPlayer2();
	SetLife(pPlayer->nLife);

	g_gameState = GAMESTATE_NORMALL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	g_bPause = false;
}

//=============================================================================
// �Q�[���I������
//=============================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//// �|���S���̏I������
	//UninitPolygon();

	// ���b�V���t�B�[���h�̏I������
	UninitmeshField();

	//// ���b�V���t�B�[���h2�̏I������
	//UninitMeshField2();

	//// �v���C���[�̏I������
	//UninitPlayer();

	// �v���C���[(�e�q�֌W�Ȃ�)�̏I������
	UninitPlayer2();

	// ���f���̏I������
	UninitModel();

	//// �G�̏I������
	//UninitEnemy();

	// �G(�e�q�֌W�Ȃ�)�̏I������
	UninitEnemy2();

	// �e�̏I������
	UninitShadow();

	//// �ǂ̏I������
	//UninitWall();

	// ���b�V���E�H�[���̏I������
	UninitMeshWall();

	// �r���{�[�h�̏I������
	UninitBillboard();

	// �e�̏I������
	UninitBullet();

	// �����̏I������
	UninitExplosion();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �t���[���̏I������
	UninitFrame();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �X�R�A�̏I������
	UninitScore();

	// �|�[�Y���S�I������
	UninitPauseLogo();

	// �|�[�Y���ڏI������
	UninitPauseSelect();

	// �����̏I������
	UninitExplosion();
	
	// �p�[�e�B�N���̏I������
	UninitParticle();

	//// �A�C�e���̏I������
	//UninitItem();

	// �A�C�e��(���f��ver)�̏I������
	UninitItem2();

	// ���C�t�̏I������
	UninitLife();
}

//=============================================================================
// �Q�[���X�V����
//=============================================================================
void UpdateGame(void)
{
	// �A�C�e���̎擾
	ITEM2 *pItem;
	pItem = GetItem2();

	// �^�C�}�[�̎擾
	Timer *pTimer;
	pTimer = GetTimer();

	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�YON/OFF
		g_bPause = g_bPause ? false : true;
		PlaySound(SOUND_LABEL_SE_PAUSE000);
		StopSound(SOUND_LABEL_SE_PAUSE001);
	}

	if (g_bPause == false)
	{
		// �J�����̍X�V����
		UpdateCamera();

		// ���C�g�̍X�V����
		UpdateLight();

		//// �|���S���̍X�V����
		//UpdatePolygon();

		// ���b�V���t�B�[���h�̍X�V����
		UpdatemeshField();

		//// ���b�V���t�B�[���h2�̍X�V����
		//UpdateMeshField2();

		//// �v���C���[�̍X�V����
		//UpdatePlayer();

		// �v���C���[(�e�q�֌W�Ȃ�)�̍X�V����
		UpdatePlayer2();

		// ���f���̍X�V����
		UpdateModel();

		//// �G�̍X�V����
		//UpdateEnemy();

		// �G(�e�q�֌W�Ȃ�)�̍X�V����
		UpdateEnemy2();

		// �e�̍X�V����
		UpdateShadow();

		//// �ǂ̍X�V����
		//UpdateWall();

		// ���b�V���E�H�[���̍X�V����
		UpdateMeshWall();

		// �r���{�[�h�̍X�V����
		UpdateBillboard();

		// �e�̍X�V����
		UpdateBullet();

		// �����̍X�V����
		UpdateExplosion();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �t���[���̍X�V����
		UpdateFrame();

		// �^�C�}�[�̍X�V����
		UpdateTimer();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �p�[�e�B�N���̍X�V����
		UpdateParticle();

		//// �A�C�e���̍X�V����
		//UpdateItem();

		// �A�C�e��(���f��ver)�̍X�V����
		UpdateItem2();

		// ���C�t�̍X�V����
		UpdateLife();

		switch (g_gameState)
		{
		case GAMESTATE_NORMALL:		// �ʏ���
			break;

		case GAMESTATE_GAMECLEAR:	// �Q�[���N���A���
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{// ��莞�Ԃ�������
				AddScore(pTimer->nTimer * 100);
				g_gameState = GAMESTATE_NONE;
				SetFade(MODE_GAMECLEAR);
			}
			break;

		//case GAMESTATE_GAMEOVER:	// �Q�[���I�[�o�[���
		//	g_nCounterGameState++;
		//	if (g_nCounterGameState >= 60)
		//	{// ��莞�Ԃ�������
		//		g_gameState = GAMESTATE_NONE;
		//		SetFade(MODE_GAMEOVER);
		//	}
		//	break;

		case GAMESTATE_END:			// �I�����
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{// ��莞�Ԃ�������
				g_gameState = GAMESTATE_NONE;
				//SetRankingScore(GetScore());
				SetFade(MODE_GAMEOVER);
			}
			break;
		}
	}
	else
	{//�|�[�Y�̍X�V����
		UpdatePause();

		// �|�[�Y���S�X�V����
		UpdatePauseLogo();

		// �|�[�Y���ڍX�V����
		UpdatePauseSelect();

		//�t�F�[�h�̎擾
		FADE *pFade;
		pFade = GetFade();

		if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
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
			g_bPause = g_bPause ? false : true; // �|�[�Y�͉���
			PlaySound(SOUND_LABEL_SE_PAUSE001);
			StopSound(SOUND_LABEL_SE_PAUSE000);
		}
	}
}

//=============================================================================
// �Q�[���`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	//// �|���S���̕`�揈��
	//DrawPolygon();

	// ���b�V���t�B�[���h�̕`�揈��
	DrawmeshField();

	//// ���b�V���t�B�[���h2�̕`�揈��
	//DrawMeshField2();

	//// �v���C���[�̕`�揈��
	//DrawPlayer();

	// �v���C���[�̕`�揈��
	DrawPlayer2();

	// ���f���̕`�揈��
	DrawModel();

	//// �G�̕`�揈��
	//DrawEnemy();

	// �G(�e�q�֌W�Ȃ�)�̕`�揈��
	DrawEnemy2();

	//// �ǂ̕`�揈��
	//DrawWall();

	// ���b�V���E�H�[���̕`�揈��
	DrawMeshWall();

	// �e�̕`�揈��
	DrawShadow();

	// �r���{�[�h�̕`�揈��
	DrawBillboard();

	// �e�̕`�揈��
	DrawBullet();

	// �����̕`�揈��
	DrawExplosion();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();

	// �t���[���̕`�揈��
	DrawFrame();

	// �^�C�}�[�̕`�揈��
	DrawTimer();

	// �X�R�A�̕`�揈��
	DrawScore();

	// �p�[�e�B�N���̕`�揈��
	DrawParticle();

	//// �A�C�e���̕`�揈��
	//DrawItem();

	// �A�C�e��(���f��ver)�̕`�揈��
	DrawItem2();

	// ���C�t�̕`�揈��
	DrawLife();

	if (g_bPause == true)
	{//�|�[�Y�̕`�揈��
		DrawPause();

		// �|�[�Y���S�`�揈��
		DrawPauseLogo();

		// �|�[�Y���ڕ`�揈��
		DrawPauseSelect();
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