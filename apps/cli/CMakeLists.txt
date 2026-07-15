add_executable(ft_skyjo_cli main.cpp)

target_link_libraries(
    ft_skyjo_cli
    PRIVATE
        ft_skyjo::core
        ft_skyjo::project_options
        ft_skyjo::project_warnings
)
