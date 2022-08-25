#pragma once
#include "Serialization/Json.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Renderer/Renderer.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

#include "Core/Time.h"
#include "Core/Memory.h"
#include "Core/File.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Factory.h"
#include "Framework/Singleton.h"

#include "Input/InputSystems.h"
#include "Audio/AudioSystem.h"
#include "Resource/ResourceManager.h"
#include "Physics/PhysicsSystem.h"

#include "Components/TextComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/AudioComponent.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimComponent.h"

#include <memory>
#include <vector>
#include <list>

namespace neu
{
	extern InputSystem g_inputSystem;
	extern Time g_time;
	extern Renderer g_renderer;
	extern AudioSystem g_audioSystem;
	extern ResourceManager g_resources;
	extern PhysicsSystem g_physicsSystem;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();
	};
}