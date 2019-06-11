//=============================================================================
//
// �u���b�N���� [block.h]
// Author : ���R���
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
#include "sceneX.h"

//========================================
// �N���X�̒�`
//========================================
//=====================
// �u���b�N�N���X
//=====================
class CBlock : public CSceneX
{
public:
	CBlock();								// �R���X�g���N�^
	~CBlock();								// �f�X�g���N�^

	HRESULT Init(void);						// �v���C���[����������
	void Uninit(void);						// �v���C���[�I������
	void Update(void);						// �v���C���[�X�V����
	void Draw(void);						// �v���C���[�`�揈��

	static HRESULT LoadModel(void);				// �e�N�X�`���ǂݍ���
	static void UnloadModel(void);				// �e�N�X�`�����

	static HRESULT LoadMat(void);				// �}�e���A���ǂݍ���
	static void UnloadMat(void);				// �}�e���A�����

	static CBlock *Create(D3DXVECTOR3 pos);	// �I�u�W�F�N�g�̐���

	D3DXVECTOR3 GetPos(void);						// �ʒu�̎擾
	void SetPos(D3DXVECTOR3 pos);					// �ʒu�̐ݒ�

	bool GetFall(void);						// �����Ă��邩�ǂ����̎擾
	void SetFall(bool bFall);					// �����Ă��邩�ǂ����̐ݒ�

	bool Collision(D3DXVECTOR3 *pos, float fRadius);	// �����蔻��

private:
	static LPD3DXMESH		m_pMesh;			// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMat;			// �}�e���A�����̐�
	static LPDIRECT3DTEXTURE9		*m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;				// �ʒu
	D3DXVECTOR3				m_move;				// �ړ���
	D3DXVECTOR3				m_rot;				// ����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// �u���b�N�̍ŏ��l�A�ő�l
	bool					m_bLand;			// �u���b�N�ɏ���Ă��邩�ǂ���
	bool					m_bFall;			// �����Ă��邩�ǂ���
	int						m_nCntFall;			// �����Ă��鎞�Ԃ��J�E���g
	D3DXVECTOR3				m_scale;			// �g�嗦

	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
};

#endif