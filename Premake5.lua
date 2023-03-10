workspace "SweetieEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Sweetie/vendor/GLFW/include"
IncludeDir["GLAD"] = "Sweetie/vendor/GLAD/include"
IncludeDir["GLM"] = "Sweetie/vendor/GLM"

include "Sweetie/vendor/GLFW"
include "Sweetie/vendor/GLAD"

project "Sweetie"
	location "Sweetie"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Sweetie/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/GLM/glm/**.hpp",
		"%{prj.name}/vendor/GLM/glm/**.inl"

	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog-1.x/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",             
		"%{IncludeDir.GLM}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"SW_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
			"SW_ENABLE_ASSERTS",
			"OPENGL_RENDERING_API"
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Diste"
		defines "SW_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Examples/**.h",
		"%{prj.name}/Examples/**.cpp"
	}

	includedirs
	{
		"Sweetie/vendor/spdlog-1.x/include",
		"Sweetie/src",
		"%{IncludeDir.GLM}"
	}

	links
	{
		"Sweetie"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SW_DIST"
		runtime "Release"
		optimize "On"


