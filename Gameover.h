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
class Gameover {
public:
	Gameover();
	~Gameover();
	int Update();
	void Initialize();
	void Drow2DNear();
	Input* input_ = nullptr;
	uint32_t textureHandelGameover_ = 0;
	Sprite* spriteGameover_ = nullptr;
	uint32_t textureHandelEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;
	int EnterTimer = 0;


};
