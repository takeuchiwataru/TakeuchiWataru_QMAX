//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "block.h"
#include "item.h"
#include "score.h"
#include "timer.h"
#include "input.h"
#include "pause.h"
#include "pauselogo.h"
#include "pauseselect.h"
#include "fade.h"
#include "bg.h"
#include "rankingscore.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
// �u���b�N���̍\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	BLOCKTYPE nType;
}BlockInfo;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COIN_WIDTH		(30)				//�R�C���̕�
#define COIN_HEIGHT		(50)				//�R�C���̍���

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[���̏��
int g_nCounterGameState;					//��ԊǗ��J�E���^�[
bool g_bPause;								//�|�[�Y�����ǂ���

//***********************************
// �u���b�N���̃f�[�^
//***********************************
BlockInfo g_aBlockInfo[] =
{
	{ D3DXVECTOR3(-100,680,0),50,50,BLOCKTYPE_NOMALL },				//����
	{ D3DXVECTOR3(750,680,0),50,50,BLOCKTYPE_NOMALL },				//���E
	{ D3DXVECTOR3(-100,500,0),50,50,BLOCKTYPE_NOMALL },				//2�i�ڍ�
	{ D3DXVECTOR3(1000,500,0),50,50,BLOCKTYPE_NOMALL },				//2�i�ډE
	{ D3DXVECTOR3(-100,300,0),50,50,BLOCKTYPE_NOMALL },				//3�i�ڍ�
	{ D3DXVECTOR3(1150,300,0),50,50,BLOCKTYPE_NOMALL },				//3�i�ډE
	{ D3DXVECTOR3(250,550,0),50,50,BLOCKTYPE_NOMALL },				//������̒�
	{ D3DXVECTOR3(100,350,0),50,50,BLOCKTYPE_NOMALL },				//2�i�ڂ���̒�
	{ D3DXVECTOR3(150,150,0),50,50,BLOCKTYPE_NOMALL },				//3�i�ڂ���̒�
	{ D3DXVECTOR3(500,450,0),50,50,BLOCKTYPE_BERUTOKONBEA },		//�^��(�x���g�R���x�A)
	{ D3DXVECTOR3(200,150,0),50,50,BLOCKTYPE_BERUTOKONBEA },		//��̃x���g�R���x�A
	{ D3DXVECTOR3(50,150,0),50,50,BLOCKTYPE_NOMALL },				//4�i�ڂ̉󂹂�u���b�N�Ƃ̊�
	{ D3DXVECTOR3(-100,150,0),50,50,BLOCKTYPE_NOMALL },				//4�i�ڂ̉󂹂�u���b�N�Ƃ̊�
	{ D3DXVECTOR3(1100,150,0),50,50,BLOCKTYPE_NOMALL },				//4�i��
	{ D3DXVECTOR3(1050,150,0),50,50,BLOCKTYPE_NOMALL },				//3�i�ڒ�
	{ D3DXVECTOR3(SCREEN_WIDTH / 2,250,0),50,50,BLOCKTYPE_JUMP },	//�W�����v��
	{ D3DXVECTOR3(950,150,0),50,50,BLOCKTYPE_FALL },				//�����鏰

};

//=============================================================================
// �Q�[������������
//=============================================================================
void InitGame(void)
{
	//�w�i����������
	InitBG();

	//�v���C���[�̏���������
	InitPlayer();

	//�u���b�N�̏���������
	InitBlock();
	int nCntBlock;
	for (nCntBlock = 0; nCntBlock < sizeof g_aBlockInfo / sizeof(BlockInfo);nCntBlock++)
	{
		SetBlock(g_aBlockInfo[0].pos,650,50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[1].pos, 650, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[2].pos, 400, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[3].pos, 400, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[4].pos, 300, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[5].pos, 300, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[6].pos, 50, 130, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[7].pos, 50, 100, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[8].pos, 50, 150, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[9].pos, 300, 50, BLOCKTYPE_BERUTOKONBEA);
		SetBlock(g_aBlockInfo[10].pos, 300, 50, BLOCKTYPE_BERUTOKONBEA);
		SetBlock(g_aBlockInfo[11].pos, 100, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[12].pos, 100, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[13].pos, 400, 50, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[14].pos, 50, 200, BLOCKTYPE_NOMALL);
		SetBlock(g_aBlockInfo[15].pos, 200, 50, BLOCKTYPE_JUMP);
		SetBlock(g_aBlockInfo[16].pos, 100, 50, BLOCKTYPE_FALL);

	}

	SetBlock(D3DXVECTOR3(100, 450, 0.0f), 50, 50, BLOCKTYPE_PUSH);
	SetBlock(D3DXVECTOR3(1000, 550, 0.0f), 50, 130, BLOCKTYPE_PUSH);
	SetBlock(D3DXVECTOR3(0, 150, 0.0f), 50, 50, BLOCKTYPE_BREAK);
	SetBlock(D3DXVECTOR3(1100, 300, 0.0f), 50, 50, BLOCKTYPE_BREAK);
	//SetBlock(D3DXVECTOR3(0, 150, 0.0f), 50, 50, BLOCKTYPE_BREAK);
	//SetBlock(D3DXVECTOR3(600, 300, 0.0f), 100, 100, BLOCKTYPE_JUMP);

	//�A�C�e���̏���������
	InitItem();

	//�A�C�e���̃Z�b�g
	SetItem(D3DXVECTOR3(200, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//���ߕӂ̃R�C��
	SetItem(D3DXVECTOR3(1100, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(400, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(850, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(630, 630, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(630, 500, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	//SetItem(D3DXVECTOR3(200, 450, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	//SetItem(D3DXVECTOR3(1150, 450, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(550, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//�x���g�R���x�A��̃R�C��
	SetItem(D3DXVECTOR3(590, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(630, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN2);
	SetItem(D3DXVECTOR3(670, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(710, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(0, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);		//6�̃R�C��
	SetItem(D3DXVECTOR3(0, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(50, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(50, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(100, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(100, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(150, 100, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN2);
	SetItem(D3DXVECTOR3(250, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN2);

	SetItem(D3DXVECTOR3(1100, 100, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//�E��̃R�C��
	SetItem(D3DXVECTOR3(1150, 50, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN2);
	SetItem(D3DXVECTOR3(1200, 100, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(1100, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//8�̃R�C��
	SetItem(D3DXVECTOR3(1100, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1150, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1150, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1200, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1200, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1250, 200, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1250, 250, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(50, 350, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);	//�������̃R�C��	
	SetItem(D3DXVECTOR3(0, 350, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(50, 450, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(0, 450, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(200, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(1050, 400, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	SetItem(D3DXVECTOR3(650, 150, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(700, 100, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(750, 50, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);
	SetItem(D3DXVECTOR3(800, 10, 0.0f), COIN_WIDTH, COIN_HEIGHT, ITEMTYPE_COIN);

	//�X�R�A�̏���������
	InitScore();

	//�^�C�}�[�̏���������
	InitTimer();

	//�|�[�Y�̏���������
	InitPause();

	// �|�[�Y���S����������
	InitPauseLogo();

	// �|�[�Y���ڏ���������
	InitPauseSelect();

	// �����̏���������
	InitExplosion();

	g_gameState = GAMESTATE_NORMALL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	g_bPause = false;
}
//=============================================================================
// �Q�[���I������
//=============================================================================
void UninitGame(void)
{
	//�w�i�I������
	UninitBG();

	//�v���C���[�̏I������
	UninitPlayer();

	//�u���b�N�̏I������
	UninitBlock();

	//�A�C�e���̏I������
	UninitItem();

	//�X�R�A�̏I������
	UninitScore();

	//�^�C�}�[�̏I������
	UninitTimer();

	//�|�[�Y�̏I������
	UninitPause();

	// �|�[�Y���S�I������
	UninitPauseLogo();

	// �|�[�Y���ڏI������
	UninitPauseSelect();

	// �����̏I������
	UninitExplosion();
}
//=============================================================================
// �Q�[���X�V����
//=============================================================================
void UpdateGame(void)
{
	//�t�F�[�h�̎擾
	FADE *fade;
	fade = GetFade();

	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�YON/OFF
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		// �w�i�X�V����
		UpdateBG();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �u���b�N�̍X�V����
		UpdateBlock();

		//�A�C�e���̍X�V����
		UpdateItem();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �^�C�}�[�̍X�V����
		UpdateTimer();

		// �����̍X�V����
		UpdateExplosion();

		switch (g_gameState)
		{
		case GAMESTATE_NORMALL:  // �ʏ���
			break;

		case GAMESTATE_GAMEOVER:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{
				g_gameState = GAMESTATE_NONE;

				//��ʂ̐ݒ�
				SetFade(MODE_GAMEOVER);
			}
			break;

		case GAMESTATE_END:     //�I�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{// ��莞�Ԃ�������
				g_gameState = GAMESTATE_NONE;
				SetRankingScore(GetScore());
				SetFade(MODE_RESULT);
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
		}

	}
}
//=============================================================================
// �Q�[���`�揈��
//=============================================================================
void DrawGame(void)
{
	//�w�i�`�揈��
	DrawBG();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�^�C�}�[�̕`�揈��
	DrawTimer();

	//�����̕`�揈��
	DrawExplosion();

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
