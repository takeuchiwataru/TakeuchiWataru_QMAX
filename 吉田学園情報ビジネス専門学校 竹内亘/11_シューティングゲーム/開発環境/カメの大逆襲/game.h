//=============================================================================
//
// �Q�[������ [game.h]
// Author : �|���j
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER (2)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CGame
{
public:
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore * GetScore(void);
	static CRemain * GetRemain(void);
	static CRemain * GetRemain2(void);
	static CPlayer * GetPlayer(void);
	static CPlayer * GetPlayer2(void);
	//static CLife * GetLife(void);

private:
	static CScore * m_pScore;
	static CPlayer * m_pPlayer[MAX_PLAYER];
	static CRemain * m_pRemain[MAX_PLAYER];
	int m_nTime;
	//static CLife  * m_pLife;
};

#endif