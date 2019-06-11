//=============================================================================
//
// UI�G�l�~�[���� [UIEnemy.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIENEMY_H_
#define _UIENEMY_H_

#include "main.h"
#include "scene2D.h"

#define MAX_ENEMY2D (1)
#define MAX_ENEMYNUM (3)

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;

//*********************************************************************
//UI�G�l�~�[�N���X�̒�`
//*********************************************************************
class CUIEnemy : public CScene2D  //�h���N���X
{
public:
	CUIEnemy();
	~CUIEnemy();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIEnemy *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	void PlusEnemy(int nAddEnemy);
	int GetEnemyNum(void);
	void SetEnemyBool(bool bGetEnemy);
private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ENEMY2D];	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_ENEMY2D];	// 2D�|���S���ւ̃|�C���^
	CNumber						*m_apNumber[MAX_ENEMYNUM];	// �����ւ̃|�C���^
	int							m_nEnemy;					// �l����
	bool						m_bGetEnemy;					// �擾���
	float						m_fScale;					// �g��k����
	int							m_ScaleCounter;				// �g��k���̃J�E���^�[
};
#endif
