#include "../Engine/Engine.h"
#include "LinkGame.h"
#include <iostream>

int main() 
{
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	//initialize engine
	neu::g_audioSystem.Initialize();
	neu::g_eventManager.Initialize();
	neu::g_inputSystem.Initialize();
	neu::g_physicsSystem.Initialize();
	neu::g_renderer.Initialize();
	neu::g_resources.Initialize();

	neu::Engine::Instance().Register();

	//window
	neu::g_renderer.CreateWindow("Test", 800, 600);
	neu::g_renderer.SetClearColor(neu::Color::black);

	//create game
	std::unique_ptr<LinkGame> game = std::make_unique<LinkGame>();
	game->Initialize();

	float angle = 0;
	bool quit = false;

	//game loop
	while (!quit)
	{
		//update
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();
		neu::g_physicsSystem.Update();
		neu::g_eventManager.Update();
		
		
		//quit with esc
		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) quit = true;
		
		angle += 360.0f * neu::g_time.deltaTime;
		game->Update();
		
		// render
		neu::g_renderer.BeginFrame();
		
		game->Draw(neu::g_renderer);
		
		neu::g_renderer.EndFrame();
	}

	game->Shutdown();
	game.reset();

	//scene.RemoveAll();
	neu::Factory::Instance().Shutdown();

	//shutdown
	neu::g_audioSystem.Shutdown();
	neu::g_eventManager.Shutdown();
	neu::g_inputSystem.Shutdown();
	neu::g_physicsSystem.Shutdown();
	neu::g_resources.Shutdown();
	neu::g_renderer.Shutdown();
}