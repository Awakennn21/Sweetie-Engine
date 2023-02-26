#pragma once
#include "Platform/Rendering/Camera.h"
#include "Platform/OpenGl/OpenGlShader.h"

namespace Sweetie
{
	class OpenGlCamera : public Camera
	{
	private:

		glm::vec3 m_CameraPosition;
		glm::vec3 m_CameraLookAt;


		glm::vec3 m_UpVector;
		glm::vec3 m_ForwardVector;
		glm::vec3 m_LeftVector;


		float m_CameraViewWidth;
		float m_CameraViewHeight;
		float m_CameraFOV;

	public:
		OpenGlCamera(glm::vec3 position, glm::vec3 initLookAtPos, float FOV);

		inline virtual glm::vec3 GetCameraPosition() const override { return m_CameraPosition; };
		inline virtual glm::vec3 GetCameraRotation() const override { return m_CameraPosition; };
		inline virtual glm::mat4 GetMVP() const override { return m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix; };
		inline virtual glm::vec3 GetCameraLookAt() const override { return m_CameraLookAt; }
		inline virtual glm::vec3 GetForwardVector() const override { return m_ForwardVector; };
		inline virtual glm::vec3 GetLeftVector() const override { return m_LeftVector; };

		inline virtual void SetCameraPosition(glm::vec3 position) override;
		inline virtual void SetCameraLookAt(glm::vec3 position) override { m_CameraLookAt = position; };
		
		virtual void AddRotationYaw(float angle) override;
		virtual void AddRotationPitch(float angle) override;
		virtual void AddRotationRoll(float angle) override;
	};
}
