#include "LinkGame.h"
#include "../Engine/Engine.h"
#include "EnemyComponent.h"

void LinkGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

	m_scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;
	std::vector<std::string> sceneNames = { "Scenes/prefabs.txt", "Scenes/Tilemap.txt", "Scenes/level.txt" };

	for (auto& sceneName : sceneNames)
	{
		bool success = neu::json::Load(sceneName, document);
		if (!success)
		{
			LOG("Could not load scene %s", sceneName.c_str());
			continue;
		}
		m_scene->Read(document);
	}
	m_scene->Initialize();

	neu::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&LinkGame::OnNotify, this, std::placeholders::_1));
	neu::g_eventManager.Subscribe("EVENT_PLAYER_DEAD", std::bind(&LinkGame::OnNotify, this, std::placeholders::_1));
}

void LinkGame::Shutdown()
{
	m_scene->RemoveAll();
}

void LinkGame::Update()
{
	switch (m_gameState)
	{
	case LinkGame::titleScreen:
		if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::State::Pressed)
		{
			m_scene->GetActorFromName("Title")->SetActive(false);

			m_gameState = gameState::startLevel;
		}
		break;

	case LinkGame::game:
		break;

	case LinkGame::gameOver:
		break;

	case LinkGame::playerDead:
		m_stateTimer -= neu::g_time.deltaTime;

		if (m_stateTimer <= 0)
		{
			m_gameState = gameState::startLevel;
			m_gameState = (m_gameState > 0) ? gameState::startLevel : gameState::gameOver;
		}
		break;

	case LinkGame::startLevel:
		for (int i = 0; i < 10; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
			actor->m_transform.position = { neu::randomf(0, 800), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		
		for (int i = 0; i < 3; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Ghost");
			actor->m_transform.position = { neu::randomf(0, 800), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		m_lives = 3;
		m_gameState = gameState::game;
		break;
	default:
		break;
	}

	m_scene->Update();
}

void LinkGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void LinkGame::OnAddPoints(const neu::Event& event)
{
	AddPoints(std::get<int>(event.data));

	std::cout << event.name << std::endl;
	std::cout << GetScore() << std::endl;

	std::cout << std::get<int>(event.data) << std::endl;
}

void LinkGame::OnPlayerDead(const neu::Event& event)
{
	m_gameState = gameState::playerDead;
	m_lives--; //lives
	m_stateTimer = 3;
}

void LinkGame::OnNotify(const neu::Event& event)
{
	if (event.name == "EVENT_ADD_POINTS")
	{
		AddPoints(std::get<int>(event.data));
	}

	if (event.name == "EVENT_PLAYER_DEAD")
	{
		m_gameState = gameState::playerDead;
		m_lives--; //lives
		m_stateTimer = 3;
	}
}
