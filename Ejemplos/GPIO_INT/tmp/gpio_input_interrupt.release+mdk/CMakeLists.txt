cmake_minimum_required(VERSION 3.27)

# Roots
include("../roots.cmake")

set(CONTEXT gpio_input_interrupt.release+mdk)
set(TARGET ${CONTEXT})
set(DNAME MCXA156VLL)
set(DPACK NXP::MCXA156_DFP@25.12.00)
set(DPACK_DIR "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00")
set(OUT_DIR "${SOLUTION_ROOT}/Objects/release")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LD_SCRIPT "${SOLUTION_ROOT}/mdk/MCXA156_flash.scf")
set(LD_SCRIPT_PP ${LD_SCRIPT})

# Processor Options
set(CPU Cortex-M33)
set(FPU SP_FPU)
set(DSP DSP)
set(BYTE_ORDER Little-endian)

# Toolchain config map
set(COMPILER AC6)
include("toolchain.cmake")

# Setup project
project(${CONTEXT} LANGUAGES C ASM)

# Enable color diagnostics
set(CMAKE_COLOR_DIAGNOSTICS ON)

# Compilation database
add_custom_target(database
  COMMAND ${CMAKE_COMMAND} -E make_directory "${OUT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" "${OUT_DIR}"
)
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})

# Setup context
add_executable(${CONTEXT})
set_target_properties(${CONTEXT} PROPERTIES PREFIX "" SUFFIX ".axf" OUTPUT_NAME "gpio_input_interrupt")
set_target_properties(${CONTEXT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})
add_library(${CONTEXT}_GLOBAL INTERFACE)

# Includes
target_include_directories(${CONTEXT} PUBLIC
  "${SOLUTION_ROOT}/mdk/RTE/_release_mdk"
  "${CMSIS_PACK_ROOT}/ARM/CMSIS/6.3.0/CMSIS/Core/Include"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/components/lists"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/components/uart"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/drivers"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/periph1"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/debug_console_lite"
  "${CMSIS_PACK_ROOT}/NXP/MCXA156_DFP/25.12.00/devices/MCXA156/utilities/str"
  "${SOLUTION_ROOT}/."
)

# Defines
target_compile_definitions(${CONTEXT} PUBLIC
  $<$<COMPILE_LANGUAGE:C,CXX>:
    CPU_MCXA156VLL
    CPU_MCXA156VLL
    _RTE_
  >
)

# Compile options
target_compile_options(${CONTEXT} PUBLIC
  $<$<COMPILE_LANGUAGE:ASM>:
    "SHELL:${ASM_CPU}"
    "SHELL:${ASM_FLAGS}"
    "SHELL:${ASM_BYTE_ORDER}"
  >
  $<$<COMPILE_LANGUAGE:C>:
    "SHELL:${CC_CPU}"
    "SHELL:${CC_FLAGS}"
    "SHELL:${CC_BYTE_ORDER}"
    "SHELL:-mfpu=fpv5-sp-d16"
    "SHELL:-mcpu=cortex-m33"
    "SHELL:-std=gnu11"
    "SHELL:-fshort-enums"
    "SHELL:-fshort-wchar"
    "SHELL:-ffunction-sections"
    "SHELL:-fno-common"
    "SHELL:-fdata-sections"
    "SHELL:-fno-builtin"
    "SHELL:-mthumb"
    "SHELL:-fno-rtti"
  >
)

# Compile Options Abstractions
add_library(${CONTEXT}_ABSTRACTIONS INTERFACE)
cbuild_set_options_flags(CC "speed" "off" "" "gnu11" CC_OPTIONS_FLAGS_${CONTEXT})
cbuild_set_options_flags(ASM "speed" "off" "" "" ASM_OPTIONS_FLAGS_${CONTEXT})
target_compile_options(${CONTEXT}_ABSTRACTIONS INTERFACE
  $<$<COMPILE_LANGUAGE:C>:
    "SHELL:${CC_OPTIONS_FLAGS_${CONTEXT}}"
  >
  $<$<COMPILE_LANGUAGE:ASM>:
    "SHELL:${ASM_OPTIONS_FLAGS_${CONTEXT}}"
  >
)

# Add groups and components
include("groups.cmake")
include("components.cmake")

target_link_libraries(${CONTEXT} PUBLIC
  Group_source
  Group_board
  ARM_CMSIS_CORE_6_2_0
  NXP_Device_CMSIS_MCXA156_header_1_0_0
  NXP_Device_CMSIS_MCXA156_system_1_0_0
  NXP_Device_SDK_Drivers_clock_2_0_0
  NXP_Device_SDK_Drivers_common_2_6_2
  NXP_Device_SDK_Drivers_gpio_2_8_3
  NXP_Device_SDK_Drivers_inputmux_2_0_10
  NXP_Device_SDK_Drivers_inputmux_connections_2_0_0
  NXP_Device_SDK_Drivers_lists_1_0_0
  NXP_Device_SDK_Drivers_lpuart_2_10_0
  NXP_Device_SDK_Drivers_lpuart_adapter_1_0_0
  NXP_Device_SDK_Drivers_mcx_spc_2_10_0
  NXP_Device_SDK_Drivers_port_2_5_1
  NXP_Device_SDK_Drivers_reset_2_4_0
  NXP_Device_SDK_Utilities_assert_lite_1_0_0
  NXP_Device_SDK_Utilities_debug_console_lite_1_0_0
  NXP_Device_SDK_Utilities_misc_utilities_1_1_1
  NXP_Device_SDK_Utilities_str_1_0_0
  NXP_Device_Startup_1_0_0
)

# Linker options
target_link_options(${CONTEXT} PUBLIC
  "SHELL:${LD_CPU}"
  "SHELL:${_LS}\"${LD_SCRIPT_PP}\""
  "SHELL:--cpu=Cortex-M33"
  "SHELL:--library_type=microlib"
  "SHELL:--strict"
  "SHELL:--remove"
  "SHELL:--diag_suppress 6314"
  "SHELL:--summary_stderr"
  "SHELL:--map"
  "SHELL:--load_addr_map_info"
  "SHELL:--xref"
  "SHELL:--callgraph"
  "SHELL:--symbols"
  "SHELL:--info summarysizes"
  "SHELL:--info sizes"
  "SHELL:--info totals"
  "SHELL:--info unused"
  "SHELL:--info veneers"
  "SHELL:--entry=Reset_Handler"
)
set(LD_DEPS ${LD_SCRIPT})
set_target_properties(${CONTEXT} PROPERTIES LINK_DEPENDS "${LD_DEPS}")
