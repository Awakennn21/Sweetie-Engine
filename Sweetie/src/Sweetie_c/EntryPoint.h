#pragma once

#ifdef SW_PLATFORM_WINDOWS
extern Sweetie::Application* Sweetie::CreateApplication();

int main(int argc, char** argv)
{
	Sweetie::Log::Init();
	SW_CORE_INFO("Core Logger initlalized");	
	SW_INFO("App Logger initlalized");

	auto App  = Sweetie::CreateApplication();
	App->Run();
	delete App;
}
#endif
