#include "PhysicsComponent.h"
#include "Source/Engine.h"

namespace neu 
{
	void PhysicsComponent::Update()
	{
		m_velocity += m_acceleration * g_time.deltaTime;
		m_owner->m_Transform.position += m_velocity * g_time.deltaTime;
		m_velocity *= m_damping;

		m_acceleration = Vector2::zero;
	}
}
