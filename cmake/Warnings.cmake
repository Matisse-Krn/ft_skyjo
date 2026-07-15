include_guard(GLOBAL)

function(ft_skyjo_set_project_warnings target warnings_as_errors)
    if(MSVC)
        set(project_warnings
            /W4
            /permissive-
            /w14242
            /w14254
            /w14263
            /w14265
            /w14287
            /we4289
            /w14296
            /w14311
            /w14545
            /w14546
            /w14547
            /w14549
            /w14555
            /w14619
            /w14640
            /w14826
            /w14905
            /w14906
            /w14928
        )

        if(warnings_as_errors)
            list(APPEND project_warnings /WX)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        set(project_warnings
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wshadow
            -Wcast-align
            -Wcast-qual
            -Wold-style-cast
            -Woverloaded-virtual
            -Wnon-virtual-dtor
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
        )

        if(warnings_as_errors)
            list(APPEND project_warnings -Werror)
        endif()
    endif()

    target_compile_options(${target} INTERFACE ${project_warnings})
endfunction()
