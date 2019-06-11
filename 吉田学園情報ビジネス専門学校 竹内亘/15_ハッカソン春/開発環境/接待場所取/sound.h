//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************************
//サウンドクラスの定義
//*********************************************************************
//基本クラス
class CSound
{
public:
	// サウンドファイル
	typedef enum //ラベルと数と並びを揃える
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGMタイトル
		SOUND_LABEL_BGM_TUTORIAL,	// BGMチュートリアル
		SOUND_LABEL_BGM_GAME,		// BGMゲーム
		SOUND_LABEL_BGM_RESULT,		// BGMリザルト
		SOUND_LABEL_BGM_GAMEOVER,	// BGMゲームオーバー
		SOUND_LABEL_BGM_RANKING,	// BGMランキング
		SOUND_LABEL_SE_DECIDE,		// 決定
		SOUND_LABEL_SE_PAUSE,		// ポーズ
		SOUND_LABEL_SE_SELECT,		// セレクト
		SOUND_LABEL_SE_CANCEL,		// キャンセル

		SOUND_LABEL_SE_FOOTSTEP,	// 足音
		SOUND_LABEL_SE_JUMP,		// ジャンプ
		SOUND_LABEL_SE_SCORE,		// スコア加算
		SOUND_LABEL_SE_ITEMGET,		// アイテム獲得
		SOUND_LABEL_SE_SODAFULL,	// 炭酸
		SOUND_LABEL_SE_SODA,		// 炭酸2
		SOUND_LABEL_SE_SODAKAIHOU,	// 解放
		SOUND_LABEL_SE_TUMBLE,		// 転がり
		SOUND_LABEL_SE_HIT00,		// 衝突
		SOUND_LABEL_SE_HIT01,		// 衝突
		SOUND_LABEL_SE_HIT02,		// 衝突
		SOUND_LABEL_SE_START00,		// スタート
		SOUND_LABEL_SE_START01,		// スタート

		SOUND_LABEL_SE_DAMAGE,		// スタート
		SOUND_LABEL_SE_BREAK,		// スタート
		SOUND_LABEL_SE_THROW,		// スタート
		SOUND_LABEL_SE_WARNING,		// スタート

		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	// パラメータ構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

protected:
	IXAudio2				*m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;						// マスターボイスへのポインタ
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};			// ソースボイスへのポインタ
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};			// オーディオデータへのポインタ
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};				// オーディオデータサイズ
    // 各音素材のパラメータ ラベルと数と並びを揃える
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/title.wav", -1 },		// タイトル
		{ "data/BGM/tutorial.wav", -1 },	// チュートリアル
		{ "data/BGM/game.wav", -1 },		// ゲーム
		{ "data/BGM/result.wav", -1 },		// リザルト
		{ "data/BGM/gameover.wav", -1 },	// ゲームオーバー
		{ "data/BGM/ranking.wav", -1 },		// ランキング
		{ "data/SE/decide.wav", 0 },		// 決定音
		{ "data/SE/pause.wav", 0 },			// ポーズ音
		{ "data/SE/select.wav", 0 },		// セレクト音
		{ "data/SE/cansel.wav", 0 },		// キャンセル音
		{ "data/SE/footstep2.wav", 0 },		// 足音
		{ "data/SE/jump.wav", 0 },			// ジャンプ音
		{ "data/SE/score.wav", 0 },			// スコア音
		{ "data/SE/itemget.wav", 0 },		// アイテムゲット音
		{ "data/SE/sodafull.wav", 0 },		// 炭酸音
		{ "data/SE/soda.wav", 0 },			// 炭酸音
		{ "data/SE/kaihou.wav", 0 },		// 解放音
		{ "data/SE/tumble.wav", 0 },		// 転がり音
		{ "data/SE/destroy002.wav", 0 },	// 衝撃音000
		{ "data/SE/destroy003.wav", 0 },	// 衝撃音001
		{ "data/SE/hit.wav", 0 },			// 衝撃音002
		{ "data/SE/Start00.wav", 0 },			// スタート音00
		{ "data/SE/Start01.wav", 0 },			// スタート音01

		{ "data/SE/damage.wav", 0 },		// 衝撃音001
		{ "data/SE/glass-break.wav", 0 },	// 衝撃音002
		{ "data/SE/throw.wav", 0 },			// スタート音00
		{ "data/SE/warning.wav", 0 },		// スタート音01

	};
};
#endif
