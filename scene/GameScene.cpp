#include "GameScene.h"
#include "Enemy.h"
#include "Player.h"
#include "TextureManager.h"
#include "list"
#include <cassert>
#include "ImGuiManager.h"

#pragma region ゲームシーン
GameScene::GameScene() {}

GameScene::~GameScene() 
{ 
	//delete modelSkydome_;
}

void GameScene::Initialize() {

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");
	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// ワールドトランスフォームの初期化
	// worldTransform_.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// プレイヤーモデルの生成
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	// エネミーモデルの生成
	enemyFighterBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	enemyFighterL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	enemyFighterR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));

#pragma region エネミーモデル
	// エネミーモデル
	std::vector<Model*> enemyModels = {
	    enemyFighterBody_.get(), enemyFighterL_arm_.get(), enemyFighterR_arm_.get()};

	// エネミーの生成
	enemy_ = std::make_unique<Enemy>();

	// エネミーの初期化
	enemy_->Initialize(enemyModels);
#pragma endregion

#pragma region 自キャラモデル
	// 自キャラモデル
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get()};

	// 自キャラの生成
	player_ = std::make_unique<Player>();

	// 自キャラの初期化
	player_->Initialize(playerModels);
#pragma endregion

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
	skydome_ = std::make_unique<Skydome>();
	// 天球初期化
	skydome_->Initialize(modelSkydome_);
#pragma endregion

#pragma region 地面の初期化
	// 3Dモデルの生成
	modelGround_ = Model::CreateFromOBJ("ground", true);

	// 地面の生成
	ground_ = std::make_unique<Ground>();
	// 地面初期化
	ground_->Initialize(modelGround_);
#pragma endregion

	// カメラ
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&followCamera_->GetViewProjection());
}

void GameScene::Update() {

	// カメラ処理
	if (isDebugCameraActive_) {
		debugcamera_->Update();
		viewProjection_.matView = debugcamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugcamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {

		// 追従カメラの更新
		followCamera_->Update();
		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
		// ビュープロジェクション行列の更新と転送
		// viewProjection_.UpdateMatrix();
	}
	if (input_->TriggerKey(DIK_M)) {

		isDebugCameraActive_ = true;
	}

	// 自キャラの更新
	player_->Update();

	// 敵キャラの更新
	enemy_->Update();

	// 天球
	skydome_->Update();

	// 地面
	ground_->Update();


	CheckAllCollisions();

	if (!enemy_->IsDead()) {
		isSceneEnd_ = true;
	}
}

void GameScene::Reset() 
{
	isSceneEnd_ = false;


	// エネミーモデル
	std::vector<Model*> enemyModels = {
	    enemyFighterBody_.get(), enemyFighterL_arm_.get(), enemyFighterR_arm_.get()};

	// エネミーの生成
	enemy_ = std::make_unique<Enemy>();

	// エネミーの初期化
	enemy_->Initialize(enemyModels);

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
	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 敵の描画
	enemy_->Draw(viewProjection_);

	// 天球の描画
	skydome_->Draw(viewProjection_);

	// 地面の描画
	ground_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB,posC;
	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	posA = player_->GetWorldPosition();

#pragma region プレイヤーと敵の当たり判定
	posB = enemy_->GetWorldPosition();

	float dx = posA.x - posB.x;
	float dy = posA.y - posB.y;
	float dz = posA.z - posB.z;

	float dist = sqrtf(dx * dx + dy * dy + dz * dz);
	
	float A[] = {posA.x, posA.y, posA.z};
	float B[] = {posB.x, posB.y, posB.z};

	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定

	// 自弾と敵キャラの当たり判定
	for (PlayerBullet* bullet : playerBullets) {

		posC = bullet->GetWorldPosition();
		 
			//posB = enemy_->GetWorldPosition();
			float radius = 1;
			float dx = (posC.x - posB.x) * (posC.x - posB.x);
			float dy = (posC.y - posB.y) * (posC.y - posB.y);
			float dz = (posC.z - posB.z) * (posC.z - posB.z);
			float distance = dx + dy + dz;
			if (distance <= (radius + radius) * (radius + radius)) {
				enemy_->OnCollision();
				bullet->OnCollision();
			}
		
	}
#pragma endregion

	#pragma region デバック
	ImGui::Begin("Begin");

	ImGui::DragFloat("dist", &dist);
	ImGui::DragFloat3("playerPos", A);
	ImGui::DragFloat3("EnemyPos", B);
	ImGui::End();
	#pragma endregion


	if (dist <= 0.1f + 0.1f) {
		// 自キャラのコールバック
		player_->OnCollision();

		isSceneEnd_ = true;

		// 敵キャラのコールバック
		enemy_->OnCollision();


	}

#pragma endregion
}
