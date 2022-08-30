#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace neu
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
	}

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
		
		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
			velocity = component->m_velocity;
		}
		
		if (g_inputSystem.GetKeyState(key_space) == InputSystem::State::Pressed)
		{
			auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->Play();
			}
		}
		
		auto renderComponent = m_owner->GetComponent<RenderComponent>();
		if (renderComponent)
		{
			if (velocity.x != 0) renderComponent->SetFlipHorizontal(velocity.x < 0);
		}
	}


	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetName() == "Coin")
		{
			Event _event;
			_event.name = "EVENT_ADD_POINTS";
			_event.data = 100;
			
			g_eventManager.Notify(_event);
			other->SetDestroy();
		}
		
		if (other->GetTag() == "Enemy")
		{
			Event _event;
			_event.name = "EVENT_DAMAGE";
			_event.data = damage;
			_event.receiver = other;

			g_eventManager.Notify(_event);

		}

		std::cout << "player enter\n";
	}

	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		std::cout << "player exit\n";
	}

	bool neu::PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool neu::PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, jump);
		return true;
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			if (health <= 0)
			{
				m_owner->SetDestroy();

				Event _event;
				_event.name = "EVENT_PLAYER_DEAD";

				g_eventManager.Notify(_event);
			}
		}
	}
}