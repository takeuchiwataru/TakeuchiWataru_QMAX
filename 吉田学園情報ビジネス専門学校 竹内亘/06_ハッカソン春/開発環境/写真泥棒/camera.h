//=============================================================================
//
// �J�������� [camera.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef enum
{
	CAMERASTATE_NORMAL = 0, // �ʏ�̏��
	CAMERASTATE_MOVE,       // �ړ����Ă�����
	CAMERASTATE_SPIN,       // ���񂵂Ă�����
	CAMERASTATE_MAX
}CAMERASTATE;
typedef struct
{
	D3DXVECTOR3 posV;             // ���݂̎��_
  	D3DXVECTOR3 posR;             // ���݂̒����_
	D3DXVECTOR3 posVDest;         // �ړI�̎��_
	D3DXVECTOR3 posRDest;         // �ړI�̒����_
	D3DXVECTOR3 posVAdd;          // �ړI�̍��W
	D3DXVECTOR3 posRAdd;          // �ړI�̍��W
	D3DXVECTOR3 vecU;             // ������x�N�g��
	D3DXMATRIX  mtxProjection;    // �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX  mtxView;          // �r���[�}�g���b�N�X
	D3DVIEWPORT9 ViewPort;        // �r���[�|�[�g
	D3DXVECTOR3 rot;              // ���݂̌���
	D3DXVECTOR3 rotDest;          // �ړI�̌���
	CAMERASTATE state;            // ���
	float       rotDiff;          // �����̍���
	D3DXVECTOR3 fLength;          // ����
	float       fWaraparoundSpeed;// ��荞�ݑ��x
	int         nWaraparoundTime; // ��荞�ݑ҂�����
	int         nCounterTime;     // �҂����ԃJ�E���^�[
}Camera;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);

#endif
