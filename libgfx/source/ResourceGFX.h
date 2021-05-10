#pragma once
#include "Maths/vec3.h"
#include "lib_Export.h"

lib_API typedef void(*GraphicsInitFunction) (void);
lib_API bool InitLibGraph(GraphicsInitFunction function);
//lib_API void SetViewPort(int initWidth, int initHeight, int width, int height);
lib_API void WireFrameGFX(bool wireframe);
lib_API void ClearWindow(Core::Maths::vec4& color);
lib_API void EnableBackFaceCulling();