#pragma once
#include "Platform/Rendering/Camera.h"
#include "Platform/OpenGl/OpenGlShader.h"

namespace Sweetie
{
	class OpenGlCamera : public Camera
	{
	private:

		glm::vec3 m_CameraPosition;

		glm::vec3 m_UpVector;
		glm::vec3 m_ForwardVector;
		glm::vec3 m_LeftVector;

		float m_CameraViewWidth;
		float m_CameraViewHeight;
		float m_CameraFOV;
		float m_Sensivity;

	public:
		OpenGlCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float cameraImageWidth = 1920.f, float cameraImageHeight = 1080.f, float sensivity = 0.05f, float FOV = 60.f);

		inline virtual glm::vec3 GetCameraPosition() const override { return m_CameraPosition; };
		inline virtual glm::vec3 GetCameraRotation() const override { return m_CameraPosition; };
		inline virtual glm::mat4 GetMVP() const override { return m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix; };
		inline virtual glm::vec3 GetForwardVector() const override { return m_ForwardVector; };
		inline virtual glm::vec3 GetLeftVector() const override { return m_LeftVector; };

		inline virtual void SetCameraPosition(glm::vec3 position) override;
		
		virtual void AddRotationYaw(float angle) override;
		virtual void AddRotationPitch(float angle) override;
		virtual void AddRotationRoll(float angle) override;
	};
}
