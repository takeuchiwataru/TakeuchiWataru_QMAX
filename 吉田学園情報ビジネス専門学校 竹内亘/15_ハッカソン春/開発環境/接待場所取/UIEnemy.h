//=============================================================================
//
// UIエネミー処理 [UIEnemy.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIENEMY_H_
#define _UIENEMY_H_

#include "main.h"
#include "scene2D.h"

#define MAX_ENEMY2D (1)
#define MAX_ENEMYNUM (3)

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;

//*********************************************************************
//UIエネミークラスの定義
//*********************************************************************
class CUIEnemy : public CScene2D  //派生クラス
{
public:
	CUIEnemy();
	~CUIEnemy();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIEnemy *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	void PlusEnemy(int nAddEnemy);
	int GetEnemyNum(void);
	void SetEnemyBool(bool bGetEnemy);
private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ENEMY2D];	// テクスチャへのポインタ
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_move;						// 移動量
	D3DXVECTOR3					m_posold;					// 前回の位置
	float						m_fWidth, m_fHeight;		// 幅 高さ
	D3DXMATRIX					m_mtrxWorld;				// ワールドマトリックス
	CScene2D					*m_pScene2D[MAX_ENEMY2D];	// 2Dポリゴンへのポインタ
	CNumber						*m_apNumber[MAX_ENEMYNUM];	// 数字へのポインタ
	int							m_nEnemy;					// 獲得数
	bool						m_bGetEnemy;					// 取得状態
	float						m_fScale;					// 拡大縮小量
	int							m_ScaleCounter;				// 拡大縮小のカウンター
};
#endif
