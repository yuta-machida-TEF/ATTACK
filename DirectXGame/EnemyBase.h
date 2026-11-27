#pragma once

#include "GameObject.h"
#include <KamataEngine.h>

//EnemyBaseがEnemy,Enemy2の親クラス
class EnemyBase : public GameObject {
public:
	virtual ~EnemyBase() = default;

	// 初期化
	virtual void Initialize(KamataEngine::Model* model,
		KamataEngine::Vector3 position) = 0;

	// 更新
	virtual void Update()= 0;

	// 描画
	virtual void Draw(KamataEngine::Camera& camera) = 0;

	// ワールド変換取得
	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	// 敵を倒す
	void Kill();

	// 生存判定
	bool IsAlive() const { return isAlive_; }

	// 敵のサイズ取得
	const KamataEngine::Vector3& GetSize() const { return size_; }

// protected は、親クラス自身と、その親クラスを継承した子クラスからアクセスできる領域です。
// つまり、EnemyとEnemy2から共通データを利用できます。
protected:
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Vector2 velocity_ = {0.0f, 0.0f};

	const float gravity_ = -0.020f;

	bool isGround_ = true;

	const float groundY_ = -7.0f;

	bool isAlive_ = true;

	KamataEngine::Vector3 size_ = {1.0f, 1.0f, 1.0f};

	KamataEngine::WorldTransform worldTransform_;
};