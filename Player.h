#pragma once

#include "Model.h"
#include "WorldTransform.h"

class Player {
public:

	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransform() { return worldtransform_; }

	void SetViewProjection(const ViewProjection* viewprojection) {
		viewprojection_ = viewprojection;
	}

	Player();
	~Player();

	// 初期化
	void Initialize(Model* model, uint32_t textureHandle);
	// 更新処理
	void Update();
	// 描画処理
	void Draw(ViewProjection& viewprojection);

private:
	// ワールド変換データ
	WorldTransform worldtransform_;
	// カメラのビュープロジェクション
	const ViewProjection* viewprojection_ = nullptr;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};
