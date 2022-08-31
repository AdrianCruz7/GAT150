#pragma once
#include "../Engine/Framework/Game.h"
#include "../Engine/Framework/Event.h"

class LinkGame : public neu::Game, public neu::INotify 
{
public:
	enum gameState
	{
		titleScreen,
		game,
		gameOver,
		playerDead,
		startLevel
	};

public:
	virtual void Initialize() override;
	virtual void Shutdown() override;

	virtual void Update() override;
	virtual void Draw(neu::Renderer& renderer) override;

	virtual void OnNotify(const neu::Event& event) override;

	void OnAddPoints(const neu::Event& event);
	void OnPlayerDead(const neu::Event& event);

private:
	//change this back to titleSceen when done
	gameState m_gameState = gameState::titleScreen;
	float m_stateTimer = 0;
	int m_lives = 3;

};