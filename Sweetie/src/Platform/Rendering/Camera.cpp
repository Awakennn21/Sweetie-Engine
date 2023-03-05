#include "pch.h"
#include "Camera.h"
#include "Platform/OpenGl/OpenGlCamera.h"

Sweetie::Camera* Sweetie::Camera::Create(glm::vec3 position, float cameraImageWidth, float cameraImageHeight, float sensitivity, float FOV )
{
#ifdef OPENGL_RENDERING_API
	return new OpenGlCamera(position, cameraImageWidth, cameraImageHeight, sensitivity, FOV);
#else
	_Static_assert(false);
	return nullptr;
#endif // OPENGL_RENDERING_API
}
