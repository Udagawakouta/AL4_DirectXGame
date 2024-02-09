#include "Player.h"
#include "Input.h"
#include "MyMath.h"
#include <Xinput.h>
#include <cassert>
#define _USE_MATH_DEFINES
#include "math.h"

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldtransformBase_.matWorld_.m[3][0];
	worldPos.y = worldtransformBase_.matWorld_.m[3][1];
	worldPos.z = worldtransformBase_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Initialize(const std::vector<Model*>& models) {
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);

	worldtransformBase_.Initialize();
	worldtransformBody_.Initialize();
	worldtransformHead_.Initialize();
	worldtransformL_arm_.Initialize();
	worldtransformR_arm_.Initialize();

	// 親子関係結ぶ
	worldtransformBody_.parent_ = &worldtransformBase_; // ボディの親をベースにする
	worldtransformHead_.parent_ = &worldtransformBody_;
	worldtransformL_arm_.parent_ = &worldtransformBody_;
	worldtransformR_arm_.parent_ = &worldtransformBody_;

	// 各パーツ位置調整
	worldtransform_.translation_.x = 1.0f;
	worldtransform_.translation_.y = 1.0f;
	worldtransform_.translation_.z = 1.0f;

	worldtransformBody_.translation_ = {0.0f, 0.0f, 0.0f};

	// 腕の座標指定
	worldtransformHead_.translation_.y = 1.5f;
	worldtransformL_arm_.translation_.x = -0.5f;
	worldtransformR_arm_.translation_.x = 0.5f;
	worldtransformL_arm_.translation_.y = 1.3f;
	worldtransformR_arm_.translation_.y = 1.3f;

	// ICO_ = Model::CreateFromOBJ("ico",false);
}

void Player::Update() {

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;

	// ゲームパッド状態
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// キャラクターの移動速さ
		const float Speed = 0.3f;
		// 移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * Speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * Speed};
		// 移動量に速さを反映
		move = Normalize(move);
		move = Multiply2(Speed, move);

		// 回転行列
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewprojection_->rotation_);
		// 移動ベクトルをカメラの角度だけ回転
		move = TransformNormal(move, rotateMatrix);

		// 移動
		worldtransformBase_.translation_ = Add(worldtransformBase_.translation_, move);

		// playerのY軸周り角度(θy)
		worldtransformBase_.rotation_.y = std::atan2(move.x, move.z);
	}

	UpdateFloatingGimmick();

	// 行列を定数バッファに転送
	worldtransformBase_.UpdateMatrix();
	worldtransformBody_.UpdateMatrix();
	worldtransformHead_.UpdateMatrix();
	worldtransformL_arm_.UpdateMatrix();
	worldtransformR_arm_.UpdateMatrix();

	BaseCharacter::Update();
}

void Player::Draw(const ViewProjection& viewprojection) {
	// BaseCharacter::Draw(viewprojection);

	// models_ {body, head, LArm,RArm};
	// ICO_->Draw(worldtransformBase_, viewprojection);
	models_[0]->Draw(worldtransformBody_, viewprojection);
	models_[1]->Draw(worldtransformHead_, viewprojection);
	models_[2]->Draw(worldtransformL_arm_, viewprojection);
	models_[3]->Draw(worldtransformR_arm_, viewprojection);
}

void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }

void Player::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	const uint16_t period = 120;
	// 1フレームでのパラメーター加算値
	const float step = 2.0f * (float)M_PI / period;
	// パラメーターを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * M_PI);
	// 浮遊の振幅<m>
	const float floatingAmplitude = 0.5f;
	// 浮遊を座標に反映
	worldtransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude;
	// 腕の動き
	worldtransformL_arm_.rotation_.x = std::sin(floatingParameter_) * 0.75f;
	worldtransformR_arm_.rotation_.x = std::sin(floatingParameter_) * 0.75f;
}

void Player::OnCollision() {}
