//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "result.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "sky.h"
#include "field.h"
#include "shadow.h"
#include "player.h"
#include "effect.h"
#include "animal.h"
#include "score.h"
#include "timer.h"
#include "frame.h"
#include "particle.h"
#include "model.h"
#include "film.h"
#include "filmframe.h"
#include "pause.h"
#include "ranking.h"
#include "sound.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	ANIMALTYPE type;
}ANIMAL_INFO;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;   // �Q�[���̏��
int       g_nCounterGameState;            // �Q�[���̏�ԊǗ��J�E���^�[
bool      g_bPuase;                       // �|�[�Y�����ǂ���

ANIMAL_INFO g_AnimalInfo[] = 
{
	{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(800.0f,0.0f,400.0f),D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(-300.0f,0.0f,0.0f),D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(-800.0f,0.0f,-130.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(-800.0f,0.0f,830.0f),D3DXVECTOR3(3.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(-800.0f,0.0f,1030.0f),D3DXVECTOR3(10.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(0.0f,0.0f,1100.0f),D3DXVECTOR3(-1.0f,0.0f,-1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(850.0f,0.0f,1130.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(-450.0f,0.0f,-1130.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_DOG },

	{ D3DXVECTOR3(500.0f,0.0f,-1000.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(500.0f,0.0f,-500.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(900.0f,0.0f,-600.0f),D3DXVECTOR3(2.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(-400.0f,0.0f,-600.0f),D3DXVECTOR3(2.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(450.0f,0.0f,800.0f),D3DXVECTOR3(1.0f,0.0f,1.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CAT },
	{ D3DXVECTOR3(500.0f,0.0f,-0.0f),D3DXVECTOR3(1.0f,1.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * -0.5f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(0.0f,0.0f,-500.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXVECTOR3(0.0f,D3DX_PI * 1.0f,0.0f), ANIMALTYPE_CROW },
	{ D3DXVECTOR3(-500.0f,0.0f,-720.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * 1.0f,0.0f), ANIMALTYPE_DOG },
	{ D3DXVECTOR3(-50.0f,0.0f,-920.0f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,D3DX_PI * 1.0f,0.0f), ANIMALTYPE_CROW },

};

//=============================================================================
// �Q�[����ʏ���������
//=============================================================================
void InitGame(void)
{
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �t�B�[���h�̏���������
	InitField();

	// ��̏���������
	InitSky();

	// �e�̏���������
	InitShadow();

	// �v���C���[�̏���������
	InitPlayer();

	// ���f���̏���������
	InitModel();

	// �����̏���������
	InitAnimal();

	for (int nCntAnimal = 0; nCntAnimal < sizeof g_AnimalInfo / sizeof(ANIMAL_INFO); nCntAnimal++)
	{// ������ݒu����񐔌J��Ԃ�
		SetAnimal(g_AnimalInfo[nCntAnimal].pos, g_AnimalInfo[nCntAnimal].move, g_AnimalInfo[nCntAnimal].rot, g_AnimalInfo[nCntAnimal].type);
	}

	// �G�t�F�N�g�̏���������
	InitEffect();

	// �p�[�e�B�N���̏���������
	InitParticle();

	// �X�R�A�̏���������
	InitScore();

	// �^�C�}�[�̏���������
	InitTimer();

	// �t���[���̏���������
	InitFrame();

	// �t�B�����̏���������
	InitFilm();

	// �t�B�����̃t���[���̏���������
	InitFilmFrame();

	// �|�[�Y����������
	InitPause();

	// �|�[�Y���S����������
	InitPauseLogo();

	// �|�[�Y���ڏ���������
	InitPauseSelect();

	g_GameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPuase = false;
}
//=============================================================================
// �Q�[����ʏI������
//=============================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// �t�B�[���h�̏I������
	UninitField();

	// ��̏I������
	UninitSky();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();

	// ���f���̏I������
	UninitModel();

	// �����̏I������
	UninitAnimal();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �p�[�e�B�N���̏I������
	UninitParticle();

	// �X�R�A�̏I������
	UninitScore();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �t���[���̏I������
	UninitFrame();

	// �t�B�����̏I������
	UninitFilm();

	// �t�B�����̃t���[���̏I������
	UninitFilmFrame();

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
	FADE fade;
	fade = GetFade();

	if (GetJoyPadTrigger(DIJS_BUTTON_9,0) == TRUE && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL || GetKeyboardTrigger(DIK_P) == true && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL)
	{// �|�[�YON/OFF
		g_bPuase = g_bPuase ? false : true;
	}

	if (g_bPuase == false)
	{// �|�[�YOFF
	    // �J�����̍X�V����
		UpdateCamera();

		// ���C�g�̍X�V����
		UpdateLight();

		// �t�B�[���h�̍X�V����
		UpdateField();

		// ��̍X�V����
		UpdateSky();

		// �e�̍X�V����
		UpdateShadow();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// ���f���̍X�V����
		UpdateModel();

		// �����̍X�V����
		UpdateAnimal();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �p�[�e�B�N���̍X�V����
		UpdateParticle();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �^�C�}�[�̍X�V����
		UpdateTimer();

		// �t���[���̍X�V����
		UpdateFrame();

		// �t�B�����̍X�V����
		UpdateFilm();

		// �t�B�����̃t���[���̍X�V����
		UpdateFilmFrame();

#ifdef _DEBUG
		if (GetKeyboardTrigger(DIK_F3) && g_GameState == GAMESTATE_NORMAL)
		{// �f�o�b�N�p
			g_GameState = GAMESTATE_END;
		}
#endif

		switch (g_GameState)
		{
		case GAMESTATE_NORMAL:  // �ʏ���
			break;

		case GAMESTATE_RETRY:   // ��蒼�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
			{// ��莞�Ԃ�������
				g_GameState = GAMESTATE_NONE_RETRY;
				SetFade(MODE_GAME);
			}
			break;

		case GAMESTATE_END:     //�I�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
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

		if (GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// ����{�^���������ꂽ
			RESTART restart;
			restart = GetRestart();
			FADE fade;
			fade = GetFade();

			if (fade == FADE_NONE)
			{// �t�F�[�h��ԂłȂ�
				switch (restart)
				{
				case RESTART_CONTINUE:  // �Q�[���ĊJ
					break;
				case RESTART_RETRY:     // �Q�[����蒼��
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_GAME);
					return; // ����ȏ�Q�[����Update���Ȃ�
					break;
				case RESTART_QUIT:      // �^�C�g���J��
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_TITLE);
					return; // ����ȏ�Q�[����Update���Ȃ�
					break;
				}
				g_bPuase = g_bPuase ? false : true; // �|�[�Y�͉���
			}
		}
	}
}
//=============================================================================
// �Q�[����ʕ`�揈��
//=============================================================================
void DrawGame(void)
{		
	// �J�����̐ݒ�
	SetCamera();

	// �t�B�[���h�̕`�揈��
	DrawField();

	// ��̕`�揈��
	DrawSky();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// ���f���̕`�揈��
	DrawModel();

	// �����̕`�揈��
	DrawAnimal();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();

	// �p�[�e�B�N���̕`�揈��
	DrawParticle();

	// �e�̕`�揈��
	DrawShadow();

	// �X�R�A�̕`�揈��
	DrawScore();

	// �^�C�}�[�̕`�揈��
	DrawTimer();

	// �t���[���̕`�揈��
	DrawFrame();

	// �t�B�����̕`�揈��
	DrawFilm();

	// �t�B�����̃t���[���̕`�揈��
	DrawFilmFrame();

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