include_guard(GLOBAL)

function(ft_skyjo_enable_sanitizers target enable_asan enable_ubsan)
    if(MSVC)
        if(enable_asan)
            target_compile_options(${target} INTERFACE /fsanitize=address)
        endif()

        if(enable_ubsan)
            message(WARNING "UBSan is not configured for MSVC in this project")
        endif()

        return()
    endif()

    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        if(enable_asan OR enable_ubsan)
            message(WARNING "Sanitizers are not configured for ${CMAKE_CXX_COMPILER_ID}")
        endif()
        return()
    endif()

    set(sanitizers "")

    if(enable_asan)
        list(APPEND sanitizers address)
    endif()

    if(enable_ubsan)
        list(APPEND sanitizers undefined)
    endif()

    if(sanitizers)
        list(JOIN sanitizers "," sanitizer_list)
        target_compile_options(
            ${target}
            INTERFACE
                -fsanitize=${sanitizer_list}
                -fno-omit-frame-pointer
        )
        target_link_options(
            ${target}
            INTERFACE
                -fsanitize=${sanitizer_list}
                -fno-omit-frame-pointer
        )
    endif()
endfunction()
