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
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm);
	// 更新処理
	void Update();
	// 描画処理
	void Draw(ViewProjection& viewprojection);


	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();
	// 浮遊ギミック更新
	void UpdateFloatingGimmick();
	
	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

private:
	// ワールド変換データ
	WorldTransform worldtransform_;
	WorldTransform worldtransformBase_;
	WorldTransform worldtransformBody_;
	WorldTransform worldtransformHead_;
	WorldTransform worldtransformL_arm_;
	WorldTransform worldtransformR_arm_;

	// カメラのビュープロジェクション
	const ViewProjection* viewprojection_ = nullptr;
	// 3Dモデル
	Model* model_;
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;
	
	// Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};
