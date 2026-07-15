add_library(ft_skyjo_core STATIC)
add_library(ft_skyjo::core ALIAS ft_skyjo_core)

target_sources(
    ft_skyjo_core
    PRIVATE
        version.cpp
)

target_include_directories(
    ft_skyjo_core
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
    ft_skyjo_core
    PUBLIC
        ft_skyjo::project_options
    PRIVATE
        ft_skyjo::project_warnings
)
