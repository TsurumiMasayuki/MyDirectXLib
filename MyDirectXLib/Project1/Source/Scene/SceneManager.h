#pragma once
#include <string>
#include <unordered_map>

class AbstractScene;

//シーン管理クラス
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	//更新処理
	void update();
	//描画処理
	void draw();

	//シーン管理にシーン追加
	void addScene(std::string key, AbstractScene* pAbstractScene);
	//シーン変更
	void changeScene(std::string key);

private:
	//コピーコンストラクタ禁止
	SceneManager(const SceneManager&) = delete;
	//代入禁止
	SceneManager& operator = (const SceneManager&) = delete;

private:
	//現在のシーン名
	std::string m_CurrentScene;
	//シーン管理用map
	std::unordered_map<std::string, AbstractScene*> m_Scenes;
};

