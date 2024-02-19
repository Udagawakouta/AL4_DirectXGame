#pragma once

#include "input/Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"
#include "PlayerBullet.h"
#include "list"

class Player:public BaseCharacter {
public:// メンバ関数
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

	// 攻撃
	void Attack(); 

	bool IsDead() const { return isDead_; }

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

public:// 定数
	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	static const int32_t kLifeTime = 60 * 5;

private:// メンバ変数
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
	Model* modelBullets_ = nullptr;


	Model* ICO_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 死亡フラグ
	bool isDead_ = false;

	// 弾
	std::list<PlayerBullet*> bullets_;
	// デスフラグ
	bool isEnemyDead_ = false;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;


	XINPUT_STATE joyState_;
	XINPUT_STATE preJoyState_;
};