add_executable(sys_hsearch sys_hsearch.c)
add_executable(sys_hsearch_binary sys_hsearch_binary.c)

add_executable(sys_hsearch_r sys_hsearch_r.c)
target_compile_definitions(sys_hsearch_r PRIVATE _GNU_SOURCE)
