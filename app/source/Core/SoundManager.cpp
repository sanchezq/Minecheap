#include "SoundManager.h"
#include <iostream>
#include "App.h"
#include "GameManager.h"

SoundManager::SoundManager()
{
	m_soundEngine = irrklang::createIrrKlangDevice();
	if (!m_soundEngine)
	{
		std::cerr << "Failed to load Irrklang" << std::endl;
		return;//TODO close the APP ?
	}
	m_soundEngine->setSoundVolume(0.2f);
}

SoundManager::~SoundManager()
{
	if (m_soundInit != nullptr)
	{
		m_soundInit->drop();
	}
	m_soundEngine->drop();
}

irrklang::ISound* SoundManager::Play2D(const char* path, bool loop)
{
	return m_soundEngine->play2D(path, loop, false, true);
}

irrklang::ISound* SoundManager::Play3D(const char* path, const vec3& position, bool loop)
{
	return m_soundEngine->play3D(path, { position.m_x, position.m_y, position.m_z }, loop, false, true);
}

void SoundManager::SetDistance(irrklang::ISound* music, const float distance)
{
	if (music != nullptr)
	{
		music->setMinDistance(distance);
	}
}

void SoundManager::Volume(irrklang::ISound* music, const float volume)
{
	if (music != nullptr)
	{
		music->setVolume(volume);
	}
}

void SoundManager::BackgroundMusicInit(const char* path, bool loop)
{
	m_soundInit = m_soundEngine->play2D(path, loop, false, true);
	if (m_soundInit)
	{
		m_soundInit->setVolume(0.6f);
		m_soundInit->setMinDistance(5.f);
	}
}

void SoundManager::StopBackgroundMusicInit()
{
	if (m_soundInit)
	{
		m_soundInit->stop();
	}
}

void SoundManager::VolumeInitBackground(const float volume)
{
	if (m_soundInit)
	{
		m_soundInit->setVolume(volume);
	}
}

void SoundManager::Stop(irrklang::ISound* music)
{
	if (music != nullptr)
	{ 
		music->stop();
	}
}

void SoundManager::StopAllMusics()
{
	m_soundEngine->stopAllSounds();
}

void SoundManager::SetPosition(irrklang::ISound* sound, const vec3& position)
{
	if (sound != nullptr)
	{
		sound->setPosition({ position.m_x, position.m_y, position.m_z });
	}
}

void SoundManager::SetListenerPosition(const LowRenderer::Camera& camera, const vec3& velPerSecond)
{
	m_soundEngine->setListenerPosition({ camera.m_cameraPos.m_x, camera.m_cameraPos.m_y, camera.m_cameraPos.m_z },
							{ camera.m_cameraFront.m_x, camera.m_cameraFront.m_y, camera.m_cameraFront.m_z },
							{ velPerSecond.m_x, velPerSecond.m_y, velPerSecond.m_z },
							{ camera.m_cameraUp.m_x, camera.m_cameraUp.m_y, camera.m_cameraUp.m_z });
}


