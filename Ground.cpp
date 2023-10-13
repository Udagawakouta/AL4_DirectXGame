#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model) { 
	assert(model);

	model_ = model;
	// ワールドトランスフォームの初期化
	worldtransform_.Initialize();
	// X,Y,Z方向のスケーリングを設定
	worldtransform_.scale_ = {10.0f, 10.0f, 10.0f};
}

void Ground::Update() { 
	worldtransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection& viewProjection_) {
	// 3Dモデル描画
	model_->Draw(worldtransform_, viewProjection_);
}