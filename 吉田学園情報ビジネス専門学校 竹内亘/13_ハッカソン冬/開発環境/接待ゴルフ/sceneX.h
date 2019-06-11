//=============================================================================
//
// ���f������ [sceneX.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//�V�[��X�N���X�̒�`
//*********************************************************************
class CSceneX : public CScene //�h���N���X
{
public:
	typedef struct
	{
		DWORD nNumMat = 0;						//�}�e���A�����̐�
		D3DXVECTOR3 pos;						//�ʒu
		D3DXVECTOR3 rot;						//����
		D3DXMATRIX	mtxWorld;					//���[���h�}�g���b�N�X
		float fShadow;							//�e�̑傫��
		int nIdxShadow;							//�e�̃C���f�b�N�X
		int nType;								//���f���̎��
		bool bUse;								//�g�p���Ă��邩
		D3DXVECTOR3 VtxMinModel, VtxMaxModel;	//���f���̍ŏ��l�A�ő�l
	} MODEL;

	CSceneX();
	~CSceneX();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	void Setrot(D3DXVECTOR3 rot);
	MODEL *GetModel(void);
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, MODEL **pModel*/);
	void SetModel(D3DXVECTOR3 pos, int nType);
	static CSceneX *Create(D3DXVECTOR3 pos);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture, LPD3DXMESH Mesh, LPD3DXBUFFER Buff);	//TEXTURE�����蓖�Ă�

	//�����o�ϐ�
private:
	LPD3DXMESH m_pMeshModel;					//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMatModel;				//�}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9	m_pTextureModel;		//�e�N�X�`���ւ̃|�C���^
	DWORD m_nNumMatModel = 0;					//�}�e���A�����̐�
	MODEL m_aModel;
};


#endif