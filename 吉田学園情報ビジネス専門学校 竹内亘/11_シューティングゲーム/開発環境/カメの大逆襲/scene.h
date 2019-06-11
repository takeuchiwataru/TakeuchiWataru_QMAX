//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : �|���j
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCENE		(3000)									// �|���S���ő吔
#define NUM_PRIORITY	(8)										// �D�揇�ʂ̍ő吔

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScene
{
public:
	typedef enum 
	{// �I�u�W�F�N�g�̎��
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		// �v���C���[
		OBJTYPE_ENEMY,		// �G
		OBJTYPE_BOSS,		// �{�X
		OBJTYPE_BULLET,		// �e
		OBJTYPE_EXPLOSION,	// ����
		OBJTYPE_LIFE,		// ���C�t
		OBJTYPE_EFFECT,		// �G�t�F�N�g
		OBJTYPE_PARTICLE,	// �p�[�e�B�N��
		OBJTYPE_ITEM,		// �A�C�e��
		OBJTYPE_MAEINAPLANT,// �C��
		OBJTYPE_TITLELOGO,	// �^�C�g�����S
		OBJTYPE_RESULTLOGO,	// ���U���g���S
		OBJTYPE_TUTORIAL,	// �`���[�g���A�����S
		OBJTYPE_PRESSENTER,	// �v���X�G���^�[
		OBJTYPE_PAUSEMAT,	// �|�[�Y�䎆
		OBJTYPE_PAUSESELECT,// �|�[�Y����
		OBJTYPE_FRAME,		// �t���[��
		OBJTYPE_IMAGE,		// �摜
		OBJTYPE_AVATAR,		// ���g
		OBJTYPE_RANKINGRANK,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual	HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual	void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	
	void SetObjType(OBJTYPE ObjType);
	OBJTYPE GetObjType(void);
	static CScene * GetScene(int nPriority,int nIdx);
	//static CScene * GetScene(void);

	// �ÓI�����o�֐�
	static void ReleseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

protected:
	void Release(void);

private:
	static CScene *m_apScene[NUM_PRIORITY][MAX_SCENE];
	static int m_nNumAll;
	int m_nID;			// �������g�̔ԍ�
	OBJTYPE m_objType;	// �I�u�W�F�N�g�̎��
	int m_nPriority;	// �D�揇�ʂ̔ԍ�
};
#endif