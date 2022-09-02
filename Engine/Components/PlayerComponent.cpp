#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace neu
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
		g_eventManager.Subscribe("EVENT_HEALTH", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);
	}
	
	void neu::PlayerComponent::Update()
	{

		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if(camera)
		{
			camera->m_transform.position = math::Lerp(camera -> m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}

		Vector2 direction = Vector2::zero;
		//bool pause = true;
		
		//movement
		if (g_inputSystem.GetKeyState(key_left) == InputSystem::State::Held)
		{

			direction = Vector2::left;
			store = Vector2::left;
		}
		
		if (g_inputSystem.GetKeyState(key_right) == InputSystem::State::Held)
		{

			direction = Vector2::right;
			store = Vector2::right;
		}
		
		if (m_groundCount > 0 && g_inputSystem.GetKeyState(key_up) == InputSystem::State::Held)
		{
			std::cout << "Jump" << std::endl;
			
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * jump);
			}
		}

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::State::Pressed)
		{
			auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->Play();
			}
		}

		if (g_inputSystem.GetKeyState(key_down) == InputSystem::State::Pressed)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Bullet");
			actor->m_transform.position = m_owner->m_transform.position;
			actor->Initialize();

			auto physics = actor->GetComponent<PhysicsComponent>();
			Vector2 force = store * 100;

			actor->lifespan = 10;
			
			if (physics) physics->ApplyForce(force);
			m_owner->GetScene()->Add(std::move(actor));

			auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->Play();
			}


		}

		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			// if in the air (m_groundCount == 0) then reduce force 
			float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

			component->ApplyForce(direction * speed * multiplier);
			velocity = component->m_velocity;
		}
		
		auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
		if (animComponent)
		{
			if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
			if (std::fabs(velocity.x) > 0)
			{
				animComponent->SetSequence("run");
			}
			else
			{
				animComponent->SetSequence("idle");
			}
		}
		m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

	}


	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		std::cout << other->GetName() << std::endl;
		std::cout << other->GetTag() << std::endl;

		if (other->GetTag() == "Ground")
		{
			m_groundCount++;
		}

		if (other->GetName() == "Coin")
		{
			Event _event;
			_event.name = "EVENT_ADD_POINTS";
			_event.data = 100;
			
			std::cout << "touch" << std::endl;
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
		if (other->GetTag() == "Ground")
		{
			m_groundCount--;
		}

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