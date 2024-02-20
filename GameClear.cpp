#include "GameClear.h"
#include "TextureManager.h"

GameClear::GameClear() {}

GameClear::~GameClear() 
{ 
	delete sprite_;
}

void GameClear::Initialize() {
	// ファイル名を指定してテクスチャを読み込む
	texturehandle_ = TextureManager::Load("AL GC.png");
	// スプライトの生成
	sprite_ = Sprite::Create(texturehandle_, {0, 0});

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 初期化処理
	uint32_t fadeinTexHandle = TextureManager::Load("Black.png");
	fadeinSprite_ = Sprite::Create(fadeinTexHandle, {0, 0});
}

void GameClear::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		isGameClearScene = true;
	}
	fadeinColor_.w -= 0.005f;
	fadeinSprite_->SetColor(fadeinColor_);
}

void GameClear::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	sprite_->Draw();

	fadeinSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion
}

void GameClear::Reset() { 
	isGameClearScene = false;

	fadeinColor_ = {1.0f, 1.0f, 1.0f, 1.0f};
}
