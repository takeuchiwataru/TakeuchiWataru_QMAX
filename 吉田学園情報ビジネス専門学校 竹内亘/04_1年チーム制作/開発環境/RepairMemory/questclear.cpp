//=============================================================================
//
// �N�G�X�g�N���A��� [questclear.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "questclear.h"
#include "main.h"
#include "gamefade.h"
#include "sound.h"
#include "input.h"
#include "start.h"
#include "BG.h"
#include "flontpolygon.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int nCntQuestClearTimer;

//=============================================================================
// ����������
//=============================================================================
void InitQuestClear(void)
{
	nCntQuestClearTimer = 0;

	//�ϐ��Ăяo��
	InitStart();		//�G���^�[�L�[
	
	//�w�i
	//SetBG(2);

	//�G���^�[�L�[
	SetEnter(D3DXVECTOR3(190.0f, 695.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitQuestClear(void)
{
	DeleteStart();		//�G���^�[�L�[
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateQuestClear(void)
{
	//�t�F�[�h�����擾����
	GAMEFADE fade;
	fade = GetGameFade();

	QUESTTYPE pQuestType= GetQuestType();
	QUESTCLEAR *pClearQuest = GetbClearQuest();

	nCntQuestClearTimer++;

	if (nCntQuestClearTimer == 75)
	{
		if (pQuestType == QUESTTYPE_FIRST)
		{
			if (pClearQuest[0].nScore > 45000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_A, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else if (pClearQuest[0].nScore > 30000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_B, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else if (pClearQuest[0].nScore > 10000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_C, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_D, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
		}
		else if (pQuestType == QUESTTYPE_SECOND)
		{
			if (pClearQuest[1].nScore > 45000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_A, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else if (pClearQuest[1].nScore > 30000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_B, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else if (pClearQuest[1].nScore > 10000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_C, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_D, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
		}
		else if (pQuestType == QUESTTYPE_THIRD)
		{
			if (pClearQuest[2].nScore > 45000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_A, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else if (pClearQuest[2].nScore > 30000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_B, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else if (pClearQuest[2].nScore > 10000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_C, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
			else
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_D, D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500 * 10, 500 * 10);

				PlaySound(SOUND_LABEL_SE_RESULT00);
			}
		}
	}

	//����L�[�������ꂽ���ǂ���
	if (nCntQuestClearTimer > 90 && (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true))
	{
		if (fade != GAMEFADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�X�^�[�g�{�^���̐ݒ�
			SetPush(STARTSTRACT_ENTER);

			//�t�F�[�h���[�h�ݒ�
			SetGameFade(GAMESTATE_QUESTSELECT);		//�I����ʂɖ߂�
		}
	}

	UpdateStart();		//�G���^�[�L�[
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawQuestClear(void)
{
	DrawStart();		//�G���^�[�L�[
}