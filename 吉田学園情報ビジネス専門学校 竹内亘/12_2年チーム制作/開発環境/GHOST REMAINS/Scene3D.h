#pragma once
//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

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
class CScene3D : public CScene
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		/*�t�F�[�h*/STATE_FADESPIN, STATE_FADE, STATE_FADEIN, STATE_FADEOUT, STATE_FADEOUT2, STATE_FADEOUTN,
		STATE_DSTONE,
		/*��*/		STATE_FIRE,
		/*UV�t���[*/STATE_UVFLOW_0, STATE_UVFLOW_1,
		/*�{�XBG*/	STATE_BFLOW_IN, STATE_BFLOW_OUT,
		STATE_MAX
	}STATE;
	CScene3D(int nPrioryity = 3) : CScene::CScene(nPrioryity) { m_pTex = NULL; };
	~CScene3D() {};

	void CScene3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType);
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
	void		SetUVPattern(float fUV_X, float fUV_Y);
	void		PlusUV(D3DXVECTOR2 uv);
	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	CScene::DRAW_TYPE		&GetDrawType(void) { return m_DrawType; }
	void		BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTex = pTex; }

protected://*****************************************************************************

	//�ϐ��p//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	LPDIRECT3DTEXTURE9		GetTexture(void) { return m_pTex; }
private://*****************************************************************************
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	//�ϐ��錾//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3			m_pos;				//�ʒu
	D3DXVECTOR3			m_rot;				//����
	D3DXCOLOR			m_col;				//�F
	LPDIRECT3DTEXTURE9	m_pTex;				//�摜
	CScene::DRAW_TYPE	m_DrawType;			// �`�悷����@(���Z�����Ȃ�)
	D3DXVECTOR3			m_length;			//�|���S���̒���
	float				m_fCntState;		//STATE�Ǘ��p
	STATE				m_state;			//�g�p���@
	bool				m_bBILLBoard;		//�r���{�[�h���ǂ���
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneEffect : public CScene3D
{
public:

	CSceneEffect(int nPrioryity = 3) : CScene3D::CScene3D(nPrioryity) { m_pPos = NULL; m_pScene = NULL; };
	~CSceneEffect() {};

	void CSceneEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
		TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, CScene *pScene);
	void Draw(void);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
#endif
