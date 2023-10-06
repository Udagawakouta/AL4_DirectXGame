#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldtransform_.Initialize();
}

void Player::Update() { 
	worldtransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewprojection) { 
	model_->Draw(worldtransform_, viewprojection, textureHandle_);

}