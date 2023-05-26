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

	ViewProjection viewprojection_;
	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;
	Input *input_ = nullptr;
};
