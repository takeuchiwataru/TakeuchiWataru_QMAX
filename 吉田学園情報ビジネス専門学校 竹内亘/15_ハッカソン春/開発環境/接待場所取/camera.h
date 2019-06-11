//=============================================================================
//
// �J�������� [camera.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*********************************************************************
//�J�����N���X�̒�`
//*********************************************************************
class CCamera //��{�N���X
{
public:
	typedef struct
	{
		D3DXVECTOR3 posV;			//���_
		D3DXVECTOR3 posR;			//�����_
		D3DXVECTOR3 posU;			//������x�N�g��
		D3DXVECTOR3 posVDest;
		D3DXVECTOR3 posRDest;
		D3DXVECTOR3 rotCamera;		//����
		D3DXVECTOR3 rotDest;
		D3DXVECTOR3 DiffAngle;
		D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X(�e���r)
		D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X(�J�����}��)
		int nCounterAngle;			//�J�����A���O�����ς��J�E���^�[
	}Camera;

	typedef enum
	{
		CAMERASIDE_NONE = 0,		// ����
		CAMERASIDE_LEFT,			// ��
		CAMERASIDE_RIGHT,			// �E
		CAMERASIDE_MAX
	}CAMERASIDE;

	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	Camera GetCamera(void);

	//�����o�ϐ�
private:
	Camera		m_Camera;			//�J�����̏��
	float		fLength;			//����
	CAMERASIDE	m_CameraSideState;	//�J�����̉E��
	int			m_nCameraCnt;		//�J�����̃J�E���g
	int			m_nImpactCnt;		//�J�����̃J�E���g
	bool		m_bPressEnter;		//�t���O
};

#endif