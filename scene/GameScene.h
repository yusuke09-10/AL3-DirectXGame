#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "DebugText.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();
	void PlayerUpdate();
	void BeemUpdate();
	void BeemMove();
	void BeemBorn();
	void EnemyUpdate();
	void EnemyMove();
	void EnemyBorn();
	void EnemyJump();
	 void Collision();
	 void CollisionPlayerEnemy();
	void CollisionBeem();
	//
	void StageUpdate();
	void GamePlayStart();
	void GamePlayUpdate();
	void GamePlayDrow3D();
	void GamePlayDrow2DBack();
	void GamePlayDrow2DFront();
	void DrowScore();
	void TitleUpdate();
	void TitleDrow2DFront();
	void GameoverUpdate();
	void GameoverDrow2DFront();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// Bg
	uint32_t textureHandelBg_ = 0;
	Sprite* spriteBg_ = nullptr;
	ViewProjection viewprojection_;
	// stage
	uint32_t textureHandleStage_ = 0;
	Model* modelstage_ = nullptr;
	WorldTransform worldTransformStage_[20];
	// Player
	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;
	// Beem
	uint32_t textureHandleBeem_ = 0;
	Model* modelBeem_ = nullptr;
	WorldTransform worldTransformBeem_[10];
	int BeemFlag_[10] = {};
	// Enemy
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_[10];
	int EnemyFlag_[10] = {};
	int GameScore_ = 0;
	int Playerlife_ = 3;
	DebugText* debugtext_ = nullptr;
	//
	int SceneMode_ = 1;
	//
	uint32_t textureHandelTitle_ = 0;
	Sprite* spriteTitle_ = nullptr;
	//
	uint32_t textureHandelGameover_ = 0;
	Sprite* spriteGameover_ = nullptr;
	// Enter
	uint32_t textureHandelEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;
	int EnterTimer = 0;
	int BeemTimer = 0;
	int Playertimer_ = 0;
	float enmeyspeed_[10] = {};
	float enemyJumpSpeed_[10] = {};
	int GameTimer_ = 0;
	//
	uint32_t textureHandelSc_ = 0;
	Sprite* spriteSc_[5] = {};
	//
	uint32_t textureHandelScore_ = 0;
	Sprite* spriteScore_ = nullptr;
	//
	uint32_t textureHandellife_ = 0;
	Sprite* spritelife_[3] = {};
	//
	uint32_t SoundDetaHandelTitleBGM_ = 0;
	uint32_t SoundDetaHandelGamePlayBGM_ = 0;
	uint32_t SoundDetaHandelGameoverBGM_ = 0;
	uint32_t SoundDetaHandelEnemyHitSE_ = 0;
	uint32_t SoundDetaHandelPlayerHitSE_ = 0;
	uint32_t SoundHandelBGM_ = 0;
};

