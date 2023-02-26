#include "pch.h"
#include "Camera.h"
#include "Platform/OpenGl/OpenGlCamera.h"

Sweetie::Camera* Sweetie::Camera::Create(glm::vec3 position, glm::vec3 initLookAtPos, float FOV)
{
#ifdef OPENGL_RENDERING_API
	return new OpenGlCamera(position, initLookAtPos, FOV);
#else
	_Static_assert(false);
	return nullptr;
#endif // OPENGL_RENDERING_API
}
