#include "Title.h"

Title::Title() {}

Title::~Title() {
	delete spriteTitle_;
	delete spriteEnter_;
}

int Title::Update() {
	
	EnterTimer++; 
if (EnterTimer >= 40) {
		EnterTimer = 0;
	}
if (input_->TriggerKey(DIK_RETURN)) {
		audio_->StopWave(SoundHandelBGM_);
		return 0;
}
 return 1;
}

void Title::Strat() { SoundHandelBGM_ = audio_->PlayWave(SoundDetaHandelBGM_, true); }

void Title::Initialize() {
    input_ = Input::GetInstance();
 audio_ = Audio::GetInstance();
	SoundDetaHandelBGM_ = audio_->LoadWave("Audio/Ring05.wav");
    Strat();
	textureHandelTitle_ = TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandelTitle_, {0, 0});
	textureHandelEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandelEnter_, {420, 430});
}

void Title::Drow2DNear() { spriteTitle_->Draw(); 
if (EnterTimer % 40 >= 20) {
		spriteEnter_->Draw();
	}
}

