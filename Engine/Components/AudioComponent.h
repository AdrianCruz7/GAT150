#pragma once
#include "../Engine/Framework/Component.h"
#include "Audio/AudioChannel.h"
#include <string>

namespace neu
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;
		~AudioComponent();
		
		void Initialize() override; 
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Play();
		void Stop();

	public:
		AudioChannel m_channel;

		std::string m_soundname;
		float m_volume = 1;
		float m_pitch = 1;
		bool playOnStart = false;
		bool loop = false;
	};


}