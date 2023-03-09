#pragma once
#include <glm/glm.hpp>
namespace Sweetie
{
	class Camera
	{
	private:
		glm::mat4 m_ModelMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 m_CameraPosition;
		glm::vec3 m_UpVector;
		glm::vec3 m_ForwardVector;
		glm::vec3 m_LeftVector;

		float m_CameraViewWidth;
		float m_CameraViewHeight;
		float m_CameraFOV;
		float m_Sensivity;
		float m_CameraYaw;
		float m_CameraPitch;
		float m_CameraRoll;

	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float cameraImageWidth = 1920.f, float cameraImageHeight = 1080.f, float sensivity = 0.05f, float FOV = 60.f);

		inline glm::vec3 GetCameraPosition()	const { return m_CameraPosition; };
		inline glm::vec3 GetCameraRotation()	const { return m_CameraPosition; };
		inline glm::mat4 GetMVP()				const { return m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix; };
		inline glm::vec3 GetForwardVector()		const { return m_ForwardVector; };
		inline glm::vec3 GetLeftVector()		const { return m_LeftVector; };
		inline float GetCameraYaw()				const { return m_CameraYaw;};
		inline float GetCameraPitch()			const { return m_CameraPitch;};
		inline float GetCameraRoll()			const { return m_CameraRoll;};

		inline virtual void SetCameraPosition(glm::vec3 position);
		
		void AddRotationYaw(float angle);
		void AddRotationPitch(float angle);
		void AddRotationRoll(float angle);
	};
}
