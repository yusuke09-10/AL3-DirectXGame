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

	textureHandleStage_ = TextureManager::Load("stage.jpg");
	modelstage_ = Model::Create();
    worldTransformStage_.Initialize();
	worldTransformStage_.translation_ = {0, -1.5f,0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	// 変換行列を更新
	worldTransformStage_.matWorld_ = MakeAffineMatrix(
	    worldTransformStage_.scale_, worldTransformStage_.rotation_,
	    worldTransformStage_.translation_);
	worldTransformStage_.TransferMatrix();
}

void Stage::Update(){}

void Stage::Draw2DFar() { spriteBg_->Draw(); }
void Stage::Drow3D() {
	modelstage_->Draw(worldTransformStage_, viewprojection_, textureHandleStage_);
}