//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "title.h"
#include "titlelogo.h"
#include "pressenter.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

#include "camera.h"
#include "light.h"
#include "field.h"
#include "model.h"
#include "sky.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int            g_nCounterTitle;          // �����L���O��ʂɑJ�ڂ���^�C�~���O

//=============================================================================
// ����������
//=============================================================================
void InitTitle(void)
{
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �t�B�[���h�̏���������
	InitField();

	// ���f���̏���������
	InitModel();

	// ��̏���������
	InitSky();

	// �^�C�g�����S�̏���������
	InitTitleLogo();

	g_nCounterTitle = 0;   // �J�E���^�[��0��
}
//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// �t�B�[���h�̏I������
	UninitField();

	// ���f���̏I������
	UninitModel();

	// ��̏I������
	UninitSky();

	// �^�C�g�����S�̏I������
	UninitTitleLogo();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	// �t�B�[���h�̍X�V����
	UpdateField();

	// ���f���̍X�V����
	UpdateModel();

	// ��̍X�V����
	UpdateSky();

	// �^�C�g�����S�̍X�V����
	UpdateTitleLogo();

	FADE fade;
	fade = GetFade();
	bool *disp;
	disp = GetDispPressEnter();

	g_nCounterTitle++;

	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE && *disp == true || GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE && fade == FADE_NONE && *disp == true)
	{// ����{�^���������ꂽ
		SetFade(MODE_TUTORIAL);
		PlaySound(SOUND_LABEL_SE_DECIDE);
	}

	for (int nCntPad = 0; nCntPad < 8; nCntPad++)
	{
		if (GetJoyPadTrigger(nCntPad, 0) == TRUE &&  fade == FADE_NONE && *disp == true)
		{
			SetFade(MODE_TUTORIAL);
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
	}

	if (g_nCounterTitle % 1800 == 0 && fade == FADE_NONE)
	{// ��莞�Ԃ�����
		SetFade(MODE_RANKING);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	// �J�����̕`�揈��
	SetCamera();

	// �t�B�[���h�̕`�揈��
	DrawField();

	// ���f���̕`�揈��
	DrawModel();

	// ��̕`�揈��
	DrawSky();

	// �^�C�g�����S�̕`�揈��
	DrawTitleLogo();
}