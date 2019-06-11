#pragma once
//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _3DPOLYGON_H_
#define _3DPOLYGON_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define S3D_PRIORITY		(3)
#define S3DF_PRIORITY		(4)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C3D
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_GOAL, STATE_SHOP,
		STATE_GOAL2, STATE_SHOP2,
		/*�t�F�[�h*/STATE_FADESPIN, STATE_FADE, STATE_FADEIN, STATE_FADEOUT, STATE_FADEOUT2,
		/*UV�t���[*/STATE_UVFLOW_0, STATE_UVFLOW_1,
		STATE_MAX
	}STATE;
	C3D() { m_pTex = NULL; };
	~C3D() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
			 int nUV, int nUV_X, int nUV_Y, CScene::DRAW_TYPE DrawType);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);

	D3DXVECTOR3 &GetPosition(void)	{ return m_pos; }
	D3DXVECTOR3 &GetRotation(void)	{ return m_rot; }
	D3DXCOLOR	&GetColor(void)		{ return m_col; }
	D3DXVECTOR3	&GetLength(void)	{ return m_length; }
	float		&GetfCntState(void) { return m_fCntState; }
	STATE		&GetState(void)		{ return m_state; }
	void		SetColor(D3DXCOLOR col);
	void		SetSize(D3DXVECTOR3 length);
	void		SetUV(int nUV, int nUV_X, int nUV_Y);
	void		PlusUV(D3DXVECTOR2 uv);

	void		BindTexture(LPDIRECT3DTEXTURE9 *pTex) { m_pTex = pTex; }

protected://*****************************************************************************

	//�ϐ��p//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	LPDIRECT3DTEXTURE9		*GetTexture(void) { return m_pTex; }
	CScene::DRAW_TYPE		GetDrawType(void) { return m_DrawType; }
private://*****************************************************************************
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	//�ϐ��錾//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3			m_pos;				//�ʒu
	D3DXVECTOR3			m_rot;				//����
	D3DXCOLOR			m_col;				//�F
	LPDIRECT3DTEXTURE9	*m_pTex;			//�摜
	CScene::DRAW_TYPE	m_DrawType;			// �`�悷����@(���Z�����Ȃ�)
	D3DXVECTOR3			m_length;			//����
	float				m_fCntState;		//STATE�Ǘ��p
	STATE				m_state;			//�g�p���@

};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C3DEffect : public C3D
{
public:

	C3DEffect() { m_pPos = NULL; m_pScene = NULL; };
	~C3DEffect() {};

	void C3DEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
		int nUV, int nUV_X, int nUV_Y, CScene::DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, CScene *pScene);
	void Draw(void);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CAnim3D : public C3D
{
public:
	typedef enum
	{
		ANIMATION_NORMAL = 0,
		ANIMATION_LOOP,
		ANIMATION_MAX
	}ANIMATION;
	CAnim3D() {};
	~CAnim3D() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
			CScene::DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state);
	HRESULT Init(void);
	void	Update(void);

private://*****************************************************************************

	//�ϐ��錾//***********************************************************************
	int			m_nCntAnim;			//Animation�̃J�E���g
	int			m_nPtnAnim;			//�w�肳�ꂽ���W�ŕ\��
	int			m_nPtnHeight;		//�摜�̏c�̕�����
	int			m_nPtnWide;			//�摜�̉��̕�����
	int			m_nPtnSpeed;		//Animation���x
	ANIMATION	m_animation;		//�g�p���@
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CAnim3DEffect : public CAnim3D
{
public:

	CAnim3DEffect() { m_pPos = NULL; m_pScene = NULL; };
	~CAnim3DEffect() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
			CScene::DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
#endif
