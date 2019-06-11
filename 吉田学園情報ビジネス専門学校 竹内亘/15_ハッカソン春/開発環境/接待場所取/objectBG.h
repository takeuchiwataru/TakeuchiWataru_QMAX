//=============================================================================
//
// �I�u�W�F�N�gBG���� [objectBG.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _OBJECTBG_H_
#define _OBJECTBG_H_

#include "main.h"
#include "scene.h"
#include "sceneObject.h"
#include "shadow.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CSceneObject;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MATTEX	(20)
//*****************************************************************************
// �\����
//*****************************************************************************

//*********************************************************************
//�v���C���[�N���X�̒�`
//*********************************************************************
class CObjectBG : public CScene //�h���N���X
{
public:
	//���f���̎��
	typedef enum
	{
		MODELTYPE_BILL000 = 0,	//�r�� 0 ��
		MODELTYPE_BILL001,		//�r�� 1 ��
		MODELTYPE_BILL002,		//�r�� 2 ��
		MODELTYPE_BILL003,		//�r�� 3 ��
		MODELTYPE_FENCE000,		//�t�F���X
		MODELTYPE_TREE000,		//��
		MODELTYPE_TRUCK000,		//�g���b�N
		MODELTYPE_FINISH000,	//�t�B�j�b�V��
		MODELTYPE_MAX,			//�ő吔
	}MODELTYPE;
	//�ړ��̎��
	typedef enum
	{
		MOVETYPE_NONE = 0,
		MOVETYPE_NOT,
		MOVETYPE_X_MOVE,
		MOVETYPE_Y_MOVE,
		MOVETYPE_Z_MOVE,
		MOVETYPE_ROTATION_X,
		MOVETYPE_ROTATION_Y,
		MOVETYPE_ROTATION_Z,
		MOVETYPE_HOUSE,
		MOVETYPE_MAX
	}MOVETYPE;

	CObjectBG();
	~CObjectBG();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CObjectBG *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, MODELTYPE type, MOVETYPE nMovetype,int nCollision);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);

	bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private:
	//�����o�ϐ�
	D3DXVECTOR3					m_pos;				//�ʒu
	D3DXVECTOR3					m_posold;			//�O��̈ʒu
	D3DXVECTOR3					m_move;				//�ړ���
	D3DXVECTOR3					m_ModelMove;		//�ړ��̎d��
	D3DXVECTOR3					m_rot;				//����
	D3DXMATRIX					m_mtxWorld;			//���[���h�}�g���b�N�X
	MODELTYPE					m_Type;				//�^�C�v


	float						m_fDestAngle;		//�p�x
	float						m_fDiffAngle;		//����
	static LPD3DXMESH			m_pMesh[MODELTYPE_MAX];			//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[MODELTYPE_MAX];		//�}�e���A�����ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture[MODELTYPE_MAX];		//�e�N�X�`���ւ̃|�C���^
	static DWORD				m_nNumMat[MODELTYPE_MAX];		//�}�e���A�����̐�
	int							m_nCount;			// �J�E���^�[
	MOVETYPE					m_nMoveType;		// �����̎��
	int							m_nCollision;		// �����蔻���ONOFF
	CShadow						*m_pShadow;			// �e�ւ̃|�C���^
public:
	CSceneObject				*m_pObject;

};

#endif