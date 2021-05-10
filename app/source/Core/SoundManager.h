#pragma once
#include <irrKlang.h>
#include "Maths/vec3.h"
#include "LowRenderer/Camera.h"
class SoundManager
{
public:
	using vec3 = Core::Maths::vec3;
	SoundManager();
	~SoundManager();

	irrklang::ISound* Play2D(const char* path, bool loop);
	irrklang::ISound* Play3D(const char* path, const vec3& position, bool loop);
	void SetDistance(irrklang::ISound* music, const float distance);
	void Volume(irrklang::ISound* music, const float volume);
	void Stop(irrklang::ISound* music);
	void StopAllMusics();

	void BackgroundMusicInit(const char* path, bool loop);

	void SetPosition(irrklang::ISound* sound, const vec3& position);
	void SetListenerPosition(const LowRenderer::Camera& camera, const vec3& velPerSecond = {0.f, 0.f, 0.f});
	void StopBackgroundMusicInit();
	void VolumeInitBackground(const float volume);
private:
	irrklang::ISoundEngine* m_soundEngine = nullptr;
	irrklang::ISound* m_soundInit = nullptr;
};