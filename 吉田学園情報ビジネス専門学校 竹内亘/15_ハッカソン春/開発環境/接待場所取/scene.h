//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_PRIORITY			(8)

//*********************************************************************
//�I�u�W�F�N�g�N���X�̒�`
//*********************************************************************
class CScene //��{�N���X
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,		//�����l
		OBJTYPE_SCENE2D,		//�V�[��2D
		OBJTYPE_SCENE3D,		//�V�[��3D
		OBJTYPE_MODEL,			//���f��
		OBJTYPE_SHADOW,			//�e
		OBJTYPE_SCENEX,			//�V�[��X
		OBJTYPE_OBJECT,			//�I�u�W�F�N�g
		OBJTYPE_PAUSE,			//�|�[�Y
		OBJTYPE_BILLBOARD,		//�r���{�[�h
		OBJTYPE_BILLBOARDENEMY,	//�r���{�[�h �G
		OBJTYPE_BILLBOARDITEM,	//�r���{�[�h �A�C�e��
		OBJTYPE_BILLBOARDOBJECT,//�r���{�[�h �I�u�W�F�N�g
		OBJTYPE_BULLET,			//�e
		OBJTYPE_ENEMY,			//�G
		OBJTYPE_EFFECT,			//�G�t�F�N�g
		OBJTYPE_EFFECTADD,		//�G�t�F�N�g(���Z����)
		OBJTYPE_MESHFIELD,		//���b�V���t�B�[���h
		OBJTYPE_MESHCYLINDER,	//���b�V���V�����_�[
		OBJTYPE_FIELD,			//�t�B�[���h
		OBJTYPE_BGMODEL,		//�w�i�p���f��
		OBJTYPE_MAX				//�ő吔
	}OBJTYPE;
	CScene(int nPriority = 3,OBJTYPE ObjType = OBJTYPE_NONE);
	virtual ~CScene();
	virtual HRESULT Init() = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void Setpos(D3DXVECTOR3 pos);				//�ʒu�ݒ�
	static int GetNumAll(void);					//�����擾
	static void ReleaseAll(void);				//�S�Ă�j��
	static void UpdateAll(void);				//�S�Ă��X�V
	static void DrawAll(void);					//�S�Ă�`��
	void UninitAll(void);						//���S�t���O�������Ă�����̂�j��
	void SetObjType(OBJTYPE ObjType);			//�^�C�v��ݒ�
	CScene::OBJTYPE GetObjType(void);			//�^�C�v���擾
	void SetPriority(int nPriority);

	static CScene *&GetTop(int nPriority);
	CScene *&GetNext(void) { return m_pNext; }
	bool &GetDeath(void) { return m_pDeath; }

	static void SetbPause(bool bPause);

protected:
	void Release(void);							//�t���O�𗧂Ă�
	CScene *m_pNext;							//���̃I�u�W�F�N�g�ւ̃|�C���^
private:
	//�����o�ϐ�
	static CScene	*m_pTop[NUM_PRIORITY];		//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene	*m_pCur[NUM_PRIORITY];		//���݂̃I�u�W�F�N�g�ւ̃|�C���^
	int				m_nPriority;				//�D�揇�ʂ̔ԍ�
	CScene			*m_pPrev;					//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	OBJTYPE			m_ObjType;					//���
	bool			m_bDeath;					//���S�t���O
	bool			m_pDeath;					//���S�t���O

	static bool		m_bPause;					//�|�[�Y
};

#endif