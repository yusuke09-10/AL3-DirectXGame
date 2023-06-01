#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class Enemy {
public:
	Enemy();

	~Enemy();

	void Initialize(ViewProjection viewprojection_);

	void Update();
	void Drow3D();
	void Born();
	void Move();
	// en
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_;
	Input* input_ = nullptr;
	int aliveFlag_ = 0;

private:
	ViewProjection viewprojection_;
};