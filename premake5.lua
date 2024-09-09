workspace "Quiet"
    architecture "x86_64"
    startproject "Quiet-Editor"

    configurations{
        "Debug",
        "Release"
    }

    flags{
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = 	"Engine/Vendor/GLFW/include"
IncludeDir["Glad"] = 	"Engine/Vendor/Glad/include"
IncludeDir["ImGui"] = 	"Engine/Vendor/ImGui"
IncludeDir["glm"] = 	"Engine/Vendor/glm"
IncludeDir["stb"] = 	"Engine/Vendor/stb"

--include vendor dependencies group
group "Dependencies"
    include "Engine/Vendor"
group ""

---------------------------------------------
--- ENGINE ----------------------------------
---------------------------------------------
project "Engine"
    location "Engine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "Quiet_PCH.h"
    pchsource "Engine/Source/Quiet_PCH.cpp"

    files{
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "%{prj.name}/Vendor/stb/**.h",
        "%{prj.name}/Vendor/glm/glm/**.hpp",
        "%{prj.name}/Vendor/glm/glm/**.inl"
    }

    defines{
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs{
		"%{prj.name}/Source",
        "%{prj.name}/Vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb}"
	}

    links{
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines{
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "QT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "QT_RELEASE"
        runtime "Release"
        optimize "on"
