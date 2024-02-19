#include "FollowCamera.h"
#include "MyMath.h"
#include <Input.h>
#include <Xinput.h>

void FollowCamera::Initialize() {
	viewprojection_.Initialize();
	viewprojection_.farZ = 1400.0f;

}

void FollowCamera::Update() {
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 5.0f, -20.0f};
		// カメラの角度から回転行列を計算
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewprojection_.rotation_);

		// オフセットをカメラの回転に合わせて回転
		offset = TransformNormal(offset, rotateMatrix);

		// 座標をコピーしてオフセットずらす
		viewprojection_.translation_ = Add(target_->translation_, offset);

	}
	XINPUT_STATE joyState_;
	if (Input::GetInstance()->GetJoystickState(0, joyState_)) {
		const float kRadian = 0.02f;
		viewprojection_.rotation_.y += (float)joyState_.Gamepad.sThumbRX / SHRT_MAX * kRadian;
	}
	// ビュー行列の更新
	viewprojection_.UpdateMatrix();
	//viewprojection_.TransferMatrix();
}
