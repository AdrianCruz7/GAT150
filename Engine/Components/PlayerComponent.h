#pragma once
#include "../Engine/Framework/Component.h"

namespace neu
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent() = default;

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float speed = 0;
	};
}