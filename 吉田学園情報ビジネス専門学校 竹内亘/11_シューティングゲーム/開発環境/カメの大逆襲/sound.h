//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
	} SOUNDPARAM;

	//*************************************
	// サウンドファイル
	//*************************************
	typedef enum //ラベルと数と並びを揃える
	{
		SOUND_LABEL_BGM_GAME = 0,
		SOUND_LABEL_BGM_TITLE,
		SOUND_LABEL_BGM_TUTORIAL,
		SOUND_LABEL_BGM_CLEAR,
		SOUND_LABEL_BGM_OVER,
		SOUND_LABEL_SE_BABURU,
		SOUND_LABEL_SE_EXPLOSION,
		SOUND_LABEL_SE_PS,
		SOUND_LABEL_SE_DAMAGE,
		SOUND_LABEL_SE_SELECT,
		SOUND_LABEL_SE_ENETR,
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();

	virtual HRESULT Init(HWND hWnd);
	virtual void Uninit(void);

	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイスへのポインタ
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータへのポインタ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	// 各音素材のパラメータ ラベルと数と並びを揃える
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{"data/BGM/game.wav",-1},		// ゲームBGM
		{"data/BGM/title.wav",-1 },		// タイトルBGM
		{"data/BGM/tutorial.wav",-1 },	// チュートリアルBGM
		{"data/BGM/clear.wav",-1 },		// クリアBGM
		{"data/BGM/over.wav",-1 },		// オーバーBGM
		{"data/SE/baburu.wav",0},		// 弾の発射(バブル)
		{"data/SE/explosion.wav",0 },	// 爆発(バブル)
		{"data/SE/ps.wav",0 },	// 爆発(バブル)
		{"data/SE/damage.wav",0},		// ダメージ
		{"data/SE/select.wav", 0 },		// 選択音
		{"data/SE/enter.wav", 0 },		// 決定音

		//{ "data/BGM/game.wav", -1 },		// ゲームBGM
		//{ "data/BGM/title.wav", -1 },		// タイトルBGM
		//{ "data/BGM/3Dranking.wav", -1 },		// ランキングBGM
		//{ "data/BGM/gameclear.wav", -1 },	// ゲームクリアBGM
		//{ "data/BGM/gameover.wav", -1 },	// ゲームオーバーBGM
		//{ "data/SE/karasu.wav", 0 },		// カラスの鳴き声
		//{ "data/SE/pause000.wav", 0 },		// ポーズ開く
		//{ "data/SE/pause001.wav", 0 },		// ポーズ閉じる
		//{ "data/SE/select000.wav", 0 },		// 選択音
		//{ "data/SE/enter001.wav", 0 },		// 決定音
	};
};
#endif
