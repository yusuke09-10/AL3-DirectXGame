#include "Player.h"

Player::Player() {}

Player::~Player() { delete modelPlayer_; }

void Player::Initialize(ViewProjection viewprojection) { 
	viewprojection_ = viewprojection;
	input_ = Input::GetInstance();
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelPlayer_ = Model::Create();
	worldTransformPlayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformPlayer_.Initialize();
}


void Player::Update() {
	// Move
	if (worldTransformPlayer_.translation_.x > 4) {
		worldTransformPlayer_.translation_.x = 4;
	}
	if (worldTransformPlayer_.translation_.x < -4) {
		worldTransformPlayer_.translation_.x = -4;
	}

	if (input_->PushKey(DIK_RIGHT)) {
		worldTransformPlayer_.translation_.x += 0.1f;
	}
	if (input_->PushKey(DIK_LEFT)) {
		worldTransformPlayer_.translation_.x -= 0.1f;
	}
	// player変換行列を更新
	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);
	// playerバッファ転送
	worldTransformPlayer_.TransferMatrix();
}

void Player::Drow3D() {
	modelPlayer_->Draw(worldTransformPlayer_, viewprojection_, textureHandlePlayer_);

}

void Player::Strat() { worldTransformPlayer_.translation_.x = 0; }
