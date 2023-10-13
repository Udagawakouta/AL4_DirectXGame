#include "Player.h"
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
}

void Player::Update() { 
	worldtransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewprojection) { 
	model_->Draw(worldtransform_, viewprojection, textureHandle_);

}