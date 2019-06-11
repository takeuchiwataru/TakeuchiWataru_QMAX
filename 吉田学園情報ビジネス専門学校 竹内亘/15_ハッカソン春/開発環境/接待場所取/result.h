//=============================================================================
//
// リザルト処理 [result.h]
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
//　前方宣言
//*****************************************************************************
class CNumber;


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUM	(3)		// 桁数
#define MAX_2D	(2)		// 2Dポリゴンの数

//*********************************************************************
//リザルトクラスの定義
//*********************************************************************
class CResult //基本クラス
{
public:
	typedef enum
	{
		RESULTSTATE_NONE = 0,		//初期状態
		RESULTSTATE_ITEMCNT,		//アイテムを数えている
		RESULTSTATE_TIMECNT,		//タイムを数えている
		RESULTSTATE_END,			//全ての処理が終わった
		RESULTSTATE_MAX,			//最大数
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

	//メンバ変数
private:
	int						m_nCntTimer;
	static CScore			*m_pScore[1];
	CNumber					*m_apItem[MAX_NUM];
	CNumber					*m_apTime[MAX_NUM];
	LPDIRECT3DTEXTURE9		m_pTexture[MAX_2D];				// テクスチャへのポインタ
	CScene2D				*m_pScene2D[MAX_2D];

	static D3DXVECTOR3				m_bluePos;

	RESULTSTATE				m_State;
	int						m_nScore;
	int						m_nTime;
	int						m_nItem;
	int						m_nSoundCnt;
};

#endif