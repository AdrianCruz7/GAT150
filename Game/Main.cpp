#include "../Engine/Engine.h"
#include <iostream>

int main() 
{
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	//initialize engine
	neu::g_inputSystem.Initialize();
	neu::g_renderer.Initialize();
	neu::g_audioSystem.Initialize();
	neu::g_resources.Initialize();
	neu::g_physicsSystem.Initialize();

	neu::Engine::Instance().Register();

	//window
	neu::g_renderer.CreateWindow("Test", 1200, 800);
	neu::g_renderer.SetClearColor(neu::Color::black);

	//std::shared_ptr<neu::Texture> texture = neu::g_resources.Get<neu::Texture>("textures/player.png", &neu::g_renderer);
	//neu::g_audioSystem.AddAudio("laser", "Audio/laser_shoot.wav");

	//scene
	neu::Scene scene;

	rapidjson::Document document;
	bool success = neu::json::Load("level.txt", document);
	assert(success);
	scene.Read(document);
	scene.Initialize();

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
		
		
		//quit with esc
		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) quit = true;
		
		angle += 360.0f * neu::g_time.deltaTime;
		scene.Update();
		
		// render
		neu::g_renderer.BeginFrame();
		
		scene.Draw(neu::g_renderer);
		
		neu::g_renderer.EndFrame();
	}

	//shutdown
	neu::g_audioSystem.Shutdown();
	neu::g_inputSystem.Shutdown();
	neu::g_resources.Shutdown();
	neu::g_renderer.Shutdown();
}