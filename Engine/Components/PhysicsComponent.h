#pragma once
#include "../Engine/Framework/Component.h"
#include "../Engine/Math/Vector2.h"

namespace neu
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		void Update() override;
		virtual void ApplyForce(const Vector2& force) { m_acceleration += force; };

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Vector2 m_velocity;
		Vector2 m_acceleration;

		float m_damping = 1;
	};
}