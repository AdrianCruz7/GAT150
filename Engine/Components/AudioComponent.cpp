#include "AudioComponent.h"
#include "Engine.h"

void neu::AudioComponent::Update()
{
}

void neu::AudioComponent::Play()
{
	g_audioSystem.PlayAudio(m_soundname, loop);
}

void neu::AudioComponent::Stop()
{
}

bool neu::AudioComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool neu::AudioComponent::Read(const rapidjson::Value& value)
{
	return false;
}