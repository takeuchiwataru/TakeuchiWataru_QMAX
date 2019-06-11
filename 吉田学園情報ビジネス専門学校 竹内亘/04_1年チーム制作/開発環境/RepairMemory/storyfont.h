//=============================================================================
//
// �X�g�[���[�t�H���g���� [storyfont.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _STORYFONT_H_
#define _STORYFONT_H_

#include "main.h"

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
typedef enum
{
	// �N�G�X�g1
	TYPESTORYFONT_01 = 0,	//�N�G�X�g�P-�˗��V�[��
	TYPESTORYFONT_02,		//�N�G�X�g�P-�񍐃V�[�������NA
	TYPESTORYFONT_03,		//�N�G�X�g�P-�񍐃V�[�������NB&C
	TYPESTORYFONT_04,		//�N�G�X�g�P-�񍐃V�[�������ND
	TYPESTORYFONT_05,		//�N�G�X�g�P-�����NA�V�[��
	TYPESTORYFONT_06,		//�N�G�X�g�P-�����NB&C�V�[��
	TYPESTORYFONT_07,		//�N�G�X�g�P-�����ND�V�[��

	// �N�G�X�g�Q
	TYPESTORYFONT_11,		//�N�G�X�g2-�˗��V�[��
	TYPESTORYFONT_12,		//�N�G�X�g2-�񍐃V�[��A�����N
	TYPESTORYFONT_13,		//�N�G�X�g2-�񍐃V�[��B&C�����N
	TYPESTORYFONT_14,		//�N�G�X�g2-�񍐃V�[��D�����N
	TYPESTORYFONT_15,		//�N�G�X�g2-�����N�`�V�[��
	TYPESTORYFONT_16,		//�N�G�X�g2-�����NB&C�V�[��
	TYPESTORYFONT_17,		//�N�G�X�g2-�����ND�V�[��

	// �N�G�X�g�R
	TYPESTORYFONT_21,		//�N�G�X�g3-�˗��V�[��
	TYPESTORYFONT_22,		//�N�G�X�g3-�񍐃V�[��A�����N
	TYPESTORYFONT_23,		//�N�G�X�g3-�񍐃V�[��B&C�����N
	TYPESTORYFONT_24,		//�N�G�X�g3-�񍐃V�[��D�����N
	TYPESTORYFONT_25,		//�N�G�X�g3-�����NA�V�[��
	TYPESTORYFONT_26,		//�N�G�X�g3-�����NB&C�V�[��
	TYPESTORYFONT_27,		//�N�G�X�g3-�����ND�V�[��
	TYPESTORYFONT_MAX,
}TYPESTORYFONT;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	TYPESTORYFONT	type;			//�t�H���g�̃^�C�v
	bool			bUse;			//�g�p���Ă��邩�ǂ���
}StoryFont;

typedef struct
{
	char			Line[256];		//�i�[���镶����
	int				nTex;			//�e�N�X�`���̔ԍ�
	int				nIdx;			//�|���S����ID��ݒ�
	bool			bUse;			//�g�p���Ă��邩�ǂ���
}StoryLine;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitStoryFont(void);
void UninitStoryFont(void);
void UpdateStoryFont(void);
void DrawStoryFont(void);

void SetStoryFont(TYPESTORYFONT type);
bool GetStoryFont(void);

void DeleteStoryFont(void);

#endif