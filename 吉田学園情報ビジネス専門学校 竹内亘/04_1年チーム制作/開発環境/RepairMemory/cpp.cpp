//=============================================================================
//
// �^�C�g����� [title.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "input.h"
//#include "sound.h"
#include "start.h"
#include "fade.h"
//#include "meshFild.h"
#include "polygon.h"
#include "flontpolygon.h"

//=============================================================================
// �}�N����`
//=============================================================================


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTitle = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nCntTime;										//�G�t�F�N�g�̃J�E���^�[
int g_nCntTimeTitle;								//�^�C�g�����Ԃ̃J�E���^�[

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitTitle(void)
{
	//�ϐ��錾
	g_nCntTime = 0;
	g_nCntTimeTitle = 0;

	//�֐��Ăяo��
	InitPolygon();		//�|���S��
	//InitMeshFild();		//���b�V���t�B�[���h
	InitStart();		//�X�^�[�g�{�^��
	InitFlontPolygon();	//�t�����g�|���S��

	//�^�C�g��
	SetFlontPolygon(0, D3DXVECTOR3(610.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1200.0f, 300.0f);

	//�{�^���̃Z�b�g
	SetEnter(D3DXVECTOR3(630.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitTitle(void)
{
	//�֐��Ăяo��
	UninitPolygon();			//�|���S��
	//UninitMeshFild();		//���b�V���t�B�[���h
	UninitStart();			//�X�^�[�g�{�^��
	UninitFlontPolygon();	//�t�����g�|���S��
	
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateTitle(void)
{
	//���Ԃ����Z����
	g_nCntTime++;
	g_nCntTimeTitle++;

	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();

	//�֐��Ăяo��
	UpdatePolygon();		//�|���S��
	//UpdateMeshFild();		//���b�V���t�B�[���h
	UpdateStart();			//�X�^�[�g�{�^��
	UpdateFlontPolygon();	//�t�����g�|���S��
	
	
	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�X�^�[�g�{�^���̐ݒ�
			SetPush(STARTSTRACT_ENTER);

			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_STORY);
			//PlaySound(SOUND_LABEL_SE_ENTER);	//���艹
		}
	}
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawTitle(void)
{
	//�֐��Ăяo��
	DrawPolygon();		//�|���S��
	//DrawMeshFild();	//���b�V���t�B�[���h
	DrawStart();		//�X�^�[�g�{�^��
	DrawFlontPolygon();	//�t�����g�|���S��
}