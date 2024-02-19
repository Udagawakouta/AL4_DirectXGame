#include "TitleScene.h"
#include "TextureManager.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {

	delete sprite_;
}

void TitleScene::Initialize() { 
	// ファイル名を指定してテクスチャを読み込む
	texturehandle_ = TextureManager::Load("AL Title.png");
	// スプライトの生成
	sprite_ = Sprite::Create(texturehandle_, {0, 0});

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

}

void TitleScene::Update() 
{ 
	if (input_->TriggerKey(DIK_SPACE))
	{
		isTitleScene = true;
	}
}

void TitleScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

}
