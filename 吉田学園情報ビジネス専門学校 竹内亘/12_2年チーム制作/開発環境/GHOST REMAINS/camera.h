//=============================================================================
//
// �J�������� [camera.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCamera
{
public:
	typedef enum
	{//���f���̎��
		STATE_NONE = 0,	//�������Ȃ�
		STATE_GAME,		//�Q�[��
		STATE_MOVIE,		//���[�r�[

	}CAMERA_STATE;
	typedef enum
	{//���f���̎��
		VIEW_IGNORE = 0,	//���ɂ��ւ��Ȃ�
		VIEW_FOLLOW,		//�Ǐ]
		VIEW_WATCH,			//�ǂ킸�Ɍ��邾��

	}CAMERA_VIEW;
	typedef enum
	{//���f���̎��
		SCENE_VIEW_NORMAL = 0,	//�ʏ�ʂ蓮��
		SCENE_VIEW_STOP,		//���f���̂ݎ~�܂�

	}SCENE_VIEW;
	typedef enum
	{//���f���̎��
		SCENE_TYPE_NO = 0,	//�߂�@�ԈႦ�悤�̑Ώ�
		SCENE_TYPE_BOSS,	//�{�X�O�̃V�[��

	}SCENE_TYPE;
	typedef struct
	{
		CAMERA_STATE	state;		//���
		CAMERA_VIEW		ViewC;		//������ �J����
		SCENE_VIEW		ViewS;		//������ �J�����ȊO(���f����)
		SCENE_TYPE		scene;			//���̃V�[����

		int				nCntState;		//���[�r�[�̐i�s�x
		int				nCntTime;		//�V�[���̃t���[�����L�^
		D3DXVECTOR3		*pChar;		//���̃L������Ǐ]���邩
		D3DXVECTOR3		*pMove;		//���̃L������Ǐ]���邩
	}Info;
	CCamera();
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Reset(void);
	bool DrawCamera(D3DXVECTOR3 &pos, float fLength);
	void SetCamera(void);
	void SetScene(SCENE_TYPE type);
	void UpdateScene(void);
	static Info &GetInfo(void) { return m_info; };

	void SetnQuake(int nQuake, float fQuake) { m_nQuake = nQuake; m_fQuake = fQuake; };
	float *&GetpDistance(void) { return m_pDistance; };
	float &GetfDRot(void) { return m_fDRot; };
	D3DXVECTOR3 &GetRot(void) { return m_rot; };
	D3DXVECTOR3 &GetposR(void) { return m_posR; };

private://*****************************************************************************
	static Info	m_info;

		//�ϐ��錾//***********************************************************************
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_vecU;			
	D3DXVECTOR3 m_goal;			//�������ʒu
	D3DXVECTOR3 m_targetpos;	//�Ǐ]����ꏊ
	D3DXVECTOR3 m_rot;			//�p�x
	D3DXVECTOR3 m_addpos;			//�J�����̐����ړ���
	float		m_fDistance;		//�J�����ƒ����_�̋���
	float		*m_pDistance;		//�J�����ƒ����_�̋����̖ړI�l
	float		m_fGMagnification;	//�ړI�ɂ����܂ł̔{��
	float		m_fQuake;			//�h��̑傫��
	int			m_nQuake;			//�h��
	float		m_fDRot;			//���������̖ړI�̊p�x	

	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
};

#endif
