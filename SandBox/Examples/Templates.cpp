#pragma once
#include <Sweetie.h>
#include <Windows.h>


using namespace Sweetie;
class CameraLayer : public Sweetie::Layer
{
	float tab[30] =
	{
		0.0f, 0.0f, 0.0f,	0.34f,0.23f,0.99f,
		5.0f, 0.0f, 0.0f,	0.87f,0.567f,0.34f,
		0.0f, 0.0f, 5.0f,	0.320f,0.48f,0.0f,
		5.0f, 0.0f, 5.0f,	0.50f,0.25f,0.567f,
		2.5f, 5.0f, 2.5f,	0.1f,0.21f,0.65f
	};
	uint32_t Index[18] =
	{
		0, 1, 2,  // base triangle 1
		1, 3, 2,  // base triangle 2
		0, 2, 4,  // side triangle 1
		2, 3, 4,  // side triangle 2
		3, 1, 4,  // side triangle 3
		1, 0, 4   // side triangle 4
	};
	std::shared_ptr<VertexArray> VAO;
	std::shared_ptr<VertexBuffer> VB;
	std::shared_ptr<IndexBuffer> IB;
	std::shared_ptr<Shader> S;
	std::shared_ptr<Camera> C;
	
	float LastMousePosX;
	float LastMousePosY;

	const int RotationStep = 3;

public:
	CameraLayer()
	{
		VAO.reset(VertexArray::Create());
		VAO->Bind();

		VB.reset(VertexBuffer::Create(tab, sizeof(tab)));
		VB->Bind();
		BufferLayout Layout =
		{
			{BufferElementType::Float3,"Positon"},
			{BufferElementType::Float3,"Color"},
		}; 
		VB->SetLayout(Layout);	
		VAO->AddVertexBuffer(VB);
		

		IB.reset(IndexBuffer::Create(Index, 18));
		IB->Bind();
		VAO->SetIndexBuffer(IB);


		S.reset(Shader::Create("../Sweetie/res/Shaders/BasicShaders.shader"));
		S->Bind();

		C.reset(new Camera(glm::vec3(30.0f, 0.0f, 30.0f),1920,1080,0.3));
		Renderer::EnableCulling();
	}

	void OnUpdate()
	{
		Renderer::BeginScene();
		{
			RenderCommand::Clear({ 0.8f,0.8f,0.8f,0.8f });
			S->Bind();
			S->SendDataMat4f("m_MVP", C->GetMVP());
			Renderer::Submit(VAO);
		}
		Renderer::EndScene();
	}

	void OnEvent(Sweetie::Event & e)
	{
		Sweetie::EventDispatcher d(e);
		d.Dispatch<Sweetie::EventMouseMoved>(BIND_EVENT_FUNCTION(CameraLayer::OnMouseMoved));
		d.Dispatch<Sweetie::EventMouseButtonPressed>(BIND_EVENT_FUNCTION(CameraLayer::OnMouseButtonPressed));
		d.Dispatch<Sweetie::EventKeyPressed>(BIND_EVENT_FUNCTION(CameraLayer::OnKeyPressed));
	}

	bool OnMouseMoved(Sweetie::EventMouseMoved& e)
	{
		if (Input::IsMouseButtonPressed(SW_MOUSE_BUTTON_3))
		{
			if (e.GetMouseX() > LastMousePosX)
			{
				C->AddRotationYaw(-RotationStep);
			}
			else if (e.GetMouseX() < LastMousePosX)
			{
				C->AddRotationYaw(RotationStep);
			}

			if (e.GetMouseY() > LastMousePosY )
			{
				if (C->GetCameraPitch() - RotationStep > -89.f)
				{
					C->AddRotationPitch(-RotationStep);
				}
				
			}
			else if (e.GetMouseY() < LastMousePosY)
			{
				if (C->GetCameraPitch() + RotationStep < 89.f)
				{
					C->AddRotationPitch(RotationStep);
				}
			}
			LastMousePosX = e.GetMouseX();
			LastMousePosY = e.GetMouseY();
		}
		return true;
	}

	bool OnMouseButtonPressed(Sweetie::EventMouseButtonPressed& e)
	{
		return true;
	}

	bool OnKeyPressed(Sweetie::EventKeyPressed& e)
	{
		if (e.GetKeyCode() == SW_KEY_D)
		{
			C->SetCameraPosition(C->GetCameraPosition() + 0.5f * C->GetLeftVector());
		}
		if (e.GetKeyCode() == SW_KEY_A)
		{
			C->SetCameraPosition(C->GetCameraPosition() + -0.5f * C->GetLeftVector());
		}


		if (e.GetKeyCode() == SW_KEY_W)
		{
			C->SetCameraPosition(C->GetCameraPosition() + 0.5f * C->GetForwardVector());
		}
		if (e.GetKeyCode() == SW_KEY_S)
		{
			C->SetCameraPosition(C->GetCameraPosition() + -0.5f * C->GetForwardVector());
		}
		return true;
	}
};

class  CameraApp : public Sweetie::Application
{

public:
	CameraApp()
		:Application()
	{
		PushLayer(new CameraLayer());
	}
};

Sweetie::Application* Sweetie::CreateApplication()
{
	return new CameraApp;
}
