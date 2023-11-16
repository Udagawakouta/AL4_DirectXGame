#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "BaseCharacter.h"
#include <vector>

class Enemy:public BaseCharacter {
public:
	// ‰Šú‰»
	void Initialize(const std::vector<Model*>& models) override;

	// XV
	void Update() override;

	// •`‰æ
	void Draw(const ViewProjection& viewProjection) override;
};
