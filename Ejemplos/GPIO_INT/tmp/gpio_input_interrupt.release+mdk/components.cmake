# components.cmake

# component ARM::CMSIS:CORE@6.2.0
add_library(ARM_CMSIS_CORE_6_2_0 INTERFACE)
target_include_directories(ARM_CMSIS_CORE_6_2_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/6.3.0/CMSIS/Core/Include"
)
target_compile_definitions(ARM_CMSIS_CORE_6_2_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_link_libraries(ARM_CMSIS_CORE_6_2_0 INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:CMSIS:MCXA156_header@1.0.0
add_library(NXP_Device_CMSIS_MCXA156_header_1_0_0 INTERFACE)
target_include_directories(NXP_Device_CMSIS_MCXA156_header_1_0_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/periph1"
)
target_compile_definitions(NXP_Device_CMSIS_MCXA156_header_1_0_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_link_libraries(NXP_Device_CMSIS_MCXA156_header_1_0_0 INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:CMSIS:MCXA156_system@1.0.0
add_library(NXP_Device_CMSIS_MCXA156_system_1_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/system_MCXA156.c"
)
target_include_directories(NXP_Device_CMSIS_MCXA156_system_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156"
)
target_compile_definitions(NXP_Device_CMSIS_MCXA156_system_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_CMSIS_MCXA156_system_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_CMSIS_MCXA156_system_1_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:clock@2.0.0
add_library(NXP_Device_SDK_Drivers_clock_2_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers/fsl_clock.c"
)
target_include_directories(NXP_Device_SDK_Drivers_clock_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_clock_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_clock_2_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_clock_2_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:common@2.6.2
add_library(NXP_Device_SDK_Drivers_common_2_6_2 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers/fsl_common.c"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers/fsl_common_arm.c"
)
target_include_directories(NXP_Device_SDK_Drivers_common_2_6_2 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_common_2_6_2 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_common_2_6_2 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_common_2_6_2 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:gpio@2.8.3
add_library(NXP_Device_SDK_Drivers_gpio_2_8_3 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers/fsl_gpio.c"
)
target_include_directories(NXP_Device_SDK_Drivers_gpio_2_8_3 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_gpio_2_8_3 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_gpio_2_8_3 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_gpio_2_8_3 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:inputmux@2.0.10
add_library(NXP_Device_SDK_Drivers_inputmux_2_0_10 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers/fsl_inputmux.c"
)
target_include_directories(NXP_Device_SDK_Drivers_inputmux_2_0_10 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_inputmux_2_0_10 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_inputmux_2_0_10 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_inputmux_2_0_10 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:inputmux_connections@2.0.0
add_library(NXP_Device_SDK_Drivers_inputmux_connections_2_0_0 INTERFACE)
target_include_directories(NXP_Device_SDK_Drivers_inputmux_connections_2_0_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_inputmux_connections_2_0_0 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_inputmux_connections_2_0_0 INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:lists@1.0.0
add_library(NXP_Device_SDK_Drivers_lists_1_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/components/lists/fsl_component_generic_list.c"
)
target_include_directories(NXP_Device_SDK_Drivers_lists_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/components/lists"
)
target_compile_definitions(NXP_Device_SDK_Drivers_lists_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_lists_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_lists_1_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:lpuart@2.10.0
add_library(NXP_Device_SDK_Drivers_lpuart_2_10_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers/fsl_lpuart.c"
)
target_include_directories(NXP_Device_SDK_Drivers_lpuart_2_10_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_lpuart_2_10_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_lpuart_2_10_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_lpuart_2_10_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:lpuart_adapter@1.0.0
add_library(NXP_Device_SDK_Drivers_lpuart_adapter_1_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/components/uart/fsl_adapter_lpuart.c"
)
target_include_directories(NXP_Device_SDK_Drivers_lpuart_adapter_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/components/uart"
)
target_compile_definitions(NXP_Device_SDK_Drivers_lpuart_adapter_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_lpuart_adapter_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_lpuart_adapter_1_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:mcx_spc@2.10.0
add_library(NXP_Device_SDK_Drivers_mcx_spc_2_10_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers/fsl_spc.c"
)
target_include_directories(NXP_Device_SDK_Drivers_mcx_spc_2_10_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_mcx_spc_2_10_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_mcx_spc_2_10_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_mcx_spc_2_10_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:port@2.5.1
add_library(NXP_Device_SDK_Drivers_port_2_5_1 INTERFACE)
target_include_directories(NXP_Device_SDK_Drivers_port_2_5_1 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_port_2_5_1 INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_port_2_5_1 INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Drivers:reset@2.4.0
add_library(NXP_Device_SDK_Drivers_reset_2_4_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers/fsl_reset.c"
)
target_include_directories(NXP_Device_SDK_Drivers_reset_2_4_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
)
target_compile_definitions(NXP_Device_SDK_Drivers_reset_2_4_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Drivers_reset_2_4_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Drivers_reset_2_4_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Utilities:assert_lite@1.0.0
add_library(NXP_Device_SDK_Utilities_assert_lite_1_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/debug_console_lite/fsl_assert.c"
)
target_include_directories(NXP_Device_SDK_Utilities_assert_lite_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/debug_console_lite"
)
target_compile_definitions(NXP_Device_SDK_Utilities_assert_lite_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Utilities_assert_lite_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Utilities_assert_lite_1_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Utilities:debug_console_lite@1.0.0
add_library(NXP_Device_SDK_Utilities_debug_console_lite_1_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/debug_console_lite/fsl_debug_console.c"
)
target_include_directories(NXP_Device_SDK_Utilities_debug_console_lite_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/debug_console_lite"
)
target_compile_definitions(NXP_Device_SDK_Utilities_debug_console_lite_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Utilities_debug_console_lite_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Utilities_debug_console_lite_1_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:SDK Utilities:misc_utilities@1.1.1
add_library(NXP_Device_SDK_Utilities_misc_utilities_1_1_1 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/fsl_memcpy.S"
)
target_include_directories(NXP_Device_SDK_Utilities_misc_utilities_1_1_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(NXP_Device_SDK_Utilities_misc_utilities_1_1_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Utilities_misc_utilities_1_1_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Utilities_misc_utilities_1_1_1 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
set_source_files_properties("${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/fsl_memcpy.S" PROPERTIES
  COMPILE_DEFINITIONS "__MICROLIB=1;__CC_ARM=1;_RTE_=1;CPU_MCXA156VLL=1;CPU_MCXA156VLL;_RTE_"
)

# component NXP::Device:SDK Utilities:str@1.0.0
add_library(NXP_Device_SDK_Utilities_str_1_0_0 OBJECT
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/str/fsl_str.c"
)
target_include_directories(NXP_Device_SDK_Utilities_str_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/str"
)
target_compile_definitions(NXP_Device_SDK_Utilities_str_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_SDK_Utilities_str_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_SDK_Utilities_str_1_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# component NXP::Device:Startup@1.0.0
add_library(NXP_Device_Startup_1_0_0 OBJECT
  "${SOLUTION_ROOT}/mdk/RTE/Device/MCXA156VLL/startup_MCXA156.S"
)
target_include_directories(NXP_Device_Startup_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(NXP_Device_Startup_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(NXP_Device_Startup_1_0_0 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(NXP_Device_Startup_1_0_0 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
set_source_files_properties("${SOLUTION_ROOT}/mdk/RTE/Device/MCXA156VLL/startup_MCXA156.S" PROPERTIES
  COMPILE_DEFINITIONS "__MICROLIB=1;__CC_ARM=1;_RTE_=1;CPU_MCXA156VLL=1;CPU_MCXA156VLL;_RTE_"
)
