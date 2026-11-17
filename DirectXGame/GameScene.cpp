#include "GameScene.h"
#include <algorithm>
#include<numbers>
#include<cmath>

using namespace KamataEngine;

// デストラクタ
GameScene::~GameScene() {

	// オブジェクトの解放
	delete player_;
	delete enemy_;
	delete enemy2_;
	delete stage_;

	// パーティクルの解放
	for (Particle* particle : particles_) {
		delete particle;
	}

	particles_.clear();

	// 3Dモデルの解放
	delete modelPlayer_;
	delete modelEnemy_;
	delete modelEnemy2_;
	delete modelBlock_;
	delete modelParticle_;
}
// 初期化
void GameScene::Initialize() 
{

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

	// 追従カメラの初期化
	camera2_.translation_ = {0.0f, 5.0f, -20.0f};
	camera2_.Initialize();

	player_ = new Player();
	player_->Initialize(modelPlayer_);

	enemy_ = new Enemy();
	enemy_->Initialize(modelEnemy_);

	enemy2_ = new Enemy2();
	enemy2_->Initialize(modelEnemy2_);

	stage_ = new Stage();
	stage_->Initialize(modelBlock_);

    // ポリモーフィズムによるオブジェクト管理
	gameObjects_.push_back(player_);
	gameObjects_.push_back(enemy_);
	gameObjects_.push_back(enemy2_);

}

// 更新
void GameScene::Update() {

	 Input* input = Input::GetInstance();

	// Cキーを押した瞬間に切り替える
	if (input->TriggerKey(DIK_C)) {
		isCamera2_ = !isCamera2_;
	}

	// プレイヤー更新
	player_->Update(stage_, enemy_, enemy2_);

	// 追従カメラを更新
	if (isCamera2_) {

		// プレイヤーの現在位置を取得
		const Vector3& playerPosition = player_->GetWorldTransform().translation_;

		// カメラがプレイヤーを追いかける位置
		const float followSpeed = 0.1f;

		camera2_.translation_.x += (playerPosition.x - camera2_.translation_.x) * followSpeed;

		camera2_.translation_.y += (playerPosition.y - camera2_.translation_.y) * followSpeed;

		// Z座標は固定して、前後の距離を維持
		camera2_.translation_.z = -20.0f;
	}

	// カメラの行列を更新
	camera2_.UpdateMatrix();

	//========================================
	// 敵1が倒された瞬間
	//========================================

	if (enemyWasAlive_ && !enemy_->IsAlive()) {

		Vector3 position = enemy_->GetWorldTransform().translation_;

		CreateParticles(position);
	}

	// 現在の敵1の生存状態を保存
	enemyWasAlive_ = enemy_->IsAlive();

	//========================================
	// 敵2が倒された瞬間
	//========================================

	if (enemy2WasAlive_ && !enemy2_->IsAlive()) {

		Vector3 position = enemy2_->GetWorldTransform().translation_;

		CreateParticles(position);
	}

	// 現在の敵2の生存状態を保存
	enemy2WasAlive_ = enemy2_->IsAlive();

	//========================================
	// その他の更新
	//========================================

	stage_->Update();

	enemy_->Update();

	enemy2_->Update();

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

	// 使用するカメラを選択
	Camera& activeCamera = isCamera2_ ? camera2_ : camera_;

	//オブジェクトを共通の型で描画
	for (GameObject* object : gameObjects_) {
	
		object->Draw(activeCamera);
	}

	// ステージ
	stage_->Draw(activeCamera);

	// パーティクル
	for (Particle* particle : particles_) {
		particle->Draw(activeCamera);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}