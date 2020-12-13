#[[
CMake options for the GCC compiler.
#]]

#[[
Warnings
#]]
option(GCC_WARN_ALL "Issue warnings about \"all\" questionable and easy-to-fix problems" ON)
if(GCC_WARN_ALL)
    add_compile_options("-Wall")
endif()

option(GCC_WARN_EXTRA "Issue \"extra\" warnings that are not enabled by \"all\"" OFF)
if(GCC_WARN_EXTRA)
    add_compile_options("-Wextra")
endif()

option(GCC_WARN_PEDANTIC "Issue pedantic warnings for strict ISO C/C++ compliance" OFF)
if(GCC_WARN_PEDANTIC)
    add_compile_options("-Wpedantic")
endif()


#[[
Sanitizers
#]]
# asan and tsan are mutually exclusive
# leak sanitizer is included in the address sanitizer
# memory sanitizer requires LLVM, x86, and compiling the **entire** stack with sanitizer flags
set(GCC_SANITIZER_VALUES
    None Address Thread
    CACHE
    INTERNAL
    "List of possible values for the GCC_SANITIZER variable"
    )
string(REPLACE
    ";"
    " "
    GCC_SANITIZER_VALUES_PRETTY
    "${GCC_SANITIZER_VALUES}"
    )
set(GCC_SANITIZER
    "None"
    CACHE
    STRING
    "Compile and link with a sanitizer. Automatically sets CMAKE_BUILD_TYPE to Debug. Options are: ${GCC_SANITIZER_VALUES_PRETTY}"
    )
set_property(CACHE GCC_SANITIZER PROPERTY STRINGS ${GCC_SANITIZER_VALUES})

if(NOT GCC_SANITIZER IN_LIST GCC_SANITIZER_VALUES)
    message(FATAL_ERROR "GCC_SANITIZER value not allowed: ${GCC_SANITIZER}")
endif()

if(GCC_SANITIZER STREQUAL "Address")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Debug")
    # The Clang docs recommend using -O1 or higher for performance
    add_compile_options("-fsanitize=address" "-fno-omit-frame-pointer" "-O2")
    link_libraries("-fsanitize=address")
elseif(GCC_SANITIZER STREQUAL "Leak")
    message(FATAL_ERROR "Leak sanitizer is incorporated in the Address sanitizer")
elseif(GCC_SANITIZER STREQUAL "Memory")
    # Major project - must compile *all* libraries with the memory sanitizer
    message(FATAL_ERROR "Memory sanitizer is not supported")
elseif(GCC_SANITIZER STREQUAL "Thread")
    # The Clang docs recommend using -O2 or higher for performance
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Debug")
    add_compile_options("-fsanitize=thread" "-O2")
    link_libraries("-fsanitize=thread")
endif()

# ubsan can be enabled independent of the other sanitizers
# The Clang docs state that the performance penalty is slight.
option(GCC_SANITIZER_UNDEFINED "Compile and link with the undefined behavior sanitizer. Automatically sets CMAKE_BUILD_TYPE to Debug.")
if(GCC_SANITIZER_UNDEFINED)
    add_compile_options("-fsanitize=undefined" "-fno-omit-frame-pointer")
    link_libraries("-fsanitize=undefined")
endif()


#[[
Optimization
WARNING: Apply optimization flags *last* to override any optimization settings that are automatically applied.
TODO verify:
If multiple optimization levels are applied, the last optimization level is used.
#]]
if(OPTIMIZE)
    set(GCC_OPTIMIZATION_VALUES
        O0 O1 02 03 Og Os Ofast
        CACHE
        INTERNAL
        "List of possible values for the GCC_OPTIMIZATION variable"
        )
    string(REPLACE
        ";"
        " "
        GCC_OPTIMIZATION_VALUES_PRETTY
        "${GCC_OPTIMIZATION_VALUES}"
        )
    set(GCC_OPTIMIZATION
        "O0"
        CACHE
        STRING
        "Set the gcc optimization level. Options are: ${GCC_OPTIMIZATION_VALUES_PRETTY}"
        )
    set_property(CACHE GCC_OPTIMIZATION PROPERTY STRINGS ${GCC_OPTIMIZATION_VALUES})
    if(GCC_OPTIMIZATION)
        add_compile_options("-${GCC_OPTIMIZATION}")
    endif()
    mark_as_advanced(CLEAR GCC_OPTIMIZATION)
else()
    mark_as_advanced(FORCE GCC_OPTIMIZATION)
endif()
