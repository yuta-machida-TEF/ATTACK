#include "GameScene.h"
#include <algorithm>
#include <cmath>
#include <numbers>

using namespace KamataEngine;

// デストラクタ
GameScene::~GameScene() {

	// 敵のメモリ解放
	for (EnemyBase* enemy : enemies_) {
		delete enemy;
	}

	enemies_.clear();

	// その他のオブジェクトの解放
	delete player_;
	delete stage_;

	for (Particle* particle : particles_) {
		delete particle;
	}

	particles_.clear();
}
// 初期化
void GameScene::Initialize() {

	// 3Dモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("player");
	modelEnemy_ = Model::CreateFromOBJ("enemy");
	modelBlock_ = Model::CreateFromOBJ("block");
	modelEnemy2_ = Model::CreateFromOBJ("enemy");

	// パーティクル用モデル
	modelParticle_ = Model::CreateFromOBJ("deathParticle");
	assert(modelParticle_);

	// カメラの初期化
	camera_.translation_ = {0, 0, -20};
	camera_.Initialize();

	player_ = new Player();
	player_->Initialize(modelPlayer_);

	// イメージとしては、
	// クラス：設計図
	// ポリモーフィズムを使って敵を一括管理する
	//================================
	// Enemy
	//================================
	// push_backのメンバ関数の役割は、配列の最後に要素を追加する。
	EnemyBase* enemy = new Enemy();

	enemy->Initialize(modelEnemy_,{5.0f, -3.0f, 0.0f});

	// backのメンバ関数の役割は、配列の最後にある要素を取得する。
	enemies_.push_back(enemy);

	//======================
	// Enemy2
	//======================

	// Enemy2
	EnemyBase* enemy2 = new Enemy2();

	// 初期化
	enemy2->Initialize(modelEnemy2_, {10.0f, -3.0f, 0.0f});

	// 配列に追加
	enemies_.push_back(enemy2);

	for (EnemyBase* enemyBase : enemies_) {
		previousEnemyAlive_.push_back(enemyBase->IsAlive());
	}

	//===============
	// ステージ
	//===============
	stage_ = new Stage();
	stage_->Initialize(modelBlock_);

	// ポリモーフィズムによるオブジェクト管理
	gameObjects_.push_back(player_);
}

// 更新
void GameScene::Update() {

	// プレイヤー更新
	player_->Update(stage_, enemies_);

	//====================
	// 敵の更新・死亡判定
	//====================
	for (size_t i = 0; i < enemies_.size(); i++) {

		EnemyBase* enemy = enemies_[i];

		if (enemy == nullptr) {
			continue;
		}

		// 敵の更新
		if (enemy->IsAlive()) {
			enemy->Update();
		}

		// 敵が倒された瞬間
		if (previousEnemyAlive_[i] && !enemy->IsAlive()) {

			Vector3 position = enemy->GetWorldTransform().translation_;

			CreateParticles(position);
		}

		// 生存状態を保存
		previousEnemyAlive_[i] = enemy->IsAlive();
	}

	//========================================
	// その他の更新
	//========================================

	stage_->Update();

	//========================================
	// パーティクル更新
	//========================================

	for (Particle* particle : particles_) {
		particle->Update();
	}

	//========================================
	// 終了したパーティクルを削除
	//========================================

	particles_.erase(
	    std::remove_if(
	        particles_.begin(), particles_.end(),
	        [](Particle* particle) {
		        if (particle->IsFinished()) {

			        delete particle;

			        return true;
		        }

		        return false;
	        }),
	    particles_.end());
}

// パーティクル生成
void GameScene::CreateParticles(const KamataEngine::Vector3& position) {

	const int particleCount = 12;

	const float speed = 0.08f;

	for (int i = 0; i < particleCount; i++) {

		Particle* particle = new Particle();

		const float angle = 2.0f * std::numbers::pi_v<float> * static_cast<float>(i) / static_cast<float>(particleCount);

		Vector3 velocity = {std::cos(angle) * speed, std::sin(angle) * speed + 0.05f, 0.0f};

		particle->Initialize(modelParticle_, position, velocity);

		particles_.push_back(particle);
	}
}

// 描画
void GameScene::Draw() {

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// プレイヤー描画
	player_->Draw(camera_);

	// 敵をまとめて描画
	for (EnemyBase* enemy : enemies_) {

		if (enemy != nullptr && enemy->IsAlive()) {
			enemy->Draw(camera_);
		}
	}

	// ステージ
	stage_->Draw(camera_);

	// パーティクル
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}