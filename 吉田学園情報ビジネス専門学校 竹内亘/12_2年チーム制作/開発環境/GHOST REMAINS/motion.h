//=============================================================================
//
// モーション処理 [motion.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "scene.h"
#include "SceneAnim3D.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHAR_PRIORITY	(1)
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CKey
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,	//通常キー
		TYPE_ATTACK,		//攻撃キー
		TYPE_MAX
	}TYPE;
	CKey() { m_pRot = NULL; m_pEffect = NULL; };
	~CKey() {};
	void Uninit(void);

	float		&GetfSlip(void)		{ return m_fSlip; }
	float		&GetfMove(void)		{ return m_fMove; }
	int			&GetnMoveType(void) { return m_nMoveType; }
	D3DXVECTOR3 &GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 *&GetpRot(void)		{ return m_pRot; }
	D3DXVECTOR3 &GetMove(void)		{ return m_move; }
	int			&GetnFrame(void)	{ return m_nFrame; }
	int			&GetnMaxEffect(void){ return m_nMaxEffect; }
	int			*&GetpEffect(void)	{ return m_pEffect; }
	int			&GetnFloating(void) { return m_nFloating; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	float		m_fSlip;		//慣性
	float		m_fMove;		//移動可能かどうか
	int			m_nMoveType;	//移動方法	0:永続 1:単発
	D3DXVECTOR3 m_pos;			//原点移動値
	D3DXVECTOR3 *m_pRot;		//回転値
	D3DXVECTOR3	m_move;			//移動量
	int			m_nFrame;		//フレーム数
	int			m_nMaxEffect;	//下個数
	int			*m_pEffect;		//SAや無敵等、音も
	int			m_nFloating;	//移動方法	0:通常 1:浮遊 2:地面付かない
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CAtkKey : public CKey
{
public:

	CAtkKey() {};
	~CAtkKey() {};

	int			&GetnAtkType(void)			{ return m_nAtkType; }
	int			&GetnAtkParts(void)			{ return m_nAtkParts; }
	int			&GetnCntAtk(void)			{ return m_nCntAtk; }
	int			&GetnHitFrame(int nCount)	{ return m_nHitFrame[nCount]; }
	float		&GetfRange(void)			{ return m_fRange; }
	float		&GetfAtkplus(void)			{ return m_fAtkplus; }
	D3DXVECTOR3 &GetBlown(void)				{ return m_blown; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	int			m_nAtkType;		//攻撃タイプ
	int			m_nAtkParts;	//攻撃部位
	int			m_nCntAtk;		//攻撃個数
	int			m_nHitFrame[2];	//攻撃有効F
	float		m_fRange;		//攻撃範囲
	float		m_fAtkplus;		//ダメージ倍率
	D3DXVECTOR3	m_blown;		//吹っ飛び
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class COneMotion
{
public:

	COneMotion() { m_type = NULL; m_Key = NULL; };
	~COneMotion() {};
	void Uninit(void);

	int			&GetnNorBranch(void)			{ return m_nNorBranch; }
	int			&GetnLandBranch(void)			{ return m_nLandBranch; }
	int			&GetnStartCancel(int nNumber)	{ return m_nStartCancel[nNumber]; }
	int			&GetnEndCancel(int nNumber)		{ return m_nEndCancel[nNumber]; }
	int			&GetnOtherCancel(int nNumber)	{ return m_nOtherCancel[nNumber]; }
	int			&GetnStartKey(void)			{ return m_nStartKey; }
	int			&GetnMaxKey(void)				{ return m_nMaxKey; }
	CKey::TYPE	*&GetType(void)					{ return m_type; }
	CKey		**&GetKey(void)					{ return m_Key; }


private://*****************************************************************************
		//変数宣言//***********************************************************************
	int		m_nNorBranch;		//通常分岐
	int		m_nLandBranch;		//着地分岐
	int		m_nStartCancel[2];	//初動キャンセル	 開始, 終了
	int		m_nEndCancel[2];	//振り切りキャンセル 開始, 終了
	int		m_nOtherCancel[2];	//その他キャンセル	 開始, 終了
	int		m_nStartKey;		//キャンセル時開始フレーム

	int			m_nMaxKey;		//キーの最大数
	CKey::TYPE	*m_type;		//キーのタイプ
	CKey		**m_Key;		//キー本体
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CMotion
{
public:
	typedef enum
	{
		TYPE_BOX_Sword,	//剣
		TYPE_ENEMY,	//敵
		TYPE_MAX
	}TYPE;
	CMotion()	{ m_OneMotion = NULL; };
	~CMotion()	{};

	static void Load(void);
	static void UnLoad(void);
	void Uninit(void);

	static CMotion *GetMotion(int nType)	 { return m_pMotion[nType]; };
	COneMotion *&GetOneMotion(void) { return m_OneMotion; };
	int &GetnMaxParts(void)			 { return m_nMaxParts; };
	int &GetnMaxMotion(void)		 { return m_nMaxMotion; };

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static int			m_nNumMotion;			//最大キャラ数
	static CMotion		**m_pMotion;				//モーション本体

	int m_nMaxParts;	//構成しているパーツ数
	int m_nMaxMotion;	//構成しているモーション数
	COneMotion *m_OneMotion;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCharParts
{
public:
	typedef enum
	{
		PLAYER_hara,		//ボックスリグ	腹
		PLAYER_hip,		//ボックスリグ	尻
		PLAYER_head,		//ボックスリグ	頭
		PLAYER_armUL,		//ボックスリグ	左上腕
		PLAYER_armDL,		//ボックスリグ	下腕
		PLAYER_handL,		//ボックスリグ	手
		PLAYER_armUR,		//ボックスリグ	右上腕
		PLAYER_armDR,		//ボックスリグ	下腕
		PLAYER_handR,		//ボックスリグ	手
		PLAYER_legUL,		//ボックスリグ	左腿
		PLAYER_legDL,		//ボックスリグ	脛
		PLAYER_footL,		//ボックスリグ	足
		PLAYER_legUR,		//ボックスリグ	右腿
		PLAYER_legDR,		//ボックスリグ	脛
		PLAYER_footR,		//ボックスリグ	足

		ENEMY,				//敵
		PARTS_MAX
	}PARTS;
	CCharParts(void) {};
	~CCharParts() {};

	static void SetPlayer(CCharParts **&Parts, int &nMaxParts);
	static void SetEnemy(CCharParts **&Parts, int &nMaxParts);
	void SetParts(PARTS parts, int nPair);

	PARTS		&GetParts(void)		 { return m_type; }
	int			&GetnParent(void)	 { return m_nParent; }
	D3DXMATRIX	&GetmtxWorld(void)	 { return m_mtxWorld; }
	D3DXVECTOR3 &Getaddrot(void)	 { return m_addrot; }
	D3DXVECTOR3 &GetaddRotmove(void) { return m_addRotmove; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	PARTS			m_type;						//モデルの種類 自分
	int				m_nParent;					//親の番号
	D3DXMATRIX		m_mtxWorld;					//ワールドマトリックス
	D3DXVECTOR3		m_addrot;					//加算の向き モーション
	D3DXVECTOR3		m_addRotmove;				//モーションの移動
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCharacter	:	public CScene
{
public:
	typedef struct
	{//種類ごとのモデル情報保存
		LPD3DXMESH		MeshModel = NULL;		//メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffMatModel = NULL;	//マテリアル情報へのポインタ
		DWORD			nNumMatModel = NULL;	//マテリアルの情報数
		D3DXVECTOR3		addPos;					//位置のプラス値
		CScene::TEXTURE	tex;					//画像
		char			aText[32];				//モデル読み込みが遅いため必要になるまでテキストで管理
	}MODEL_PARTS;
	typedef enum
	{
		MOTION_NEUTRAL,		//ニュートラル
		MOTION_WALK,		//歩き
		MOTION_JUMP,		//ジャンプ
		MOTION_LAND,		//着地
	}MOTION;
	CCharacter(int nPrioryity = CHAR_PRIORITY) : CScene::CScene(nPrioryity) { m_pTex = NULL; m_pParts = NULL; m_pScene = NULL; };
	~CCharacter() {};

	static void Load(CCharParts::PARTS parts);
	static void Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(bool bMove);	//モーションの更新
	void Draw(void);
	void CancelUpdate(void);						//モーションのキャンセル更新
	void SetCancelMotion(int nNumber);				//モーションのキャンセル設定
	void ResetMotion(void);							//モーションをニュートラルにリセット
	void SetRotMotion(void);						//現在のキーに角度を完全に合わせる
	void SetPlusFrame(float fPFrame, float fCount);	//フレームの進行速度設定
	void Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLength);	//キャラ同士のあたり判定
	void CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLength, CScene *pChar);	//キャラ同士のあたり判定
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);			//設定処理

	D3DXVECTOR3 &Getpos(void)			{ return m_pos; }
	D3DXVECTOR3 &Getposold(void)		{ return m_posold; }
	D3DXVECTOR3 &Getrot(void)			{ return m_rot; }
	D3DXVECTOR3 &Getmove(void) { return m_move; }
	D3DXVECTOR3 &Getaddpos(void)		{ return m_addpos; }
	D3DXVECTOR3 &GetaddPosmove(void)	{ return m_addPosmove; }
	float		&GetfRot(void)		{ return m_fRot; }
	float		&GetfSpeed(void) { return m_fSpeed; }
	float		&GetfFramePlus(void) { return m_fFramePlus; }
	int			&GetnNumMotion(int nNumber) { return m_nNumMotion[nNumber]; }
	bool		&GetbJump(void) { return m_bJump; }
	float		&GetfCola(void) { return m_fCola; }
	void		Land(void);
	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }

	static MODEL_PARTS *&GetpartsAll(int nNumber) { return m_partsAll[nNumber]; }

private://*****************************************************************************
	void SetEffect(CKey *&pKey);

		//変数宣言//***********************************************************************
	static MODEL_PARTS	*m_partsAll[CCharParts::PARTS_MAX];	//全パーツ情報

	LPDIRECT3DTEXTURE9	m_pTex;				//画像
	CScene::DRAW_TYPE	m_DrawType;			// 描画する方法(加算合成など)
	int				m_nMaxParts;		//パーツ数
	CCharParts		**m_pParts;			//自分のパーツ情報
	CMotion::TYPE	m_Type;				//モーションの種類
	D3DXVECTOR3		m_pos;				//プレイヤーの原点
	D3DXVECTOR3		m_posold;			//前回のモデルの位置
	D3DXVECTOR3		m_rot;				//プレイヤーの向き
	D3DXVECTOR3		m_move;				//モデルの位置
	D3DXVECTOR3		m_addpos;			//加算の位置 モーション
	D3DXVECTOR3		m_addPosmove;		//モーションの移動
	D3DXVECTOR3		m_length;			//ポリゴンの長さ
	D3DXVECTOR3		m_FNor;				//地面の法線
	float			m_fCola;			//透明度
	float			m_fSpeed;			//素早さ
	float			m_fRot;				//移動方向
	int				m_nInvincible;		//無敵時間
	int				m_nNumMotion[4];	//0:現在のモーション 1:次のモーション 2:キー番号 3:前のモーション
	float			m_fFrame;			//現在のフレーム数
	float			m_fFramePlus;		//フレームへのプラス値
	float			m_fFramePlus2;		//フレームへの自由値
	float			m_fInitFrame;		//フレームの速度が初期化されるまでの値
	float			m_fMotionFrame;		//MOTION全体のフレーム数をカウント
	int				m_nCancelFrame;		//キャンセル待ちの保持フレーム数
	int				m_nLeg;				//右足を出しているか左足を出しているか
	int				m_nStamina;			//スタミナ
	int				m_nHit[16];			//殴った敵
	bool			m_bJump;
	CScene			*m_pScene;
	CScene3D		*m_pShadow;			//影のポインタ
	//int				nLockChar;				//lockしているキャラ

};
#endif
