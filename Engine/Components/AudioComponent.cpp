#include "AudioComponent.h"
#include "../Source/Engine.h"

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
