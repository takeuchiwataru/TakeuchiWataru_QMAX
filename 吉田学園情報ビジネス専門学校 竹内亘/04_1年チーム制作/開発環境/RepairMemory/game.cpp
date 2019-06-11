//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "fade.h"
#include "gamefade.h"
#include "questfade.h"
#include "meshcylinder.h"
#include "meshwall.h"
#include "select.h"
#include "meshfield.h"
#include "shadow.h"
#include "xplayer.h"
#include "xenemy.h"
#include "xobject.h"
#include "effect.h"
#include "item.h"
#include "pause.h"
#include "start.h"
#include "itemCnt.h"
#include "mark.h"
#include "flontpolygon.h"
#include "itemfont.h"
#include "storyfont.h"
#include "Bottun.h"
#include "time.h"
#include "score.h"
#include "questclear.h"
#include "BG.h"
#include "light.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_QUEST	(3)		//�N�G�X�g�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
GAMESTATE	g_gameState = GAMESTATE_NONE;		//�Q�[���̏��
QUESTTYPE	g_questType = QUESTTYPE_MAX;		//�N�G�X�g�̃^�C�v
QUESTSTATE	g_QuesutState = QUESTSTATE_NONE;	//�N�G�X�g�̏��
int			g_nCounterGameState;				//��ԊǗ��J�E���^�[
int			g_nCounterQuest;					//�N�G�X�g�̏�ԊǗ��J�E���^�[
int			g_nCounterGame;						//�G�l�~�[�o���̃J�E���^�[
bool		g_bPause;							//�|�[�Y���g�p���Ă��邩�ǂ���
bool		g_bWireframe;						//���C���[�t���[�������Ă��邩�ǂ���
QUESTCLEAR	g_bClearQuest[MAX_QUEST];			//�N�G�X�g���N���A�������ǂ���
bool		g_bAllClear;
bool		g_Tutorial;
int			g_nCntTutorial;

//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	//�ϐ��̏�����
	g_gameState = GAMESTATE_QUESTSELECT;	//�Q�[���̏��
	g_nCounterGameState = 0;				//��ԊǗ��J�E���^�[
	g_nCounterGame = 0;						//�J�E���^�[
	g_bPause = false;						//�|�[�Y������

	for (int nCnt = 0; nCnt < MAX_QUEST; nCnt++)
	{
		g_bClearQuest[nCnt].nScore = 0;					//�N�G�X�g���N���A���X�R�A
		g_bClearQuest[nCnt].bClear = false;				//�N�G�X�g���N���A���Ă��邩�ǂ���
	}
	g_bAllClear = false;
	g_Tutorial = false;
	g_nCntTutorial = 0;

	//�֐��Ăяo��
	InitCamera();					//�J����
	InitPause();					//�|�[�Y����
	InitMeshCylinder();				//��
	InitMeshWall();					//��
	InitMeshField();				//�n��
	InitShadow();					//�e
	InitXPlayer();					//�v���C���[
	InitXEnemy();					//�Z��
	InitXObject();					//�I�u�W�F�N�g
	InitItem();						//�A�C�e��
	InitEffect();					//�G�t�F�N�g
	InitStart();					//�X�^�[�g�{�^��
	InitItemCnt();					//�A�C�e���J�E���^�[
	InitMark();						//�}�[�N
	InitFlontPolygon();				//�t�����g�|���S��
	InitItemFont();					//�Q�[���t�H���g
	InitStoryFont();				//�X�g�[���[�t�H���g
	InitBottun();					//�{�^��
	InitTime();						//����
	InitScore();					//�X�R�A
	InitGameFade(g_gameState);		//�Q�[���t�F�[�h
	InitQuestFade(g_QuesutState);	//�N�G�X�g�t�F�[�h

	//��ʂ̃��[�h�ݒ�
	SetGameState(g_gameState);
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	//�֐��Ăяo��
	UninitCamera();			//�J����
	UninitPause();			//�|�[�Y����
	UninitMeshCylinder();	//��
	UninitMeshWall();		//��
	UninitMeshField();		//�n��
	UninitShadow();			//�e
	UninitXPlayer();		//�v���C���[
	UninitXEnemy();			//�Z��
	UninitXObject();		//�I�u�W�F�N�g
	UninitItem();			//�A�C�e��
	UninitEffect();			//�G�t�F�N�g
	UninitStart();			//�X�^�[�g�{�^��
	UninitItemCnt();		//�A�C�e���J�E���^�[
	UninitMark();			//�}�[�N
	UninitFlontPolygon();	//�t�����g�|���S��
	UninitItemFont();		//�t�H���g
	UninitStoryFont();		//�X�g�[���[�t�H���g
	UninitBottun();			//�{�^��
	UninitSelect();			//�N�G�X�g�I�����
	UninitTime();			//�^�C��
	UninitScore();			//�X�R�A
	UninitGameFade();		//�Q�[���t�F�[�h
	UninitQuestFade();		//�N�G�X�g�t�F�[�h
	UninitQuestClear();
	DeleteBG();

	SetLight();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();

	//�N�G�X�g�t�F�[�h�̏����擾����
	QUESTFADE questfade;
	questfade = GetQuestFade();

	if (fade == FADE_NONE && GetKeyboardTrigger(DIK_P) == true || GetButtonTrigger(3) == true)
	{//�|�[�YON/OFF
		g_bPause = g_bPause ? false : true;

		PlaySound(SOUND_LABEL_SE_PAUSE);
	}

	if (g_bPause == false)
	{
		UpdateCamera();				//�J����
		UpdateStart();				//�X�^�[�g�{�^��
		switch (g_gameState)
		{
		case GAMESTATE_QUESTSELECT:
			if (g_bAllClear == false)
			{
				if (g_Tutorial == false)
				{
					UpdateSelect();
				}
				else
				{
					if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
					{
						if (g_nCntTutorial == 2)
						{
							DeleteFlontPolygonA(FLONTPOLYGONTEXTURE_TUTORIAL00);
							PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
							g_nCntTutorial--;
						}
						else if (g_nCntTutorial == 1)
						{
							DeleteFlontPolygonA(FLONTPOLYGONTEXTURE_TUTORIAL01);
							PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
							g_nCntTutorial--;
						}
						else if (g_nCntTutorial == 0)
						{
							DeleteFlontPolygonA(FLONTPOLYGONTEXTURE_TUTORIAL02);
							PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
							g_Tutorial = false;
						}
					}
				}
			}
			break;

		case GAMESTATE_QUESTPLAY:
			switch (g_QuesutState)
			{
			case QUESTSTATE_MISSTION:
				UpdateMeshCylinder();		//��
				UpdateMeshWall();			//��
				UpdateMeshField();			//�n��
				UpdateShadow();				//�e
				UpdateXObject();			//�I�u�W�F�N�g
				UpdateXEnemy();				//�Z��
				UpdateXPlayer();			//�v���C���[
				SetRainEffect(D3DXVECTOR3(50, 90, 100), EFFECTTYPE_RESURRECTIONWATER, 1, 10, 0, 0);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ�	/����
				UpdateEffect();				//�G�t�F�N�g
				UpdateFlontPolygon();		//�t�����g�|���S��
				UpdateStoryFont();			//�X�g�[���[�t�H���g
				break;

			case QUESTSTATE_SEARCH:
				UpdateMeshCylinder();		//��
				UpdateMeshWall();			//��
				UpdateMeshField();			//�n��
				UpdateShadow();				//�e
				UpdateXObject();			//�I�u�W�F�N�g
				UpdateXEnemy();				//�Z��
				UpdateXPlayer();			//�v���C���[
				UpdateItem();				//�A�C�e��

				SetRainEffect(D3DXVECTOR3(50, 90, 100), EFFECTTYPE_RESURRECTIONWATER, 1, 10, 0, 0);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ�	/����
				UpdateEffect();				//�G�t�F�N�g
				UpdateMark();				//�}�[�N
				UpdateBottun();				//�{�^��
				UpdateFlontPolygon();		//�t�����g�|���S��
				UpdateItemCnt();			//�A�C�e���J�E���^�[
				UpdateItemFont();			//�A�C�e���t�H���g
				UpdateTime();				//����
				UpdateScore();				//�X�R�A
				break;

			case QUESTSTATE_PUZZLE:
				UpdateMeshField();			//�n��
				UpdateShadow();				//�e
				UpdateXObject();			//�I�u�W�F�N�g
				UpdateEffect();				//�G�t�F�N�g
				UpdateFlontPolygon();		//�t�����g�|���S��
				UpdateTime();				//����
				break;

			case QUESTSTATE_REPORT:
			case QUESTSTATE_CLEAR:
				UpdateMeshCylinder();		//��
				UpdateMeshWall();			//��
				UpdateMeshField();			//�n��
				UpdateShadow();				//�e
				UpdateXObject();			//�I�u�W�F�N�g
				UpdateXEnemy();				//�Z��
				UpdateXPlayer();			//�v���C���[
				UpdateEffect();				//�G�t�F�N�g
				UpdateFlontPolygon();		//�t�����g�|���S��
				UpdateStoryFont();			//�X�g�[���[�t�H���g

				if (g_QuesutState == QUESTSTATE_CLEAR)
				{
					UpdateQuestClear();		//�N�G�X�g�N���A���
					UpdateScore();			//�X�R�A
				}
				break;

			case QUESTSTATE_OVER:
				break;
			}
			break;

	/*	case GAMESTATE_END_CLIA:
			g_nCounterGameState++;	//��ԊǗ��J�E���^�[�����Z

			if (g_nCounterGameState >= 60)
			{
				g_gameState = GAMESTATE_NONE;

				//�t�F�[�h���[�h�ݒ�
				if (fade != FADE_OUT)
				{
					SetFade(MODE_GAMECLEAR);
				}
			}
			break;
			*/
		case GAMESTATE_END_OVER:
			//g_nCounterGameState++;	//��ԊǗ��J�E���^�[�����Z

			//if (g_nCounterGameState > 60)
			{
				g_gameState = GAMESTATE_NONE;

				//�t�F�[�h���[�h�ݒ�
				if (fade != FADE_OUT)
				{
					SetFade(MODE_GAMEOVER);
				}
			}
			break;
		}


		//�|�[�Y�̏�Ԃ����Z�b�g����
		SetPauseState(PAUSESTATE_CONTINUE);
	}
	else if (fade == FADE_NONE)
	{
		UpdatePause();		//�|�[�Y����
	}

		//�N�G�X�g�̏�Ԑݒ�
		UpdateGameFade();			//�Q�[���t�F�[�h
		UpdateQuestFade();			//�N�G�X�g�t�F�[�h

	/*//�f�o�b�O�L�[
	if (questfade != QUESTFADE_OUT)
	{
		if (GetKeyboardTrigger(DIK_F7) == true)
		{//�N�G�X�g�N���A��Ԃɂ���
			SetQuestFade(QUESTSTATE_CLEAR);
		}
	}
	if (fade != FADE_OUT)
	{
		if (GetKeyboardTrigger(DIK_F8) == true)
		{//�Q�[���N���A��Ԃɂ���
			SetGameFade(GAMESTATE_END_CLIA);
		}
		if (GetKeyboardTrigger(DIK_F9) == true)
		{//�Q�[���I�[�o�[��Ԃɂ���
			SetGameFade(GAMESTATE_END_OVER);
		}
	}*/
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//if (GetKeyboardTrigger(DIK_F3) == true)
	{//�|�[�YON/OFF
		//g_bWireframe = g_bWireframe ? false : true;
	}

	if (g_bWireframe == true)
	{
		//���C���[�t���[���̕\��
		//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	SetUpCamera();		//�J����

	switch (g_gameState)
	{
	case GAMESTATE_QUESTSELECT:
		if (g_bAllClear == false)
		{
			DrawSelect();				//�I�����
			DrawFlontPolygon();			//�t�����g�|���S��
		}
		break;

	case GAMESTATE_QUESTPLAY:

		switch (g_QuesutState)
		{//�N�G�X�g�̏�Ԑݒ�
		case QUESTSTATE_MISSTION:
			DrawMeshCylinder();	//��
			DrawMeshWall();		//��
			DrawMeshField();	//�n��
			DrawShadow();		//�e
			DrawXObject();		//�I�u�W�F�N�g
			DrawXEnemy();		//�Z��
			DrawXPlayer();		//�v���C���[
			DrawEffect();		//�G�t�F�N�g
			DrawFlontPolygon();	//�t�����g�|���S��
			DrawStoryFont();	//�X�g�[���[�t�H���g
			break;

		case QUESTSTATE_SEARCH:
			DrawMeshCylinder();	//��
			DrawMeshWall();		//��
			DrawMeshField();	//�n��
			DrawShadow();		//�e
			DrawXObject();		//�I�u�W�F�N�g
			DrawXEnemy();		//�Z��
			DrawXPlayer();		//�v���C���[
			DrawItem();			//�A�C�e��
			DrawEffect();		//�G�t�F�N�g
			DrawMark();			//�}�[�N
			DrawFlontPolygon();	//�t�����g�|���S��
			//DrawBottun();		//�{�^��
			DrawScore();		//�X�R�A
			DrawItemCnt();		//�A�C�e���J�E���^�[
			DrawItemFont();		//�A�C�e���t�H���g
			DrawTime();			//����
			//DrawScore();		//�X�R�A
			break;

		case QUESTSTATE_PUZZLE:
			DrawMeshField();	//�n��
			DrawXObject();		//�I�u�W�F�N�g
			DrawShadow();		//�e
			DrawEffect();		//�G�t�F�N�g
			DrawFlontPolygon();	//�t�����g�|���S��
			DrawTime();			//����
			break;

		case QUESTSTATE_REPORT:
		case QUESTSTATE_CLEAR:
			DrawMeshCylinder();	//��
			DrawMeshWall();		//��
			DrawMeshField();	//�n��
			DrawShadow();		//�e
			DrawXObject();		//�I�u�W�F�N�g
			DrawXEnemy();		//�Z��
			DrawXPlayer();		//�v���C���[
			DrawEffect();		//�G�t�F�N�g
			DrawFlontPolygon();	//�t�����g�|���S��
			DrawStoryFont();	//�X�g�[���[�t�H���g

			if (g_QuesutState == QUESTSTATE_CLEAR)
			{
				DrawQuestClear();		//�N�G�X�g�N���A���
				DrawScore();			//�X�R�A
			}
			break;

		case QUESTSTATE_OVER:
			break;
		}

		DrawStart();		//�X�^�[�g�{�^��
		break;
	}


	if (g_bWireframe == false)
	{
		//���C���[�t���[���̕\�����f�t�H���g�ɖ߂�
		//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	if (g_bPause == true)
	{
		DrawPause();	//�|�[�Y����
	}
	DrawQuestFade();	//�N�G�X�g�t�F�[�h
	DrawGameFade();		//�Q�[���t�F�[�h
}

//=============================================================================
// �Q�[����Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	//��ʂ�����
	switch (g_gameState)
	{
	case GAMESTATE_QUESTSELECT:
		StopSound(SOUND_LABEL_BGM_TUTORIAL);	//�T�E���h��~
		g_QuesutState = QUESTSTATE_NONE;
		UninitSelect();							//�N�G�X�g�I�����
		break;

	case GAMESTATE_QUESTPLAY:
		StopSound(SOUND_LABEL_BGM_GAME);		//�T�E���h��~
		g_gameState = GAMESTATE_NONE;
		g_QuesutState = QUESTSTATE_NONE;
		break;
	}

	if (g_bPause == true)
	{
		DeleteMeshCylinder();				//�������
		DeleteMeshWall();					//�ǂ�����
		DeleteMeshField();					//�n�ʂ�����
		DeleteShadow();						//�e������
		DeleteXObject();					//�I�u�W�F�N�g������
		DeleteXEnemy();						//�Z�l������
		DeleteXPlayer();					//�v���C���[������
		AllDeleteItem();					//�A�C�e��������
		DeleteEffect();						//�G�t�F�N�g������
		DeleteMark();						//�}�[�N������
		DeleteBottun();						//�{�^��������
		SetBottunType(BOTTUNTYPE_NOMAL);	//�{�^����ʏ��Ԃɖ߂�
		DeleteAllFlontPolygon();			//�t�����g�|���S�������ׂď���
		DeleteItemCnt();					//�A�C�e���J�E���^��������
		DeleteItemFont();					//�A�C�e���t�H���g��������
		DeleteStoryFont();					//�X�g�[���[�t�H���g��������
											//�X�R�A
		SetTimeState(TIMESTATE_STOP);		//���Ԃ��~�߂�

		g_Tutorial = false;
		g_nCntTutorial = 0;
		g_bPause = false;
	}

	int nCntClear = 0;

	for (int nCnt = 0; nCnt < MAX_QUEST; nCnt++)
	{
		if (g_bClearQuest[nCnt].bClear == true)
		{
			nCntClear++;
		}
	}

	if (nCntClear == 3)
	{
		g_bAllClear = true;
		SetFade(MODE_GAMECLEAR);
	}
	else
	{
		//��ʂ𐶐�����
		switch (state)
		{
		case GAMESTATE_QUESTSELECT:
			PlaySound(SOUND_LABEL_BGM_TUTORIAL);	//�T�E���h�Đ�
			InitSelect();							//�N�G�X�g�I�����
			break;

		case GAMESTATE_QUESTPLAY:
			PlaySound(SOUND_LABEL_BGM_GAME);		//�T�E���h�Đ�
			g_QuesutState = QUESTSTATE_MISSTION;

			switch (g_questType)
			{
			case QUESTTYPE_FIRST:
				SetStoryFont(TYPESTORYFONT_01);		//�X�g�[���[�t�H���g
				break;

			case QUESTTYPE_SECOND:
				SetStoryFont(TYPESTORYFONT_11);		//�X�g�[���[�t�H���g
				break;

			case QUESTTYPE_THIRD:
				SetStoryFont(TYPESTORYFONT_21);		//�X�g�[���[�t�H���g
				break;
			}

			break;
		}
	}

	//���
	g_gameState = state;
}

//=============================================================================
// �N�G�X�g�^�C�v�̐ݒ�
//=============================================================================
void SetQuestType(QUESTTYPE type)
{
	//���
	g_questType = type;

	switch (g_questType)
	{
	case QUESTTYPE_TUTORIAL:
		SetGameFade(GAMESTATE_QUESTPLAY);	//�N�G�X�g�v���C���[�h�ɂ���
		break;

	case QUESTTYPE_FIRST:
		SetGameFade(GAMESTATE_QUESTPLAY);	//�N�G�X�g�v���C���[�h�ɂ���
		break;

	case QUESTTYPE_SECOND:
		SetGameFade(GAMESTATE_QUESTPLAY);	//�N�G�X�g�v���C���[�h�ɂ���
		break;

	case QUESTTYPE_THIRD:
		SetGameFade(GAMESTATE_QUESTPLAY);	//�N�G�X�g�v���C���[�h�ɂ���
		break;

	case QUESTTYPE_TITLE:
		g_gameState = GAMESTATE_NONE;	//�Q�[�����g�p���Ȃ���Ԃɐݒ�
		SetFade(MODE_TITLE);			//�^�C�g���֐ݒ�
		break;
	}
}

//=============================================================================
// �N�G�X�g�̏�Ԑݒ�
//=============================================================================
void SetQuestState(QUESTSTATE state)
{
	int nClearScore = 0;

	int nScore;
	nScore = 45000;
//	nScore = 30000;
//	nScore = 10000;
//	nScore = 5000;

	//��ʂ�����
	switch (g_QuesutState)
	{
	case QUESTSTATE_NONE:

		DeleteAllFlontPolygon();			//�t�����g�|���S�������ׂď���

		break;
	case QUESTSTATE_MISSTION:

		SetTimeState(TIMESTATE_START);

	case QUESTSTATE_SEARCH:
	case QUESTSTATE_CLEAR:

		DeleteMeshCylinder();				//�������
		DeleteMeshWall();					//�ǂ�����
		DeleteMeshField();					//�n�ʂ�����
		DeleteShadow();						//�e������
		DeleteXObject();					//�I�u�W�F�N�g������
		DeleteXEnemy();						//�Z�l������
		DeleteXPlayer();					//�v���C���[������
		AllDeleteItem();					//�A�C�e��������
		DeleteEffect();						//�G�t�F�N�g������
		DeleteMark();						//�}�[�N������
		DeleteBottun();						//�{�^��������
		SetBottunType(BOTTUNTYPE_NOMAL);	//�{�^����ʏ��Ԃɖ߂�
		DeleteAllFlontPolygon();			//�t�����g�|���S�������ׂď���
		DeleteItemCnt();					//�A�C�e���J�E���^��������
		DeleteItemFont();					//�A�C�e���t�H���g��������
		DeleteStoryFont();					//�X�g�[���[�t�H���g��������
											//�X�R�A
		SetTimeState(TIMESTATE_STOP);		//���Ԃ��~�߂�

		if (g_QuesutState == QUESTSTATE_CLEAR)
		{
			UninitQuestClear();						//�N�G�X�g�N���A���
													//�X�R�A

			//�N�G�X�g�̃��U���g����
			SetGameFade(GAMESTATE_QUESTSELECT);		//�N�G�X�g�I����ʂɖ߂�
		}
		break;

	case QUESTSTATE_PUZZLE:
		DeleteMeshField();					//�n�ʂ�����
		DeleteShadow();						//�e������
		DeleteXObject();					//�I�u�W�F�N�g������
		DeleteEffect();						//�G�t�F�N�g������
		DeleteAllFlontPolygon();			//�t�����g�|���S�������ׂď���
		SetTimeState(TIMESTATE_STOP);		//���Ԃ��~�߂�

		nClearScore = GetScore();
		SetQuestClearScore(nClearScore);

		break;

	case QUESTSTATE_OVER:
		SetGameFade(GAMESTATE_END_OVER);		//�Q�[���I�[�o�[��ʂɈړ�����
		break;
	}

	//��ʂ𐶐�����
	switch (state)
	{
	case QUESTSTATE_NONE:
		break;
	case QUESTSTATE_MISSTION:

		ReSetScore();
		SetTimeState(TIMESTATE_RESET);

	case QUESTSTATE_SEARCH:
	case QUESTSTATE_REPORT:

		SetLight();

		//��
		SetMeshCylinder();

		//��
		SetMeshWall(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetMeshWall(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetMeshWall(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetMeshWall(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetMeshWall(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetMeshWall(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetMeshWall(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetMeshWall(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//�n��
		SetMeshField(FIELDTEXT_FIELD_1, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_2, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_3, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_4, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_5, FIELDTEXTURE_PARK);
		SetMeshField(FIELDTEXT_FIELD_6, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_7, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_8, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_9, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_OTHER_1, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_OTHER_2, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_OTHER_3, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_OTHER_4, FIELDTEXTURE_FIELD);
		SetMeshField(FIELDTEXT_FIELD_WALL_1, FIELDTEXTURE_WALLTOP2);
		SetMeshField(FIELDTEXT_FIELD_WALL_2, FIELDTEXTURE_WALLTOP2);
		SetMeshField(FIELDTEXT_FIELD_WALL_3, FIELDTEXTURE_WALLTOP);
		SetMeshField(FIELDTEXT_FIELD_WALL_4, FIELDTEXTURE_WALLTOP);
		SetMeshField(FIELDTEXT_FIELD_HUNSUI, FIELDTEXTURE_HUNSUI);

		//�I�u�W�F�N�g
		SetXObject(TEXTTYPE_SEARCH_HOUSE_0);
		SetXObject(TEXTTYPE_SEARCH_HOUSE_1);
		SetXObject(TEXTTYPE_SEARCH_HOUSE_2);
		SetXObject(TEXTTYPE_SEARCH_HOUSE_3);
		SetXObject(TEXTTYPE_SEARCH_HOUSE_4);
		SetXObject(TEXTTYPE_SEARCH_HOUSE_5);
		SetXObject(TEXTTYPE_SEARCH_HOUSE_6);
		SetXObject(TEXTTYPE_SEARCH_HOUSE_7);
		SetXObject(TEXTTYPE_SEARCH_HOUSE_8);

		switch (g_questType)
		{
		case QUESTTYPE_TUTORIAL:
			break;

		case QUESTTYPE_FIRST:
			//�J����
			SetCamera(D3DXVECTOR3(-3831.0f, 150.0f, 1571.0f), D3DXVECTOR3(-3943.0f, 50.0f, 1857.0f), D3DXVECTOR3(0.0f, 0.38f, 0.0f), -280.0f, CAMERATYPE_GAME_SEARCH);

			//�v���C���[
			SetXPlayer(D3DXVECTOR3(-3937.0f, 0.0f, 1869.0f), D3DXVECTOR3(0.0f, 2.02f, 0.0f));

			if (state == QUESTSTATE_MISSTION)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_2, D3DXVECTOR3(-4000.0f, 0.0f, 1900.0f), D3DXVECTOR3(0.0f, -1.11f, 0.0f), D3DXVECTOR3(0.0f, -1.11f, 0.0f));
			}
			else if (state == QUESTSTATE_SEARCH)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_2, D3DXVECTOR3(-4000.0f, 0.0f, 1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.11f, 0.0f));

				//�A�C�e��
				//SetItem(D3DXVECTOR3(-3800.0f, 0.0f, 1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_00);

				//�A�C�e��
				SetItem(D3DXVECTOR3(-3700.0f, 0.0f, 1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_00);
				SetItem(D3DXVECTOR3(-900.0f, 0.0f, 2200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-3800.0f, 0.0f, 1480.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);
				SetItem(D3DXVECTOR3(2100.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), ITEMTYPE_GIAR_03);
				SetItem(D3DXVECTOR3(-1980.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), ITEMTYPE_GIAR_00);
				SetItem(D3DXVECTOR3(2600.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-1950.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);
				SetItem(D3DXVECTOR3(-2500.0f, 0.0f, -3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_03);
				SetItem(D3DXVECTOR3(2230.0f, 0.0f, 3880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-700.0f, 0.0f, -2120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);

				SetFlontPolygon(FLONTPOLYGONTEXTURE_PARTS_WIN_CLOCK, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
			}
			else if (state == QUESTSTATE_REPORT)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_2, D3DXVECTOR3(-4000.0f, 0.0f, 1900.0f), D3DXVECTOR3(0.0f, -1.11f, 0.0f), D3DXVECTOR3(0.0f, -1.11f, 0.0f));

				g_bClearQuest[0].nScore = rand() % 4500 + nScore;
				SetScore(g_bClearQuest[0].nScore);
				
				if (g_bClearQuest[0].nScore > 45000)
				{
					SetStoryFont(TYPESTORYFONT_02);		//�X�g�[���[�t�H���g
				}
				else if (g_bClearQuest[0].nScore > 10000)
				{
					SetStoryFont(TYPESTORYFONT_03);		//�X�g�[���[�t�H���g
				}
				else
				{
					SetStoryFont(TYPESTORYFONT_04);		//�X�g�[���[�t�H���g
				}
			}

			break;

		case QUESTTYPE_SECOND:
			//�J����
			SetCamera(D3DXVECTOR3(2252.0f, 150.0f, 1740.0f), D3DXVECTOR3(2446.0f, 50.0f, 1951.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), -280.0f, CAMERATYPE_GAME_SEARCH);

			//�v���C���[
			SetXPlayer(D3DXVECTOR3(2445.0f, 0.0f, 1950.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

			if (state == QUESTSTATE_MISSTION)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_4, D3DXVECTOR3(2545.0f, 0.0f, 1950.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
			}
			else if (state == QUESTSTATE_SEARCH)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_4, D3DXVECTOR3(2545.0f, 0.0f, 1950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

				//�A�C�e��
				//SetItem(D3DXVECTOR3(2205.0f, 0.0f, 1950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_00);

				//�A�C�e��
				SetItem(D3DXVECTOR3(-3700.0f, 0.0f, 1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_00);
				SetItem(D3DXVECTOR3(-900.0f, 0.0f, 2200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-3800.0f, 0.0f, 1480.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);
				SetItem(D3DXVECTOR3(2100.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), ITEMTYPE_GIAR_03);
				SetItem(D3DXVECTOR3(-1980.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), ITEMTYPE_GIAR_00);
				SetItem(D3DXVECTOR3(2600.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-1950.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);
				SetItem(D3DXVECTOR3(-2500.0f, 0.0f, -3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_03);
				SetItem(D3DXVECTOR3(2230.0f, 0.0f, 3880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-700.0f, 0.0f, -2120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);

				SetFlontPolygon(FLONTPOLYGONTEXTURE_PARTS_WIN_MUSICBOX, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
			}
			else if (state == QUESTSTATE_REPORT)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_4, D3DXVECTOR3(2545.0f, 0.0f, 1950.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

				g_bClearQuest[1].nScore = rand() % 4500 + nScore;
				SetScore(g_bClearQuest[1].nScore);

				if (g_bClearQuest[1].nScore > 45000)
				{
					SetStoryFont(TYPESTORYFONT_12);		//�X�g�[���[�t�H���g
				}
				else if (g_bClearQuest[1].nScore > 10000)
				{
					SetStoryFont(TYPESTORYFONT_13);		//�X�g�[���[�t�H���g
				}
				else
				{
					SetStoryFont(TYPESTORYFONT_14);		//�X�g�[���[�t�H���g
				}
			}

			break;

		case QUESTTYPE_THIRD:
			//�J����
			SetCamera(D3DXVECTOR3(209.7f, 150.0f, -734.4f), D3DXVECTOR3(96.1f, 50.0f, -478.0f), D3DXVECTOR3(0.0f, 0.38f, 0.0f), -280.0f, CAMERATYPE_GAME_SEARCH);

			//�v���C���[
			SetXPlayer(D3DXVECTOR3(95.5f, 0.0f, -478.7f), D3DXVECTOR3(0.0f, -2.50f, 0.0f));

			if (state == QUESTSTATE_MISSTION)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_3, D3DXVECTOR3(145.0f, 0.0f, -410.0f), D3DXVECTOR3(0.0f, 0.62f, 0.0f), D3DXVECTOR3(0.0f, 0.62f, 0.0f));
			}
			else if (state == QUESTSTATE_SEARCH)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_3, D3DXVECTOR3(145.0f, 0.0f, -410.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.62f, 0.0f));

				//�A�C�e��
				//SetItem(D3DXVECTOR3(-100.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_00);

				//�A�C�e��
				SetItem(D3DXVECTOR3(-3700.0f, 0.0f, 1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_00);
				SetItem(D3DXVECTOR3(-900.0f, 0.0f, 2200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-3800.0f, 0.0f, 1480.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);
				SetItem(D3DXVECTOR3(2100.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), ITEMTYPE_GIAR_03);
				SetItem(D3DXVECTOR3(-1980.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), ITEMTYPE_GIAR_00);
				SetItem(D3DXVECTOR3(2600.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-1950.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);
				SetItem(D3DXVECTOR3(-2500.0f, 0.0f, -3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_03);
				SetItem(D3DXVECTOR3(2230.0f, 0.0f, 3880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_01);
				SetItem(D3DXVECTOR3(-700.0f, 0.0f, -2120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_GIAR_02);

				SetFlontPolygon(FLONTPOLYGONTEXTURE_PARTS_WIN_DOLL, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
			}
			else if (state == QUESTSTATE_REPORT)
			{
				//NPC
				SetXEnemy(ENEMYTYPE_3, D3DXVECTOR3(145.0f, 0.0f, -410.0f), D3DXVECTOR3(0.0f, 0.62f, 0.0f), D3DXVECTOR3(0.0f, 0.62f, 0.0f));

				g_bClearQuest[2].nScore = rand() % 4500 + nScore;
				SetScore(g_bClearQuest[2].nScore);

				if (g_bClearQuest[2].nScore > 45000)
				{
					SetStoryFont(TYPESTORYFONT_22);		//�X�g�[���[�t�H���g
				}
				else if (g_bClearQuest[2].nScore > 10000)
				{
					SetStoryFont(TYPESTORYFONT_23);		//�X�g�[���[�t�H���g
				}
				else
				{
					SetStoryFont(TYPESTORYFONT_24);		//�X�g�[���[�t�H���g
				}
			}

			break;
		}

		if (state == QUESTSTATE_SEARCH)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTCLEAR, D3DXVECTOR3(SCREEN_WIDTH / 2, 40, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 80);

			SetScore(D3DXVECTOR3(950.0f, 15.0f, 0.0f), 40.0f, 60.0f);

			//�{�^��
			SetBottun();

			//�����̐�
			SetFlontPolygon(FLONTPOLYGONTEXTURE_NUMBER_SLASH, D3DXVECTOR3(275, 50, 0), D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f), 50.0f, 50.0f);

			SetTimeState(TIMESTATE_START);		//���Ԃ�����������

			PlaySound(SOUND_LABEL_SE_PAZZLEIN);
		}

		break;

	case QUESTSTATE_PUZZLE:

		SetLight();

		SetCamera(D3DXVECTOR3(0.0f, 900.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -350.0f, CAMERATYPE_GAME_PUZZLE);	//�J������ݒ肷��
		SetTimeState(TIMESTATE_STOP);																			//���Ԃ�i�߂�

		//�n��
		SetMeshField(FIELDTEXT_FIELD_PAZZLE, FIELDTEXTURE_PAZZLE);

		switch (g_questType)
		{
		case QUESTTYPE_TUTORIAL:
			break;

		case QUESTTYPE_FIRST:

			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_BG, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 + 35, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, SCREEN_HEIGHT - 70);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_1, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 230, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_2, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 230, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_3, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 330, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_4, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 330, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_5, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 550, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_6, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 550, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_MB1, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 650, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_MB2, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 650, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);

			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_S0, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 - 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, 60);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_S1, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, 60);

			SetXObject(TEXTTYPE_PUZZLE_1);
			SetXObject(TEXTTYPE_PUZZLE_1_A);
			SetXObject(TEXTTYPE_PUZZLE_1_W);
			break;

		case QUESTTYPE_SECOND:

			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_BG, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 + 35, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, SCREEN_HEIGHT - 70);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_1, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 230, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_2, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 230, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_3, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 330, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_4, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 330, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_5, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 550, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_6, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 550, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_7, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 650, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_8, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 650, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);

			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_S0, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 - 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, 60);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_S1, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, 60);

			SetXObject(TEXTTYPE_PUZZLE_2);
			SetXObject(TEXTTYPE_PUZZLE_2_A);
			SetXObject(TEXTTYPE_PUZZLE_2_W);
			break;

		case QUESTTYPE_THIRD:

			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_BG, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 + 35, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, SCREEN_HEIGHT - 70);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_1, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 230, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_2, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 230, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_3, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 330, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_4, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 330, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_5, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 550, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_6, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 550, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_7, D3DXVECTOR3(SCREEN_WIDTH / 2 + 466, 650, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_ZENMAI, D3DXVECTOR3(SCREEN_WIDTH / 2 + 566, 650, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80);

			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_S0, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 - 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, 60);
			SetFlontPolygon(FLONTPOLYGONTEXTURE_MENU_S1, D3DXVECTOR3(SCREEN_WIDTH / 2 + 516, SCREEN_HEIGHT / 2 + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240, 60);

			SetXObject(TEXTTYPE_PUZZLE_3);
			SetXObject(TEXTTYPE_PUZZLE_3_A);
			SetXObject(TEXTTYPE_PUZZLE_3_W);
			break;
		}

		SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTCLEAR, D3DXVECTOR3(SCREEN_WIDTH / 2, 40, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 80);

		//SetFlontPolygon(FLONTPOLYGONTEXTURE_POINTER, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f), 30, 30);
		SetFlontPolygon(FLONTPOLYGONTEXTURE_POINTER, D3DXVECTOR3(SCREEN_WIDTH - 120, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f), 30, 30);

		SetFlontPolygon(FLONTPOLYGONTEXTURE_PAZZLE_START, D3DXVECTOR3(SCREEN_WIDTH + 400, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 700, 300);
		PlaySound(SOUND_LABEL_SE_PAZZLEIN);

		break;

	case QUESTSTATE_CLEAR:
		InitQuestClear();		//�N�G�X�g�N���A���

		SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTCLEAR, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
		SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 - 420, SCREEN_HEIGHT / 2 + 110, 0.0f), 80.0f, 120.0f);

		switch (g_questType)
		{
		case QUESTTYPE_FIRST:
			g_bClearQuest[0].bClear = true;
			break;

		case QUESTTYPE_SECOND:
			g_bClearQuest[1].bClear = true;
			break;

		case QUESTTYPE_THIRD:
			g_bClearQuest[2].bClear = true;
			break;
		}
		break;

	case QUESTSTATE_OVER:
		break;
	}

	//���
	g_QuesutState = state;
}

//=============================================================================
// �Q�[����Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=============================================================================
// �N�G�X�g��Ԃ̎擾
//=============================================================================
QUESTSTATE GetQuestState(void)
{
	return g_QuesutState;
}

//=============================================================================
// �N�G�X�g��Ԃ̎擾
//=============================================================================
QUESTTYPE GetQuestType(void)
{
	return g_questType;
}

//=============================================================================
// �|�[�Y��Ԃ̎擾
//=============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}

//=============================================================================
// �|�[�Y��Ԃ̎擾
//=============================================================================
bool GetGAMEPause(void)
{
	return g_bPause;
}

//=============================================================================
// �N�G�X�g�̏�Ԃ̏��̎擾
//=============================================================================
QUESTCLEAR *GetbClearQuest(void)
{
	return &g_bClearQuest[0];
}

//=============================================================================
// �N�G�X�g�̃X�R�A�擾
//=============================================================================
void SetQuestClearScore(int nScore)
{
	if (g_questType == QUESTTYPE_FIRST)
	{
		if (g_bClearQuest[0].nScore < nScore)
		{
			g_bClearQuest[0].nScore = nScore;
		}
	}
	else if (g_questType == QUESTTYPE_SECOND)
	{
		if (g_bClearQuest[1].nScore < nScore)
		{
			g_bClearQuest[1].nScore = nScore;
		}
	}
	else if (g_questType == QUESTTYPE_THIRD)
	{
		if (g_bClearQuest[2].nScore < nScore)
		{
			g_bClearQuest[2].nScore = nScore;
		}
	}
}

void SetShowTutorial(bool bTutorial)
{
	if (g_Tutorial == false && bTutorial == true)
	{
		SetFlontPolygon(FLONTPOLYGONTEXTURE_TUTORIAL02, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
		SetFlontPolygon(FLONTPOLYGONTEXTURE_TUTORIAL01, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
		SetFlontPolygon(FLONTPOLYGONTEXTURE_TUTORIAL00, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH, SCREEN_HEIGHT);

		g_nCntTutorial = 2;
		g_Tutorial = true;
	}

	g_Tutorial = bTutorial;
}