//=========================================================================================================================
//
// �J�������� [camera.h]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// �J�����̍\����
//*************************************************************************************************************************
typedef enum
{
	CAMERATYPE_NONE = 0,
	CAMERATYPE_TITLE,
	CAMERATYPE_GAME_SEARCH,
	CAMERATYPE_GAME_PUZZLE,
	CAMERATYPE_RESULT,
	CAMERATYPE_RANKING,
	CAMERATYPE_MAX,
}CAMERATYPE;

typedef struct
{
	D3DXVECTOR3 posV;				// ���_
	D3DXVECTOR3 posVDest;			// �ڕW���_
	D3DXVECTOR3 posR;				// �����_
	D3DXVECTOR3 posRDest;			// �ڕW�����_
	D3DXVECTOR3 vecU;				// ������x�N�g��
	D3DXVECTOR3	rot;				// �p�x
	float		fDistance;			// ����
	float		fResetRot;			// ���Z�b�g����
	float		fResetRotDest;		// �ڕW���Z�b�g����
	bool		bReset;				// ���Z�b�g
	D3DXMATRIX	mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	mtxView;			// �r���[�}�g���b�N�X
	CAMERATYPE type;
}Camera;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitCamera(void);				// �J��������������
void UninitCamera(void);			// �J�����I������
void UpdateCamera(void);			// �J�����X�V����
void SetUpCamera(void);				// �J�����ݒ菈��	// �`���

void SetCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 rot, float fDistance, CAMERATYPE type);	// �J�����ݒ菈��
Camera *GetCamera(void);			// �J�����擾����

#endif
