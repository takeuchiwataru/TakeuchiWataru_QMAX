//=============================================================================
//
// �I�u�W�F�N�gBG���� [objectBG.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _BALL_H_
#define _BALL_H_

#include "main.h"
#include "scene.h"
#include "sceneObject.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************
//class CModel;
class CSceneObject;
class CMeshOrbit;

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
class CBall : public CScene //�h���N���X
{
public:
	//���f���̎��
	typedef enum
	{
		MODELTYPE_BALL = 0,	//�r�� 0 ��
		MODELTYPE_MAX,			//�ő吔
	}MODELTYPE;

	CBall();
	~CBall();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CBall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, MODELTYPE type, int nCollision);
	static HRESULT Load(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	int GetTryTimer(void);

	//�n�ʂƂ̓����蔻��
	void CollisitionGround(void);

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
	int							m_nCollision;		// �����蔻���ONOFF
	int m_nTimer;
	int m_nTryTimer;
	int m_nPlusX;
	int m_nPlusZ;
	bool						m_bJump;				//�W�����v���
	bool m_bHit;
	bool m_bendBall;

public:
	CSceneObject				*m_pObject;
	CMeshOrbit					*m_pMeshOrbit;					//�O�Տ��
};

#endif