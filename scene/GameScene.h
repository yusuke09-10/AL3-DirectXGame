#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"
#include "DebugCamera.h"
#include "AxisIndicator.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();
	
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	//スクリーン描画ハンドルetc...
	uint32_t textureHandle_ = 0;
	uint32_t textureHandle1_ = 0;
	uint32_t soundDetaHandle_ = 0;
	uint32_t voiceHandle = 0;
	float inputFloat3[3] = {0, 0, 0};

	Sprite* sprite_ = nullptr;
	Model* model_ = nullptr;
	DebugCamera* debugcamera_ = nullptr;
	WorldTransform worldtransform_;
	ViewProjection viewprojection_;
};
