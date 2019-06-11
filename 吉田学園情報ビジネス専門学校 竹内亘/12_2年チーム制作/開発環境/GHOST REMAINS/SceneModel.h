#pragma once
//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PRIORITY		(0)
#define MAX_SWITCH			(4)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneModel : public CScene
{
public:
	typedef enum
	{
		//���[���@����
		MODEL_FENCE,	//��
		MODEL_STEEL,	//�S��
		//���[���@���S
		MODEL_STONE,	//��
		MODEL_STEEL_B,	//�S����
		//���[�h
		MODEL_BOX,		//�ؔ�
		MODEL_STONE_S,	//����
		//�G���g�����X
		
		MODEL_BROCK,	//�u���b�N
		MODEL_MFIELD,	//�ړ���
		MODEL_MFIELD2,	//�ړ���2
		MODEL_DFIELD,	//�����鏰
		MODEL_SPEAR,	//��
		MODEL_BUTTON,		//�{�^��
		MODEL_BUTTONFLOR,	//�{�^����
		MODEL_DROP_STONE,	//����
		MODEL_GOAL,		//�S�[��
		MODEL_WARP,		//�{�^��
		MODEL_NOLOOK,	//�{�^��

		MODEL_MAX
	}MODEL;
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_FADE,
		STATE_FADEIN,
		STATE_FADEOUT,
		STATE_MAX
	}STATE;
	CSceneModel(int nPrioryity = MODEL_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CSceneModel() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, DRAW_TYPE DrawType, bool bHit);
	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	static void	LoadModel(MODEL model, LPDIRECT3DTEXTURE9 &tex);					//���f���̐���
	static void UnLoadModel(void);				//Model���
	static void GetLength(MODEL model, D3DXVECTOR3 &length);
	static float GetHeight(MODEL model);

	D3DXVECTOR3			&GetPosition(void)				{ return m_pos; }
	D3DXVECTOR3			&GetRotation(void)				{ return m_rot; }
	void		BindTexture(LPDIRECT3DTEXTURE9 pTex)	{ m_pTex = pTex; }
	MODEL				&GetModel(void)					{ return m_Model; }
	CScene::DRAW_TYPE	&GetDrawType(void)				{ return m_DrawType; }


protected://*****************************************************************************
	//���f��//*********************************************************************
	static MODEL_DRAW *m_Model_Draw[MODEL_MAX];					//���f���ւ̃|�C���^


	//�ϐ��錾//***********************************************************************
	//D3DXMATRIX			m_mtxWorld;			//���[���h�}�g���b�N�X
	D3DXCOLOR			&GetColor(void)		{ return m_col; }
	LPDIRECT3DTEXTURE9	&GetTexture(void)	{ return m_pTex; }
	STATE				&GetState(void)		{ return m_state; }
	float				&GetfCntState(void) { return m_fCntState; }

private://*****************************************************************************
	//�ϐ��錾//***********************************************************************
	D3DXVECTOR3			m_pos;				//�ʒu
	D3DXVECTOR3			m_rot;				//����
	D3DXCOLOR			m_col;				//�F
	LPDIRECT3DTEXTURE9	m_pTex;				//�摜
	MODEL				m_Model;			//���f��
	CScene::DRAW_TYPE	m_DrawType;			// �`�悷����@(���Z�����Ȃ�)
	STATE				m_state;			//�g�p���@
	float				m_fCntState;		//STATE�Ǘ��p
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneObjct : public CSceneModel
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		USE_MAX
	}USE;
	CSceneObjct(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) { SetObjType(OBJTYPE_OBJ); };
	~CSceneObjct() {};

	HRESULT	Init(void);
	void	Update(void);
	void	Draw(void);
	void	DropUninit(void);
	void	DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky);		//�A�C�e���h���b�v�֐�
	bool	DropExplosion(void);										//�����h���b�v
	void	CSceneObjct::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL model, bool bHit, USE use, D3DXVECTOR3 speed, float fPlusRot, int nReturn, int nStop, int nCntReturn, int nNumber);

	static void SetObjField(void);
	static CScene	*CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
		   CScene	*Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	static void	CollisionAllR(void);
	void		CollisionR(CScene *pScene);
	static void	InitSwitch(bool bMode);

	USE		*GetUse(void) { return &m_use; }
	D3DXVECTOR3		&GetPosold(void) { return m_posold; }
	D3DXVECTOR3		&GetRotOld(void) { return m_rotold; }
	D3DXVECTOR3		&GetMove(void) { return m_move; }
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static bool m_bSwitch[MAX_SWITCH];	//�X�C�b�`
	USE m_use;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_rotold;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3	m_speed;
	float		m_fPlusRot;
	int			m_nReturn;
	int			m_nCntReturn;
	int			m_nStop;
	int			m_nCntStop;
	int			m_nNumber;
};

#endif
