#include "GameScene.h"
#include "TextureManager.h"
#include "PrimitiveDrawer.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//データの解放
	delete sprite_;
	delete model_;
	delete debugcamera_;
}

void GameScene::Initialize() {
	//読み込み
	textureHandle_ = TextureManager::Load("sample.png");
	textureHandle1_ = TextureManager::Load("sample.png");
	audio_ = Audio::GetInstance();
	soundDetaHandle_ = audio_->LoadWave("fanfare.wav");
	//音源の再生
	voiceHandle=audio_->PlayWave(soundDetaHandle_,true);
	//モデルなどの生成
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	model_ = Model::Create();

	dxCommon_ = DirectXCommon::GetInstance();
	//ライン描画の参照先指定
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewprojection_);
	input_ = Input::GetInstance();
	worldtransform_.Initialize();
	viewprojection_.Initialize();
	//デバッグカメラの生成
	debugcamera_ = new DebugCamera(1280, 720);
	//軸表示の有無
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸の参照先指定
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugcamera_->GetViewProjection());
}

void GameScene::Update() { 
	Vector2 pos = sprite_->GetPosition();
	pos.x += 1;
	pos.y += 1;
	sprite_->SetPosition(pos);
	if (input_->TriggerKey(DIK_SPACE) ) {
		audio_->StopWave(voiceHandle);
	}
	ImGui::Begin("Debug");
	ImGui::InputFloat3("InputFloat", inputFloat3);
	ImGui::Text("Ikehata Yusuke %d %d %d", 2050, 9, 10);
	ImGui::SliderFloat3("inputfloat", inputFloat3, 0.0f, 7.0f);
	ImGui::End();
	ImGui::ShowDemoWindow();
	debugcamera_->Update();
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
	sprite_->Draw();
	PrimitiveDrawer::GetInstance()->DrawLine3d({40, 0, 0}, {-40, 0, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 30, 0}, {0, -30, 0}, {0.0f, 0.0f, 1.0f, 1.0f});
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 20}, {0, 0, -20}, {0.0f, 1.0f, 0.0f, 1.0f});
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
	model_->Draw(worldtransform_, debugcamera_->GetViewProjection(), textureHandle1_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
