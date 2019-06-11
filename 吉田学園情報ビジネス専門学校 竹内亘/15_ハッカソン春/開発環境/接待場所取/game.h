//=============================================================================
//
// �Q�[������ [game.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "player.h"
#include "sound.h"
#include "UIItem.h"
#include "UITime.h"
#include "UILife.h"
#include "UIEnemy.h"

#define NUMENEMY_FILE	"data\\TEXT\\NumEnemy"	// �ݒu�������f���������o���e�L�X�g

//*********************************************************************
//�Q�[���N���X�̒�`
//*********************************************************************
class CGame //��{�N���X
{
public:
	CGame();
	~CGame();
	static CGame *Create(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *GetPlayer(void);
	static CUIItem *GetUIItem(void);
	static CTime *GetUITime(void);
	static CUILife *GetUILife(void);
	static CUIEnemy *GetUIEnemy(void);
	void SetEnemySpawn(void);
	void SaveNumEnemy(void);
	//�����o�ϐ�
private:
	static CPlayer			*m_pPlayer;
	static CSound			*m_pSound;
	static CUIItem			*m_pItem;
	static CUILife			*m_pLife;
	static CUIEnemy			*m_pUIEnemy;
	static CTime			*m_pTime;
	int						m_nFadeCnt;
	int						m_EnemyCreateCnt;
	bool					m_bPouse;
	int						m_EnemyNum;
};

#endif