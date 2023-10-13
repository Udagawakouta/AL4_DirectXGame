#pragma once

#include "WorldTransform.h"
#include "Model.h"

class Ground {
public:
	void Initialize(Model*model);

	void Update();

	void Draw(ViewProjection& viewProjection_);

	private:
	// ワールド変換データ
	WorldTransform worldtransform_;
	// モデル
	Model* model_ = nullptr;
};
