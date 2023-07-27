#include "Gameplay.h"

Gameplay::Gameplay() {}

Gameplay::~Gameplay() {
	for (int i = 0; i < 20; i++) {
		delete stage_[i];
	}
	delete player_;
	delete spriteScore_;
	for (int i = 0; i < 3; i++) {
		delete spritelife_[i];
	}
	for (int i = 0; i < 10; i++) {
		delete enemys_[i];
	}
	for (int i = 0; i < 10; i++) {
		delete beams_[i];
	}
	for (int i = 0; i < 5; i++) {
		delete spriteSc_[i];
	}
	
}

void Gameplay::Initialize(ViewProjection viewprojection) { 

	viewprojection_ = viewprojection; 
	for (int i = 0; i < 20; i++) {
		stage_[i] = new Stage();
	}
	
	player_ = new Player();
	for (int i = 0; i < 10; i++) {
		beams_[i] = new Beam();
	}
	for (int i = 0; i < 10; i++) {
		enemys_[i] = new Enemy();
	}
	audio_ = Audio::GetInstance();
	SoundDetaHandelBGM_ = audio_->LoadWave("Audio/Ring08.wav");
	SoundDetaHandelEnemyHitSE_ = audio_->LoadWave("Audio/chord.wav");
	SoundDetaHandelPlayerHitSE_ = audio_->LoadWave("Audio/tada.wav");
	SoundHandelBGM_ = audio_->PlayWave(SoundDetaHandelBGM_, true);
	textureHandelScore_ = TextureManager::Load("score.png");
	spriteScore_ = Sprite::Create(textureHandelScore_, {100, 0});
	textureHandelSc_ = TextureManager::Load("number.png");
	textureHandellife_ = TextureManager::Load("player.png");
	for (int i = 0; i < 5; i++) {
		spriteSc_[i] = Sprite::Create(textureHandelSc_, {300.0f + i * 26, 0});
	}
	for (int i = 0; i < 3; i++) {
		spritelife_[i] = Sprite::Create(textureHandellife_, {800.0f + i * 60, 0});
		spritelife_[i]->SetSize({40, 40});
	}
	for (Stage*stage:stage_) {
		stage->Initialize(viewprojection_);
	}
	input_ = Input::GetInstance();
	
	player_->Initialize(viewprojection_);
	for (Enemy *enemy : enemys_) {
		enemy->Initialize(viewprojection_);
	}
	for (Beam*beam:beams_) {
		beam->Initialize(viewprojection_, player_);
	}
	debugtext_ = DebugText::GetInstance();
	debugtext_->Initialize();
}

int Gameplay::Update() {
	for (Stage* stage : stage_) {
		stage->StageUpdate();
	}
	player_->Update();
    for (Beam* beam : beams_) {
		beam->Update();
	}
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}
	Shot();
	CollisionPlayerEnemy();
	CollisionBeem();
	if (playerTimer>0) {
		playerTimer--;
	}
	if (Playerlife_==0) {
		audio_->StopWave(SoundHandelBGM_);
		return 2;
	}
	return 0;
}

void Gameplay::Drow3D() {
	for (Stage* stage : stage_) {
		stage->Drow3D();
	}
	if (playerTimer %4<2) {
		player_->Drow3D();
	}
	
	for (Beam* beam : beams_) {
		beam->Drow3D();
	}
	for (Enemy* enemy : enemys_) {
		enemy->Drow3D();
	}
}

void Gameplay::Drow2DNear() {
	DrowScore();
}

void Gameplay::Drow2DFar() { 
	for (Stage* stage : stage_) {
		stage->Draw2DFar();
	}
}

void Gameplay::CollisionPlayerEnemy() {
	for (Enemy* enemy : enemys_) {
		if (enemy->GetFlag() == 1) {
			float dx = abs(player_->GetX() - enemy->GetX());
			float dz = abs(player_->GetZ() - enemy->GetZ());
			if (dx < 1 && dz < 1) {
				audio_->PlayWave(SoundDetaHandelPlayerHitSE_);
				enemy->Hit();
				playerTimer = 60;
				Playerlife_ -= 1;
			}
		}
	}
}

void Gameplay::CollisionBeem() {
	for (Enemy* enemy : enemys_) {
		for (Beam* beam : beams_) {
			if (enemy->GetFlag() == 1) {
				float dx = abs(beam->GetX() - enemy->GetX());
				float dz = abs(beam->GetZ() - enemy->GetZ());
				if (dx < 1 && dz < 1) {
					audio_->PlayWave(SoundDetaHandelEnemyHitSE_);
					enemy->Hitr();
					enemy->Jumpr();
					beam->Hitr();
					GameScore_ += 1;
				}
			}
		}
	}
}

void Gameplay::DrowScore() {

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
}

void Gameplay::Start() {
	GameScore_ = 0;
	Playerlife_ = 3;
	playerTimer = 0;
	for (Enemy* enemy : enemys_) {
		enemy->Strat();
	}
	player_->Strat();
	player_->Update();
	for (Beam* beam : beams_) {
		beam->Strat();
	}
}

void Gameplay::Shot() {
	if (shotTimer == 0) {

		if (input_->PushKey(DIK_SPACE)) {
			for (Beam* beam : beams_) {
				if (beam->GetFlag() == 0) {
					beam->Born();
					beam->Update();
					shotTimer = 1;
					break;
				}
			}
		}
	} else {
		shotTimer++;
		if (shotTimer>10) {
			shotTimer = 0;
		}
	}
}
