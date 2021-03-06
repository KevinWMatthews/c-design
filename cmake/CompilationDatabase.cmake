#[[
Generate compilation database (compile_commands.json).
This is used by tools such as clangd for indexing the source code.
#]]

option(BUILD_COMPILATION_DATABASE "Generate compilation database/Clang abstract syntax tree (compile_commands.json)" ON)
if(BUILD_COMPILATION_DATABASE)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    add_custom_target(compilation_database
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/compile_commands.json ${PROJECT_SOURCE_DIR}/compile_commands.json
        COMMENT "Symlinking compilation database into the project root"
        )
else()
    set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
endif()
