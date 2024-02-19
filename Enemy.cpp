#include "Enemy.h"
#include "MyMath.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "GameScene.h"

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldtransformBase_.matWorld_.m[3][0];
	worldPos.y = worldtransformBase_.matWorld_.m[3][1];
	worldPos.z = worldtransformBase_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Initialize(const std::vector<Model*>& models) {
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);

	worldtransformBase_.Initialize();
	worldtransformBody_.Initialize();
	worldtransformL_arm_.Initialize();
	worldtransformR_arm_.Initialize();

	// 親子関係結ぶ
	worldtransformBody_.parent_ = &worldtransformBase_;
	worldtransformL_arm_.parent_ = &worldtransformBody_;
	worldtransformR_arm_.parent_ = &worldtransformBody_;

	// 腕の座標指定
	worldtransformBody_.translation_.z = 0.0f;
	worldtransformL_arm_.translation_.x = -1.0f;
	worldtransformR_arm_.translation_.x = 1.0f;
	worldtransformL_arm_.translation_.y = 1.0f;
	worldtransformR_arm_.translation_.y = 1.0f;

	// ICO_ = Model::CreateFromOBJ("ico", false);

}

void Enemy::Update() { 

	// 速さ
	const float kSpeed = 0.3f;
	Vector3 velocity{0.0f, 0.0f, kSpeed};

	Matrix4x4 rotateMatrix = MakeRotateMatrix(worldtransformBase_.rotation_);

	// 自機のY軸回り
	worldtransformBase_.rotation_.y += 0.03f;

	// 移動ベクトルを敵の角度だけ回転
	velocity = TransformNormal(velocity, worldtransformBase_.matWorld_);

	// 移動量
	worldtransformBase_.translation_ = Add(worldtransformBase_.translation_, velocity);
	// 行列を定数バッファに転送
	worldtransformBase_.UpdateMatrix();
	worldtransformBody_.UpdateMatrix();
	worldtransformL_arm_.UpdateMatrix();
	worldtransformR_arm_.UpdateMatrix();

	BaseCharacter::Update();
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	// ICO_->Draw(worldtransformBase_, viewProjection);
	if (isDead_ == true) {
	models_[0]->Draw(worldtransformBody_, viewProjection);
	models_[1]->Draw(worldtransformL_arm_, viewProjection);
	models_[2]->Draw(worldtransformR_arm_, viewProjection);
	}
}

void Enemy::OnCollision() {

	isDead_ = false; 
}

