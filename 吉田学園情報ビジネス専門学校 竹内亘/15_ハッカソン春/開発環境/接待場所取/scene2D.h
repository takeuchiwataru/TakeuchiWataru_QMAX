//=============================================================================
//
// �V�[��2D���� [scene2D.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//�V�[��2D�N���X�̒�`
//*********************************************************************
class CScene2D : public CScene //�h���N���X
{
public:
	//CScene(int nPriority = 3, OBJTYPE ObjType = OBJTYPE_NONE);

	CScene2D(int nPriority = 5);
	~CScene2D();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, float fWidth, float fHeight ,int nPriority = 5);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTURE�����蓖�Ă�
	void SetPos(D3DXVECTOR3 pos, float fSpin, float fScale, D3DXCOLOR col);
	void SetRot(float fSpin);
	D3DXVECTOR3 Getpos(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtx(void);			//���_�����擾
	void SetbDraw(bool bDraw);
	void SetColor(D3DXCOLOR col);
	void SetScale(float fScale);
	void SetExplosion(int m_PatternAnim);
	void SetPosition(D3DXVECTOR3 pos, float nSizeX, float nSizeY);
	void SetCol(D3DXCOLOR col);

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	float					m_fSpin;				// ��]
	float					m_fWidth, m_fHeight;	// ������
	float					m_fLength;				// �傫��
	float					m_fScale;				// �傫���ύX
	D3DXCOLOR				m_Col;
	bool					m_bDraw;
};

#endif