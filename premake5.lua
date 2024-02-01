workspace "Smol"
    configurations { "Release", "Debug" }
    cppdialect "C++20"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        sanitize { "Address", "Fuzzer" }

project "Smol"
    kind "StaticLib"
    language "C++"
    location "build/"
    files { "src/*.cpp", "src/*.tpp" }
    includedirs { "lib" }

project "SmolTests"
    kind "ConsoleApp"
    language "C++"
    location "build/"
    links { "gtest", "gmock", "Smol" }
    files { "gtest/*.cpp" }
    includedirs { "lib" }
