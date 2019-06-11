//=============================================================================
//
// �{�X���� [boss.h]
// Author : �|���j
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_TEXTURE (2)		// �G�̎��
#define BOSSSIZE (100)				// �G�̑傫��
#define BOSS_LIFE (400)				// �{�X�̗̑�

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CBoss : public CEnemy
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	typedef enum
	{// �G�̎��
		BOSSTYPE_000 = 0,
		BOSSTYPE_MAX,
	}BOSSTYPE;

	typedef enum
	{// �v���C���[�̏��
		BOSSSTATE_NORMAL = 0,	// �ʏ���
		BOSSSTATE_DAMEGE,		// �_���[�W���
		BOSSSTATE_MAX,
	}BOSSSTATE;

	CBoss();
	~CBoss();
	HRESULT Init(D3DXVECTOR3 pos, BOSSTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBoss * Create(D3DXVECTOR3 pos, BOSSTYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	void HitBoss(int nDamage);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[BOSSTYPE_MAX];	// ���L�e�N�X�`���̃|�C���^

	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nLife;
	int						m_nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;	// �A�j���V�����p�^�[��
	BOSSTYPE				m_nType;		// �G�̎��
	BOSSSTATE				m_State;		// �v���C���[�̏��
	int m_nCounterState;					// ��ԊǗ��̃J�E���^�[
	float					m_fMoveX = 2.0f;
	float					m_fMoveY = 1.0f;
	int						m_nTime;
};
#endif