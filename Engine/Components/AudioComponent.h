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

		void Play();
		void Stop();

	public:
		std::string m_soundname;

		bool playOnAwake = false;
		float volume = 1.0f;
		float m_pitch = 0.0f;
		bool loop = false;
	};


}