//=============================================================================
//
// 2DPolygon���� [2DPolygon.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _2DPOLYGON_H_
#define _2DPOLYGON_H_

#include "main.h"
#include "scene.h"
#include "SceneAnim3D.h"
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C2D
{
public:
	C2D() {};
	~C2D() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, D3DXCOLOR col);
	void	SetPosition(float fRot);
	void	SetPosition2(float fSize);
	void	SetUV(int nUV, int nUV_X, int nUV_Y);
	void	SetUV_Camera(float fUV_X, float fUV_Y, float m_fDiameter);
	void	SetGageUV(float fMaxLengthX);
	void	SetGage(float fLengthX, bool bDirection);
	void	SetColor(D3DXCOLOR col);
	void	SetSideAlpha(float fCol, float fMinCol, int nID);
	void	PlusUV(D3DXVECTOR2 uv);

	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 pTex)	 { m_pTex = pTex; }
	void	BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }

	float		*GetfLengthX(void) { return &m_fLengthX; }
	D3DXVECTOR3 &GetPosition(void) { return m_pos; }
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;				// �|���S���̈ʒu
	LPDIRECT3DTEXTURE9		m_pTex;			// �e�N�X�`���ԍ�
	CScene::DRAW_TYPE		m_DrawType;		// �`�悷����@(���Z�����Ȃ�)
	float					m_fLengthX;			// �|���S���̒���X
	float					m_fLengthY;			// �|���S���̒���Y
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C2DAnim : public C2D
{
public:
	C2DAnim() {};
	~C2DAnim() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, 
		CSceneAnim3D::ANIMATION animation, D3DXCOLOR col);
	void	Update(void);
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	int			m_nCntAnim;			//Animation�̃J�E���g
	int			m_nPtnAnim;			//�w�肳�ꂽ���W�ŕ\��
	int			m_nPtnHeight;		//�摜�̏c�̕�����
	int			m_nPtnWide;			//�摜�̉��̕�����
	int			m_nPtnSpeed;		//Animation���x
	CSceneAnim3D::ANIMATION		m_animation;		//�g�p���@
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C2DCameraBG : public C2D
{
public:
	C2DCameraBG() {};
	~C2DCameraBG() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, float fUV_X, float fUV_Y, float fDiameter, D3DXCOLOR col);
	void	Update(void);
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	float	m_fUV_X;		//UV_X
	float	m_fUV_Y;		//UV_Y
	float	m_fUV_XPlus;	//X�̃v���X�l
	float	m_fUV_YPlus;	//Y�̃v���X�l
	float	m_fDiameter;	//�J���������̔{��
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C2DPolygon : public C2D
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_FADE,
		STATE_FADEIN,
		STATE_FADEOUT,
		STATE_SLIDEIN, STATE_SLIDEOUT,
		STATE_SLIDEIN2, STATE_SLIDEOUT2,
		STATE_BIG, STATE_SMALL,
		STATE_MAX
	}STATE;
	C2DPolygon() {};
	~C2DPolygon() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col);
	void	Update(void);

	D3DXCOLOR	*GetColor(void) { return &m_col; }
	STATE		*GetState(void) { return &m_state; }
	float		&GetfCntState(void) { return m_fCntState; }
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	float				m_fCntState;		//STATE�Ǘ��p
	STATE				m_state;			//�g�p���@
	D3DXCOLOR m_col;
};
#endif
