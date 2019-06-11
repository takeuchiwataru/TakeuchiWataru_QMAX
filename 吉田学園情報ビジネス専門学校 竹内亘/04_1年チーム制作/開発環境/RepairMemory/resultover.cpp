//=============================================================================
//
// ���U���g[ �Q�[���I�[�o�[ ]��� [result.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "resultover.h"
#include "main.h"
//#include "sound.h"
#include "input.h"
#include "fade.h"
#include "start.h"
#include "flontpolygon.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int g_nCntTimeResultOver;	//�Q�[����ʐ؂�ւ��J�E���^�[

//=============================================================================
// ���U���g����������
//=============================================================================
void InitResultOver(void)
{
	g_nCntTimeResultOver = 0;	//�J�E���^�[�̏�����

	InitFlontPolygon();		//�t�����g�|���S��
	InitStart();			//�G���^�[�L�[

	//�Q�[���I�[�o�[���S
	SetFlontPolygon(FLONTPOLYGONTEXTURE_GAME_OVER, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000.0f, 300.0f);

	//�G���^�[�L�[
	SetEnter(D3DXVECTOR3(1090.0f, 685.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================================================
// ���U���g�I������
//=============================================================================
void UninitResultOver(void)
{
	UninitFlontPolygon();	//�t�����g�|���S��
	UninitStart();			//�G���^�[�L�[
}

//=============================================================================
// ���U���g�X�V����
//=============================================================================
void UpdateResultOver(void)
{
	g_nCntTimeResultOver++;

	//�t�F�[�h�����擾����
	FADE g_fade;
	g_fade = GetFade();

	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
	{
		if (g_fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�T�E���h�Đ�
			//PlaySound(SOUND_LABEL_SE_ENTER);

			//�G���^�[�L�[�̏�ԕύX
			SetPush(STARTSTRACT_ENTER);

			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
	}

	if (g_nCntTimeResultOver == INTERVAL_TIME)
	{
		//�t�F�[�h���[�h�ݒ�
		SetFade(MODE_TITLE);
	}

	if (GetKeyboardTrigger(DIK_B) == true)
	{
		if (g_fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//StopSound(SOUND_LABEL_BGM003);

			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_GAME);
		}
	}

	UpdateFlontPolygon();	//�t�����g�|���S��
	UpdateStart();			//�G���^�[�L�[
}

//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void DrawResultOver(void)
{
	DrawFlontPolygon();		//�t�����g�|���S��
	DrawStart();			//�G���^�[�L�[
}