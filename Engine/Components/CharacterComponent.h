#pragma once
#include "../Engine/Framework/Component.h"
#include "../Engine/Physics/Collision.h"
#include "../Engine/Framework/Event.h"

namespace neu
{
	class CharacterComponent : public Component, public ICollision, public INotify
	{
	public:
		CharacterComponent() = default;
		virtual ~CharacterComponent();

		virtual void Initialize() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float health = 100;
		float damage = 10;
		float speed = 0;
	};
}