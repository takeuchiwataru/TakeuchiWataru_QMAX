//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CPlayer : public CCharacter
{
public:
	CPlayer(int nPrioryity = CHAR_PRIORITY) : CCharacter::CCharacter(nPrioryity) {};
	~CPlayer() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);	//ゲージセット処理
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);

	bool &GetbDrop(void) { return m_bDrop; }
	float &GetfStop(void) { return m_fStop; }
	float &GetfHeart(void) { return m_fHeart; }

private://*****************************************************************************
	//変数宣言//***********************************************************************
	float m_fHeart;		//心臓音
	float m_fDistance;	//カメラとの距離
	float m_fStop;		//プレイヤーのStop
	bool  m_bDrop;		//落下死
};

#endif
