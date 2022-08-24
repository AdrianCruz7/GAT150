#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace neu
{
	void neu::PlayerComponent::Update()
	{
		Vector2 direction = Vector2::zero;
		//movement
		bool pause = true;

		if (g_inputSystem.GetKeyState(key_left) == InputSystem::State::Held)
		{
			//m_owner->m_transform.rotation -= 180 * g_time.deltaTime;
			direction = Vector2::left;
		}

		if (g_inputSystem.GetKeyState(key_right) == InputSystem::State::Held)
		{
			//m_owner->m_transform.rotation += 180 * g_time.deltaTime;
			direction = Vector2::right;
		}

		if (g_inputSystem.GetKeyState(key_up) == InputSystem::State::Held)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * speed);
			}
		}

		
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
		}

		//m_owner->m_transform.position += direction * 300 * g_time.deltaTime;


		if (g_inputSystem.GetKeyState(key_space) == InputSystem::State::Pressed)
		{
			auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->Play();
			}
		}
	}

	bool neu::PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool neu::PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);
		return true;
	}

}