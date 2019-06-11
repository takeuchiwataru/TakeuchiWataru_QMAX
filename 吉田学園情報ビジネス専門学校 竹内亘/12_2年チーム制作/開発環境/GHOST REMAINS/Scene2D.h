//=============================================================================
//
// �V�[������ [scene2D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
#include "SceneAnim3D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define S2D_PRIORITY		(6)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScene2D : public CScene
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_FADE, STATE_FADEIN, STATE_FADEIN5, STATE_FADEOUT, STATE_FADEOUT2,
		STATE_FLOW0, STATE_FLOW1, STATE_FLOW2,
		STATE_SLIDE_IN, STATE_SLIDE_OUT1, STATE_SLIDE_OUT2,
		STATE_FLASH, STATE_FLASH2,
		STATE_BIG, STATE_SMALL,
		STATE_COL_FLOW,		//�E�ɗ���Ȃ��瓧���x�㏸
		STATE_ZCLEAR,		//�`��I����Z�N���A
		STATE_MAX
	}STATE;

	CScene2D(int nPrioryity = S2D_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CScene2D() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTex = pTex; }
	void	BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	CScene::DRAW_TYPE &GetDrawType(void) { return m_DrawType; }

	void CScene2D::SetColor(D3DXCOLOR col);
	void CScene2D::SetPosition(D3DXVECTOR3 pos);
	void CScene2D::SetPosition2(float fSize);
	void CScene2D::SetUV(int nUV, int nUV_X, int nUV_Y);
	void CScene2D::SetGageUV(float fMaxLengthX);
	void CScene2D::SetGage(float fLengthX, bool bDirection);
	void CScene2D::SetSideAlpha(float fCol, float fMinCol, int nID);

	void CScene2D::PlusUV(D3DXVECTOR2 fUV);

	D3DXVECTOR3 *GetPosition(void) { return &m_pos; }
	D3DXCOLOR	*GetColor(void) { return &m_col; }
	STATE		*GetState(void) { return &m_state; }
	float		*GetfCntState(void) { return &m_fCntState; }
	float		&GetfLengthX(void) { return m_fLengthX; }
	float		&GetfLengthY(void) { return m_fLengthY; }
protected://*****************************************************************************
private://*****************************************************************************
	//�ϐ��錾//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;				// �|���S���̈ʒu
	D3DXCOLOR				m_col;
	LPDIRECT3DTEXTURE9		m_pTex;			// �e�N�X�`���ԍ�
	CScene::DRAW_TYPE		m_DrawType;		// �`�悷����@(���Z�����Ȃ�)
	float					m_fLengthX;			// �|���S���̒���X
	float					m_fLengthY;			// �|���S���̒���Y
	STATE					m_state;				//�J�E���g�p
	float					m_fCntState;			//�J�E���g�p
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneAnim2D : public CScene2D
{
public:
	CSceneAnim2D(int nPrioryity = S2D_PRIORITY) : CScene2D::CScene2D(nPrioryity) {};
	~CSceneAnim2D() {};
	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed,
		float fCntState, STATE state, CSceneAnim3D::ANIMATION animation, D3DXCOLOR col, CScene2D::TEXTURE Texture);
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
#endif
