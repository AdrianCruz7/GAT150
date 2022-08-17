#include "Engine.h"

namespace neu
{
	Renderer g_renderer;
	InputSystem g_inputSystem;
	Time g_time;
	AudioSystem g_audioSystem;
	ResourceManager g_resources;

	void Engine::Register()
	{
		REGISTER_CLASS(Actor); //== Factory::Instance().Register<Actor>("Actor");
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
	}
}