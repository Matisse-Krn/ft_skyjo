include(Catch)

add_executable(ft_skyjo_tests version_tests.cpp)

target_link_libraries(
    ft_skyjo_tests
    PRIVATE
        ft_skyjo::core
        ft_skyjo::project_options
        ft_skyjo::project_warnings
        Catch2::Catch2WithMain
)

catch_discover_tests(ft_skyjo_tests)
