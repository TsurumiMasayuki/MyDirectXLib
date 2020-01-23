#pragma once

class SceneManager;

//ゲームクラス
class Game
{
public:
	Game();
	~Game();

	void init();		//初期化処理
	void update();		//更新処理
	void draw();		//描画処理
	void shutdown();	//終了処理

private:
	SceneManager* m_pSceneManager;
};

