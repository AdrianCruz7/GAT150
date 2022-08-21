#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace neu
{
	void neu::PlayerComponent::Update()
	{
		//update transform with input
		Vector2 direction = Vector2::zero;

		float p_speed = 100;

		//movement
		if (g_inputSystem.GetKeyState(key_left) == InputSystem::State::Held)
		{
			m_owner->m_transform.rotation -= 180 * g_time.deltaTime;
		}

		if (g_inputSystem.GetKeyState(key_right) == InputSystem::State::Held)
		{
			m_owner->m_transform.rotation += 180 * g_time.deltaTime;
		}

		float thrust = 0;
		if (g_inputSystem.GetKeyState(key_up) == InputSystem::State::Held)
		{
			thrust = 300;
		}

		//gravity/force
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			Vector2 force = Vector2::Rotate({ 1, 0 }, math::DegToRad(m_owner->m_transform.rotation)) * thrust;
			component->ApplyForce(force);

			force = (Vector2{ 400, 300 } - m_owner->m_transform.position).Normalized() * 1.0f;
			component->ApplyForce(force);
		}

		m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

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