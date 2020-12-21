#[[
Attach custom GCC targets to an existing executable:
  * disassemble
#]]
function(CREATE_CUSTOM_GCC_TARGETS)
    set(options "")
    set(one_value_args TARGET_NAME)
    set(multi_value_args "")
    cmake_parse_arguments(CREATE_CUSTOM_GCC_TARGETS "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    set(target ${CREATE_CUSTOM_GCC_TARGETS_TARGET_NAME})
    if(NOT target)
        message(FATAL_ERROR "Must specify TARGET_NAME")
    endif()

    get_target_property(target_path ${target} RUNTIME_OUTPUT_DIRECTORY)
    if(NOT target_path)
        get_target_property(target_path ${target} BINARY_DIR)
    endif()

    #[[
    Configure disassemble target
    #]]
    add_custom_target(${target}-disassemble
        DEPENDS
        ${target}.lst
        )

    add_custom_command(
        OUTPUT
        ${target}.lst
        COMMAND
        # objdump <option(s)> <file(s)>
        # -h, --[section-]headers  Display the contents of the section headers
        # -S, --source             Intermix source code with disassembly
        ${CMAKE_OBJDUMP} --section-headers --source ${target_path}/${target} > ${target}.lst
        DEPENDS
        ${target}
        COMMENT
        "Generating disassembly file ${target}.lst"
    )
endfunction()
