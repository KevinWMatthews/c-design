add_executable(signal_flag_bad signal_flag_bad.c)
target_link_libraries(signal_flag_bad PRIVATE Threads::Threads)
create_custom_gcc_targets(TARGET_NAME signal_flag_bad)

add_executable(signal_flag_good signal_flag_good.c)
target_link_libraries(signal_flag_good PRIVATE Threads::Threads)
create_custom_gcc_targets(TARGET_NAME signal_flag_good)

add_executable(signal_wait_single signal_wait_single.c)
target_link_libraries(signal_wait_single PRIVATE Threads::Threads)

add_executable(my_signal_wait my_signal_wait.c)
target_link_libraries(my_signal_wait PRIVATE my_signal::my_signal)

add_executable(my_signal_wait2 my_signal_wait2.c)
target_link_libraries(my_signal_wait2 PRIVATE my_signal::my_signal)
