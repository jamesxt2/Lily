workspace "Lily"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Lily/vendor/GLFW/include"
IncludeDir["Glad"] = "Lily/vendor/Glad/include"
IncludeDir["ImGui"] = "Lily/vendor/imgui"
IncludeDir["glm"] = "Lily/vendor/glm"

include "Lily/vendor/GLFW"
include "Lily/vendor/Glad"
include "Lily/vendor/imgui"

project "Lily"
	location "Lily"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/"..outputdir.."/%{prj.name}")
	objdir("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "llpch.h"
	pchsource "Lily/src/llpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS",
			"LL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		buildoptions "/utf-8"
	
	filter "configurations:Debug"
		defines "LL_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "LL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LL_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/"..outputdir.."/%{prj.name}")
	objdir("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Lily/vendor/spdlog/include",
		"Lily/src",
		"Lily/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Lily"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS"
		}

		buildoptions "/utf-8"
	
	filter "configurations:Debug"
		defines "LL_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "LL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LL_DIST"
		runtime "Release"
		optimize "on"