#[[
Run static analysis using Cppcheck.
Uses Clang's abstract syntax tree, compile_commands.json instead of scanning the source.
#]]

find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    add_custom_target(static_analysis_cppcheck
        COMMAND ${CPPCHECK} --project=compile_commands.json --quiet
        DEPENDS compilation_database
        COMMENT "Running static analysis with cppcheck"
        )
else()
    message(STATUS "Static analysis with CppCheck is not available")
endif()

