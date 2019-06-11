//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSound
{// サウンドクラス
public:
	typedef enum
	{// サウンドファイル
		/* *** BGM *** */
		LABEL_TITLE = 0,		// タイトル
		LABEL_TUTORIAL,		// チュートリアル
		LABEL_GAME,			// ゲーム
		LABEL_ESCAPE,			// 追われている
		LABEL_CLEAR,			// クリア
		LABEL_OVER,			// ゲームオーバー
		LABEL_RESULT,		// チュートリアル
		LABEL_RANKING,		// ランキング
		LABEL_SE_START,		// スタート
		LABEL_SE_ENEMY,		// 敵の出現
		LABEL_SE_DETH,		// プレイヤーの死亡音
		LABEL_SE_APPIROBJ,	// オブジェクト出現音
		LABEL_SE_DropBrock,	// 落ちる床
		LABEL_SE_HEARTBEAT,	// 心拍音
		LABEL_SE_JUMP,		// ジャンプ
		LABEL_SE_SPEAR,		// 槍
		LABEL_SE_SWICH,		// ボタン
		LABEL_SE_FIRE,		// 炎
		LABEL_SE_LAND,		// 着地
		LABEL_SE_PAUSE,		// ポーズ
		LABEL_SE_ENTTER,		// 決定音
		LABEL_SE_CURSOR,		// カーソル
		LABEL_SE_WALK,		// 歩く
		LABEL_SE_CANCEL,		// キャンセル
		LABEL_SE_RANKING,		// ランキング

		LABEL_MAX	// 総数
	} LABEL;

	CSound();
	~CSound() {};
	HRESULT Init(HWND hWnd);
	void	Uninit(void);
	HRESULT Play(LABEL label);
	void	Stop(LABEL label);
	void	Stop(void);
	void	CountUp(void);
	void	CountReset(LABEL label) { m_aSoundParam[label].nCntFrame = 0; };
private:
	typedef struct
	{// パラメータ
		char *pFilename;	// ファイル名
		int  nCntLoop;		// ループカウント(-1でループ再生)
		int  nPlayNext;		//次の再生までに必要なF数
		int  nCntFrame;		//現在のFカウント
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイスへのポインタ
	IXAudio2SourceVoice	*m_apSourceVoice[LABEL_MAX];	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[LABEL_MAX];						// オーディオデータへのポインタ
	DWORD m_aSizeAudio[LABEL_MAX];						// オーディオデータサイズ

	// 各音素材のパラメータ
	PARAM m_aSoundParam[LABEL_MAX] =
	{
		/* *** BGM *** */
		{ "data/BGM/00_title.wav", -1, 5 },			// タイトル
		{ "data/BGM/01_tutorial.wav", -1, 5 },		// チュートリアル
		{ "data/BGM/02_game.wav", -1, 5 },			// ゲーム
		{ "data/BGM/03_escape.wav", -1, 5 },		// 追われている
		{ "data/BGM/04_gameclear.wav", -1, 5 },		// ゲームクリア
		{ "data/BGM/05_gameover.wav", -1, 5 },		// ゲームオーバー
		{ "data/BGM/Result.wav", -1, 5 },		// リザルト
		{ "data/BGM/06_ranking.wav", -1, 5 },		// ランキング
		{ "data/SE/00_gamestart.wav", 0, 5 },		// ゲームスタート
		{ "data/SE/01_enemyappearance.wav", 0, 5 },	// 敵の出現
		{ "data/SE/02_death.wav", 0, 120 },			// 死亡
		{ "data/SE/03_appearance.wav", 0, 5 },		// オブジェクトの出現
		{ "data/SE/04_Drop.wav", 0, 5 },			// 落ちる床
		{ "data/SE/05_heartbeat.wav",0, 5 },		// 心音
		{ "data/SE/06_jump.wav",0, 5 },				// ジャンプ
		{ "data/SE/07_spear.wav",0, 5 },			// 槍
		{ "data/SE/08_swich02.wav",0, 5 },			// ボタン
		{ "data/SE/09_fire.wav",0, 5 },				// 炎
		{ "data/SE/10_landing.wav",0, 5 },			// 歩く
		{ "data/SE/11_pause.wav",0, 5 },			// ポーズ音
		{ "data/SE/12_decision.wav",0, 5 },			// 決定音
		{ "data/SE/13_cursor.wav",0, 5 },			// カーソル音
		{ "data/SE/15_foot.wav",0, 5 },				// キャンセル音
		{ "data/SE/14_cancel.wav",0, 5 },			// キャンセル音
		{ "data/SE/RankingSE.wav",0, 5 },			// キャンセル音

	};
};

#endif
