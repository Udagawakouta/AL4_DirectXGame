#pragma once

#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
	// 初期化
	void Initialize(Model* model, uint32_t textureHandle);
	// 更新処理
	void Update();
	// 描画処理
	void Draw(ViewProjection& viewprojection);

private:
	// キーボード入力
	Input* input_ = nullptr;
	// ワールド変換データ
	WorldTransform worldtransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};
