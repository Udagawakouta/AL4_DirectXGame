﻿#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Player.h"
#include <memory>
#include "Skydome.h"
#include "Ground.h"
#include "FollowCamera.h"
#include "Enemy.h"
#include "Scene.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();
	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() {

		return SceneType::kGameOver; 
	

	}

	void Reset();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// スプライト
	Sprite* sprite_ = nullptr;

	// プレイヤーモデルデータ
	std::unique_ptr<Model> modelPlayer_;
	// プレイヤーモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;

	// エネミーモデルデータ
	std::unique_ptr<Model> modelEnemy_;
	// エネミーモデル
	std::unique_ptr<Model> enemyFighterBody_;
	std::unique_ptr<Model> enemyFighterHead_;
	std::unique_ptr<Model> enemyFighterL_arm_;
	std::unique_ptr<Model> enemyFighterR_arm_;

	// std::unique_ptr<Model> model_;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// デバックカメラ有効
	bool isDebugCameraActive_ = false;
	// デバックカメラの生成
	DebugCamera* debugcamera_ = nullptr;
	// 自キャラ
	std::unique_ptr<Player> player_;
	std::unique_ptr<PlayerBullet> playerBullets_;
	// 敵キャラ
	std::unique_ptr<Enemy> enemy_;

	// 天球
	std::unique_ptr <Skydome> skydome_ = nullptr;
	// 3D天球モデル
	Model* modelSkydome_ = nullptr;
	// 地面
	std::unique_ptr <Ground>ground_ = nullptr;
	// 3D地面モデル
	Model* modelGround_ = nullptr;


	// カメラ
	std::unique_ptr<FollowCamera> followCamera_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	bool isSceneEnd_ = false;


};

