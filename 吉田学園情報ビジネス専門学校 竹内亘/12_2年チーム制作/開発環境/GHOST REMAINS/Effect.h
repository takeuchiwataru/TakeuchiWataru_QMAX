//=============================================================================
//
// シーン処理 [scene2D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene.h"
#include "SceneAnim3D.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define S2D_PRIORITY		(6)
//*****************************************************************************
// クラスの定義
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
		//変数宣言//***********************************************************************
	TYPE			m_Type;			// セット情報
	D3DXVECTOR3		m_posold;		// 自身前の位置
	float			*m_pPos[3];		// 追尾する原点 X, Y, Z
	D3DXVECTOR3		*m_rot;			// 原点からの角度
	float			m_fDistance;	// 原点からのプラス値
	float			m_fLength;		//進んだ距離保存
	float			m_fInterval;	//セットまでの間隔
	int				m_nLife;		//寿命
	bool			*m_bDelete;		//消える判定
};

#endif
