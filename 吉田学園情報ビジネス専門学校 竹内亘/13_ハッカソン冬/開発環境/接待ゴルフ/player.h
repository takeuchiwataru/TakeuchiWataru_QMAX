//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CModel;
class CMeshOrbit;
class CObjectBG;
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
class CPlayer : public CScene //派生クラス
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
		PLAYERSTATE_NONE = 0,		//初期状態
		PLAYERSTATE_NORMAL,			//通常
		PLAYERSTATE_DAMAGE,			//ダメージ
		PLAYERSTATE_DEATH,			//死亡
		PLAYERSTATE_APPEAR,			//無敵
		PLAYERSTATE_GAMEEND,		//残機無し終了
		PLAYERSTATE_GAMECLEAR,		//ゲームをクリア
		PLAYERSTATE_MAX,			//最大数
	}PLAYERSTATE;

	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CPlayer *Create(D3DXVECTOR3 pos, float fLength);
	static HRESULT Load(void);
	static void UnLoad(void);
	static void HitDamage(int nDamage);
	static D3DXVECTOR3 GetPos(void);
	static D3DXVECTOR3 GetRot(void);
	static D3DXVECTOR3 GetMove(void);

	//地面との当たり判定
	void CollisitionGround(void);
	//オブジェクトの当たり判定
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	//敵ビルボードの当たり判定
	void CollisitionBillBoardEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	//アイテムビルボードの当たり判定
	void CollisitionBillBoardItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	//ボールの当たり判定
	void CollisitionBall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

	//モーションの更新関数
	void UpdateMotion(void);

	//ファイル読み込み関数
	void FileLoad(void);						//ファイル読み込み
	char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	char *GetLineTop(char *pStr);				//行の先頭を取得
	int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て
private:
	//メンバ変数
	static D3DXVECTOR3			m_pos;					//位置
	D3DXVECTOR3					m_posold;				//前回の位置
	static D3DXVECTOR3			m_move;					//移動量
	static D3DXVECTOR3			m_rot;					//向き
	static PLAYERSTATE			m_State;				//プレイヤーの状態
	D3DXMATRIX					m_mtxWorld;				//ワールドマトリックス
	float						m_fDestAngle;			//プレイヤーの角度
	float						m_fDiffAngle;			//差分
	bool						m_bJump;				//ジャンプ状態
	bool						m_bLand;				//着地状態
	int							m_nGameEndCnt;			//ゲームが終わるまでのカウント
	int							m_nJumpEndTimer;		//ゲーム終了時のジャンプ

	static LPD3DXMESH			m_pMeshModel[MAX_PARTS];		//メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMatModel[MAX_PARTS];		//マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9	m_pTextureModel[MAX_PARTS];		//テクスチャへのポインタ
	static DWORD				m_nNumMatModel[MAX_PARTS];		//マテリアル情報の数
	// モーション関数
	KEY_INFO					*m_pKeyInfo[MAX_MOTION];		//キー情報へのポインタ
	int							m_nKey;							//現在のキーナンバー
	int							m_nCountFlame;					//フレーム数

	int							m_nNumParts;					//パーツ数
	int							m_aIndexParent[MAX_PARTS];		//親のインデックス
	KEY							m_aKayOffset[MAX_PARTS];		//オフセット情報
	MOTION_INFO					m_aMotionInfo[MAX_MOTION];		//モーション情報
	int							m_nMotionType;					//モーションのタイプ(int型)
	bool						m_bMotionEnd;					//モーションの終わり
	D3DXVECTOR3					m_OffSetPos[MAX_PARTS];			//オフセット情報(モーション)
	CObjectBG					*m_pHole;						//穴情報
public:
	CModel						*m_apModel[MAX_PARTS];			//パーツ情報
	CMeshOrbit					*m_pMeshOrbit;					//軌跡情報
};

#endif