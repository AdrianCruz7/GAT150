#pragma once
#include "Actor.h"
#include "../Serialization/Serializable.h"
#include <list>
#include <memory>

namespace neu
{
	//forward declaration
	class Renderer;
	class Game;

	class Scene : public ISerializable
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game { game } {}
		~Scene() = default;

		void Update();
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);

		template<typename T>
		T* GetActor();

		Game* GetGame() { return m_game; }

	private:
		Game* m_game = nullptr;
		std::list<std::unique_ptr<Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}
}