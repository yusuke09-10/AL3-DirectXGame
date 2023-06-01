#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete stage_;
	delete player_;
	delete enemy_;
	delete beam_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewprojection_.translation_.y = 1;
	viewprojection_.translation_.z = -6;
	viewprojection_.Initialize();
	stage_ = new Stage();
	player_ = new Player();
	beam_ = new Beam();
	enemy_ = new Enemy();
	stage_->Initialize(viewprojection_);
	player_->Initialize(viewprojection_);
	enemy_->Initialize(viewprojection_);
	beam_->Initialize(viewprojection_,player_);
	debugtext_ = DebugText::GetInstance();
	debugtext_->Initialize();
	
}

void GameScene::Update() { 
	Collision();
	stage_->Update(); 
    player_->Update();
	beam_->Update();
	enemy_->Update();
}
void GameScene::Collision() {
	CollisionPlayerEnemy();
	CollisionBeem();
}
void GameScene::CollisionPlayerEnemy() {
	
		if (enemy_->GetFlag()==1) {
			float dx = abs(player_->GetX()- enemy_->GetX());
			float dz = abs(player_->GetZ() - enemy_->GetZ());
			if (dx < 1 && dz < 1) {
				enemy_->Hit();
			    Playerlife_ -= 1;
			}
		}
	
}
void GameScene::CollisionBeem() {
	    if (enemy_->GetFlag() == 1) {
		    float dx = abs(beam_->GetX() - enemy_->GetX());
		    float dz = abs(beam_->GetZ() - enemy_->GetZ());
		    if (dx < 1 && dz < 1) {
			    enemy_->Hit();
			    beam_->Hit();
			    GameScore_ += 1;
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
	stage_->Draw2DFar();
	
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
	stage_->Drow3D();
	player_->Drow3D();
	beam_->Drow3D();
	enemy_->Drow3D();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	char str[100];
	char Lstr[100];
	sprintf_s(str, "SCORE:%d", GameScore_);
	debugtext_->Print(str, 10, 10, 2);
	sprintf_s(Lstr, "LIFE:%d", Playerlife_);
	debugtext_->Print(Lstr, 900, 10, 2);
	debugtext_->DrawAll();
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
