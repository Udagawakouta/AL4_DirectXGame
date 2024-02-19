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

class TitleScene {
public:
	TitleScene();

	~TitleScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	//フラグ
	bool isSceneEnd() { return isTitleScene; }

	//ゲームシーンに飛ばす
	SceneType NextScene() { return SceneType::kGamePlay; }

	//リセットの関数
	void Reset() { isTitleScene = false; }

private:
	// テクスチャ
	uint32_t texturehandle_ = 0;
	// スプライト
	Sprite* sprite_ = nullptr;
	// フラグ
	bool isTitleScene = false;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

};
