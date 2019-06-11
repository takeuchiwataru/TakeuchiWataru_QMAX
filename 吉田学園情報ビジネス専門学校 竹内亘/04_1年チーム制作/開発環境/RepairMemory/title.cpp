//=============================================================================
//
// �^�C�g����� [title.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "meshcylinder.h"
#include "meshwall.h"
#include "meshfield.h"
#include "shadow.h"
#include "xobject.h"
#include "start.h"
#include "fade.h"
#include "flontpolygon.h"
#include "titleanim.h"

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
	int nIndx = 0;

	//�ϐ��̏�����
	g_nCntTime = 0;
	g_nCntTimeTitle = 0;

	//�֐��Ăяo��
	InitCamera();		//�J����
	InitMeshCylinder();	//��
	InitMeshWall();		//��
	InitMeshField();	//�n��
	InitShadow();		//�e
	InitXObject();		//�I�u�W�F�N�g
	InitStart();		//�X�^�[�g�{�^��
	InitFlontPolygon();	//�t�����g�|���S��

	//�J����
	SetCamera(D3DXVECTOR3(0.0f, 550.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -2000.0f, CAMERATYPE_TITLE);

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

	//�^�C�g��


	//�{�^���̃Z�b�g
	SetEnter(D3DXVECTOR3(630.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetTitleAnim();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitTitle(void)
{
	//�֐��Ăяo��	
	UninitCamera();			//�J����
	UninitMeshCylinder();	//��
	UninitMeshWall();		//��
	UninitMeshField();		//�n��
	UninitShadow();			//�e
	UninitXObject();		//�I�u�W�F�N�g
	UninitStart();			//�X�^�[�g�{�^��
	UninitFlontPolygon();	//�t�����g�|���S��

	DeleteTitleAnim();
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateTitle(void)
{
	//���Ԃ����Z����
	g_nCntTime++;
	g_nCntTimeTitle++;

	TitleAnim pTitleAnim = GetTitleAnim();

	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();

	//�֐��Ăяo��
	UpdateCamera();			//�J����
	UpdateMeshCylinder();	//��
	UpdateMeshWall();		//��
	UpdateMeshField();		//�n��
	UpdateShadow();			//�e
	UpdateXObject();		//�I�u�W�F�N�g
	UpdateStart();			//�X�^�[�g�{�^��
	UpdateFlontPolygon();	//�t�����g�|���S��
	
	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
	{
		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			if (pTitleAnim.nCntAnimNum != 118)
			{
				SetTitleAnimNum();
			}
			else
			{
				//�X�^�[�g�{�^���̐ݒ�
				SetPush(STARTSTRACT_ENTER);

				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_STORY);
				PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
			}
		}
	}
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawTitle(void)
{
	//�֐��Ăяo��
	SetUpCamera();		//�J����
	DrawMeshCylinder();	//��
	DrawMeshWall();		//��
	DrawMeshField();	//�n��
	DrawShadow();		//�e
	DrawXObject();		//�I�u�W�F�N�g
	DrawStart();		//�X�^�[�g�{�^��
	DrawFlontPolygon();	//�t�����g�|���S��
}