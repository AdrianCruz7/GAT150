#include "../Engine/Source/Engine.h"
#include <iostream>

int main() 
{
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	rapidjson::Document document;
	bool success = neu::json::Load("json.txt", document);
	assert(success);

	int i1;
	neu::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	neu::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	//initialize engine
	neu::g_inputSystem.Initialize();
	neu::g_renderer.Initialize();
	neu::g_audioSystem.Initialize();
	neu::g_resources.Initialize();

	//window
	neu::g_renderer.CreateWindow("Test", 1200, 800);

	//initialize quit

	//sprite
	neu::Scene scene;

	bool quit = false;
	//game loop
	while (!quit)
	{
		//update
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();


		//quit with esc
		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) quit = true;

		//angle += 360.0f * neu::g_time.deltaTime;
		scene.Update();
		
		// render
		neu::g_renderer.BeginFrame();

		scene.Draw(neu::g_renderer);
		//neu::g_renderer.Draw(texture, { 400, 300 }, angle, { 1, 1 }, { 0.5f, 1.0f });
		
		neu::g_renderer.EndFrame();
	}

	//shutdown
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}