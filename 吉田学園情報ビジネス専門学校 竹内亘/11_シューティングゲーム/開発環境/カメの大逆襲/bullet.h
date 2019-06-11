//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �|���j
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIT_SIZE (30)				// �����蔻��̃T�C�Y
#define BULLET_SIZE (15)			// �e�̑傫��
#define BULLET_LIFE (50)			// �e�̃��C�t

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CBullet : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	typedef enum
	{// �e�̎��
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PlAYER000,
		BULLETTYPE_ENEMY000,
		BULLETTYPE_MAX
	}BULLETTYPE;

	CBullet();
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE BulletType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE BulletType);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nLife;
	BULLETTYPE m_bulletType;				// �e�̎��
};
#endif