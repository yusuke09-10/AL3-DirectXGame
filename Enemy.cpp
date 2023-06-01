#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() { delete modelEnemy_; }

void Enemy::Initialize(ViewProjection viewprojection) {
	input_ = Input::GetInstance();
	viewprojection_ = viewprojection;
	// Beem
	textureHandleEnemy_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();

	worldTransformEnemy_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformEnemy_.Initialize();
}
void Enemy::Update() {
	Move();
	Born();
	worldTransformEnemy_.matWorld_ = MakeAffineMatrix(
	    worldTransformEnemy_.scale_, worldTransformEnemy_.rotation_,
	    worldTransformEnemy_.translation_);
	// バッファ転送
	worldTransformEnemy_.TransferMatrix();
}
void Enemy::Move() {
	if (aliveFlag_ == 1) {
		worldTransformEnemy_.rotation_.x -= 0.1f;
		worldTransformEnemy_.translation_.z -= 0.3f;
		//worldTransformEnemy_.translation_.x += enmeyspeed_[i];
		//if (worldTransformEnemy_.translation_.x >= 4) {
		//	enmeyspeed_[i] = -0.1f;
		//}
		//if (worldTransformEnemy_[i].translation_.x <= -4) {
		//	enmeyspeed_[i] = 0.1f;
		//}
	}
	if (worldTransformEnemy_.translation_.z < -5 ) 
	{
		aliveFlag_ = 0;
	}
	
}
void Enemy::Born() {
	int x = rand() % 80;
	float x2 = (float)x / 10 - 4;
	if (rand() % 10 == 0) {
		

			if (aliveFlag_ == 0) {
				worldTransformEnemy_.translation_.x = x2;
				worldTransformEnemy_.translation_.y = 0;
				worldTransformEnemy_.translation_.z = 40.0f;
				aliveFlag_= 1;
				//if (rand() % 2 == 0) {
				//	enmeyspeed_[i] = 0.1f;
				//} else {
				//	enmeyspeed_[i] = -0.1f;
				//}
			}
		
	}
	
}
void Enemy::Drow3D() {
	if (aliveFlag_ == 1) {
		    modelEnemy_->Draw(worldTransformEnemy_, viewprojection_, textureHandleEnemy_);
	}
}