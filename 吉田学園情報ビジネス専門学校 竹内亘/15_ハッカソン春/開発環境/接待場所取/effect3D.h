//=============================================================================
//
// �I�u�W�F�N�gBG���� [objectBG.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

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
class C3DEffect : public CScene //�h���N���X
{
public:
	//���f���̎��
	typedef enum
	{
		EFFECTTYPE_BILL000 = 0,	//�r�� 0 ��
		EFFECTTYPE_BILL001,		//�r�� 1 ��
		EFFECTTYPE_BILL002,		//�r�� 2 ��
		EFFECTTYPE_BILL003,		//�r�� 3 ��
		EFFECTTYPE_FENCE000,	//�t�F���X
		EFFECTTYPE_TREE000,		//��
		EFFECTTYPE_LEAF000,		//�t
		EFFECTTYPE_TRUCK000,	//�g���b�N
		EFFECTTYPE_BIN000,		//�r��
		EFFECTTYPE_MAX,			//�ő吔
	}EFFECTTYPE;

	C3DEffect();
	~C3DEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static C3DEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, EFFECTTYPE type,int nLife);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);

private:
	//�����o�ϐ�
	D3DXVECTOR3					m_pos;				//�ʒu
	D3DXVECTOR3					m_posold;			//�O��̈ʒu
	D3DXVECTOR3					m_move;				//�ړ���
	D3DXVECTOR3					m_ModelMove;		//�ړ��̎d��
	D3DXVECTOR3					m_rot;				//����
	D3DXMATRIX					m_mtxWorld;			//���[���h�}�g���b�N�X
	EFFECTTYPE					m_Type;				//�^�C�v

	float						m_fDestAngle;		//�p�x
	float						m_fDiffAngle;		//����

	static LPD3DXMESH			m_pMesh[EFFECTTYPE_MAX];			//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[EFFECTTYPE_MAX];		//�}�e���A�����ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture[EFFECTTYPE_MAX];		//�e�N�X�`���ւ̃|�C���^
	static DWORD				m_nNumMat[EFFECTTYPE_MAX];		//�}�e���A�����̐�

	int							m_nCount;			// �J�E���^�[
	int							m_nLife;			// ������܂ł̃��C�t
	CShadow						*m_pShadow;			// �e�ւ̃|�C���^
public:
	CSceneObject				*m_pObject;
};

#endif