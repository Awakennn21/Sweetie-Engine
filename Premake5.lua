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
IncludeDir["ImGui"] = "Sweetie/vendor/ImGui"
IncludeDir["GLM"] = "Sweetie/vendor/GLM"

include "Sweetie/vendor/GLFW"
include "Sweetie/vendor/GLAD"
include "Sweetie/vendor/ImGui"

project "Sweetie"
	location "Sweetie"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLM}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"

		defines
		{
			"SW_PLATFORM_WINDOWS",
			"SW_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
			"SW_ENABLE_ASSERTS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
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
		cppdialect "C++20"
		staticruntime "off"
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


