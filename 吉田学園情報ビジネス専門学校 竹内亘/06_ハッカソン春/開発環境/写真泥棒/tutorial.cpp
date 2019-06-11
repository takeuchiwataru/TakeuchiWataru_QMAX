//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "tutorial.h"
#include "sky.h"
#include "field.h"
#include "fade.h"
#include "pressenter.h"
#include "input.h"
#include "sound.h"
#include "tutorialbg.h"
#include "camera.h"
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//***************************************************************************** 
TUTORIAL_STATE g_TutorialState;		//���
int g_MoveTimer;	//�ړ��̃^�C�}�[
int g_nCntMove;	//�ړ��̃J�E���^�[

//=============================================================================
// ����������
//=============================================================================
void InitTutorial(void)
{
	g_nCntMove = 0;							//�ړ��J�E���^�[��������
	g_MoveTimer = 0;						//�ړ��^�C�}�[��������
	g_TutorialState = TUTORIAL_STATE_NONE;	//��Ԃ̏�����

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�`���[�g���A��bg�̏���������
	InitTutorialBG();

	// ��̏���������
	InitSky();

	// �t�B�[���h�̏���������
	InitField();

	SetTutorialBG(D3DXVECTOR3(0.0f, 150.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetTutorialBG(D3DXVECTOR3(1500.0f, 150.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

}
//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{
	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�`���[�g���A��bg�̏I������
	UninitTutorialBG();

	// ��̏I������
	UninitSky();

	// �t�B�[���h�̏I������
	UninitField();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	FADE fade;
	fade = GetFade();

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	//�`���[�g���A��bg�̍X�V����
	UpdateTutorialBG();

	// ��̍X�V����
	UpdateSky();

	// �t�B�[���h�̍X�V����
	UpdateField();

	//�J�����̎擾
	Camera *pCamera = GetCamera();

	switch (g_TutorialState)
	{
	case TUTORIAL_STATE_NONE:	//�ʏ���
		pCamera->posV.x -= 0.0f;
		pCamera->posV.z -= 0.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength.x;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength.z;
		break;
	case TUTORIAL_STATE_MOVE:	//�ړ����


		pCamera->posV.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posV.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength.x;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength.z;
		g_MoveTimer++;

		if (g_MoveTimer == 150.0f)
		{//�J�E���g���W�T�ɂȂ����ꍇ
			g_TutorialState = TUTORIAL_STATE_NONE;		//�ʏ��Ԃɖ߂�
			g_nCntMove++;								//�ړ��J�E���^�[�𑫂�
			g_MoveTimer = 0;							//�^�C�}�[������������
		}

		break;
	case TUTORIAL_STATE_REMOVE:	//�߂���

		pCamera->posV.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posV.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength.x;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength.z;
		g_MoveTimer++;
		if (g_MoveTimer == 150.0f)
		{//�J�E���g���W�T�ɂȂ����ꍇ
			g_TutorialState = TUTORIAL_STATE_NONE;		//�ʏ��Ԃɖ߂�
			g_nCntMove--;								//�ړ��J�E���^�[�𑫂�
			g_MoveTimer = 0;							//�^�C�}�[������������
		}
		break;
	}
	if (g_TutorialState == TUTORIAL_STATE_NONE)
	{//�ʏ��Ԃ̏ꍇ
		if (g_nCntMove == 0)
		{
			if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoyPadTrigger(DIJS_BUTTON_20, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_12, 0) == true)
			{
				g_TutorialState = TUTORIAL_STATE_MOVE;
			}
		}
		if (g_nCntMove == 1)
		{
			if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoyPadTrigger(DIJS_BUTTON_21, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_13, 0) == true)
			{
				g_TutorialState = TUTORIAL_STATE_REMOVE;
			}
		}
	}
	if (g_nCntMove == 1)
	{
		for (int nCntJoyPad = 0; nCntJoyPad < 8; nCntJoyPad++)
		{
			if (GetJoyPadTrigger(nCntJoyPad, 0) == TRUE && fade == FADE_NONE)
			{
				SetFade(MODE_GAME);
			}
		}
		if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
		{// ����{�^���������ꂽ
			SetFade(MODE_GAME);
		}
	}
	//if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE && fade == FADE_NONE)
	//{// ����{�^���������ꂽ
	//	SetFade(MODE_GAME);
	//}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	//�J�����̐ݒu
	SetCamera();

	// ��̕`�揈��
	DrawSky();

	// �t�B�[���h�̕`�揈��
	DrawField();

	//�`���[�g���A��bg�̕`�揈��
	DrawTutorialBG();
}