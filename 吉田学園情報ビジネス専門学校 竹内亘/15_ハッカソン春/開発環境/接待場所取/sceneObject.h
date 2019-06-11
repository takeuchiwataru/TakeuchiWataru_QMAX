//=============================================================================
//
// �V�[���I�u�W�F�N�g���� [sceneObject.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//���f���N���X�̒�`
//*********************************************************************
class CSceneObject
{
public:
	CSceneObject();
	~CSceneObject();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff);	//TEXTURE�����蓖�Ă�
	void SetParent(CSceneObject *pModel);
	D3DXMATRIX GetMtxWorld(void);
	void SetMtxWorld(D3DXMATRIX MtxWorld);

	void VtxMinMaxSet(void);

	D3DXVECTOR3 VtxMin(void) { return m_VtxMinModel; }
	D3DXVECTOR3 VtxMax(void) { return m_VtxMaxModel; }

	void Setpos(D3DXVECTOR3 pos);
	void Setrot(D3DXVECTOR3 rot);
	D3DXVECTOR3 Getrot(void);
	D3DXVECTOR3 GetPos(void);

	void SetbShadow(bool bShadow);


	//�����o�ϐ�
private:
	D3DXVECTOR3				m_pos;					//�ʒu
	D3DXVECTOR3				m_rot;					//����


	LPD3DXMESH				m_pMeshModel;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMatModel;		//�}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9		*m_pTextureModel;		//�e�N�X�`���ւ̃|�C���^
	DWORD					m_nNumMatModel = 0;		//�}�e���A�����̐�
	D3DXVECTOR3				m_VtxMinModel, m_VtxMaxModel;		//���f���̍ŏ��l�A�ő�l
	D3DXMATRIX				m_mtxWorld;				//���[���h�}�g���b�N�X
	CSceneObject			*m_pParent;				//�e���f���ւ̃|�C���^

	bool					m_bShadow;				//�e�̃t���O
};


#endif