#pragma once

#include"GameObject.h"
#include <KamataEngine.h>

class EnemyBase : public GameObject {
public:
	virtual ~EnemyBase() = default;

	// 初期化
	virtual void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position);

	// 更新
	virtual void Update();

	// 描画
	virtual void Draw(KamataEngine::Camera& camera);

	// 敵を倒す
	void Kill();

	// 生存判定
	bool IsAlive() const { return isAlive_; }

	// ワールド変換取得
	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	// 敵のサイズ取得
	const KamataEngine::Vector3& GetSize() const { return size_; }

//protected は、親クラス自身と、その親クラスを継承した子クラスからアクセスできる領域です。
//つまり、EnemyとEnemy2から共通データを利用できます。
protected:
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// 落下速度
	KamataEngine::Vector2 velocity_ = {0.0f, 0.0f};

	// 重力
	const float gravity_ = -0.020f;

	// 地面にいるか
	bool isGround_ = true;

	// 地面の高さ
	const float groundY_ = -7.0f;

	// 生存状態
	bool isAlive_ = true;

	// 敵のサイズ
	KamataEngine::Vector3 size_ = {1.0f, 1.0f, 1.0f};

	// ワールド変換
	KamataEngine::WorldTransform worldTransform_;
};
