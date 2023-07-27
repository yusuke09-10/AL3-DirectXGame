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
	void Strat();
	void Jump();
	void Hit() { aliveFlag_ = 0; }
	void Hitr() { aliveFlag_ = 2; }
	void Jumpr() {  JumpSpeed_=1; }
	// en
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_;
	Input* input_ = nullptr;
	float GetX() { return worldTransformEnemy_.translation_.x; }
	float GetZ() { return worldTransformEnemy_.translation_.z; }
	int GetFlag() { return aliveFlag_; }
	
	int aliveFlag_ = 0;
	float Xspeed = 0;
	float JumpSpeed_ = 0;

private:
	ViewProjection viewprojection_;
};