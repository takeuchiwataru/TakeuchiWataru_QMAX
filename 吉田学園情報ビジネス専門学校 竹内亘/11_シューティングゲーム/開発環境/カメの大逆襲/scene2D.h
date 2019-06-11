//=============================================================================
//
// �I�u�W�F�N�g2D���� [scene2D.h]
// Author : �|���j
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_TEXTURE_000 "data/TEXTURE/player000.png"			// �v���C���[1�̃e�N�X�`��
#define PLAYER_TEXTURE_001 "data/TEXTURE/player001.png"			// �v���C���[2�̃e�N�X�`��
#define BULEET_TEXTURE_000	"data/TEXTURE/baburu.png"			// �e�̃e�N�X�`��
#define EXPLOSION_TEXTURE_000 "data/TEXTURE/explosion000.png"	// �����̃e�N�X�`��
#define ENEMY_TEXTURE_000	"data/TEXTURE/enemy000.png"			// �G1�̃e�N�X�`��
#define ENEMY_TEXTURE_001	"data/TEXTURE/enemy001.png"			// �G2�̃e�N�X�`��
#define ENEMY_TEXTURE_002	"data/TEXTURE/enemy002.png"			// �G3�̃e�N�X�`��
#define BOSS_TEXTURE_000	"data/TEXTURE/boss000.png"			// �{�X1�̃e�N�X�`��
#define ITEM_TEXTURE_000	"data/TEXTURE/item000.png"			// �A�C�e��1�̃e�N�X�`��
#define ITEM_TEXTURE_001	"data/TEXTURE/item0011.png"			// �A�C�e��2�̃e�N�X�`��
#define ITEM_TEXTURE_002	"data/TEXTURE/item002.png"			// �A�C�e��3�̃e�N�X�`��
#define ITEM_TEXTURE_003	"data/TEXTURE/item003.png"			// �A�C�e��4�̃e�N�X�`��
#define MARINE_TEXTURE_000	"data/TEXTURE/marineplant.png"		// �C���̃e�N�X�`��
#define EFFECT_TEXTURE_000 "data/TEXTURE/effect000.jpg"			// �G�t�F�N�g�̃e�N�X�`��
#define PARTICLE_TEXTURE_000 "data/TEXTURE/effect000.jpg"		// �G�t�F�N�g�̃e�N�X�`��
#define TITLELOGO_TEXTURE "data/TEXTURE/title_logo.png"			// �^�C�g�����S�̃e�N�X�`��
#define RESULTLOGO_TEXTURE "data/TEXTURE/result_logo.png"		// ���U���g���S�̃e�N�X�`��
#define POLIGON_SIZE	(30)									// �|���S���̃T�C�Y

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScene2D : public CScene
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	CScene2D(int nPriority);
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT InitAnim(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos,float fwidth,float fheight);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetExplosion(int nPatternAnim);				// �����A�j���[�V�����ݒu
	void SetPattern2(int nPatternAnim);					// 2�p�^�[���̃A�j���[�V�����ݒu(�G...)
	void SetEffect(float fRadius);						// �G�t�F�N�g�̐ݒu
	void SetParticle(int nRadius, D3DXVECTOR3 pos);	// �p�[�e�B�N���̐ݒu
	void SetColor(D3DXCOLOR col);						// �J���[�̐ݒu
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);

	//// �ÓI�����o�֐�
	//static CScene2D * Create(D3DXVECTOR3 pos);	// �g���ĂȂ�

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_move;			// �ړ�
	D3DXCOLOR				m_col;			// �F 
	float					m_rot;
	float					m_fLength;
	float					m_fAdd;
};
#endif