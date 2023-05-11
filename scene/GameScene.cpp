#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>

//コンストラクタ
GameScene::GameScene() {}
//デストラクタ
GameScene::~GameScene() {
	delete spriteBg_;
	delete modelstage_;
	delete modelPlayer_;
	delete modelBeem_;
	delete modelEnemy_;
	delete spriteTitle_;
	delete spriteGameover_;
	delete spriteEnter_;
}
//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandelBg_ = TextureManager::Load("bg.jpg");
	spriteBg_ = Sprite::Create(textureHandelBg_, {0,0});
	textureHandelTitle_= TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandelTitle_, {0, 0});
	textureHandelGameover_ = TextureManager::Load("gameover.png");
	spriteGameover_ = Sprite::Create(textureHandelGameover_, {0, 0});
	textureHandelEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandelEnter_, {420, 430});
	//
	viewprojection_.translation_.y = 1;
	viewprojection_.translation_.z = -6;
	viewprojection_.Initialize();
	//stage create
	textureHandleStage_ = TextureManager::Load("stage.jpg");
	modelstage_ = Model::Create();
	worldTransformStage_.Initialize();
	//ステージ位置変更
	worldTransformStage_.translation_ = {0, -1.5f, 0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	//変換行列を更新
	worldTransformStage_.matWorld_ = MakeAffineMatrix(
	    worldTransformStage_.scale_, worldTransformStage_.rotation_,
	    worldTransformStage_.translation_);
	//バッファ転送
	worldTransformStage_.TransferMatrix();
	//ぷれいやー
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelPlayer_ = Model::Create();
	worldTransformPlayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformPlayer_.Initialize();
	//Beem
	textureHandleBeem_ = TextureManager::Load("beam.png");
	modelBeem_ = Model::Create();
	worldTransformBeem_.scale_ = {0.3f, 0.3f, 0.3f};
	worldTransformBeem_.Initialize();
	//Enemy
	textureHandleEnemy_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();
	worldTransformEnemy_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformEnemy_.Initialize();
	srand((unsigned int)time(NULL));
	//Debug
	debugtext_ = DebugText::GetInstance();
	debugtext_->Initialize();
}
//更新
void GameScene::Update() {
	EnterTimer++;
	if (EnterTimer>=40) {
		EnterTimer = 0;
	}
	switch (SceneMode_) {
	case 0:
		GamePlayUpdate();
		break;
	case 1:
		TitleUpdate();
		break;
	case 2:
		GameoverUpdate();
		break;
	}
	 
}
void GameScene::GamePlayUpdate() {
	PlayerUpdate();
	BeemUpdate();
	EnemyUpdate();
	Collision();
	if (Playerlife_ == 0) {
		SceneMode_ = 2;
	}
}
void GameScene::TitleUpdate() {
	if (input_->TriggerKey(DIK_RETURN)) {
		SceneMode_ = 0;
	}
}
void GameScene::GameoverUpdate() {
	GamePlayStart();
	if (input_->TriggerKey(DIK_RETURN)) {
		SceneMode_ = 1;
	}
}
void GameScene::GamePlayStart() { 
	GameScore_ = 0;
	Playerlife_ = 3;
	worldTransformPlayer_.rotation_.x = 0;
	worldTransformPlayer_.translation_.x = 0;
	BeemFlag_ = 0;
	EnemyFlag_ = 0;
}
    //Player Update
void GameScene::PlayerUpdate() {
	// Move
	if (worldTransformPlayer_.translation_.x > 4) {
		worldTransformPlayer_.translation_.x = 4;
	}
	if (worldTransformPlayer_.translation_.x < -4) {
		worldTransformPlayer_.translation_.x = -4;
	}

	if (input_->PushKey(DIK_RIGHT)) {
		worldTransformPlayer_.translation_.x += 0.1f;
	}
	if (input_->PushKey(DIK_LEFT)) {
		worldTransformPlayer_.translation_.x -= 0.1f;
	}
	
	// player変換行列を更新
	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);
	// playerバッファ転送
	worldTransformPlayer_.TransferMatrix();
}
// Beem Update
void GameScene::BeemUpdate() {
	BeemMove();
	BeemBorn();
	// 変換行列を更新
	worldTransformBeem_.matWorld_ = MakeAffineMatrix(
	    worldTransformBeem_.scale_, worldTransformBeem_.rotation_,
	    worldTransformBeem_.translation_);
	// バッファ転送
	worldTransformBeem_.TransferMatrix();
}
void GameScene::BeemMove() {
	if (BeemFlag_ == 1) {
		worldTransformBeem_.rotation_.x += 0.1f;
	worldTransformBeem_.translation_.z += 0.4f;}
	if (worldTransformBeem_.translation_.z > 40) {
	BeemFlag_ = 0;
	}
}
void GameScene::BeemBorn() {
	if (BeemFlag_ == 0) {
		if (input_->PushKey(DIK_SPACE)) {
			worldTransformBeem_.translation_.x = worldTransformPlayer_.translation_.x;
			worldTransformBeem_.translation_.y = worldTransformPlayer_.translation_.y;
			worldTransformBeem_.translation_.z = worldTransformPlayer_.translation_.z;
			BeemFlag_ = 1;
		}
	}
}
// EnemyUpdate
void GameScene::EnemyUpdate() {
	EnemyMove();
	EnemyBorn();
	// 変換行列を更新
	worldTransformEnemy_.matWorld_ = MakeAffineMatrix(
	    worldTransformEnemy_.scale_, worldTransformEnemy_.rotation_,
	    worldTransformEnemy_.translation_);
	// バッファ転送
	worldTransformEnemy_.TransferMatrix();
}
void GameScene::EnemyMove() {
	if (EnemyFlag_ == 1) {
		worldTransformEnemy_.rotation_.x -= 0.1f;
		worldTransformEnemy_.translation_.z -= 0.3f;
	}
	if (worldTransformEnemy_.translation_.z < -5) {
		EnemyFlag_ = 0;
	}
}
void GameScene::EnemyBorn() {
	int x = rand() % 80;
	float x2 = (float)x / 10 - 4;
	if (EnemyFlag_ == 0) {
		worldTransformEnemy_.translation_.x = x2;
		worldTransformEnemy_.translation_.z = 40.0f;
		EnemyFlag_ = 1;
	}
}
//HitBox
void GameScene::Collision() { CollisionPlayerEnemy();
	CollisionBeem();
}
void GameScene::CollisionPlayerEnemy() { 
	if (EnemyFlag_==1) {
		float dx = abs(worldTransformPlayer_.translation_.x - worldTransformEnemy_.translation_.x);
		float dz = abs(worldTransformPlayer_.translation_.z - worldTransformEnemy_.translation_.z);
		if (dx < 1 && dz < 1) {
			EnemyFlag_ = 0;
			Playerlife_ -= 1;
		}
	}
}
void GameScene::CollisionBeem() {
	if (EnemyFlag_ == 1) {
		float dx = abs(worldTransformBeem_.translation_.x - worldTransformEnemy_.translation_.x);
		float dz = abs(worldTransformBeem_.translation_.z - worldTransformEnemy_.translation_.z);
		if (dx < 1 && dz < 1) {
			EnemyFlag_ = 0;
			GameScore_ += 1;
		}
	}
}
    //描画
void GameScene::Draw() {
	switch (SceneMode_) {
	case 0:
		GamePlayDrow2DFront();
		break;
	case 1:
		TitleDrow2DFront();
		break;
	case 2:
		GameoverDrow2DFront();
		break;
	}
	switch (SceneMode_) {
	case 0:
		GamePlayDrow3D();
		break;
	}
	switch (SceneMode_) {
	case 0:
		GamePlayDrow2DBack();
		break;
	}
}
void GameScene::GamePlayDrow2DBack() {
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	Sprite::PreDraw(commandList);
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	/// // score
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

void GameScene::GamePlayDrow3D() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	modelstage_->Draw(worldTransformStage_, viewprojection_, textureHandleStage_);
	modelPlayer_->Draw(worldTransformPlayer_, viewprojection_, textureHandlePlayer_);
	if (BeemFlag_ == 1) {
		modelBeem_->Draw(worldTransformBeem_, viewprojection_, textureHandleBeem_);
	}
	if (EnemyFlag_ == 1) {
		modelEnemy_->Draw(worldTransformEnemy_, viewprojection_, textureHandleEnemy_);
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();

}
void GameScene::GamePlayDrow2DFront() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	spriteBg_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion
}
void GameScene::TitleDrow2DFront() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	spriteTitle_->Draw();
	if (EnterTimer%40>=20) {
		spriteEnter_->Draw();
	}
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}
void GameScene::GameoverDrow2DFront() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	spriteGameover_->Draw();
	if (EnterTimer % 40 >= 20) {
		spriteEnter_->Draw();
	}
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}
