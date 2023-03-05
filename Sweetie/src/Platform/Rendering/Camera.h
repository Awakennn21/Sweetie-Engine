#pragma once
#include "pch.h"
#include "Sweetie_c/Core.h"
#include "Platform/Rendering/Shader.h"
#include <glm/glm.hpp>

namespace Sweetie
{
	class Camera
	{
	protected:
		glm::mat4 m_ModelMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;


	public:
		virtual ~Camera() {};
		virtual glm::vec3 GetCameraPosition() const = 0;
		virtual glm::vec3 GetCameraRotation() const = 0;
		virtual glm::mat4 GetMVP() const = 0;
		virtual glm::vec3 GetForwardVector() const = 0;
		virtual glm::vec3 GetLeftVector() const = 0;


		virtual void SetCameraPosition(glm::vec3 position) = 0;
		
		virtual void AddRotationYaw(float angle) = 0;
		virtual void AddRotationPitch(float angle) = 0;
		virtual void AddRotationRoll(float angle) = 0;

		static Camera* Create(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float cameraImageWidth = 1920.f, float cameraImageHeight = 1080.f, float sensitivity = 0.05f, float FOV = 60.f);
	};
}