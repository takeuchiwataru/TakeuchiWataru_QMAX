//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene.h"
#include "shadow.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CModel;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PARTS		(30)
#define MAX_MOTION		(30)

//*****************************************************************************
// 構造体
//*****************************************************************************

//*********************************************************************
//プレイヤークラスの定義
//*********************************************************************
class CEnemy : public CScene //派生クラス
{
public:
	//キー要素
	typedef struct
	{
		float fposX;
		float fposY;
		float fposZ;
		float frotX;
		float frotY;
		float frotZ;
	}KEY;
	//キー情報
	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PARTS];
	}KEY_INFO;

	//モーション情報
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKayInfo[MAX_MOTION];
	}MOTION_INFO;

	typedef enum
	{
		ENEMYSTATE_NONE = 0,		//初期状態
		ENEMYSTATE_NEUTRAL,		//待機
		ENEMYSTATE_NORMAL,			//通常
		ENEMYSTATE_DAMAGE,			//ダメージ
		ENEMYSTATE_DYING,			//瀕死
		ENEMYSTATE_BIG,			//膨らんでいる
		ENEMYSTATE_DEATH,			//死亡
		ENEMYSTATE_APPEAR,			//無敵
		ENEMYSTATE_GAMEEND,		//残機無し終了
		ENEMYSTATE_GAMECLEAR,		//ゲームをクリア
		ENEMYSTATE_MAX,			//最大数
	}ENEMYSTATE;

	typedef enum
	{
		DASHSTATE_NORMAL = 0,		//初期状態
		DASHSTATE_DASH,				//ダッシュ
		DASHSTATE_MAX,				//最大数
	}DASHSTATE;


	typedef enum
	{
		MOTIONSTATE_NEUTRAL = 0,
		MOTIONSTATE_RUN,
		MOTIONSTATE_DAMAGE,
	}MOTIONSTATE;

	CEnemy();
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength);
	static HRESULT Load(void);
	static void UnLoad(void);
	static void HitDamage(int nDamage);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetMove(void);
	MOTIONSTATE GetMotionState(void);
	void SetMotionState(MOTIONSTATE MotionState);
	ENEMYSTATE GetPlayerState(void);
	CModel *GetapModel(int nIdx);

	//地面との当たり判定
	void CollisitionGround(void);
	//オブジェクトの当たり判定
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	bool Collision(D3DXVECTOR3 *pos, float fRadius);	// 当たり判定
	//モーションの更新関数
	void UpdateMotion(void);
	//ファイル読み込み関数
	static void FileLoad(void);						//ファイル読み込み
	static char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	static char *GetLineTop(char *pStr);			//行の先頭を取得
	static int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て
private:
	//メンバ変数
	D3DXVECTOR3					m_pos;					//位置
	D3DXVECTOR3					m_posold;				//前回の位置
	D3DXVECTOR3					m_move;					//移動量
	D3DXVECTOR3					m_rot;					//向き
	ENEMYSTATE					m_State;				//プレイヤーの状態
	D3DXMATRIX					m_mtxWorld;				//ワールドマトリックス
	float						m_fDestAngle;			//プレイヤーの角度
	float						m_fDiffAngle;			//差分
	bool						m_bJump;				//ジャンプ状態
	int							m_nCntTumble;			//回転の数
	bool						m_bLand;				//着地状態
	int							m_nCntAppear;			//無敵時間
	bool						m_bFinish;				//ゴールフラグ
	bool						m_bStart;				//スタートフラグ
	int							m_nGameEndCnt;			//ゲームが終わるまでのカウント
	int							m_nJumpEndTimer;		//ゲーム終了時のジャンプ
	int							m_nStartTimer;			//ゲーム開始時の待機時間
	int							m_nCntTimer;			//ランキングまでのタイマー
	static LPD3DXMESH			m_pMeshModel[MAX_PARTS];		//メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMatModel[MAX_PARTS];		//マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9	m_pTextureModel[MAX_PARTS];		//テクスチャへのポインタ
	static DWORD				m_nNumMatModel[MAX_PARTS];		//マテリアル情報の数
	// モーション関数
	static KEY_INFO				*m_pKeyInfo[MAX_MOTION];		//キー情報へのポインタ
	int							m_nKey;							//現在のキーナンバー
	int							m_nCountFlame;					//フレーム数

	static int					m_nNumParts;					//パーツ数
	static int					m_aIndexParent[MAX_PARTS];		//親のインデックス
	static KEY					m_aKayOffset[MAX_PARTS];		//オフセット情報
	static MOTION_INFO			m_aMotionInfo[MAX_MOTION];		//モーション情報
	int							m_nMotionType;					//モーションのタイプ(int型)
	bool						m_bMotionEnd;					//モーションの終わり
	int							m_nOldMotion;					//前回のモーション
	static D3DXVECTOR3			m_OffSetPos[MAX_PARTS];			//オフセット情報(モーション)
	MOTIONSTATE					m_MotionState;
	DASHSTATE					m_DashState;
	D3DXCOLOR					m_effectCol;
public:
	CModel						*m_apModel[MAX_PARTS];			//パーツ情報
};

#endif