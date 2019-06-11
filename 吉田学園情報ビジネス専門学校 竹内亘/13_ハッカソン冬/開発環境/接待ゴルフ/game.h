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
#include "meshField.h"
#include "meshFieldBG.h"
#include "UIScore.h"

//=============================================================================
// �O���錾
//=============================================================================
class CBall;
//*********************************************************************
//�Q�[���N���X�̒�`
//*********************************************************************
class CGame //��{�N���X
{
public:
	typedef enum
	{
		ENEMY_POSTYPE_NORMAL = 0,		//�J�j
		ENEMY_POSTYPE_IKA,				//�C�J
		ENEMY_POSTYPE_KURO,				//�N��
		ENEMY_POSTYPE_SAKANA,			//�T�J�i
		ENEMY_POSTYPE_KAI,				//�J�C
		ENEMY_POSTYPE_TAKO,				//�^�R
		ENEMY_POSTYPE_BONUS,			//�{�[�i�X
		ENEMY_POSTYPE_MAX,				//�ő吔
	}ENEMY_POSTYPE;

	CGame();
	~CGame();
	static CGame *Create(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CPlayer *GetPlayer(void);
	static CSound *GetSound(void);
	static CBall *GetBall(void);

	static CUIItem *GetUIItem(void);
	static CSceneMeshFieldBG *GetSceneMeshField(void);

	static CScore *GetScore(void);
	void SetEnemySpawn(int nCntSpawn);
	//�����o�ϐ�
private:
	static CCamera				*m_pCamera;		// �J�����̃|�C���^
	static CLight				*m_pLight;		// ���C�g�̃|�C���^

	static CPlayer				*m_pPlayer;
	static CSound				*m_pSound;
	static CUIItem				*m_pItem;
	static CSceneMeshFieldBG		*m_MeshField;
	static CBall			*m_pBall;
	static CScore				*m_pScore;

	int							m_nFadeCnt;
	bool						g_bPouse;
	int							m_nCntSpawn;
	ENEMY_POSTYPE				m_EnemyPosType;
	bool						m_bSpawnBoss;
};

#endif