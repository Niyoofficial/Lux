workspace "Lux"
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
IncludeDir["GLFW"] = "%{wks.location}/Lux/Vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Lux/Vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Lux/Vendor/ImGui"
IncludeDir["glm"] = "%{wks.location}/Lux/Vendor/glm"

group "Dependencies"
	include "Lux/Vendor/GLFW"
	include "Lux/Vendor/Glad"
	include "Lux/Vendor/ImGui"
group ""

project "Lux"
	location "Lux"
	kind "StaticLib"
	cppdialect "C++17"
	language "C++"
	staticruntime "on"

	pchheader "lxpch.h"
	pchsource "Lux/Source/lxpch.cpp"
	
	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/Vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LUX_PLATFORM_WINDOWS",
			"LUX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "LUX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LUX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LUX_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"
	staticruntime "on"
	
	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Lux/Vendor/spdlog/include",
		"Lux/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Lux"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"LUX_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "LUX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LUX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LUX_DIST"
		runtime "Release"
		optimize "on"
