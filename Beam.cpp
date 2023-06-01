#include "Beam.h"

Beam::Beam() {

}

Beam::~Beam() { delete modelBeam_; }

void Beam::Initialize(ViewProjection viewprojection, Player* player) { 
	input_ = Input::GetInstance();
	player_ = player;
	viewprojection_ = viewprojection;
	// Beem
	textureHandleBeam_ = TextureManager::Load("beam.png");
	modelBeam_ = Model::Create();

	worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
	worldTransformBeam_.Initialize();
}

void Beam::Update(){
	Move();
	Born();
	worldTransformBeam_.matWorld_ = MakeAffineMatrix(
	    worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
	    worldTransformBeam_.translation_);
	// バッファ転送
	worldTransformBeam_.TransferMatrix();
	
}
void Beam::Move() {
	
		if (aliveFlag_ == 1) {
			worldTransformBeam_.rotation_.x += 0.1f;
			worldTransformBeam_.translation_.z += 0.4f;
		}
		if (worldTransformBeam_.translation_.z > 40) {
		    aliveFlag_ = 0;
		}
}
void Beam::Born() {

	    if (aliveFlag_ == 0) {
		    worldTransformBeam_.translation_.z = 0;
		    if (input_->PushKey(DIK_SPACE)) {
			     worldTransformBeam_.translation_.x = player_->GetX();
			    aliveFlag_ = 1;
		    }
	    }
}	    
		    void Beam::Drow3D() {
	    if (aliveFlag_ == 1) {
		    modelBeam_->Draw(worldTransformBeam_, viewprojection_, textureHandleBeam_);
	    }
	
}
