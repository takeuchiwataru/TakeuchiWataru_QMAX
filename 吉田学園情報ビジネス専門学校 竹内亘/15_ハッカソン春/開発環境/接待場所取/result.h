//=============================================================================
//
// ���U���g���� [result.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "UIScore.h"
#include "scene2D.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_NUM	(3)		// ����
#define MAX_2D	(2)		// 2D�|���S���̐�

//*********************************************************************
//���U���g�N���X�̒�`
//*********************************************************************
class CResult //��{�N���X
{
public:
	typedef enum
	{
		RESULTSTATE_NONE = 0,		//�������
		RESULTSTATE_ITEMCNT,		//�A�C�e���𐔂��Ă���
		RESULTSTATE_TIMECNT,		//�^�C���𐔂��Ă���
		RESULTSTATE_END,			//�S�Ă̏������I�����
		RESULTSTATE_MAX,			//�ő吔
	}RESULTSTATE;

	CResult();
	~CResult();
	static CResult *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddTime(int nValue);
	void AddItem(int nValue);

	static D3DXVECTOR3 GetBluePos(void);

	int LoadNumEnemy(void);

	//�����o�ϐ�
private:
	int						m_nCntTimer;
	static CScore			*m_pScore[1];
	CNumber					*m_apItem[MAX_NUM];
	CNumber					*m_apTime[MAX_NUM];
	LPDIRECT3DTEXTURE9		m_pTexture[MAX_2D];				// �e�N�X�`���ւ̃|�C���^
	CScene2D				*m_pScene2D[MAX_2D];

	static D3DXVECTOR3				m_bluePos;

	RESULTSTATE				m_State;
	int						m_nScore;
	int						m_nTime;
	int						m_nItem;
	int						m_nSoundCnt;
};

#endif