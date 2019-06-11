//=============================================================================
//
// �G���� [enemy.h]
// Author : �|���j
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_TEXTURE (2)		// �G�̎��
#define ENEMYSIZE (25)				// �G�̑傫��
#define BALLET_SPEED (10)			// �G�̒e�̃X�s�[�h

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CEnemy : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	typedef enum
	{// �G�̎��
		ENEMYTYPE_000 = 0,
		ENEMYTYPE_001,
		ENEMYTYPE_002,
		ENEMYTYPE_TEST,
		ENEMYTYPE_MAX,
	}ENEMYTYPE;

	CEnemy();
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, ENEMYTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEnemy * Create(D3DXVECTOR3 pos, ENEMYTYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	//static void HitEnemy(int nDamage);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMYTYPE_MAX];	// ���L�e�N�X�`���̃|�C���^

	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nLife;
	int						m_nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;	// �A�j���V�����p�^�[��
	ENEMYTYPE               m_nType;		// �G�̎��
	float					m_fMoveX = 1.5f;
	float					m_fMoveY = 1.0f;
};
#endif