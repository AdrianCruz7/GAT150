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
		Actor(const Transform& transform) : m_transform{ transform } {}
		
		// Inherited via GameObject
		virtual void Initialize() override;

		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void AddChild(std::unique_ptr<Actor> child);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return 0; }  //m_model.GetRadius() * std::max(m_Transform.scale.x, m_Transform.scale.y); }
		
		const std::string GetTag() { return tag; }
		void SetTag(const std::string& name) { this->name = name; }

		const std::string& GetName() { return tag; }
		void SetName(const std::string& name) { this->name = name; }

		friend class Scene;
		friend class Component;
		friend class ModelComponent;
		
	public:
		bool m_destroy = false;

		Scene* m_scene = nullptr;
		Actor* m_parent = nullptr;
		
		Transform m_transform;
		Model m_model;

	protected:
		std::string name;
		std::string tag;

		Vector2 m_velocity;
		float m_damping = 1;

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