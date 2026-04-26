# groups.cmake

# group source
add_library(Group_source OBJECT
  "${SOLUTION_ROOT}/gpio_input_interrupt.c"
)
target_include_directories(Group_source PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_source PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_source_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_source_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_source PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_source PUBLIC
  Group_source_ABSTRACTIONS
)

# group board
add_library(Group_board OBJECT
  "${SOLUTION_ROOT}/pin_mux.c"
  "${SOLUTION_ROOT}/board.c"
  "${SOLUTION_ROOT}/clock_config.c"
)
target_include_directories(Group_board PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${SOLUTION_ROOT}/."
)
target_compile_definitions(Group_board PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_board_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_board_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_board PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_board PUBLIC
  Group_board_ABSTRACTIONS
)
