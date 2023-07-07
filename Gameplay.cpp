#include "Gameplay.h"

Gameplay::Gameplay() {}

Gameplay::~Gameplay() {
	delete stage_;
	delete player_;
	for (int i = 0; i < 10; i++) {
		delete enemys_[i];
	}
	for (int i = 0; i < 10; i++) {
		delete beams_[i];
	}
	
}

void Gameplay::Initialize(ViewProjection viewprojection) { 

	viewprojection_ = viewprojection; 
	stage_ = new Stage();
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
	input_ = Input::GetInstance();
	stage_->Initialize(viewprojection_);
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
	stage_->Update();
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
	if (Playerlife_==0) {
		audio_->StopWave(SoundHandelBGM_);
		return 2;
	}
	return 0;
}

void Gameplay::Drow3D() {
	stage_->Drow3D();
	player_->Drow3D();
	for (Beam* beam : beams_) {
		beam->Drow3D();
	}
	for (Enemy* enemy : enemys_) {
		enemy->Drow3D();
	}
}

void Gameplay::Drow2DNear() {
	char str[100];
	char Lstr[100];
	sprintf_s(str, "SCORE:%d", GameScore_);
	debugtext_->Print(str, 10, 10, 2);
	sprintf_s(Lstr, "LIFE:%d", Playerlife_);
	debugtext_->Print(Lstr, 900, 10, 2);
	debugtext_->DrawAll();
}

void Gameplay::Drow2DFar() { stage_->Draw2DFar(); }

void Gameplay::CollisionPlayerEnemy() {
	for (Enemy* enemy : enemys_) {
		if (enemy->GetFlag() == 1) {
			float dx = abs(player_->GetX() - enemy->GetX());
			float dz = abs(player_->GetZ() - enemy->GetZ());
			if (dx < 1 && dz < 1) {
				audio_->PlayWave(SoundDetaHandelPlayerHitSE_);
				enemy->Hit();
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
					enemy->Hit();
					beam->Hitr();
					GameScore_ += 1;
				}
			}
		}
	}
}

void Gameplay::Start() {
	GameScore_ = 0;
	Playerlife_ = 3;
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
