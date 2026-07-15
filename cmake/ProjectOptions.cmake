include_guard(GLOBAL)

include(Sanitizers)
include(Warnings)

function(ft_skyjo_setup_project_options)
    add_library(ft_skyjo_project_options INTERFACE)
    add_library(ft_skyjo::project_options ALIAS ft_skyjo_project_options)

    target_compile_features(ft_skyjo_project_options INTERFACE cxx_std_20)

    add_library(ft_skyjo_project_warnings INTERFACE)
    add_library(ft_skyjo::project_warnings ALIAS ft_skyjo_project_warnings)

    ft_skyjo_set_project_warnings(
        ft_skyjo_project_warnings
        ${FT_SKYJO_WARNINGS_AS_ERRORS}
    )

    ft_skyjo_enable_sanitizers(
        ft_skyjo_project_options
        ${FT_SKYJO_ENABLE_ASAN}
        ${FT_SKYJO_ENABLE_UBSAN}
    )
endfunction()
