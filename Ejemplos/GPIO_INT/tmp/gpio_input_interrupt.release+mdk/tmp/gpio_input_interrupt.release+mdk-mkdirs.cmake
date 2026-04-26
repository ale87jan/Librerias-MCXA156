# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk")
  file(MAKE_DIRECTORY "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk")
endif()
file(MAKE_DIRECTORY
  "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/1"
  "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk"
  "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk/tmp"
  "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk/src/gpio_input_interrupt.release+mdk-stamp"
  "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk/src"
  "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk/src/gpio_input_interrupt.release+mdk-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk/src/gpio_input_interrupt.release+mdk-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Github/Librerias-MCXA156/Ejemplos/GPIO_INT/tmp/gpio_input_interrupt.release+mdk/src/gpio_input_interrupt.release+mdk-stamp${cfgdir}") # cfgdir has leading slash
endif()
