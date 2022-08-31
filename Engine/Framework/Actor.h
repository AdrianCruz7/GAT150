#pragma once
#include "GameObject.h"
#include "Component.h"
#include "../Engine/Renderer/Model.h"
#include <vector>

namespace neu
{
	class Scene;
	class Component;
	class Renderer;

	class Actor : public GameObject, public ISerializable
	{
	public:
		Actor() = default;
		Actor(const Actor& other);
		Actor(const Transform& transform) : m_transform{ transform } {}

		CLASS_DECLARATION(Actor)

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void AddChild(std::unique_ptr<Actor> child);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();
	
		const std::string GetTag() { return tag; }
		void SetTag(const std::string& name) { this->tag = tag; }

		const std::string& GetName() { return name; }
		void SetName(const std::string& name) { this->name = name; }

		void SetDestroy() { m_destroy = true; }
		bool IsDestroyed() { return m_destroy; }

		void SetActive(bool active = true) { this->active = active; }
		bool IsActive() { return active; }

		Scene* GetScene() { return m_scene; }

		friend class Scene;
		friend class Component;
		friend class ModelComponent;

		Transform m_transform;

		float lifespan = 0;

	protected:
		std::string name;
		std::string tag;

		bool active = true;
		bool m_destroy = false;

		Model m_model;

		Scene* m_scene = nullptr;
		Actor* m_parent = nullptr;

		//Vector2 m_velocity;
		//float m_damping = 1;

		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<std::unique_ptr<Actor>> m_children;		
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}