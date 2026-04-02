workspace "Lily"
	architecture "x64"

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

include "Lily/vendor/GLFW"

project "Lily"
	location "Lily"
	kind "SharedLib"
	language "C++"

	targetdir("bin/"..outputdir.."/%{prj.name}")
	objdir("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "llpch.h"
	pchsource "Lily/src/llpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS",
			"LL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.."/Sandbox")
		}

		buildoptions "/utf-8"
	
	filter "configurations:Debug"
		defines "LL_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "LL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LL_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Lily/src"
	}

	links
	{
		"Lily"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS"
		}

		buildoptions "/utf-8"
	
	filter "configurations:Debug"
		defines "LL_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "LL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LL_DIST"
		optimize "On"