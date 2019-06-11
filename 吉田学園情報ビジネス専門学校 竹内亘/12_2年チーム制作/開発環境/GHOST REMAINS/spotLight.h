//=============================================================================
//
// スポットライト処理 [spotLight.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TITLE_LIGHT (5)

//========================================
// クラスの定義
//========================================
//=====================
// ライトクラス
//=====================
class CSpotLight
{
public:
	CSpotLight();		// コンストラクタ
	~CSpotLight();		// デストラクタ

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Set(void);

private:
	static D3DLIGHT9 m_light[MAX_TITLE_LIGHT];	// ライトの情報
	D3DXVECTOR3 m_pos;
	int m_nCntTime;
	bool m_bLight;
	int m_nCountLighting;
};

#endif
