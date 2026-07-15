include_guard(GLOBAL)

find_package(Catch2 3.15.2 CONFIG QUIET)

if(NOT Catch2_FOUND)
    include(FetchContent)

    set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
    set(CATCH_INSTALL_EXTRAS ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG 191fa38c9b1596cd2576ab531d4ab4d5e8e05190
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(Catch2)
endif()

list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
