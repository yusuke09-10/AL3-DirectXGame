#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Stage.h"
#include "Player.h"
#include "Beam.h"
#include "Enemy.h"
#include "DebugText.h"

class Gameplay {
public:
	Gameplay();

	~Gameplay();

	void Initialize(ViewProjection viewprojection);

	int Update();
	void Drow3D();
	void Drow2DNear();
	void Drow2DFar();
	void CollisionPlayerEnemy();
	void CollisionBeem();
	void DrowScore();
	void Start();
	void Shot();
	Stage* stage_[20] = {};
	Player* player_ = nullptr;
	Beam* beams_[10] = {};
	Enemy* enemys_[10] = {};
	Input* input_ = nullptr;
	DebugText* debugtext_ = nullptr;
	int GameScore_ = 0;
	int Playerlife_ = 3;
	int shotTimer = 0;
	int Get() { return Playerlife_; };
	Audio* audio_ = nullptr;
	uint32_t SoundDetaHandelBGM_ = 0;
	uint32_t SoundHandelBGM_ = 0;
	uint32_t SoundDetaHandelEnemyHitSE_ = 0;
	uint32_t SoundDetaHandelPlayerHitSE_ = 0;
	uint32_t textureHandelSc_ = 0;
	Sprite* spriteSc_[5] = {};
	uint32_t textureHandelScore_ = 0;
	Sprite* spriteScore_ = nullptr;
	uint32_t textureHandellife_ = 0;
	Sprite* spritelife_[3] = {};
	int playerTimer = 0;
	private:
	ViewProjection viewprojection_;
	    
};
