#include "Player.h"
#include "Input.h"
#include "MyMath.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォームの初期化
	worldtransform_.Initialize();
	// X,Y,Z方向のスケーリングを設定
	worldtransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldtransform_.translation_ = {0.0f, 2.0f, 0.0f};
	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();
}

void Player::Update() {
	// キャラクターの移動ベクトル
	Vector3 move = {3, 3, 3};

	worldtransform_.UpdateMatrix();

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;

	// ゲームパッド状態
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// キャラクターの移動速さ
		const float Speed = 0.3f;
		// 移動量
		Vector3 move = {(float)joyState.Gamepad.sThumbLX, 0.0f, joyState.Gamepad.sThumbLY};
		// 移動量に速さを反映
		move = Normalize(move) * Speed;
		// 移動

	}
}

void Player::Draw(ViewProjection& viewprojection) {
	model_->Draw(worldtransform_, viewprojection, textureHandle_);
}