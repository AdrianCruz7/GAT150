#pragma once
#include "../Engine/Framework/Component.h"
#include "../Components/CollisionComponent.h"

namespace neu
{
	class PlayerComponent : public Component, public ICollision
	{
	public:
		PlayerComponent() = default;

		void Update() override;
		void Initialize() override;

		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float speed = 0;
	};
}