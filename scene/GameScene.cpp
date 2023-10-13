#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() { 
	
}

GameScene::~GameScene() {
	delete modelSkydome_;
	delete modelGround_;
	delete debugcamera_;
}

void GameScene::Initialize()
{

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");
	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	
	// ワールドトランスフォームの初期化
	//worldTransform_.Initialize();
	
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.farZ = 1600.0f;
	viewProjection_.UpdateMatrix();

	// 3Dモデルの生成
	model_.reset(Model::Create());

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 自キャラの初期化
	player_->Initialize(model_.get(), textureHandle_);
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	#pragma region デバックカメラ
	// デバックカメラの生成
	debugcamera_ = new DebugCamera(1280, 720);
	debugcamera_->SetFarZ(1400.0f);
#pragma endregion


	#pragma region 天球の初期化
	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// 天球の生成
	skydome_ = new Skydome();
	// 天球初期化
	skydome_->Initialize(modelSkydome_);
#pragma endregion


	#pragma region 地面の初期化
	// 3Dモデルの生成
	modelGround_ = Model::CreateFromOBJ("ground", true);

	// 地面の生成
	ground_ = new Ground();
	// 地面初期化
	ground_->Initialize(modelGround_);
	#pragma endregion
}

void GameScene::Update() {
	//// スプライトの今の座標を取得
	//Vector2 position = sprite_->GetPosition();
	//// 座標を{2,1}移動
	//position.x = 2.0f;
	//position.y = 1.0f;
	//// 移動した座標をスプライトに反映
	//sprite_->SetPosition(position);

	// 3Dモデルの生成
	//model_ = Model::Create();

	// カメラ処理
	if (isDebugCameraActive_) {
		debugcamera_->Update();
		viewProjection_.matView = debugcamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugcamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {

		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
	if (input_->TriggerKey(DIK_M)) {

		isDebugCameraActive_ = true;
	}

	// デバックカメラの生成
	debugcamera_->Update();

	// 自キャラの更新
	player_->Update();

	// 天球
	skydome_->Update();

	// 地面
	ground_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

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
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 天球の描画
	skydome_->Draw(viewProjection_);

	// 地面の描画
	ground_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();



#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();



	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
