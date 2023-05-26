#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "Player.h"
class Beam {
public:
	Beam();

	~Beam();

	void Initialize(ViewProjection viewprojection_,Player* player);

	void Update();
	void Drow3D();
	void Born();
	void Move();
	// Bea
	Player* player_ = nullptr;
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = nullptr;
	WorldTransform worldTransformBeam_;
	Input* input_ = nullptr;
	int aliveFlag_ = 0;
	private:
	ViewProjection viewprojection_;
};
