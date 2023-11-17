#include "Enemy.h"

void Enemy::Initialize(const std::vector<Model*>& models) {
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);
}

void Enemy::Update() { 
	BaseCharacter::Update();
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	BaseCharacter::Draw(viewProjection);
}
