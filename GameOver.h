#pragma once
#include <memory>
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"

class GameOver 
{
public:

	GameOver();

	~GameOver();

	void Initialize();

	void Update();

	void Draw();

	// フラグ
	bool isSceneEnd() { return isGameOverScene; }

	// ゲームシーンに飛ばす
	SceneType NextScene() { return SceneType::kTitle; }

	// リセットの関数
	void Reset();

private:
	Sprite* fadeinSprite_ = nullptr;
	Vector4 fadeinColor_ = {1.0f, 1.0f, 1.0f, 1.0f};

	// テクスチャ
	uint32_t texturehandle_ = 0;
	// スプライト
	Sprite* sprite_ = nullptr;
	// フラグ
	bool isGameOverScene = false;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
};