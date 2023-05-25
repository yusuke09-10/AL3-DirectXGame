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
	textureHandelSc_ = TextureManager::Load("number.png");
	for (int i = 0; i < 5; i++) {
		spriteSc_[i] = Sprite::Create(textureHandelSc_, {300.0f+i*26,0});
	}
	
	textureHandelTitle_= TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandelTitle_, {0, 0});
	textureHandelScore_ = TextureManager::Load("score.png");
	spriteScore_ = Sprite::Create(textureHandelScore_, {100, 0});
	textureHandelGameover_ = TextureManager::Load("gameover.png");
	spriteGameover_ = Sprite::Create(textureHandelGameover_, {0, 0});
	textureHandelEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandelEnter_, {420, 430});
	//
	SoundDetaHandelTitleBGM_ = audio_->LoadWave("Audio/Ring05.wav");
	SoundDetaHandelGamePlayBGM_ = audio_->LoadWave("Audio/Ring08.wav");
    SoundDetaHandelGameoverBGM_ = audio_->LoadWave("Audio/Ring09.wav");
	SoundDetaHandelEnemyHitSE_ = audio_->LoadWave("Audio/chord.wav");
	SoundDetaHandelPlayerHitSE_ = audio_->LoadWave("Audio/tada.wav");
	SoundHandelBGM_ = audio_->PlayWave(SoundDetaHandelTitleBGM_,true);
	//
	viewprojection_.translation_.y = 1;
	viewprojection_.translation_.z = -6;
	viewprojection_.Initialize();
	//stage create
	textureHandleStage_ = TextureManager::Load("stage2.jpg");
	modelstage_ = Model::Create();
	for (int  i = 0; i < 20; i++) {
		worldTransformStage_[i].Initialize();
	}
	//ぷれいやー
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelPlayer_ = Model::Create();
	worldTransformPlayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformPlayer_.Initialize();
	for (int i = 0; i < 3; i++) {
		spritelife_[i] = Sprite::Create(textureHandlePlayer_, {800.0f + i * 60, 0});
		spritelife_[i]->SetSize({40, 40});
	}
	//Beem
	textureHandleBeem_ = TextureManager::Load("beam.png");
	modelBeem_ = Model::Create();
	for (int i = 0; i < 10; i++) {
		worldTransformBeem_[i].scale_ = {0.3f, 0.3f, 0.3f};
		worldTransformBeem_[i].Initialize();
	}
	
	//Enemy
	textureHandleEnemy_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();
	for (int i = 0; i < 10; i++) {
		worldTransformEnemy_[i].scale_ = {0.5f, 0.5f, 0.5f};
		worldTransformEnemy_[i].Initialize();
	}
	
	srand((unsigned int)time(NULL));
	//Debug
	debugtext_ = DebugText::GetInstance();
	debugtext_->Initialize();
	for (int i = 0; i < 20; i++) {
		worldTransformStage_[i].translation_ = {0, -1.5f, 2.0f * i - 5};
		worldTransformStage_[i].scale_ = {4.5f, 1, 1};
		// 変換行列を更新
		worldTransformStage_[i].matWorld_ = MakeAffineMatrix(
		    worldTransformStage_[i].scale_, worldTransformStage_[i].rotation_,
		    worldTransformStage_[i].translation_);
		// バッファ転送
		worldTransformStage_[i].TransferMatrix();
	}
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
	GameTimer_++;
	PlayerUpdate();
	BeemUpdate();
	EnemyUpdate();
	Collision();
	StageUpdate();
	if (Playerlife_ == 0) {
		SceneMode_ = 2;
		// BGMchnge
		audio_->StopWave(SoundHandelBGM_);
		SoundHandelBGM_ = audio_->PlayWave(SoundDetaHandelGameoverBGM_, true);
	}
}
void GameScene::TitleUpdate() {
	GamePlayStart();
	if (input_->TriggerKey(DIK_RETURN)) {
		SceneMode_ = 0;
		//BGMchnge
		audio_->StopWave(SoundHandelBGM_ );
		SoundHandelBGM_ = audio_->PlayWave(SoundDetaHandelGamePlayBGM_, true);
	}
}
void GameScene::GameoverUpdate() {
	
	if (input_->TriggerKey(DIK_RETURN)) {
		SceneMode_ = 1;
		// BGMchnge
		audio_->StopWave(SoundHandelBGM_);
		SoundHandelBGM_ = audio_->PlayWave(SoundDetaHandelTitleBGM_, true);
	}
}
void GameScene::GamePlayStart() { 
	GameScore_ = 0;
	Playerlife_ = 3;
	GameTimer_ = 0;
	Playertimer_ = 0;
	worldTransformPlayer_.rotation_.x = 0;
	worldTransformPlayer_.translation_.x = 0;
	// player変換行列を更新
	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);
	// playerバッファ転送
	worldTransformPlayer_.TransferMatrix();
	for (int i = 0; i < 10; i++) {
		EnemyFlag_[i] = 0;
		BeemFlag_[i] = 0;
	}
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
	if (Playertimer_ >= 0) {
		Playertimer_--;
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
	for (int i = 0; i < 10; i++) {
		worldTransformBeem_[i].matWorld_ = MakeAffineMatrix(
		    worldTransformBeem_[i].scale_, worldTransformBeem_[i].rotation_,
		    worldTransformBeem_[i].translation_);
		// バッファ転送
		worldTransformBeem_[i].TransferMatrix();
	}
	
}
void GameScene::BeemMove() {
	for (int i = 0; i < 10; i++) {
		if (BeemFlag_[i] == 1) {
			worldTransformBeem_[i].rotation_.x += 0.1f;
			worldTransformBeem_[i].translation_.z += 0.4f;
		}
		if (worldTransformBeem_[i].translation_.z > 40) {
			BeemFlag_[i] = 0;
	}
	
	}
}
void GameScene::BeemBorn() {
	if (BeemTimer == 0) {
	BeemTimer=1;
	for (int i = 0; i < 10; i++) {
			if (BeemFlag_[i] == 0) {
				if (input_->PushKey(DIK_SPACE)) {
					worldTransformBeem_[i].translation_.x = worldTransformPlayer_.translation_.x;
					worldTransformBeem_[i].translation_.y = worldTransformPlayer_.translation_.y;
					worldTransformBeem_[i].translation_.z = worldTransformPlayer_.translation_.z;
					BeemFlag_[i] = 1;
					break;
				}
			}
	}
	} else {
	BeemTimer++;
	if (BeemTimer > 10) {
			BeemTimer = 0;
	}
	}
}
// EnemyUpdate
void GameScene::EnemyUpdate() {
	EnemyMove();
	EnemyBorn();
	EnemyJump();
	// 変換行列を更新
	for (int i = 0; i < 10; i++) {
		worldTransformEnemy_[i].matWorld_ = MakeAffineMatrix(
		    worldTransformEnemy_[i].scale_, worldTransformEnemy_[i].rotation_,
		    worldTransformEnemy_[i].translation_);
		// バッファ転送
		worldTransformEnemy_[i].TransferMatrix();
	}
	
}
void GameScene::EnemyMove() {
	for (int i = 0; i < 10; i++) {

		
		if (EnemyFlag_[i] == 1) {
			worldTransformEnemy_[i].rotation_.x -= 0.1f ;
			worldTransformEnemy_[i].translation_.z -= 0.3f;
			worldTransformEnemy_[i].translation_.x += enmeyspeed_[i];
			if (worldTransformEnemy_[i].translation_.x >= 4 ) {
				enmeyspeed_[i]=-0.1f;
				
			} if (worldTransformEnemy_[i].translation_.x <= -4) {
				enmeyspeed_[i] = 0.1f;	                               
			}
		}
		if (worldTransformEnemy_[i].translation_.z < -5) {
			EnemyFlag_[i] = 0;
		}
	}
	
}
void GameScene::EnemyBorn() {
	
	int x = rand() % 80;
	float x2 = (float)x / 10 - 4;
	if (rand()%10==0) {
		for (int i = 0; i < 10; i++) {
		
				
			
			if (EnemyFlag_[i] == 0) {
				worldTransformEnemy_[i].translation_.x = x2;
				worldTransformEnemy_[i].translation_.y = 0;
				worldTransformEnemy_[i].translation_.z = 40.0f;
				EnemyFlag_[i] = 1;
				if (rand() % 2 == 0) {
					enmeyspeed_[i] = 0.1f;
				} else {
					enmeyspeed_[i] = -0.1f;
				}
				break;
			}
		}
	}
}
void GameScene::EnemyJump() {
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i]==2) {
			worldTransformEnemy_[i].translation_.y += enemyJumpSpeed_[i];
			enemyJumpSpeed_[i] -= 0.1f;
			worldTransformEnemy_[i].translation_.x -= enmeyspeed_[i] * 4;
			if (worldTransformEnemy_[i].translation_.y < -3) {
				EnemyFlag_[i] = 0;
			}
		}
	}

}

void GameScene::StageUpdate() {
	for (int i = 0; i < 20; i++) {
		worldTransformStage_[i].translation_.z -= 0.1f;
		if (worldTransformStage_[i].translation_.z < -5) {
			worldTransformStage_[i].translation_.z += 40;
		}
			// 変換行列を更新
			worldTransformStage_[i].matWorld_ = MakeAffineMatrix(
			    worldTransformStage_[i].scale_, worldTransformStage_[i].rotation_,
			    worldTransformStage_[i].translation_);
			// バッファ転送
			worldTransformStage_[i].TransferMatrix();
		

	}
}

////HitBox
void GameScene::Collision() { CollisionPlayerEnemy();
	CollisionBeem();
}
void GameScene::CollisionPlayerEnemy() { 
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] == 1) {
			float dx =
			    abs(worldTransformPlayer_.translation_.x - worldTransformEnemy_[i].translation_.x);
			float dz =
			    abs(worldTransformPlayer_.translation_.z - worldTransformEnemy_[i].translation_.z);
			if (dx < 1 && dz < 1) {
				Playertimer_ = 60;
				EnemyFlag_[i] = 0;
				Playerlife_ -= 1;
				audio_->PlayWave(SoundDetaHandelPlayerHitSE_);
			}
	}
	
	}
}
void GameScene::CollisionBeem() {
	
	for (int i = 0; i < 10; i++) {
	    if (EnemyFlag_[i] == 1) {
			for (int k = 0; k < 10; k++) {
				float dx = abs(
				    worldTransformBeem_[k].translation_.x - worldTransformEnemy_[i].translation_.x);
				float dz = abs(
				    worldTransformBeem_[k].translation_.z - worldTransformEnemy_[i].translation_.z);
				if (BeemFlag_[k]==1) {
					
					if (dx < 1 && dz < 1) {
						EnemyFlag_[i] = 2;
						enemyJumpSpeed_[i]=1;
						BeemFlag_[k] = 0;
						GameScore_ += 1;
						audio_->PlayWave(SoundDetaHandelEnemyHitSE_);
					}
				}
				
			}
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
		
		GamePlayDrow2DFront();
		GamePlayDrow2DBack();
		GamePlayDrow3D();
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
	DrowScore();
	// 前景スプライト描画前処理
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	Sprite::PreDraw(commandList);
	
	
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
	// ステージ位置変更
	for (int i = 0; i < 20; i++) {
		modelstage_->Draw(worldTransformStage_[i], viewprojection_, textureHandleStage_);
	}
		
	
	if (Playertimer_%4<2) {
		modelPlayer_->Draw(worldTransformPlayer_, viewprojection_, textureHandlePlayer_);
	}
	
	
	for (size_t i = 0; i < 10; i++) {
			if (EnemyFlag_[i] == 1 || EnemyFlag_[i] == 2) {
				modelEnemy_->Draw(worldTransformEnemy_[i], viewprojection_, textureHandleEnemy_);
				if (BeemFlag_[i] == 1) {
					modelBeem_->Draw(worldTransformBeem_[i], viewprojection_, textureHandleBeem_);
				}
			}
		
		
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
void GameScene::DrowScore() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	Sprite::PreDraw(commandList);
	int eachnum[5] = {};
	int num = GameScore_;
	int keta = 10000;
	for (int i = 0; i < 5; i++) {
		eachnum[i] = num / keta;
		num = num % keta;
		keta = keta / 10;
	}
	for (int i = 0; i < Playerlife_; i++) {
		spritelife_[i]->Draw();
	}
	for (int i = 0; i < 5; i++) {
		spriteSc_[i]->SetSize({32, 64});
		spriteSc_[i]->SetTextureRect({32.0f * eachnum[i], 0}, {32, 64});
		spriteSc_[i]->Draw();
	}
	spriteScore_->Draw();
	Sprite::PostDraw();
	dxCommon_->ClearDepthBuffer();
}
void GameScene::GameoverDrow2DFront() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
#pragma region 
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
