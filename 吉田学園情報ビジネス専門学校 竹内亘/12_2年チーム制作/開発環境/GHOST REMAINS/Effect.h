//=============================================================================
//
// �V�[������ [scene2D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

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
class CLineEffect : public CScene
{
public:
	typedef enum
	{
		TYPE_FIRE,
		TYPE_MAX
	}TYPE;
	CLineEffect(int nPrioryity = S2D_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_pPos[0] = NULL; m_pPos[1] = NULL; m_pPos[2] = NULL;
		m_rot = NULL; m_bDelete = NULL;
	};
	~CLineEffect() {};

	void	Set(float *fPosX, float *fPosY, float *fPosZ, D3DXVECTOR3 pos,
		D3DXVECTOR3 *rot, float fDistance, float fInterval, int nLife, bool *bDelete);
	HRESULT Init(void);
	void	Update(void);
	D3DXVECTOR3	ChangePos(void);
	void MoveSet(D3DXVECTOR3 &pos);
	void SetEffect(void);
	void StartEffect(void);
	void EndEffect(void);

protected://*****************************************************************************
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	TYPE			m_Type;			// �Z�b�g���
	D3DXVECTOR3		m_posold;		// ���g�O�̈ʒu
	float			*m_pPos[3];		// �ǔ����錴�_ X, Y, Z
	D3DXVECTOR3		*m_rot;			// ���_����̊p�x
	float			m_fDistance;	// ���_����̃v���X�l
	float			m_fLength;		//�i�񂾋����ۑ�
	float			m_fInterval;	//�Z�b�g�܂ł̊Ԋu
	int				m_nLife;		//����
	bool			*m_bDelete;		//�����锻��
};

#endif
