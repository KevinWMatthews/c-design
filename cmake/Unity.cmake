include(FetchContent)
FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.5.1
)
FetchContent_MakeAvailable(unity)

find_program(RUBY
    NAMES ruby
    REQUIRED    # NOTE: this doesn't work until CMake 3.18
    DOC "Path to ruby executable"
    )

if(${RUBY} STREQUAL "RUBY-NOTFOUND")
    message(WARNING "Program 'ruby' not found. Can not auto-generate Unity test runners")
endif()

function(add_unity_test test_filename)
    get_filename_component(target ${test_filename} NAME_WE)
    add_executable(${target}
        ${test_filename}
        ${target}_runner.c
        )
    target_link_libraries(${target}
        PRIVATE
        unity::framework
        )

    if(RUBY)
        add_custom_target(${target}_generate_test_runner
            COMMAND ${RUBY} "${unity_SOURCE_DIR}/auto/generate_test_runner.rb" "${CMAKE_CURRENT_SOURCE_DIR}/${test_filename}" "${CMAKE_CURRENT_SOURCE_DIR}/${target}_runner.c"
            COMMENT "Generating test runner for: '${test_filename}'"
            )
        add_dependencies(${target} ${target}_generate_test_runner)
    endif()
endfunction()
