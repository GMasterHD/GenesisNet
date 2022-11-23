project "GenesisNet"
	kind "StaticLib"
	systemversion "latest"
	language "C++"
	cppdialect "C++20"
	location "%{wks.location}/GenesisNet"

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

	filter "configurations:Debug*"
		symbols "On"
		optimize "Off"
		defines { "GN_DEBUG" }
	filter "configurations:Release*"
		symbols "Off"
		optimize "Speed"
		defines { "GN_RELEASE", "GN_NDEBUG" }
	
	filter "system:windows"
		defines { "GN_WINDOWS" }
	filter "system:linux"
		defines { "GN_UNIX", "GN_LINUX" }
	filter "system:macosx"
		defines { "GN_MACOSX" }
