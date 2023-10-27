#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class FollowCamera {
public:
	void SetTarget(const WorldTransform* target) { target_ = target; }

	const ViewProjection& GetViewProjection() { return viewprojection_; }

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	// void Draw();

private:
	// ビュープロジェクション
	ViewProjection viewprojection_;
	// 追従対象
	const WorldTransform* target_ = nullptr;
};
