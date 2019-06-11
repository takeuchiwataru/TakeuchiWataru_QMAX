//=============================================================================
//
// �i���o�[���� [number.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
//*********************************************************************
//�i���o�[�N���X�̒�`
//*********************************************************************
class CNumber : public CScene2D //�h���N���X
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);	//�I�u�W�F�N�g����
	void SetNumber(int nNumber);
	int GetNumber(void);

	static HRESULT Load(void);
	static void UnLoad(void);
	void SetColor(D3DXCOLOR col);
	void SetScale(float scale);

private:
	//�����o�ϐ�
	D3DXVECTOR3						m_pos;
	D3DXCOLOR						m_col;
	float							m_fWidth, m_fHeight;	// ������
	float							m_fScale;
	int								m_nNumber;
	static LPDIRECT3DTEXTURE9		m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
};

#endif