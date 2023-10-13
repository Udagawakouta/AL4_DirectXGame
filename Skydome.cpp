#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) { 
	assert(model);

	model_ = model;
	// ワールドトランスフォームの初期化
	worldtransform_.Initialize();
	// X,Y,Z方向のスケーリングを設定
	worldtransform_.scale_ = {1.0f,1.0f, 1.0f};

}

void Skydome::Update() { 
	worldtransform_.UpdateMatrix();
}

void Skydome::Draw(ViewProjection& viewProjection_) {
	// 3Dモデル描画
	model_->Draw(worldtransform_, viewProjection_);
}