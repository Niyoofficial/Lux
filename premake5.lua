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

include "Lux/Vendor/GLFW"
include "Lux/Vendor/Glad"
include "Lux/Vendor/ImGui"

project "Lux"
	location "Lux"
	kind "sharedLib"
	language "C++"
	staticruntime "Off"

	pchheader "lxpch.h"
	pchsource "Lux/Source/lxpch.cpp"
	
	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
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
		"%{IncludeDir.ImGui}"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	defines
	{
		"LUX_PLATFORM_WINDOWS",
		"LUX_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../Binaries/" .. outputdir .. "/Sandbox/\"")
	}

	filter "configurations:Debug"
		defines "LUX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LUX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LUX_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"
	
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
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"Lux"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	defines
	{
		"LUX_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "LUX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LUX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LUX_DIST"
		runtime "Release"
		optimize "On"
