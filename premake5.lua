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

project "Lux"
	location "Lux"
	kind "sharedLib"
	language "C++"

	pchheader "lxpch.h"
	pchsource "Lux/Source/lxpch.cpp"
	
	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/Vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"LUX_PLATFORM_WINDOWS",
		"LUX_BUILD_DLL"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../Binaries/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "LUX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LUX_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "LUX_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
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
		"Lux/Source"
	}

	links
	{
		"Lux"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"LUX_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "LUX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LUX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LUX_DIST"
		optimize "On"
