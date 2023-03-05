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
		float m_Sensitivity;

		float m_CameraYaw;
		float m_CameraPitch;
		float m_CameraRoll;

	public:
		OpenGlCamera(glm::vec3 position, float FOV);


		inline virtual glm::vec3 GetCameraPosition() const override { return m_CameraPosition; };
		inline virtual glm::vec3 GetForwardVector() const override { return m_ForwardVector; };
		inline virtual glm::vec3 GetLeftVector() const override { return m_LeftVector; };
		inline virtual glm::mat4 GetMVP() const override { return m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix; };


		inline virtual void SetCameraPosition(glm::vec3 position) override;
		

		void AddRotationYaw(float angle) override;
		void AddRotationPitch(float angle) override;
		void AddRotationRoll(float angle) override;
	private:
		glm::vec3 ClaculateForwardVector();
	};
}
