//=============================================================================
//
// ゲーム処理 [game.h]
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
// 前方宣言
//=============================================================================
class CBall;
//*********************************************************************
//ゲームクラスの定義
//*********************************************************************
class CGame //基本クラス
{
public:
	typedef enum
	{
		ENEMY_POSTYPE_NORMAL = 0,		//カニ
		ENEMY_POSTYPE_IKA,				//イカ
		ENEMY_POSTYPE_KURO,				//クロ
		ENEMY_POSTYPE_SAKANA,			//サカナ
		ENEMY_POSTYPE_KAI,				//カイ
		ENEMY_POSTYPE_TAKO,				//タコ
		ENEMY_POSTYPE_BONUS,			//ボーナス
		ENEMY_POSTYPE_MAX,				//最大数
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
	//メンバ変数
private:
	static CCamera				*m_pCamera;		// カメラのポインタ
	static CLight				*m_pLight;		// ライトのポインタ

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