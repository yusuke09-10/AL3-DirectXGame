#include "Stage.h"

Stage::Stage() {}

Stage::~Stage() {
	delete spriteBg_;
	delete modelstage_;
}

void Stage::Initialize(ViewProjection viewprojection) {
	viewprojection_ = viewprojection;
	textureHandelBg_ = TextureManager::Load("bg.jpg");
	spriteBg_ = Sprite::Create(textureHandelBg_, {0, 0});

	textureHandleStage_ = TextureManager::Load("stage2.jpg");
	modelstage_ = Model::Create();
	for (int i = 0; i < 20; i++) {
		worldTransformStage_[i].Initialize();
	}
	for (int i = 0; i < 20; i++) {
		worldTransformStage_[i].translation_ = {0, -1.5f, 2.0f*i-5};
		worldTransformStage_[i].scale_ = {4.5f, 1, 1};
		// 変換行列を更新
		worldTransformStage_[i].matWorld_ = MakeAffineMatrix(
		    worldTransformStage_[i].scale_, worldTransformStage_[i].rotation_,
		    worldTransformStage_[i].translation_);
		worldTransformStage_[i].TransferMatrix();
	}
	
}

void Stage::Update() {}

void Stage::StageUpdate() {
	for (int i = 0; i < 20; i++) {
		worldTransformStage_[i].translation_.z -= 0.1f;
		if (worldTransformStage_[i].translation_.z < -5) {
			worldTransformStage_[i].translation_.z += 40;
		}
		// 変換行列を更新
		worldTransformStage_[i].matWorld_ = MakeAffineMatrix(
		    worldTransformStage_[i].scale_, worldTransformStage_[i].rotation_,
		    worldTransformStage_[i].translation_);
		// バッファ転送
		worldTransformStage_[i].TransferMatrix();
	}
}

void Stage::Draw2DFar() { spriteBg_->Draw(); }
void Stage::Drow3D() {
	for (int i = 0; i < 20; i++) {
		modelstage_->Draw(worldTransformStage_[i], viewprojection_, textureHandleStage_);
	}
	
}