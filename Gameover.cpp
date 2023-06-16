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
		return 1;
	}
	return 2; 
}

void Gameover::Initialize() {
	input_ = Input::GetInstance();
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
