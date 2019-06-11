//=============================================================================
//
// �t�B�[���h���� [field.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
//class CModel;
class CSceneMeshField;

//*********************************************************************
//�v���C���[�N���X�̒�`
//*********************************************************************
class CField : public CScene //�h���N���X
{
public:
	//���f���̎��
	typedef enum
	{
		FIELDTEX_NORMAL = 0,	//�^�C��
		FIELDTEX_ROADWAY,		//�ԓ�
		FIELDTEX_FOOTWAY,		//����
		FIELDTEX_GARDEN,		//��
		FIELDTEX_MAX			//�e�N�X�`���̑���
	}FIELDTEX;

	CField();
	~CField();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CField *Create(D3DXVECTOR3 pos, float fWidth,float fDepth, FIELDTEX tex, int nSplitX, int nSplitZ);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//�����o�ϐ�
	D3DXVECTOR3					m_pos;					//�ʒu
	D3DXVECTOR3					m_posold;				//�O��̈ʒu
	D3DXVECTOR3					m_move;					//�ړ���
	D3DXVECTOR3					m_rot;					//����
	float						m_fWidth, m_fDepth;		//�� ���s��
	int							m_nSplitX, m_nSplitZ;	//������
	FIELDTEX					m_Type;					//�^�C�v

	static LPDIRECT3DTEXTURE9	m_pTexture[FIELDTEX_MAX];		//�e�N�X�`���ւ̃|�C���^

	CSceneMeshField				*m_pField;			//�t�B�[���h�{�̂ւ̃|�C���^
public:
};

#endif