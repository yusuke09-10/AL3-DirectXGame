#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
class Stage {

public:
	Stage();

	~Stage();

	void Initialize(ViewProjection viewprojection_);

	void Update();
	void Drow3D();
	void Draw2DFar();
	uint32_t textureHandelBg_ = 0;
	Sprite* spriteBg_ = nullptr;
	ViewProjection viewprojection_;

	uint32_t textureHandleStage_ = 0;
	Model* modelstage_ = nullptr;
	WorldTransform worldTransformStage_;
};
