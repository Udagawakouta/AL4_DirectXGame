﻿#include "Player.h"
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

Player::~Player() { 

}

void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) {
	// NULLポインタチェック
	assert(modelBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);

	// 引数として受け取ったデータをメンバ変数に記録する
	modelFighterBody_ = modelBody;
	modelFighterHead_ = modelHead;
	modelFighterL_arm_ = modelL_arm;
	modelFighterR_arm_ = modelR_arm;
	// textureHandle_ = textureHandle;

#pragma region モデルの設定

	// 腕の座標指定
	worldtransformHead_.translation_.y = 1.5f;
	worldtransformL_arm_.translation_.x = -0.5f;
	worldtransformR_arm_.translation_.x = 0.5f;
	worldtransformL_arm_.translation_.y = 1.3f;
	worldtransformR_arm_.translation_.y = 1.3f;

#pragma endregion

	// ワールドトランスフォームの初期化
	worldtransformBase_.Initialize();
	// X,Y,Z方向のスケーリングを設定
	worldtransformBase_.scale_ = {1.0f, 1.0f, 1.0f};
	worldtransformBase_.translation_ = {0.0f, 2.0f, -5.0f};

	worldtransformBody_.Initialize();
	worldtransformHead_.Initialize();
	worldtransformL_arm_.Initialize();
	worldtransformR_arm_.Initialize();

	worldtransformBody_.parent_ = &worldtransformBase_;
	worldtransformHead_.parent_ = &worldtransformBody_;
	worldtransformL_arm_.parent_ = &worldtransformBody_;
	worldtransformR_arm_.parent_ = &worldtransformBody_;
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
}

void Player::Draw(ViewProjection& viewprojection) {
	// model_->Draw(worldtransform_, viewprojection, textureHandle_);
	modelFighterBody_->Draw(worldtransformBody_, viewprojection);
	modelFighterHead_->Draw(worldtransformHead_, viewprojection);
	modelFighterL_arm_->Draw(worldtransformL_arm_, viewprojection);
	modelFighterR_arm_->Draw(worldtransformR_arm_, viewprojection);
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
