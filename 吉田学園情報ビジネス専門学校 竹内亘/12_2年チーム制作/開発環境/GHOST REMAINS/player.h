//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CPlayer : public CCharacter
{
public:
	CPlayer(int nPrioryity = CHAR_PRIORITY) : CCharacter::CCharacter(nPrioryity) {};
	~CPlayer() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);	//�Q�[�W�Z�b�g����
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);

	bool &GetbDrop(void) { return m_bDrop; }
	float &GetfStop(void) { return m_fStop; }
	float &GetfHeart(void) { return m_fHeart; }

private://*****************************************************************************
	//�ϐ��錾//***********************************************************************
	float m_fHeart;		//�S����
	float m_fDistance;	//�J�����Ƃ̋���
	float m_fStop;		//�v���C���[��Stop
	bool  m_bDrop;		//������
};

#endif
