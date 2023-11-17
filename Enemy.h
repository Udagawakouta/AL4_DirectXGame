#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "BaseCharacter.h"
#include <vector>

class Enemy:public BaseCharacter {
public:
	// 初期化
	void Initialize(const std::vector<Model*>& models) override;

	// 更新
	void Update() override;

	// 描画
	void Draw(const ViewProjection& viewProjection) override;
};
