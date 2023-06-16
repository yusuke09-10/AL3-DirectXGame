#include "GameScene.h"

#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewprojection_.translation_.y = 1;
	viewprojection_.translation_.z = -6;
	viewprojection_.Initialize();
    gameplay.Initialize(viewprojection_);
	title.Initialize();
	gameover.Initialize();
}

void GameScene::Update() { 
	int oldScene = SceneMode;
	switch (SceneMode) {
	case 0:
		SceneMode = gameplay.Update();
		break;
	
     case 1:
	SceneMode= title.Update();
	break;
	 case 2:
	SceneMode= gameover.Update();
	break;
   }
	 if (oldScene!=SceneMode) {
	switch (SceneMode) {
	case 0:
		gameplay.Start();
		break;
	}

	 }
}
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	switch (SceneMode) {
	case 0:
		gameplay.Drow2DFar();
		break;
	case 2:
		gameplay.Drow2DFar();
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	switch (SceneMode) {
	case 0:
		gameplay.Drow3D();
		break;
	case 2:
		gameplay.Drow3D();
		break;
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	switch (SceneMode) {
	case 0:
		gameplay.Drow2DNear();
		break;
	case 1:
		title.Drow2DNear();
		break;
	case 2:
		gameover.Drow2DNear();
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
