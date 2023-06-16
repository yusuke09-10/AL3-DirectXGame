#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
class Player {
public:
	Player();

	~Player();

	void Initialize(ViewProjection viewprojection_);

	void Update();
	void Drow3D();
	void Strat();
	float GetX() { return worldTransformPlayer_.translation_.x; }
	float GetZ() { return worldTransformPlayer_.translation_.z; }
	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;
	Input *input_ = nullptr;

private:
	ViewProjection viewprojection_;
};
