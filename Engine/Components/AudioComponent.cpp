#include "AudioComponent.h"
#include "Engine.h"

namespace neu
{
	AudioComponent::~AudioComponent()
	{
		Stop();// !! call Stop() to stop the audio channel when destroyed 
	}

	void AudioComponent::Initialize()
	{
		if (playOnStart)
		{
			Play();
			// !! call Play() to start the audio if playing on awake (start) 
		}
	}

	void neu::AudioComponent::Update()
	{

	}

	void neu::AudioComponent::Play()
	{
		m_channel = g_audioSystem.PlayAudio(m_soundname, m_volume, m_pitch, loop);
	}

	void neu::AudioComponent::Stop()
	{
		m_channel.Stop();
	}

	bool neu::AudioComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool neu::AudioComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, m_soundname);
		READ_DATA(value, m_volume);
		READ_DATA(value, m_pitch);
		READ_DATA(value, playOnStart);
		READ_DATA(value, loop);

		g_audioSystem.AddAudio(m_soundname, m_soundname);

		return true;
	}
}
