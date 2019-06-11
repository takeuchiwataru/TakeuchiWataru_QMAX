//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �|���j
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MOVESPEED (7.0f)		// �v���C���[�̈ړ��X�s�[�h
#define PLAYER_SIZE (50)			// �v���C���[�̑傫��
#define PLAYER_BULLET_INTERVAL (10)	// 2way�ɂȂ������̊Ԋu
#define PLAYER_REMAIN (3)			// �v���C���[�c�@
#define MAX_JOYPAD (2)				// �ő�R���g���[���[

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CPlayer : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	typedef enum
	{// �v���C���[�̎��
		PLAYERTYPE_000 = 0,
		PLAYERTYPE_001,
		PLAYERTYPE_MAX,
	}PLAYERTYPE;
	
	typedef enum
	{// �v���C���[�̏��
		PLAYERSTATE_NORMAL = 0,	// �ʏ���
		PLAYERSTATE_DAMEGE,		// �_���[�W���
		PLAYERSTATE_DEATH,		// ���S���
		PLAYERSTATE_PS,			// �p�[�t�F�N�g�V�F�����
		PLAYERSTATE_INVICIBLE,	// ���G
		PLAYERSTATE_MAX,
	}PLAYERSTATE;

	typedef enum
	{// �A�C�e����������v���C���[���
		ITEMSTATE_NORMAL = 0,	// �ʏ���
		ITEMSTATE_ITEM_2WAY,	// 2way�A�C�e������������
		ITEMSTATE_AVATAR,		// ���g
		ITEMSTATE_SPPED_UP,		// �X�s�[�hUP
		ITEMSTATE_MAX,
	}ITEMSTATE;

	CPlayer();
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, PLAYERTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	PLAYERSTATE GetState(void);
	PLAYERTYPE GetType(void);
	void SetItemState(ITEMSTATE itemstate);		// �A�C�e�����������Ԃ̐ݒu
	int GetRemain(void);
	D3DXVECTOR3 GetPos(void);
	//PLAYERTYPE GetPlayerType(void);

	// �ÓI�����o�֐�
	static CPlayer * Create(D3DXVECTOR3 pos, PLAYERTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[PLAYERTYPE_MAX];	// ���L�e�N�X�`���̃|�C���^
	float					m_rot;
	D3DXVECTOR3 m_pos;				// �ʒu
	int m_nRemain;					// �c�@
	//int m_nLife;					// ���C�t
	//int m_nRemainAll;				// �c�@���v
	int m_nSpeed;					// �X�s�[�h
	PLAYERTYPE m_nType;				// �v���C���[�̎��
	PLAYERSTATE m_State;			// �v���C���[�̏��
	ITEMSTATE m_ItemState;			// �A�C�e����������v���C���[���
	int m_nCounterState;			// ��ԊǗ��̃J�E���^�[
	int m_nTime;					//
	int m_nNumPs;					// PS�g�p��
	static int m_nNumPlayer;		// �v���C���[�l��
};
#endif