#include "pch.h"
#include "OpenGlCamera.h"
#include "Sweetie_c/Core/Window.h"
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>


Sweetie::OpenGlCamera::OpenGlCamera(glm::vec3 position,float FOV)
    :m_CameraPosition(position), 
    m_CameraViewWidth(1920.f), m_CameraViewHeight(1080.f), m_CameraFOV(FOV), m_Sensitivity(0.5f),
    m_CameraYaw(0.0f), m_CameraPitch(0.0f),m_CameraRoll(0.0f)
{
    m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
    m_ForwardVector = ClaculateForwardVector();
    m_LeftVector = glm::normalize(glm::cross(m_ForwardVector, m_UpVector));

	m_ModelMatrix = glm::mat4(1.0f);
	m_ProjectionMatrix = glm::perspective(glm::radians(m_CameraFOV), m_CameraViewWidth / m_CameraViewHeight, 1.f, 100.f);
    m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_ForwardVector, m_UpVector);
}

void Sweetie::OpenGlCamera::SetCameraPosition(glm::vec3 position)
{
	m_CameraPosition = position; 
    m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_ForwardVector, m_UpVector);
}

void Sweetie::OpenGlCamera::AddRotationYaw(float angle)
{
	glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_UpVector); // rotation matrix

	glm::vec4 vRotatedF = rotMatrix * glm::vec4(m_ForwardVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_ForwardVector = glm::vec3(vRotatedF.x, vRotatedF.y, vRotatedF.z); // final rotated vector

	glm::vec4 vRotatedU = rotMatrix * glm::vec4(m_LeftVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_LeftVector = glm::vec3(vRotatedU.x, vRotatedU.y, vRotatedU.z); // final rotated vector

	glm::vec4 vRotatedLookAt = rotMatrix * glm::vec4(m_CameraPosition + m_ForwardVector, 0.0f); // rotated vector (homogeneous coordinates)

	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_ForwardVector, m_UpVector);

}

void Sweetie::OpenGlCamera::AddRotationPitch(float angle)
{
	glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_LeftVector); // rotation matrix

	glm::vec4 vRotatedF = rotMatrix * glm::vec4(m_ForwardVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_ForwardVector = glm::vec3(vRotatedF.x, vRotatedF.y, vRotatedF.z); // final rotated vector

	glm::vec4 vRotatedU = rotMatrix * glm::vec4(m_UpVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_UpVector = glm::vec3(vRotatedU.x, vRotatedU.y, vRotatedU.z); // final rotated vector

	glm::vec4 vRotatedLookAt = rotMatrix * glm::vec4(m_CameraPosition+m_ForwardVector, 0.0f); // rotated vector (homogeneous coordinates)

	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_ForwardVector, m_UpVector);
}

void Sweetie::OpenGlCamera::AddRotationRoll(float angle)
{
	glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), m_ForwardVector); // rotation matrix

	glm::vec4 vRotatedF = rotMatrix * glm::vec4(m_UpVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_UpVector = glm::vec3(vRotatedF.x, vRotatedF.y, vRotatedF.z); // final rotated vector

	glm::vec4 vRotatedU = rotMatrix * glm::vec4(m_LeftVector, 0.0f); // rotated vector (homogeneous coordinates)
	m_LeftVector = glm::vec3(vRotatedU.x, vRotatedU.y, vRotatedU.z); // final rotated vector

	glm::vec4 vRotatedLookAt = rotMatrix * glm::vec4(m_CameraPosition + m_ForwardVector, 0.0f); // rotated vector (homogeneous coordinates)

	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_ForwardVector, m_UpVector);
}



glm::vec3 Sweetie::OpenGlCamera::ClaculateForwardVector()
{
    glm::mat4 Rotation = glm::rotate(glm::radians(m_CameraYaw), m_UpVector); 
    glm::vec3 NewForward = glm::normalize(Rotation * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    return NewForward;
}
