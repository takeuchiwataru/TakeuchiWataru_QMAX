//=============================================================================
//
// シーン処理 [scene.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include "main.h"
#include "scene.h"
#include "sound.h"
#include "manager.h"
#include "2DPolygon.h"
#include "3DPolygon.h"
#include "Number.h"
#include "motion.h"
class	CMesh;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DUNGEON_PRIORYITY	(0)
#define MAP_SIZE		(10)
#define FIELD_SPLIT		(1)
#define FIELD_STRDOWN	(1)
#define FIELD_NUMDOWN	(1 + FIELD_STRDOWN)
#define FIELD_DOWN		(-50.0f)
#define CHIP_SIZE		(800.0f)
#define FIELD_SIZE		((float)(CHIP_SIZE / FIELD_SPLIT))
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CDungeon : public CScene
{
public:
	CDungeon(int nPrioryity = DUNGEON_PRIORYITY) : CScene::CScene(nPrioryity) { };
	~CDungeon() {};

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	static void SetDungeon_Rand(int nStatge);
	static void InitDungeon(void);

private://*****************************************************************************
	//void SetDungeon_Boss(int nStatge);

	static void SetMesh(int *nMap, int nPos, int &nRot, int nPlusX, int nPlusZ, int nLength, float fHeight, CMesh *pField, CMesh *pCeiling);
	static void SetDig(int *nMap, int nPos, int &nRot, int nPlusX, int nPlusZ, int nLengthX, int nLengthZ, float fHeight, float fPHeight, int nChip, CMesh *pField, CMesh *pCeiling);
	static void SpinDig(int &nRot, int &nLengthZ, int &nLengthX);
	static void SetRoom(int *nMap, float *fRoomC, float *fRoadC, int *nCntRoom, int *nCntRoad, CMesh *pField, CMesh *pCeiling);
	static void SetRoad(int *nMap, float *fRoomC, float *fRoadC, int *nCntRoom, int *nCntRoad, CMesh *pField, CMesh *pCeiling);
	static void SettingRoom(float *fRoomC, int *nCntRoom, float fPos, float fRot, float fHeight, float fState);
	static void SettingRoad(float *fRoadC, int *nCntRoad, float fPos, float fRot, float fHeight);

	static float ChangeRot(int &nRot);
	static int SetWall(int *nMap);

	static void SetPpos(D3DXVECTOR3 pos);					//プレイヤーの位置変更
	static void SetGpos(D3DXVECTOR3 pos);					//ゴール地点設置
	static void SetObjRoom(D3DXVECTOR3 pos);				//部屋小
	static void SetObjRoom2(D3DXVECTOR3 pos, float fRot);	//部屋中
	static void SetObjRoad(D3DXVECTOR3 pos);				//通路用
	static void SetObjEntrance(D3DXVECTOR3 pos);			//入口
	static void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);					//エネミーの配置
	
	//変数宣言//***********************************************************************
	static bool		m_bEnd;		//生成が正常終了したかどうか
	CSound::LABEL	m_BGM;		//現在かかっているBGMのラベル
	int				m_nQuake;	//地震のF数
};
#endif
