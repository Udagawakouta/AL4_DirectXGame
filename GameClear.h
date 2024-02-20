#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>
class GameClear {
public:
	GameClear();

	~GameClear();

	void Initialize();

	void Update();

	void Draw();

	// フラグ
	bool isSceneEnd() { return isGameClearScene; }

	// ゲームシーンに飛ばす
	SceneType NextScene() { return SceneType::kTitle; }

	// リセットの関数
	void Reset();

private:
	Sprite* fadeinSprite_ = nullptr;
	Vector4 fadeinColor_ = {1.0f, 1.0f, 1.0f, 0.0f};

	// テクスチャ
	uint32_t texturehandle_ = 0;
	// スプライト
	Sprite* sprite_ = nullptr;
	// フラグ
	bool isGameClearScene = false;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
};
