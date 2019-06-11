#pragma once
//=============================================================================
//
// 3D�����֌W���� [3DNumber.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _3DNUMBER_H_
#define _3DNUMBER_H_

#include "main.h"
#include "3DPolygon.h"
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C3DNumber : public CScene
{
public:
	typedef enum
	{
		TEXTURE_SCORE,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		STATE_SCORE = 0,	//�S�Ă��̂܂ܕ\��
		STATE_STATUS,		//�ő吔����̌��͓�����
		STATE_TIMER,
		STATE_MAX
	}STATE;

	C3DNumber(int nPrioryity = S3D_PRIORITY) : CScene::CScene(nPrioryity) { SetObjType(CScene::OBJTYPE_NUMBER); };
	~C3DNumber() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, int nScore, int nDigits, D3DXCOLOR col, STATE state);	//�X�R�A(����)��TEXTURE
	void	SetNumber(int nScore);
	void	AddNumber(int nValue);
	int		&GetnNumber(void) { return m_nNumber; }
	D3DXVECTOR3 &GetPosition(void) { return m_pos; }
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	STATE	m_state;		//�\���`�� 
	D3DXVECTOR3 m_pos;
	int		m_nNumber;		//���l
	int		m_nNum3D;		//�ő包��
	C3D		**m_p3D;		//�����̃|�C���^
};

#endif
