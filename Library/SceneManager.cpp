#include "SceneManager.h"
#include "SceneBase.h"
#include "../Source/SceneFactory.h"
#include <DxLib.h>

namespace
{
	std::string* currentName; // ���݂̃V�[���̖���
	std::string* nextName;    // ���̃V�[���̖���
	SceneBase* currentScene; // ���̃V�[���̃C���X�^���X��ێ�
	SceneFactory* factory;   // �V�[���؂�ւ��p��Factory�̃|�C���^�[
	bool exitRequest;
};

void SceneManager::Init()
{
	currentName = new std::string;
	nextName = new std::string;
	*nextName = "";
	*currentName = "";

	factory = new SceneFactory();
	// �ŏ��ɓ����V�[�����ASceneFactory�ɍ���Ă��炤
	currentScene = factory->CreateFirst();
	exitRequest = false;
}

void SceneManager::Update()
{
	if (*nextName != *currentName)
	{ // �V�[���؂�ւ��̎w�肪�������̂�
		if (currentScene != nullptr)
		{ // ���܂ł̃V�[�������
			ObjectManager::DeleteAllGameObject();
			delete currentScene;
			currentScene = nullptr;
		}
		currentScene = factory->Create(*nextName); // ���̃V�[�����쐬
		*currentName = *nextName;
	}
	if (currentScene != nullptr)
		currentScene->Update();
}

void SceneManager::Draw()
{
	if (currentScene != nullptr)
		currentScene->Draw();
}

void SceneManager::Release()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}
	if (factory != nullptr) {
		delete factory;
		factory = nullptr;
	}
	delete currentName;
	delete nextName;
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	*nextName = sceneName;
}

void SceneManager::Exit()
{
	exitRequest = true;
}

bool SceneManager::IsExit()
{
	return exitRequest;
}
