#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "BaseCharacter.h"
#include <vector>

class Enemy:public BaseCharacter {
public:
	// ������
	void Initialize(const std::vector<Model*>& models) override;

	// �X�V
	void Update() override;

	// �`��
	void Draw(const ViewProjection& viewProjection) override;
};
