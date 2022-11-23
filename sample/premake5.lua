workspace "GenesisNet"
	location "../"

	configurations { "Debug-x64", "Release-x64" }
	architecture "x86_64"

	include "../premake5.lua"

	project "Server"
		kind "ConsoleApp"
		systemversion "latest"
		language "C++"
		cppdialect "C++20"
		location "%{wks.location}/sample/%{prj.name}"

		debugdir "%{wks.location}/bin/%{cfg.system}/%{cfg.longname}/%{prj.name}"
		targetdir "%{wks.location}/bin/%{cfg.system}/%{cfg.longname}/%{prj.name}"
		objdir "%{wks.location}/bin-int/%{cfg.system}/%{cfg.longname}/%{prj.name}"

		files {
			"%{prj.location}/**.c",
			"%{prj.location}/**.h",
			"%{prj.location}/**.cpp",
			"%{prj.location}/**.hpp"
		}

		defines {
		}

		includedirs {
			"%{wks.location}/include/",
			"%{wks.location}/ThirdParty/enet/include/"
		}

		links {
			"GenesisNet",
			"Ws2_32.lib",
			"winmm.lib",
			"enet"
		}

		filter "configurations:Debug*"
			symbols "On"
			optimize "Off"
			defines { "TE_DEBUG" }
		filter "configurations:Release*"
			symbols "Off"
			optimize "Speed"
			defines { "TE_RELEASE", "TE_NDEBUG" }

		filter "system:windows"
			defines { "TE_WINDOWS" }
		filter "system:linux"
			defines { "TE_UNIX", "TE_LINUX" }
		filter "system:macosx"
			defines { "TE_MACOSX" }

	project "Client"
		kind "ConsoleApp"
		systemversion "latest"
		language "C++"
		cppdialect "C++20"
		location "%{wks.location}/sample/%{prj.name}"
		
		debugdir "%{wks.location}/bin/%{cfg.system}/%{cfg.longname}/%{prj.name}"
		targetdir "%{wks.location}/bin/%{cfg.system}/%{cfg.longname}/%{prj.name}"
		objdir "%{wks.location}/bin-int/%{cfg.system}/%{cfg.longname}/%{prj.name}"
		
		files {
			"%{prj.location}/**.c",
			"%{prj.location}/**.h",
			"%{prj.location}/**.cpp",
			"%{prj.location}/**.hpp"
		}
	
		defines {
		}
	
		includedirs {
			"%{wks.location}/include/",
			"%{wks.location}/ThirdParty/enet/include/"
		}
	
		links {
			"GenesisNet",
			"Ws2_32.lib",
			"winmm.lib",
			"enet"
		}
	
		filter "configurations:Debug*"
			symbols "On"
			optimize "Off"
			defines { "TE_DEBUG" }
		filter "configurations:Release*"
			symbols "Off"
			optimize "Speed"
			defines { "TE_RELEASE", "TE_NDEBUG" }
	
		filter "system:windows"
			defines { "TE_WINDOWS" }
		filter "system:linux"
			defines { "TE_UNIX", "TE_LINUX" }
		filter "system:macosx"
			defines { "TE_MACOSX" }
