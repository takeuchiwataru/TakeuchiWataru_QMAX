//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "player.h"
#include "film.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "animal.h"
#include "model.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_FILENAME   "MODEL_FILENAME"
#define CHARACTERSET     "CHARACTERSET"
#define MOVE             "MOVE"
#define JUMP             "JUMP"
#define INDEX            "INDEX"
#define PARENT           "PARENT"
#define POS              "POS"
#define ROT              "ROT"
#define PARTSSET         "PARTSSET"
#define END_PARTSSET     "END_PARTSSET"
#define END_CHARACTERSET "END_CHARACTERSET"
#define MOTIONSET        "MOTIONSET"
#define LOOP             "LOOP"
#define NUM_KEY          "NUM_KEY"
#define KEYSET           "KEYSET"
#define FRAME            "FRAME"
#define KEY              "KEY"
#define END_KEY          "END_KEY"
#define END_KEYSET       "END_KEYSET"
#define END_MOTIONSET    "END_MOTIONSET"

#define PLAYER_INERTIA   (0.123f)                                  // 慣性
#define GRAVITY_POWER    (-0.4f)                                   // 重力

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PlayerOperation(void);          // プレイヤーの操作処理
void PlayerTransition(void);         // プレイヤーの遷移処理
void PlayerAction(void);             // プレイヤーがアクション状態の処理
void PlayerMotion(void);             // モーション処理
void PlayerMotionBlend(void);        // モーションブレンド処理
void PlayerMotionAdvance(void);      // モーション進行処理
void SwitchKey(void);                // キーフレームの切り替え処理
void SwitchMotion(void);             // モーション切り替え処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player  g_Player;                 // プレイヤー情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	FILE  *pFile;           // テキストファイルへのポインタ
	char  str0[128];        // いらない文字
	char  xFileName[64];    // xファイルの名前
	D3DXVECTOR3 OffsetPos;  // 親モデルからの距離
	D3DXVECTOR3 OffsetRot;  // 親モデルからの向き
	float fJump;            // ジャンプ力
	float fMovement;        // 移動量
	int   nIdxParent;       // 親モデル
	int   nCntModel = 0;    // モデルを読み込んだ数を数える変数
	int   nCntParts = 0;    // モデルのパーツ情報を読み込んだ回数を数える変数
	int   nCntPlayer = 0;   // プレイヤーの数
	int   nCntMotion = 0;   // モーションの番号
	int   nCntKey = 0;      // キーフレームの番号を数える変数
	int   nPlaybackKey;     // フレーム数
	int   nCntKeyModel = 0; // モデルの数分のキーフレームを数える変数
	int   bLoop;            // モーションがループするかしないか
	int   nNumKey = 0;      // キーフレームの数
	D3DXVECTOR3 posAdd;     // 基準の位置に加える値
	D3DXVECTOR3 DestAngle;  // 目的の向き

	// ファイルオープン
	pFile = fopen("data/TEXT/motion.txt", "r");

	if (pFile != NULL)
	{// ファイルが開けた
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// テキストファイルの末端まで文字列を改行か空白があるまで読み取る
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// xファイルの拡張子が書かれていたら
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// モデルのファイル名を読み取ったら
					// xファイルの読み込み
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_Player.aModel[nCntModel].pBuffMat,
						NULL,
						&g_Player.aModel[nCntModel].nNumMat,
						&g_Player.aModel[nCntModel].pMesh);

					// マテリアル情報からテクスチャを引き出す
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_Player.aModel[nCntModel].nNumMat];
					g_Player.aModel[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[g_Player.aModel[nCntModel].nNumMat];

					for (DWORD nCntMat = 0; nCntMat < g_Player.aModel[nCntModel].nNumMat; nCntMat++)
					{// 頂点数の数だけ繰り返し 
					 // マテリアル情報を読み込む
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// 環境光を初期化する
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// テクスチャ情報を初期化
						g_Player.aModel[nCntModel].pTexture[nCntMat] = NULL;

						// テクスチャの情報を読み込む
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// テクスチャのファイル名がある
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_Player.aModel[nCntModel].pTexture[nCntMat]);
						}

					}
				}
				nCntModel++;  // 種類が変わるので進めておく
			}
			if (strcmp(&str0[0], CHARACTERSET) == 0)
			{// キャラクター情報が書かれていたら
				while (strcmp(&str0[0], END_CHARACTERSET) != 0)
				{// キャラクター情報が終わるまで読み取る
					if (strcmp(&str0[0], MOVE) == 0)
					{// 移動力が書かれていたら
						if (fscanf(pFile, "%s %f", &str0[0], &fMovement) == 2)
						{// 移動力を読み取ったら
							g_Player.fMovement = fMovement;
						}
					}
					if (strcmp(&str0[0], JUMP) == 0)
					{// ジャンプ力が書かれていたら
						if (fscanf(pFile, "%s %f", &str0[0], &fJump) == 2)
						{// ジャンプ力を読み取ったら
							g_Player.fJumpPower = fJump;
						}
					}

					if (strcmp(&str0[0], PARTSSET) == 0)
					{// モデルのパーツ情報が書かれていたら
						int nCntSet = 0;
						int nCntPartsNum = 0;
						while (strcmp(&str0[0], END_PARTSSET) != 0)
						{// モデルのパーツ情報が終わるまで読み取る
							if (strcmp(&str0[0], INDEX) == 0)
							{// パーツ番号を読み取る
								fscanf(pFile, "%s %d", &str0[0], &nCntPartsNum);
							}
							else if (strcmp(&str0[0], PARENT) == 0)
							{// 親モデルの番号を読み取る
								if (fscanf(pFile, "%s %d", &str0[0], &nIdxParent) == 2)
								{// 親モデルの番号を読み取る
									g_Player.aModel[nCntPartsNum].nIdxModelParent = nIdxParent;
								}
							}
							else if (strcmp(&str0[0], POS) == 0)
							{// 親モデルからの距離を読み取る
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetPos.x, &OffsetPos.y, &OffsetPos.z) == 4)
								{// 座標情報を読み取ったら
									g_Player.aModel[nCntPartsNum].pos = OffsetPos;
								}
							}
							else if (strcmp(&str0[0], ROT) == 0)
							{// 親モデルからの向きを読み取る
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetRot.x, &OffsetRot.y, &OffsetRot.z) == 4)
								{// 向き情報を読み取ったら
									g_Player.aModel[nCntPartsNum].rot = OffsetRot;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
							nCntSet++;                     // セットした回数を増やす
						}
					}
					fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
				}
			}
			if (strcmp(&str0[0], MOTIONSET) == 0)
			{// モーション情報が書かれていたら
				nCntKey = 0;    // キーフレームのポインタ座標を戻す
				while (strcmp(&str0[0], END_MOTIONSET) != 0)
				{// モーション情報が終わるまで読み取る
					if (strcmp(&str0[0], LOOP) == 0)
					{// ループするかしないかを読み取る
						if (fscanf(pFile, "%s %d", &str0[0], &bLoop) == 2)
						{// ループするかしないかを読み取れた
							if (bLoop == 1)
							{
								g_Player.aMotion[nCntMotion].bLoop = true;
							}
							else
							{
								g_Player.aMotion[nCntMotion].bLoop = false;
							}
						}
					}
					else if (strcmp(&str0[0], NUM_KEY) == 0)
					{// キーフレーム数を読み取る
						if (fscanf(pFile, "%s %d", &str0[0], &nNumKey) == 2)
						{// キーフレーム数を読み取れた
							g_Player.aMotion[nCntMotion].nNumKey = nNumKey;
						}
					}
					else if (strcmp(&str0[0], KEYSET) == 0)
					{// キーフレーム情報が書かれていたら
						nCntKeyModel = 0;
						while (strcmp(&str0[0], FRAME) != 0)
						{// キーフレーム数情報が終わるまで読み取る
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
						}
						if (fscanf(pFile, "%s %d", &str0[0], &nPlaybackKey) == 2)
						{// キーフレーム数を読み取れた
							g_Player.aMotion[nCntMotion].Key[nCntKey].nPlayBackKey = nPlaybackKey;
						}
						while (strcmp(&str0[0], END_KEYSET) != 0)
						{// キーフレーム情報が終わるまで読み取る
							if (strcmp(&str0[0], KEY) == 0)
							{// キーフレームの目的の位置情報が書かれていたら
								while (strcmp(&str0[0], END_KEY) != 0)
								{// キーフレームの目的の位置情報が終わるまで読み取る
									if (strcmp(&str0[0], POS) == 0)
									{// 座標情報を読み取る
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &posAdd.x, &posAdd.y, &posAdd.z) == 4)
										{// 座標情報を読み取ったら
											g_Player.aMotion[nCntMotion].Key[nCntKey].posAdd[nCntKeyModel] = posAdd;
										}
									}
									else if (strcmp(&str0[0], ROT) == 0)
									{// 向き情報を読み取る
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &DestAngle.x, &DestAngle.y, &DestAngle.z) == 4)
										{// 向き情報を読み取ったら
											g_Player.aMotion[nCntMotion].Key[nCntKey].DestAngle[nCntKeyModel] = DestAngle;
										}
									}
									fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
								}
								if (nCntKeyModel < MAX_MODEL - 1)
								{// モデルごとのキーフレームが用意できる数までよりポインタが進んでない
									nCntKeyModel++;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
						}
						if (nCntKey < MAX_MODEL - 1)
						{// キーフレームが用意できる数までよりポインタが進んでない
							nCntKey++;
						}
					}
					fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
				}
				if (nCntMotion < MAX_MOTION - 1)
				{// モーションが用意できる数までよりポインタが進んでない
					nCntMotion++;   // モーション番号をずらす
				}
			}
		}
	}

	// ファイルを閉じて他のプログラムからいじれるようにする
	fclose(pFile);

	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);           // 移動量を初期化
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);            // 現在の向きを初期化
	g_Player.DestAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 目的の向きを初期化
	g_Player.DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 差分を初期化
	g_Player.state = PLAYERSTATE_NORMAL;                     // 通常の状態に
	g_Player.radius = D3DXVECTOR3(11.5f, 30.0f, 11.5f);      // 当たり判定を取る範囲を初期化
	g_Player.ShadowCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f); // 影の色を設定
	g_Player.ShadowWidth = 15;                               // 影の幅を設定
	g_Player.ShadowDepth = 15;                               // 影の奥行を設定
	g_Player.bJump = false;                                  // ジャンプしていない状態に
	g_Player.mState = MOTIONSTATE_NORMAL;                    // モーションの状態は通常の状態に

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数分繰り返し
		g_Player.aModel[nCntModel].posStd = g_Player.aModel[nCntModel].pos;
		g_Player.aModel[nCntModel].rot = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel];
	}

	// 影の番号を設定
	g_Player.nIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 1.0f, g_Player.pos.z), g_Player.rot, g_Player.ShadowCol, g_Player.ShadowWidth, g_Player.ShadowDepth);

	// モーション遷移処理
	SwitchMotion();

	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 現在の位置を初期化
	g_Player.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 現在の位置を初期化
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数だけ繰り返し
		// メッシュの破棄
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		// マテリアルの破棄
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}

		// テクスチャの破棄
		for (DWORD nCntMat = 0; nCntMat < g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			if (g_Player.aModel[nCntModel].pTexture[nCntMat] != NULL)
			{
				g_Player.aModel[nCntModel].pTexture[nCntMat]->Release();
				g_Player.aModel[nCntModel].pTexture[nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	if (g_Player.state != PLAYERSTATE_TAKEPICTURE
		&& g_Player.state != PLAYERSTATE_LANDING)
	{// 動ける状態である
		// 移動処理
		PlayerOperation();
	}

	// 操作できるプレイヤーの遷移処理
	PlayerTransition();

	if (g_Player.state == PLAYERSTATE_TAKEPICTURE)
	{// プレイヤーがアクション状態である
		PlayerAction();
	}

	if (g_Player.mState == MOTIONSTATE_NORMAL)
	{// 通常のモーション状態だったら
		// モーション処理
		PlayerMotion();
	}
	else if (g_Player.mState == MOTIONSTATE_SWITCH)
	{// モーション切り替え状態だったら
		// モーションブレンド処理
		PlayerMotionBlend();
	}

	if (g_Player.mState == MOTIONSTATE_NORMAL)
	{// キーフレームを進める状態だったら
		// モーション進行処理
		PlayerMotionAdvance();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;     // 計算用マトリックス
	D3DXVECTOR3 vecRot, vecTrans;               // 計算用モデルの向き,座標
	D3DMATERIAL9 matDef;                        // 現在のマテリアル保存用
	D3DXMATERIAL *pMat;                         // マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数だけ繰り返し
		if (g_Player.aModel[nCntModel].nIdxModelParent == -1)
		{// 親がいない
			mtxParent = g_Player.mtxWorld;     // プレイヤーのマトリックス情報をもらう
		}
		else
		{// 親がいる
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;   // 親モデルのマトリックス情報をもらう
		}
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTrans);

		// 親の情報を自分に反映
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{// 設定されていたマテリアルの数だけ繰り返し
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_Player.aModel[nCntModel].pTexture[nCntMat]);

			// モデル(パーツ)の描画
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}

		// 保存していたマテリアルに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// プレイヤーの操作処理
//=============================================================================
void PlayerOperation(void)
{
	g_Player.posold = g_Player.pos;   // 前回の位置更新

	//------------------
	// キーボード操作
	//------------------
	if (GetKeyboardPress(DIK_A) == true)
	{// 左方向の入力がされた
		Camera *pCamera;
		pCamera = GetCamera();
		if (GetKeyboardPress(DIK_W) == true)
		{// 同時に上方向の入力がされた
		    // 移動処理
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player.fMovement;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player.fMovement;

			// 目的の角度変更
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.75f);
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// 同時に下方向の入力がされた
		    // 移動処理
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player.fMovement;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player.fMovement;

			 // 目的の角度変更
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.25f);
			
		}
		else
		{// 何も押されてない
		 // 移動処理
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player.fMovement;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player.fMovement;

			// 目的の角度変更
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.5f);
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{// 右方向の入力がされた
		Camera *pCamera;
		pCamera = GetCamera();
		if (GetKeyboardPress(DIK_W) == true)
		{// 同時に上方向の入力がされた
		 // 移動処理
			g_Player.move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player.fMovement;
			g_Player.move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player.fMovement;

			// 目的の角度変更
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.75f);
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// 同時に下方向の入力がされた
		 // 移動処理
			g_Player.move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player.fMovement;
			g_Player.move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player.fMovement;

			// 目的の角度変更
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.25f);

		}
		else
		{// 何も押されてない
		 // 移動処理
			g_Player.move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player.fMovement;
			g_Player.move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player.fMovement;

			// 目的の角度変更
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.5f);
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{// 上方向の入力がされた
		Camera *pCamera;
		pCamera = GetCamera();

		// 移動処理
		g_Player.move.x += sinf(pCamera->rot.y) * g_Player.fMovement;
		g_Player.move.z += cosf(pCamera->rot.y) * g_Player.fMovement;

		// 目的の角度変更
		g_Player.DestAngle.y = pCamera->rot.y + D3DX_PI;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{// 下方向の入力がされた
		Camera *pCamera;
		pCamera = GetCamera();

		// 移動処理
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * g_Player.fMovement;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * g_Player.fMovement;

		g_Player.DestAngle.y = pCamera->rot.y;

	}
	else if (GetJoyPadPress(DIJS_BUTTON_18,0) == true || GetJoyPadPress(DIJS_BUTTON_19,0) == true
		|| GetJoyPadPress(DIJS_BUTTON_20,0) == true || GetJoyPadPress(DIJS_BUTTON_21,0) == true)
	{// 十字キー入力がされた
		Camera *pCamera;
		pCamera = GetCamera();

		// 移動処理
		g_Player.move.x += sinf(pCamera->rot.y + GetJotPadRadian(0)) * g_Player.fMovement;
		g_Player.move.z += cosf(pCamera->rot.y + GetJotPadRadian(0)) * g_Player.fMovement;

		// 目的の角度変更
		g_Player.DestAngle.y = pCamera->rot.y + GetJotPadRadian(0) - D3DX_PI;

	}
	else if (GetJoyPadPress(DIJS_BUTTON_10,0) == true || GetJoyPadPress(DIJS_BUTTON_11,0) == true ||
		GetJoyPadPress(DIJS_BUTTON_12,0) == true || GetJoyPadPress(DIJS_BUTTON_13,0) == true)
	{// 左アナログスティックの入力がされた
		Camera *pCamera;
		pCamera = GetCamera();

		// 移動処理
		g_Player.move.x -= sinf(pCamera->rot.y - GetJotPadRightStick(0)) * g_Player.fMovement;
		g_Player.move.z -= cosf(pCamera->rot.y - GetJotPadRightStick(0)) * g_Player.fMovement;

		// 目的の角度変更
		g_Player.DestAngle.y = pCamera->rot.y - GetJotPadRightStick(0);

	}

	if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoyPadPress(DIJS_BUTTON_1,0) == true)
	{// ジャンプボタンが押された
		if (g_Player.bJump == false)
		{// ジャンプしていない
 			g_Player.move.y += g_Player.fJumpPower;   // 上昇させる
			g_Player.bJump = true;                    // ジャンプした状態に
			g_Player.state = PLAYERSTATE_JUMP;        // ジャンプ状態に
			// モーション切り替え処理
			SwitchMotion();
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadPress(DIJS_BUTTON_2, 0) == true)
	{// アクションボタンが押された
		if (GetFilmNum() > 0)
		{// 撮れる写真のフィルムがまだある
			if (g_Player.state = PLAYERSTATE_TAKEPICTURE)
			{// 写真を取っていない
				g_Player.state = PLAYERSTATE_TAKEPICTURE;    // 写真を取る状態に
				// モーション切り替え処理
				SwitchMotion();
			}
		}
	}
}
//=============================================================================
// プレイヤーの状態遷移処理
//=============================================================================
void PlayerTransition(void)
{
	// 重力を加算する
	g_Player.move.y += GRAVITY_POWER;

	// 位置を移動
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	// 角度の修正
	g_Player.DiffAngle.y = g_Player.DestAngle.y - g_Player.rot.y;   // 現在の向きと目的の向きの差分を計算

	if (g_Player.DiffAngle.y > D3DX_PI)
	{// 差分がD3DX_PIを超えた
		g_Player.DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player.DiffAngle.y < -D3DX_PI)
	{// 差分が-D3DX_PIを超えた
		g_Player.DiffAngle.y += D3DX_PI * 2.0f;
	}

	g_Player.rot.y += g_Player.DiffAngle.y * 0.1f;

	if (g_Player.rot.y > D3DX_PI)
	{// 現在の向きがD3DX_PIを超えた
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player.rot.y < -D3DX_PI)
	{// 現在の向きが-D3DX_PIを超えた
		g_Player.rot.y += D3DX_PI * 2.0f;
	}

	if (g_Player.bJump == false && g_Player.state != PLAYERSTATE_LANDING && g_Player.state != PLAYERSTATE_TAKEPICTURE)
	{// ジャンプしていないかつ着地状態でないかつ写真を撮っていない
		if (g_Player.move.x <= 1.0f && g_Player.move.x >= -1.0f &&
			g_Player.move.z <= 1.0f && g_Player.move.z >= -1.0f)
		{// 移動していなかったら
			if (g_Player.state != PLAYERSTATE_NORMAL)
			{// 移動していない状態じゃなかったら
				g_Player.state = PLAYERSTATE_NORMAL;     // 通常の状態に
				// モーション切り替え処理
				SwitchMotion();
			}
		}
		if (g_Player.move.x > 1.0f || g_Player.move.x < -1.0f ||
			g_Player.move.z > 1.0f || g_Player.move.z < -1.0f)
		{// 移動していたら
			if (g_Player.state != PLAYERSTATE_MOVE)
			{// 移動している状態じゃなかったら
				g_Player.state = PLAYERSTATE_MOVE;       // 移動している状態に
				// モーション切り替え処理
				SwitchMotion();
			}
		}
	}

	// 影の位置更新
	SetPositionShadow(g_Player.nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 1.0f, g_Player.pos.z));

	// 影の色更新
	SetColShadow(g_Player.nIdxShadow, g_Player.ShadowCol);

	// 影の大きさ更新
	SetSizeShadow(g_Player.nIdxShadow, g_Player.ShadowWidth, g_Player.ShadowDepth);

	if (g_Player.pos.y < 0.0f)
	{// 着地した
		g_Player.pos.y = 0.0f;         // 位置を戻す
		g_Player.move.y = 0.0f;        // 重力を消す
		g_Player.ShadowWidth = 15;     // 影の幅を戻す
		g_Player.ShadowDepth = 15;     // 影の奥行を戻す
		g_Player.ShadowCol.a = 0.15f;  // 影の透明度を戻す
		if (g_Player.state == PLAYERSTATE_JUMP)
		{// ジャンプ状態だったら
			if (g_Player.bJump == true)
			{// ジャンプしていた
				if (g_Player.move.x <= 1.0f && g_Player.move.x >= -1.0f &&
					g_Player.move.z <= 1.0f && g_Player.move.z >= -1.0f)
				{// 移動していなかったら
					g_Player.state = PLAYERSTATE_LANDING;        // 着地状態に
																 // モーション切り替え処理
					SwitchMotion();
					g_Player.move.x = 0.0f;   // 移動を無視する
					g_Player.move.z = 0.0f;   // 移動を無視する

				}
				else if (g_Player.move.x > 1.0f || g_Player.move.x < -1.0f ||
					g_Player.move.z > 1.0f || g_Player.move.z < -1.0f)
				{// 移動していたら
					g_Player.state = PLAYERSTATE_MOVE;           // 移動している状態に
					// モーション切り替え処理
					SwitchMotion();
				}
			}
			PlaySound(SOUND_LABEL_SE_GROUND);
		}
		g_Player.bJump = false;      // ジャンプしていない判定に
	}

	if (g_Player.pos.x - 50.0f <= -1450.0f)
	{// 公園の左から出ようとした
		g_Player.pos.x = -1400.0f;
	}
	if (g_Player.pos.x + 50.0f >= 1450.0f)
	{// 公園の右から出ようとした
		g_Player.pos.x = 1400.0f;
	}
	if (g_Player.pos.z - 50.0f <= -1450.0f)
	{// 公園の前から出ようとした
		g_Player.pos.z = -1400.0f;
	}
	if (g_Player.pos.z + 50.0f >= 1450.0f)
	{// 公園の後ろから出ようとした
		g_Player.pos.z = 1400.0f;
	}

	CollisionModel(&g_Player.pos, &g_Player.posold, &g_Player.move, D3DXVECTOR3(40.0f, 50.0f, 40.0f));

	// 慣性を働かせる
	g_Player.move.x += (0.0f - g_Player.move.x) * PLAYER_INERTIA;
	g_Player.move.z += (0.0f - g_Player.move.z) * PLAYER_INERTIA;

	if (g_Player.bJump == true)
	{// ジャンプしていたら
		if (g_Player.move.y > 0.0f)
		{// 空中に上がっている
			g_Player.ShadowWidth -= 0.3f;
			g_Player.ShadowDepth -= 0.3f;
			g_Player.ShadowCol.a -= 0.006f;
		}
		else if (g_Player.move.y < 0.0f)
		{// 地上に落ちている
			g_Player.ShadowWidth += 0.3f;
			g_Player.ShadowDepth += 0.3f;
			g_Player.ShadowCol.a += 0.006f;
		}
	}

	if (g_Player.state == PLAYERSTATE_MOVE)
	{// 移動していたら
		if (g_Player.nKey == 0 && g_Player.nMotionCounter == 1 || g_Player.nKey == 2 && g_Player.nMotionCounter == 1)
		{
			PlaySound(SOUND_LABEL_SE_DASH);
		}
	}
	else
	{
		StopSound(SOUND_LABEL_SE_DASH);
	}
}
//=============================================================================
// プレイヤーがアクション状態の時の処理
//=============================================================================
void PlayerAction(void)
{
	if (g_Player.nKey == 2 && g_Player.nMotionCounter == 2)
	{
		D3DXMATRIX mtxRot, mtxTrans, mtxEffect;       // 計算用マトリックス
		D3DXVECTOR3 EffectPos;                        // エフェクトを出す位置(オフセット)
		float EffectRadius = 10.0f;                   // エフェクトの半径

		EffectPos = D3DXVECTOR3(0.0f, 20.0f, -10.0f); // エフェクトを出す位置を設定

		for (int nCntEffect = 0; nCntEffect < 30; nCntEffect++, EffectRadius += 4.0f, EffectPos.z -= 15.0f)
		{// エフェクトを出す回数分繰り返し
		 // ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxEffect);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&mtxEffect, &mtxEffect, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, EffectPos.x, EffectPos.y, EffectPos.z);
			D3DXMatrixMultiply(&mtxEffect, &mtxEffect, &mtxTrans);

			// 親の情報を自分に反映
			D3DXMatrixMultiply(&mtxEffect, &mtxEffect, &g_Player.aModel[1].mtxWorld);

			SetEffect(D3DXVECTOR3(mtxEffect._41, mtxEffect._42, mtxEffect._43), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EffectRadius, 30);

			if (nCntEffect == 15)
			{
				CollisionShutterAnimal(D3DXVECTOR3(mtxEffect._41, mtxEffect._42, mtxEffect._43), D3DXVECTOR3(200.0f, 0.0f, 200.0f));
				CollisionShutterModel(D3DXVECTOR3(mtxEffect._41, mtxEffect._42, mtxEffect._43), D3DXVECTOR3(200.0f, 0.0f, 200.0f));
			}
		}

		CutFilm(1);
		PlaySound(SOUND_LABEL_SE_SHUTTER);
	}
}

//=============================================================================
// プレイヤーのモーション
//=============================================================================
void PlayerMotion(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数分繰り返し
	    // 現在の位置更新
		g_Player.aModel[nCntModel].pos.x += g_Player.aModel[nCntModel].posDiff.x / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;
		g_Player.aModel[nCntModel].pos.y += g_Player.aModel[nCntModel].posDiff.y / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;
		g_Player.aModel[nCntModel].pos.z += g_Player.aModel[nCntModel].posDiff.z / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;

		g_Player.aModel[nCntModel].rot.x += g_Player.aModel[nCntModel].DiffAngle.x / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;

		if (g_Player.aModel[nCntModel].rot.x > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].rot.x < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}

		g_Player.aModel[nCntModel].rot.y += g_Player.aModel[nCntModel].DiffAngle.y / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;

		if (g_Player.aModel[nCntModel].rot.y > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].rot.y < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}

		g_Player.aModel[nCntModel].rot.z += g_Player.aModel[nCntModel].DiffAngle.z / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;

		if (g_Player.aModel[nCntModel].rot.z > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].rot.z < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// プレイヤーのモーションブレンド処理
//=============================================================================
void PlayerMotionBlend(void)
{
	// ブレンドカウンターを進める
	g_Player.nBlendCounter++;
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// モデルのパーツ数分繰り返し
		    // 現在の位置更新
			g_Player.aModel[nCntModel].pos.x += g_Player.aModel[nCntModel].posDiff.x / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);
			g_Player.aModel[nCntModel].pos.y += g_Player.aModel[nCntModel].posDiff.y / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);
			g_Player.aModel[nCntModel].pos.z += g_Player.aModel[nCntModel].posDiff.z / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);

			g_Player.aModel[nCntModel].rot.x += g_Player.aModel[nCntModel].DiffAngle.x / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);

			if (g_Player.aModel[nCntModel].rot.x > D3DX_PI)
			{// 現在の向きがD3DX_PIを超えた
				g_Player.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			if (g_Player.aModel[nCntModel].rot.x < -D3DX_PI)
			{// 現在の向きが-D3DX_PIを超えた
				g_Player.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			g_Player.aModel[nCntModel].rot.y += g_Player.aModel[nCntModel].DiffAngle.y / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);

			if (g_Player.aModel[nCntModel].rot.y > D3DX_PI)
			{// 現在の向きがD3DX_PIを超えた
				g_Player.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			if (g_Player.aModel[nCntModel].rot.y < -D3DX_PI)
			{// 現在の向きが-D3DX_PIを超えた
				g_Player.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}

			g_Player.aModel[nCntModel].rot.z += g_Player.aModel[nCntModel].DiffAngle.z / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);

			if (g_Player.aModel[nCntModel].rot.z > D3DX_PI)
			{// 現在の向きがD3DX_PIを超えた
				g_Player.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			if (g_Player.aModel[nCntModel].rot.z < -D3DX_PI)
			{// 現在の向きが-D3DX_PIを超えた
				g_Player.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

	if (g_Player.nBlendCounter >= g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f)
	{// ブレンドカウンターが既定の値に
        g_Player.nBlendCounter = 0;            // ブレンドカウンターを初期化
		if (g_Player.aMotion[g_Player.state].nNumKey >= 2)
		{// キーフレームが2つ以上あったら
			g_Player.mState = MOTIONSTATE_NORMAL;  // モーションの状態を通常の状態に
			g_Player.nKey++;                       // キーフレームを進める
		    // キーフレーム切り替え処理
			SwitchKey();
		}
		else
		{// キーフレームがこれ以上ない
			g_Player.mState = MOTIONSTATE_STOP;    // モーションの状態をモーションしない状態に
		}
	}
}
//=============================================================================
// モーション進行処理
//=============================================================================
void PlayerMotionAdvance(void)
{
	g_Player.nMotionCounter++;   // モーションカウンターを進める
	if (g_Player.nMotionCounter >= g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey)
	{// 再生フレーム数に達した
		if (g_Player.nKey == g_Player.aMotion[g_Player.state].nNumKey - 1)
		{// 現在のキーフレーム数がそのモーションのキーフレームの総数を上回った
			if (g_Player.aMotion[g_Player.state].bLoop == true)
			{// ループする判定だったら
				g_Player.nKey = 0;             // 現在のキーフレームを元に戻す
				// キーフレーム切り替え処理
				SwitchKey();
			}
			else
			{// ループしない判定だったら
				if (g_Player.state == PLAYERSTATE_LANDING || g_Player.state == PLAYERSTATE_TAKEPICTURE)
				{// 着地状態かアクション状態だったら
					g_Player.state = PLAYERSTATE_NORMAL;  // 通常状態に

					// モーション切り替え処理
					SwitchMotion();
				}
				else
				{// それ以外のモーションならば
					g_Player.mState = MOTIONSTATE_STOP;
				}
			}
		}
		else
		{
			g_Player.nKey++;         // 現在のキーフレームを進める

			// キーフレーム切り替え処理
			SwitchKey();
		}
		g_Player.nMotionCounter = 0;   // カウンターを戻す
	}
}
//=============================================================================
// キーフレーム切り替え処理
//=============================================================================
void SwitchKey(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数分繰り返し
	    // 目標の座標設定
		g_Player.aModel[nCntModel].posDiff.x = g_Player.aModel[nCntModel].posStd.x - (g_Player.aModel[nCntModel].pos.x - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].x);
		g_Player.aModel[nCntModel].posDiff.y = g_Player.aModel[nCntModel].posStd.y - (g_Player.aModel[nCntModel].pos.y - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].y);
		g_Player.aModel[nCntModel].posDiff.z = g_Player.aModel[nCntModel].posStd.z - (g_Player.aModel[nCntModel].pos.z - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].z);

	    // 角度の差分の修正
		g_Player.aModel[nCntModel].DiffAngle.x = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].x - g_Player.aModel[nCntModel].rot.x;   // 現在の向きと目的の向きの差分を計算

		if (g_Player.aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// 角度の差分の修正
		g_Player.aModel[nCntModel].DiffAngle.y = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].y - g_Player.aModel[nCntModel].rot.y;   // 現在の向きと目的の向きの差分を計算

		if (g_Player.aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// 角度の差分の修正
		g_Player.aModel[nCntModel].DiffAngle.z = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].z - g_Player.aModel[nCntModel].rot.z;   // 現在の向きと目的の向きの差分を計算

		if (g_Player.aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// モーション切り替え処理
//=============================================================================
void SwitchMotion(void)
{
	g_Player.nMotionCounter = 0;          // モーションカウンターをリセット
	g_Player.nKey = 0;                    // 現在のキーフレームをリセット
	g_Player.mState = MOTIONSTATE_SWITCH; // モーション切り替え状態に

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数分繰り返し
	    // 目標の座標設定
		g_Player.aModel[nCntModel].posDiff.x = g_Player.aModel[nCntModel].posStd.x - (g_Player.aModel[nCntModel].pos.x - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].x);
		g_Player.aModel[nCntModel].posDiff.y = g_Player.aModel[nCntModel].posStd.y - (g_Player.aModel[nCntModel].pos.y - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].y);
		g_Player.aModel[nCntModel].posDiff.z = g_Player.aModel[nCntModel].posStd.z - (g_Player.aModel[nCntModel].pos.z - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].z);

	    // 角度の差分の修正
		g_Player.aModel[nCntModel].DiffAngle.x = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].x - g_Player.aModel[nCntModel].rot.x;   // 現在の向きと目的の向きの差分を計算

		if (g_Player.aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// 角度の差分の修正
		g_Player.aModel[nCntModel].DiffAngle.y = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].y - g_Player.aModel[nCntModel].rot.y;   // 現在の向きと目的の向きの差分を計算

		if (g_Player.aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// 角度の差分の修正
		g_Player.aModel[nCntModel].DiffAngle.z = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].z - g_Player.aModel[nCntModel].rot.z;   // 現在の向きと目的の向きの差分を計算

		if (g_Player.aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player.aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}