//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CEnemy : public CCharacter
{
public:
	CEnemy(int nPrioryity = CHAR_PRIORITY) : CCharacter::CCharacter(nPrioryity) {};
	~CEnemy() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);	//ゲージセット処理
	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	static bool &GetbWarp(void) { return m_bWarp; };
	static bool &GetbLook(void) { return m_bLook; };

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static bool m_bBGM;	//BGM
	static bool m_bWarp;	//BGM
	static bool m_bLook;	//BGM

	float m_fCntState;
	float m_fWarp;
	float m_fAppear;	//出現時フレームカウント
	bool m_bUse;	//出現しているかどうか
};

#endif
