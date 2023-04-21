#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
//コンストラクタ
GameScene::GameScene() {}
//デストラクタ
GameScene::~GameScene() {
	delete spriteBg_;
	delete modelstage_;
	delete modelPlayer_;
}
//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandelBg_ = TextureManager::Load("bg.jpg");
	spriteBg_ = Sprite::Create(textureHandelBg_, {0,0});
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

}
//更新
void GameScene::Update() {}

//Player Update

//描画
void GameScene::Draw() {

	// コマンドリストの取得
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

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	modelstage_->Draw(worldTransformStage_, viewprojection_, textureHandleStage_);
	
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
