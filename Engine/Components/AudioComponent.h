#pragma once
#include "../Engine/Framework/Component.h"
#include <string>

namespace neu
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;
		
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Play();
		void Stop();

	public:
		std::string m_soundname;

		bool playOnAwake = false;
		float m_pitch = 0.0f;
		bool loop = false;
	};


}