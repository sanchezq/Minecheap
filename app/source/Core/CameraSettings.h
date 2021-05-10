#pragma once

struct CameraSettings
{
	float m_lastX = 1250.0f / 2.f;
	float m_lastY = 800.0f / 2.f;
	bool m_active_mouse = true;
	bool m_mouse_cursor = true;
	bool m_firstMouse = true;
	bool m_wireframe = false;
	bool m_transparency = false;
};