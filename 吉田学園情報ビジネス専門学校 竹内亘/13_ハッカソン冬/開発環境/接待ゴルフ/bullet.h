//=============================================================================
//
// �e�̏��� [bullet.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "billboard.h"

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CBullet : public CSceneBillBoard //�h���N���X
{
public:
	typedef enum
	{
		BULLETTYPE_NONE = 0,	//�v���C���[���
		BULLETTYPE_MAX			//��Ԃ̑���
	}BULLETTYPE;

	typedef struct
	{
		D3DXVECTOR3 pos;					// �ʒu
		D3DXVECTOR3 move;					// �ړ���
		D3DXVECTOR3 posold;					// �O��̈ʒu
		D3DXCOLOR col;						// �F
		D3DXMATRIX	mtrxWorldBullet;		// ���[���h�}�g���b�N�X
		float fRadius;						// ���a(�傫��)
		float fHeght;						// ����
		float fWidth;						// ��
		int nLife;							// ����
		D3DXVECTOR3 VtxMin, VtxMax;			//�v���C���[�̍ŏ��l�A�ő�l
	} BULLET;

	CBullet();
	~CBullet();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos ,D3DXVECTOR3 move);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	BULLET m_Bullet;
};
#endif
