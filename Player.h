#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"
#include "list"

class Player:public BaseCharacter {
public:
	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransform() { return worldtransformBase_; }

	void SetViewProjection(const ViewProjection* viewprojection) {
		viewprojection_ = viewprojection;
	}

	// 初期化
	void Initialize(const std::vector<Model*>& models) override;
	// 更新処理
	void Update() override;
	// 描画処理
	void Draw(const ViewProjection& viewprojection) override;

	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();
	// 浮遊ギミック更新
	void UpdateFloatingGimmick();

	// 当たり判定
	void OnCollision();

	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	bool IsDead() const { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldtransformBase_;
	WorldTransform worldtransformBody_;
	WorldTransform worldtransformHead_;
	WorldTransform worldtransformL_arm_;
	WorldTransform worldtransformR_arm_;

	// カメラのビュープロジェクション
	const ViewProjection* viewprojection_ = nullptr;
	
	// 3Dモデル
	Model* modelFighterBody_   = nullptr;
	Model* modelFighterHead_   = nullptr;
	Model* modelFighterL_arm_  = nullptr;
	Model* modelFighterR_arm_  = nullptr;

	Model* ICO_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 死亡フラグ
	bool isDead_ = false;
};