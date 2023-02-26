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
		virtual glm::vec3 GetCameraLookAt() const = 0;
		virtual glm::vec3 GetCameraRotation() const = 0;
		virtual glm::mat4 GetMVP() const = 0;
		virtual glm::vec3 GetForwardVector() const = 0;
		virtual glm::vec3 GetLeftVector() const = 0;


		virtual void SetCameraPosition(glm::vec3 position) = 0;
		virtual void SetCameraLookAt(glm::vec3 position) = 0;
		
		virtual void AddRotationYaw(float angle) = 0;
		virtual void AddRotationPitch(float angle) = 0;
		virtual void AddRotationRoll(float angle) = 0;

		static Camera* Create(glm::vec3 position, glm::vec3 initLookAtPos, float FOV);
	};
}