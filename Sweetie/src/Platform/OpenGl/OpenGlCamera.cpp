#include "pch.h"
#include "OpenGlCamera.h"
#include "Sweetie_c/Window.h"
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


Sweetie::OpenGlCamera::OpenGlCamera(glm::vec3 position, float cameraImageWidth , float cameraImageHeight, float sensitivity, float FOV)
	:m_CameraPosition(position), m_CameraViewWidth(cameraImageWidth), m_CameraViewHeight(cameraImageHeight), m_Sensivity(sensitivity), m_CameraFOV(FOV)
{
	m_ModelMatrix = glm::mat4(1.0f);
	m_ProjectionMatrix = glm::perspective(glm::radians(m_CameraFOV), m_CameraViewWidth / m_CameraViewHeight, 1.f, 100.f);
	m_ViewMatrix = glm::lookAt(m_CameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), m_UpVector);


	m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_ForwardVector = glm::normalize(-glm::vec3(m_ViewMatrix[0][2], m_ViewMatrix[1][2], m_ViewMatrix[2][2]));
	m_LeftVector = glm::normalize(glm::cross(m_ForwardVector, m_UpVector));
}

void Sweetie::OpenGlCamera::SetCameraPosition(glm::vec3 position)
{
	m_CameraPosition = position; 
	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_ForwardVector + m_CameraPosition, m_UpVector);
}

void Sweetie::OpenGlCamera::AddRotationYaw(float angle)
{
	glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle*m_Sensivity), m_UpVector); // rotation matrix

	glm::vec4 vRotatedF = rotMatrix * glm::vec4(m_ForwardVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_ForwardVector = glm::vec3(vRotatedF.x, vRotatedF.y, vRotatedF.z); // final rotated vector

	glm::vec4 vRotatedU = rotMatrix * glm::vec4(m_LeftVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_LeftVector = glm::vec3(vRotatedU.x, vRotatedU.y, vRotatedU.z); // final rotated vector

	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_ForwardVector + m_CameraPosition, m_UpVector);
}

void Sweetie::OpenGlCamera::AddRotationPitch(float angle)
{
	angle *= m_Sensivity;
	glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle * m_Sensivity), m_LeftVector); // rotation matrix

	glm::vec4 vRotatedF = rotMatrix * glm::vec4(m_ForwardVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_ForwardVector = glm::vec3(vRotatedF.x, vRotatedF.y, vRotatedF.z); // final rotated vector

	glm::vec4 vRotatedU = rotMatrix * glm::vec4(m_UpVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_UpVector = glm::vec3(vRotatedU.x, vRotatedU.y, vRotatedU.z); // final rotated vector

	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_ForwardVector + m_CameraPosition, m_UpVector);
}

void Sweetie::OpenGlCamera::AddRotationRoll(float angle)
{
	angle *= m_Sensivity;
	glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle * m_Sensivity), m_ForwardVector); // rotation matrix

	glm::vec4 vRotatedF = rotMatrix * glm::vec4(m_UpVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_UpVector = glm::vec3(vRotatedF.x, vRotatedF.y, vRotatedF.z); // final rotated vector

	glm::vec4 vRotatedU = rotMatrix * glm::vec4(m_LeftVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_LeftVector = glm::vec3(vRotatedU.x, vRotatedU.y, vRotatedU.z); // final rotated vector

	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_ForwardVector + m_CameraPosition, m_UpVector);
}
