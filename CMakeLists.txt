cmake_minimum_required(VERSION 3.25)

project(
    ft_skyjo
    VERSION 0.1.0
    DESCRIPTION "Deterministic C++20 rules engine proof of concept for a Skyjo-like game"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

option(FT_SKYJO_WARNINGS_AS_ERRORS "Treat project warnings as errors" ON)
option(FT_SKYJO_ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(FT_SKYJO_ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(ProjectOptions)
ft_skyjo_setup_project_options()

add_subdirectory(src/core)
add_subdirectory(apps/cli)

if(BUILD_TESTING)
    include(Dependencies)
    add_subdirectory(tests)
endif()
