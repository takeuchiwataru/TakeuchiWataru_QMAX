//=============================================================================
//
// ���U���g[ �N���A ]��� [result.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "result.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
//#include "start.h"
#include "flontpolygon.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RESULT_POS_X		(0)								//�w�i�̍���X���W
#define RESULT_POS_Y		(0)								//�w�i�̍���Y���W
#define RESULT_WHIDTH		(SCREEN_WIDTH)					//�w�i�̕�
#define RESULT_HEIGHT		(SCREEN_HEIGHT)					//�w�i�̍���

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int g_nCntTimeResult;								//�Q�[����ʐ؂�ւ��J�E���^�[
int g_nCntRanckNum;

//=============================================================================
// ���U���g����������
//=============================================================================
void InitResult(void)
{
	g_nCntTimeResult = 0;	//�J�E���^�[�̏�����
	g_nCntRanckNum = 0;

	//�ϐ��̌Ăяo��
	//InitStart();		//�G���^�[�L�[

	InitFlontPolygon();

	SetFlontPolygon(FLONTPOLYGONTEXTURE_CLEARRESULT, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTCLEAR, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), SCREEN_WIDTH, SCREEN_HEIGHT);

	//�G���^�[�L�[
	//SetEnter(D3DXVECTOR3(1090.0f, 685.0f, 0.0f), D3DXCOLOR(0.05f, 0.5f, 0.05f, 1.0f));	

	PlaySound(SOUND_LABEL_SE_RESULT01);
}

//=============================================================================
// ���U���g�I������
//=============================================================================
void UninitResult(void)
{
	UninitFlontPolygon();

	//UninitStart();		//�G���^�[�L�[
}

//=============================================================================
// ���U���g�X�V����
//=============================================================================
void UpdateResult(void)
{
	QUESTCLEAR *pClearQuest = GetbClearQuest();

	g_nCntTimeResult++;

	if (g_nCntTimeResult == 60)
	{
		StopSound(SOUND_LABEL_SE_RESULT01);

		if (pClearQuest[0].nScore > 45000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_A, D3DXVECTOR3(SCREEN_WIDTH / 2 - 350.0f, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 3;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else if (pClearQuest[0].nScore > 30000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_B, D3DXVECTOR3(SCREEN_WIDTH / 2 - 350.0f, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 2;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else if (pClearQuest[0].nScore > 10000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_C, D3DXVECTOR3(SCREEN_WIDTH / 2 - 350.0f, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 1;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else 
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_D, D3DXVECTOR3(SCREEN_WIDTH / 2 - 350.0f, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
	}
	else if (g_nCntTimeResult == 90)
	{
		if (pClearQuest[1].nScore > 45000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_A, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 3;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else if (pClearQuest[1].nScore > 30000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_B, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 2;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else if (pClearQuest[1].nScore > 10000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_C, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 1;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_D, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
	}
	else if (g_nCntTimeResult == 120)
	{
		if (pClearQuest[2].nScore > 45000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_A, D3DXVECTOR3(SCREEN_WIDTH / 2 + 350.0f, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 3;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else if (pClearQuest[2].nScore > 30000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_B, D3DXVECTOR3(SCREEN_WIDTH / 2 + 350.0f, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 2;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else if (pClearQuest[2].nScore > 10000)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_C, D3DXVECTOR3(SCREEN_WIDTH / 2 + 350.0f, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);
			g_nCntRanckNum += 1;

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
		else
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_D, D3DXVECTOR3(SCREEN_WIDTH / 2 + 350.0f, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300 * 10, 300 * 10);

			PlaySound(SOUND_LABEL_SE_RESULT02);
		}
	}
	else if (g_nCntTimeResult == 180)
	{
		if (g_nCntRanckNum > 7)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_CLEAR_RANK_A, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000 * 10, 400 * 10);

			PlaySound(SOUND_LABEL_SE_RESULT03);
		}
		else if (g_nCntRanckNum > 4)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_CLEAR_RANK_B, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000 * 10, 400 * 10);

			PlaySound(SOUND_LABEL_SE_RESULT03);
		}
		else if (g_nCntRanckNum > 1)
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_CLEAR_RANK_C, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000 * 10, 400 * 10);

			PlaySound(SOUND_LABEL_SE_RESULT03);
		}
		else
		{
			SetFlontPolygon(FLONTPOLYGONTEXTURE_CLEAR_RANK_D, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000 * 10, 400 * 10);

			PlaySound(SOUND_LABEL_SE_RESULT03);
		}
	}

	//�t�F�[�h�����擾����
	FADE g_fade;
	g_fade = GetFade();
	
	//����L�[�������ꂽ���ǂ���
	if (g_nCntTimeResult > 200 && GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
	{
		if (g_fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�T�E���h�Đ�
			//PlaySound(SOUND_LABEL_SE_ENTER);

			//�G���^�[�L�[�̏�ԕύX
			//SetPush(STARTSTRACT_ENTER);

			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_TITLE);
		}		
	}

	//UpdateStart();		//�G���^�[�L�[

	UpdateFlontPolygon();
}

//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void DrawResult(void)
{
	//DrawStart();		//�G���^�[�L�[

	DrawFlontPolygon();
}