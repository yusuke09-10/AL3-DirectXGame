#include "Gameover.h"

Gameover::Gameover() {}

Gameover::~Gameover() { delete spriteGameover_; }

int Gameover::Update() { 
	EnterTimer++;
	if (EnterTimer >= 40) {
		EnterTimer = 0;
	}
	if (input_->TriggerKey(DIK_RETURN))
	{
		audio_->StopWave(SoundHandelBGM_);
		return 1;
	}
	return 2; 
}

void Gameover::Strat() { SoundHandelBGM_ = audio_->PlayWave(SoundDetaHandelBGM_, true); }

void Gameover::Initialize() {
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	SoundDetaHandelBGM_ = audio_->LoadWave("Audio/Ring09.wav");
	Strat();
	textureHandelGameover_ = TextureManager::Load("gameover.png");
	spriteGameover_ = Sprite::Create(textureHandelGameover_, {0, 0});
	textureHandelEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandelEnter_, {420, 430});
}

void Gameover::Drow2DNear() {
	spriteGameover_->Draw();
	if (EnterTimer % 40 >= 20) {
		spriteEnter_->Draw();
	}
}
