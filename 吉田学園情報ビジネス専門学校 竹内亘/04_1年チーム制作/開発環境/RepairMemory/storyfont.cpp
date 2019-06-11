//=============================================================================
//
// �X�g�[���[�t�H���g��� [storyfont.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "storyfont.h"
#include "input.h"
#include "flontpolygon.h"
#include "questfade.h"
#include "game.h"
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LINE	(15)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXFONT			g_pStoryFont[MAX_LINE] = {};	// �t�H���g�ւ̃|�C���^
StoryFont			g_StoryFont;					//�t�H���g�̏��
StoryLine			g_StoryLine[MAX_LINE];			//��b��
int					g_CntStoryLine;					//��b�����J�E���g����
bool				g_bStory;						//�X�g�[���[��ԂɂȂ��Ă��邩�ǂ���
int					g_nGetIndx;						//����ۑ�����ko

//=============================================================================
// ����������
//=============================================================================
void InitStoryFont(void)
{
	//�ϐ��錾
	int nCntLine;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	g_StoryFont.type = TYPESTORYFONT_MAX;
	g_StoryFont.bUse = false;
	g_nGetIndx = 0;

	for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		g_StoryLine[nCntLine].Line[0] = {};
		g_StoryLine[nCntLine].nTex = -1;
		g_StoryLine[nCntLine].nIdx = 0;
		g_StoryLine[nCntLine].bUse = false;

		//�t�H���g�̐ݒ�
		D3DXCreateFont(pDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pStoryFont[nCntLine]);
	}
	g_CntStoryLine = 0;
	g_bStory = false;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStoryFont(void)
{
	//�ϐ��錾
	int nCntLine;

	// �t�H���g�̊J��
	for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_pStoryFont[nCntLine] != NULL)
		{
			g_pStoryFont[nCntLine]->Release();
			g_pStoryFont[nCntLine] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStoryFont(void)
{
	//�ϐ��錾
	int nCntLine;

	//�t�F�[�h�̏����擾����
	QUESTFADE Fade;
	Fade = GetQuestFade();

	QUESTSTATE pQuestState = GetQuestState();
	QUESTTYPE pQuestType = GetQuestType();

	if (g_StoryFont.bUse == false)
	{
		if (Fade != QUESTFADE_OUT)
		{//�t�F�[�h�A�E�g�̏�Ԃł͂Ȃ�������
			if (pQuestState == QUESTSTATE_MISSTION)
			{
				SetQuestState(QUESTSTATE_SEARCH);
			}
			else if (pQuestState == QUESTSTATE_REPORT)
			{
				SetQuestState(QUESTSTATE_CLEAR);
			}
		}
	}

	//�X�g�[���[�̐i�s����
	if (g_bStory == true)
	{//�X�g�[���[��Ԃ�������
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
		{//�G���^�[�L�[����������
			DeleteFlontPolygon(g_nGetIndx);	//�|���S��������
			g_CntStoryLine++;				//��b���̃J�E���^�[��i�߂�

			for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
			{
				if (g_StoryLine[g_CntStoryLine].Line[0] != NULL)
				{//������NULL����Ȃ�������
					if (g_CntStoryLine == nCntLine)
					{
						g_StoryLine[nCntLine].bUse = true;		//���͂��g�p���Ă����Ԃɂ���

						//�A�C�R���摜�̐ݒ�
						g_StoryLine[nCntLine].nIdx = SetFlontPolygon(g_StoryLine[nCntLine].nTex, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 130.0f);
						g_nGetIndx = g_StoryLine[nCntLine].nIdx;

						if (g_StoryLine[nCntLine].nTex == FLONTPOLYGONTEXTURE_MESSAGE_NPC_0 || g_StoryLine[nCntLine].nTex == FLONTPOLYGONTEXTURE_MESSAGE_NPC_1 || g_StoryLine[nCntLine].nTex == FLONTPOLYGONTEXTURE_MESSAGE_NPC_2)
						{
							if (g_StoryFont.type == TYPESTORYFONT_02 || g_StoryFont.type == TYPESTORYFONT_12 || g_StoryFont.type == TYPESTORYFONT_22)
							{
								if (pQuestType == QUESTTYPE_FIRST)
								{
									SetEmotionEffect(D3DXVECTOR3(-4000.0f, 60.0f, 1900.0f), EFFECTTYPE_RESURRECTIONHAPPY, 10, 30, 10, 1);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ�	/���
								}
								else if (pQuestType == QUESTTYPE_SECOND)
								{
									SetEmotionEffect(D3DXVECTOR3(2545.0f, 60.0f, 1950.0f), EFFECTTYPE_RESURRECTIONHAPPY, 10, 30, 10, 1);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ�	/���
								}
								else if (pQuestType == QUESTTYPE_THIRD)
								{
									SetEmotionEffect(D3DXVECTOR3(145.0f, 60.0f, -410.0f), EFFECTTYPE_RESURRECTIONHAPPY, 10, 30, 10, 1);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ�	/���
								}
							}
							else if (g_StoryFont.type == TYPESTORYFONT_04 || g_StoryFont.type == TYPESTORYFONT_14 || g_StoryFont.type == TYPESTORYFONT_24)
							{
								if (pQuestType == QUESTTYPE_FIRST)
								{
									SetEmotionEffect(D3DXVECTOR3(-4000.0f, 60.0f, 1900.0f), EFFECTTYPE_RESURRECTIONANGRY, 3, 30, 10, 2);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ��@�@/�{��
								}
								else if (pQuestType == QUESTTYPE_SECOND)
								{
									SetEmotionEffect(D3DXVECTOR3(2545.0f, 60.0f, 1950.0f), EFFECTTYPE_RESURRECTIONANGRY, 3, 30, 10, 2);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ��@�@/�{��
								}
								else if (pQuestType == QUESTTYPE_THIRD)
								{
									SetEmotionEffect(D3DXVECTOR3(145.0f, 60.0f, -410.0f), EFFECTTYPE_RESURRECTIONANGRY, 3, 30, 10, 2);	//�ʒu�F �G�t�F�N�g�^�C�v �F �� : ���a �F HP �F �e�N�X�`���ԍ��@�@/�{��
								}
							}
						}
					}
					else
					{
						g_StoryLine[nCntLine].bUse = false;		//���͂��g�p���Ă��Ȃ���Ԃɂ���
					}
				}
				else
				{
					g_StoryFont.bUse = false;
					g_StoryLine[nCntLine].bUse = false;		//���͂��g�p���Ă��Ȃ���Ԃɂ���
					DeleteAllFlontPolygon();				//�|���S�������ׂď���
					g_bStory = false;						//�X�g�[���[��Ԃł͂Ȃ�����
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStoryFont(void)
{
	//�ϐ��錾
	int nCntLine;
	RECT rect = { 400, 590, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };		//X���W, Y���W, �w���̕`��͈�, Y���̕`��͈�

	// �e�L�X�g�`��
	if (g_StoryFont.bUse == true)
	{
		for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
		{
			if (g_StoryLine[nCntLine].bUse == true)
			{
				g_pStoryFont[nCntLine]->DrawText(NULL, &g_StoryLine[nCntLine].Line[0], -1, &rect, DT_LEFT, D3DXCOLOR(0.2f, 0.1f, 0.015f, 1.0f));
			}
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
void SetStoryFont(TYPESTORYFONT type)
{
	//�ϐ��錾
	int nCntLine;

	//�ϐ��̏�����
	g_CntStoryLine = 0;

	for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		g_StoryLine[nCntLine].Line[0] = {};
		g_StoryLine[nCntLine].nIdx = 0;
		g_StoryLine[nCntLine].nTex = -1;
		g_StoryLine[nCntLine].bUse = false;
	}

	if (g_StoryFont.bUse == false)
	{
		g_StoryFont.type = type;
		g_StoryFont.bUse = true;
		g_bStory = true;							//�X�g�[���[��Ԃɐݒ肷��

		switch (g_StoryFont.type)
		{
			//==============================================================================
			//�N�G�X�g�P
			//==============================================================================

		case TYPESTORYFONT_01:	//�N�G�X�g�P -�˗��V�[��-
			wsprintf(&g_StoryLine[0].Line[0], "�u���܂Ȃ���������}����\n �����Ă���Ȃ����낤���H�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�͂��I���C�����������I\n�@����́A�I���S�[���ł��ˁB�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�����Ȃ񂶂�A\n �����v�X�ɕ������Ǝv������v");
			wsprintf(&g_StoryLine[3].Line[0], "�u�����Ȃ�Ȃ��Ȃ��Ă��܂��Ă��񂶂�B�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u�ƂĂ��A��؂ȕ�������\n�@�����Ă��܂��Ăȁc�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u����ł����ɗ����񂶂�B�v");
			wsprintf(&g_StoryLine[6].Line[0], "�u����́A��ςł��ˁB\n�@�ӔC�������Ē������Ē����܂��I�v");
			wsprintf(&g_StoryLine[7].Line[0], "�u�������您�͂��������܂��ˁB�v");
			wsprintf(&g_StoryLine[8].Line[0], "�u���񂾂�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[6].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[7].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[8].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			break;

		case TYPESTORYFONT_02:	//�N�G�X�g�P -�񍐃V�[�� A�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u����������A���҂������܂����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�����A�����Ɏ������悤���ˁB�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�͂��I\n ��������ƒ������Ă��������܂����I�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u���F���΂����肾�Ǝv���܂��I�v");

			wsprintf(&g_StoryLine[4].Line[0], "�u��������A�������Ⴑ�̉������I\n�@���ɉ��������́`�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u���̃I���S�[���͂ȁA�킵���Ⴂ�����\n�@�΂����񂩂����������̂Ȃ񂶂�v");
			wsprintf(&g_StoryLine[6].Line[0], "�u���y�D���̂킵�̂��߂�\n�@���̃I���S�[���𔃂��Ă���Ăȁ`�v");
			wsprintf(&g_StoryLine[7].Line[0], "�u����͂������ꂵ�������́`�v");
			wsprintf(&g_StoryLine[8].Line[0], "�u����Ȏv���o��\n�@���̃I���S�[���ɂ�������ł��ˁB�v");
			wsprintf(&g_StoryLine[9].Line[0], "�u���肪�Ƃ��A�C���l����B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[6].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[7].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[8].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[9].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			break;

		case TYPESTORYFONT_03:	//�N�G�X�g�P -�񍐃V�[�� B&C�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u�����ɂ͒����܂���ł����c�B�v");

			wsprintf(&g_StoryLine[1].Line[0], "�u���̉��F�͉��������ȁ`�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u���X�����Ⴄ�C�����邪\n �܂��A�d���Ȃ����́`�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u���͂��̃I���S�[���͂ȁA�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u�킵���Ⴂ����\n ���΂����񂩂����������̂Ȃ񂶂�B�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u���y�D���̂킵�̂��߂�\n ���̃I���S�[���𔃂��Ă���Ăȁ`�v");
			wsprintf(&g_StoryLine[6].Line[0], "�u����͂��������������񂶂�B�v");
			wsprintf(&g_StoryLine[7].Line[0], "�u���Ⴉ��̂ǂ���̉���\n �����Ȃ��Ȃ��Ă��܂����̂��߂����ĂȁB�v");
			wsprintf(&g_StoryLine[8].Line[0], "�u�����Ȃ璼���Ă����Ǝv�����񂶂Ⴊ�A\n �c�O���̂��c�B�v");
			wsprintf(&g_StoryLine[9].Line[0], "�u�����܂���c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[6].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[7].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[8].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[9].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_04:	//�N�G�X�g�P -�񍐃V�[�� D�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u�����������ɂ�����ł����c�B�v");

			wsprintf(&g_StoryLine[1].Line[0], "�u�`�͂������肾���A\n �����܂������Ȃ�Ȃ�����Ȃ����I�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�ǂ��Ȃ��Ƃ�񂶂�I�I�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u����́A �킵�Ƃ��΂������\n��؂Ȏv���o�������񂶂�I�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u�����������璼��Ǝv�����̂Ɏc�O����I�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u�{���ɐ\���󂲂����܂���c�I�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_05:	//�N�G�X�g�P -A�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u��������A�������Ⴑ�̉������I\n�@���ɉ��������́`�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u���̃I���S�[���͂ȁA�킵���Ⴂ�����\n�@�΂����񂩂����������̂Ȃ񂶂�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u���y�D���̂킵�̂��߂�\n�@���̃I���S�[���𔃂��Ă���Ăȁ`�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u����͂������ꂵ�������́`�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u����Ȏv���o��\n�@���̃I���S�[���ɂ�������ł��ˁB�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u���肪�Ƃ��A�C���l����B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			break;

		case TYPESTORYFONT_06:	//�N�G�X�g�P -B&C�����N-\n
			wsprintf(&g_StoryLine[0].Line[0], "�u���̉��F�͉��������ȁ`�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u���X�����Ⴄ�C�����邪\n �܂��A�d���Ȃ����́`�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u���͂��̃I���S�[���͂ȁA�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u�킵���Ⴂ����\n ���΂����񂩂����������̂Ȃ񂶂�B�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u���y�D���̂킵�̂��߂�\n ���̃I���S�[���𔃂��Ă���Ăȁ`�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u����͂��������������񂶂�B�v");
			wsprintf(&g_StoryLine[6].Line[0], "�u���Ⴉ��̂ǂ���̉���\n �����Ȃ��Ȃ��Ă��܂����̂��߂����ĂȁB�v");
			wsprintf(&g_StoryLine[7].Line[0], "�u�����Ȃ璼���Ă����Ǝv�����񂶂Ⴊ�A\n �c�O���̂��c�B�v");
			wsprintf(&g_StoryLine[8].Line[0], "�u�����܂���c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[6].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[7].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[8].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_07:	//�N�G�X�g�P -D�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u�`�͂������肾���A\n �����܂������Ȃ�Ȃ�����Ȃ����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�ǂ��Ȃ��Ƃ�񂶂�I�I�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u����́A �킵�Ƃ��΂������\n��؂Ȏv���o�������񂶂�I�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u�����������璼��Ǝv�����̂Ɏc�O����I�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u�{���ɐ\���󂲂����܂���c�I�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_0;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

			//==============================================================================
			//�N�G�X�g�Q
			//==============================================================================

		case TYPESTORYFONT_11:	//�N�G�X�g2 -�˗��V�[��-
			wsprintf(&g_StoryLine[0].Line[0], "�u����𒼂��Ă���܂��񂩁H�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�͂��I�A���C�����������I\n ����́A���v�ł��ˁB�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�����Ȃ�ł�\n �����Ȃ��Ȃ��Ă��܂�����ł��B�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u�S���Ȃ�������������񂩂�������\n ��؂Ȏ��v�Ȃ�ł��B�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u����́A��ςł��ˁB\n �ӔC�������Ē������Ē����܂��I�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u�������您�͂��������܂��ˁB�v");
			wsprintf(&g_StoryLine[6].Line[0], "�u���肢���܂��B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[6].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			break;

		case TYPESTORYFONT_12:	//�N�G�X�g2 -�񍐃V�[�� A�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u���҂������܂����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�����ɒ���܂������H�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�͂��I\n ��������ƒ������Ă��������܂����I�v");

			wsprintf(&g_StoryLine[3].Line[0], "�u�I�I�A�����I�����Ă�I�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u����́A����������񂩂�����\n ��؂Ȏ��v�Ȃ�ł��B�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u�{���ɂ��肪�Ƃ��A�C���l����I�v");
			wsprintf(&g_StoryLine[6].Line[0], "�u��؂Ȏv���o�𒼂��Ă悩�����ł��I�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[6].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_13:	//�N�G�X�g2 -�񍐃V�[�� B&C�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u���҂������܂����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�����ɒ���܂������H�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�ꉞ�������̂ł����c�B�v");

			wsprintf(&g_StoryLine[3].Line[0], "�u�ςȂƂ��낪���邯�ǁA�����Ă�ˁc�B�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u���肪�Ƃ��������܂��c�B�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u�����ɒ����Ȃ����݂܂���ł����c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_14:	//�N�G�X�g2 -�񍐃V�[�� D�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u���҂������܂����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�����ɒ���܂������H�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�����������ɂ�����ł����c�B�v");

			wsprintf(&g_StoryLine[3].Line[0], "�u�܂����������Ȃ������I\n �ǂ����Ă����񂾂�I�I�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u����������񂩂�����\n ��؂Ȏ��v�Ȃ̂Ɂc�B�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u�{���ɐ\���󂲂����܂���c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_15:	//�N�G�X�g2 -A�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u�I�I,�����I�����Ă�I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u����́A����������񂩂�����\n ��؂Ȏ��v�Ȃ�ł��B�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�{���ɂ��肪�Ƃ��A�C���l����I�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u��؂Ȏv���o�𒼂��Ă悩�����ł��I�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_16:	//�N�G�X�g2 -B&C�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u�ςȂƂ��낪���邯�ǁA�����Ă�ˁc�B�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u���肪�Ƃ��������܂��c�B�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�����ɒ����Ȃ����݂܂���ł����c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_17:	//�N�G�X�g2 -D�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u�܂����������Ȃ������I\n �ǂ����Ă����񂾂�I�I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u����������񂩂�����\n ��؂Ȏ��v�Ȃ̂Ɂc�B�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�{���ɐ\���󂲂����܂���c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_1;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;


			//======================================================================================
			//�N�G�X�g�R
			//================����������������������������������������������������������������������

		case TYPESTORYFONT_21:	//�N�G�X�g3 -�˗��V�[��-
			wsprintf(&g_StoryLine[0].Line[0], "�u����𒼂��Ă���܂��񂩁H�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�͂��I�A���C�����������I\n�@����́A�[���}�C�l�`�ł��ˁB�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�����Ȃ�ł��A\n �����Ȃ��Ȃ��Ă��܂�����ł��B�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u�����z���Ă��܂����e�F����������\n ��؂ȃ[���}�C�l�`�Ȃ�ł��B�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u����́A��ςł��ˁB\n �ӔC�������Ē������Ē����܂��I�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u�������您�͂��������܂��ˁB�v");
			wsprintf(&g_StoryLine[6].Line[0], "�u���肢���܂��B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[6].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			break;

		case TYPESTORYFONT_22:	//�N�G�X�g�P-�񍐃V�[�� A�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u���҂������܂����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�����ɒ���܂������H�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�͂��I\n ��������ƒ������Ă��������܂����I�v");

			wsprintf(&g_StoryLine[3].Line[0], "�u����[���ʂ肾�[�I�����I�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u���肪�Ƃ��������܂����I�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u���ł��������ėǂ������ł��I�v");
			wsprintf(&g_StoryLine[6].Line[0], "�u�����������̂�����΂܂��A\n ���X�ւ��z�����������I�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[6].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_23:	//�N�G�X�g�P-�񍐃V�[�� B&C�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u���҂������܂����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�����ɒ���܂������H�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�ꉞ�������̂ł����c�B�v");

			wsprintf(&g_StoryLine[3].Line[0], "�u�������ǁA�Ȃ񂩕ρc�B�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u���肪�Ƃ��������܂����c�B�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u�����ɒ����Ȃ����݂܂���c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_24:	//�N�G�X�g�P-�񍐃V�[�� D�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u���҂������܂����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�����ɒ���܂�����?�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�����܂���c�őP�͐s�������̂ł����c�v");

			wsprintf(&g_StoryLine[3].Line[0], "�u�����ĂȂ������I�I�v");
			wsprintf(&g_StoryLine[4].Line[0], "�u�e�F�Ƃ̑�؂Ȏv���o�������̂ɁI�I�v");
			wsprintf(&g_StoryLine[5].Line[0], "�u�{���ɐ\���󂲂����܂���c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;

			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[4].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[5].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_25:	//�N�G�X�g3 -A�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u����[���ʂ肾�[�I�����I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u���肪�Ƃ��������܂����I�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u���ł��������ėǂ������ł��I�v");
			wsprintf(&g_StoryLine[3].Line[0], "�u�����������̂�����΂܂��A\n ���X�ւ��z�����������I�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			g_StoryLine[3].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_26:	//�N�G�X�g3 -B&C�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u�������ǁA�Ȃ񂩕ρc�B�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u���肪�Ƃ��������܂����c�B�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�����ɒ����Ȃ����݂܂���c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;

		case TYPESTORYFONT_27:	//�N�G�X�g3 -D�����N-
			wsprintf(&g_StoryLine[0].Line[0], "�u�����ĂȂ������I�I�v");
			wsprintf(&g_StoryLine[1].Line[0], "�u�e�F�Ƃ̑�؂Ȏv���o�������̂ɁI�I�v");
			wsprintf(&g_StoryLine[2].Line[0], "�u�{���ɐ\���󂲂����܂���c�B�v");

			//�e�N�X�`���̐ݒ�
			g_StoryLine[0].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[1].nTex = FLONTPOLYGONTEXTURE_MESSAGE_NPC_2;
			g_StoryLine[2].nTex = FLONTPOLYGONTEXTURE_MESSAGE_PLAYER;
			break;
		}

		//UI�̐ݒ�
		SetFlontPolygon(FLONTPOLYGONTEXTURE_FONT_BG, D3DXVECTOR3(640.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH, 180.0f);

		//�\����Ԃ̐ݒ�
		for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
		{
			if (nCntLine == 0)
			{
				g_StoryLine[nCntLine].bUse = true;

				//�摜�̐ݒ�
				g_StoryLine[nCntLine].nIdx = SetFlontPolygon(g_StoryLine[nCntLine].nTex, D3DXVECTOR3(250.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 130.0f);
				g_nGetIndx = g_StoryLine[nCntLine].nIdx;
			}
			else
			{
				g_StoryLine[nCntLine].bUse = false;
			}
		}
	}
}

//=============================================================================
// �X�g���[��Ԃ̎擾
//=============================================================================
bool GetStoryFont(void)
{
	return g_bStory;
}

//=============================================================================
// �X�g���[�j��
//=============================================================================
void DeleteStoryFont(void)
{
	//�ϐ��錾
	int nCntLine;

	//�ϐ��̏�����
	g_StoryFont.type = TYPESTORYFONT_MAX;
	g_StoryFont.bUse = false;
	g_nGetIndx = 0;

	for (nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_StoryLine[nCntLine].bUse == true)
		{
			g_StoryLine[nCntLine].Line[0] = {};
			g_StoryLine[nCntLine].nTex = -1;
			g_StoryLine[nCntLine].nIdx = 0;
			g_StoryLine[nCntLine].bUse = false;
		}
	}
	g_CntStoryLine = 0;
	g_bStory = false;
}