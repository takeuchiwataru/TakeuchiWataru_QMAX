//=============================================================================
//
// UI�G���^�[���� [UIExclamation.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIEXCLAMATION_H_
#define _UIEXCLAMATION_H_

#include "main.h"
#include "scene2D.h"

#define MAX_EXCLAMATION (1)

//*********************************************************************
//UI�G���^�[�N���X�̒�`
//*********************************************************************
class CUIExclamation : public CScene2D  //�h���N���X
{
public:
	typedef enum
	{
		ENEMYPOS_CENTER = 0,
		ENEMYPOS_RIGHT,
		ENEMYPOS_LEFT,
	}ENEMYPOS;

	CUIExclamation();
	~CUIExclamation();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIExclamation *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, ENEMYPOS type);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetItemBool(bool bGetItem);
private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_EXCLAMATION];	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;							// �ʒu
	D3DXVECTOR3					m_move;							// �ړ���
	D3DXVECTOR3					m_posold;						// �O��̈ʒu
	float						m_fWidth, m_fHeight;			// �� ����
	D3DXMATRIX					m_mtrxWorld;					// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_EXCLAMATION];	// 2D�|���S���ւ̃|�C���^
	int							m_nItem;						// �l����
	int							m_nColorFlash;					// �_�ŃJ�E���g
	D3DXCOLOR					m_Col;							// �F
	bool						m_bEnter;						// �����ꂽ���ǂ������
	float						m_fScale;						// �g��k����
	int							m_ScaleCounter;					// �g��k���̃J�E���^�[
	int							m_EnemyCreateCnt;				// �G�̐����܂ł̃J�E���g
	ENEMYPOS					m_EnemyPosType;
};
#endif
