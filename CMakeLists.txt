##########################################################################
# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann
##########################################################################

cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0054 OLD)
SET(BUILD_TYPE "PC" CACHE STRING "TARGET")

if(BUILD_TYPE STREQUAL "TARGET")
message(${BUILD_TYPE})

  ### TOOLCHAIN SETUP AREA #################################################
  # Set any variables used in the toolchain prior project() call. In that
  # case they are already set and used.
  
  ##########################################################################

  ##########################################################################
  # tools to beused for programming the AVR
  ##########################################################################
  set(AVR_UPLOADTOOL avrdude)
  set(AVR_PROGRAMMER avrispmkII)
  set(AVR_UPLOADTOOL_PORT usb)

  ##########################################################################
  # AVR and fuses needs to be set
  ##########################################################################
  set(AVR_MCU atmega328p)
  set(AVR_H_FUSE 0xd9)
  set(AVR_L_FUSE 0x62)

  ### END TOOLCHAIN SETUP AREA #############################################

  include(generic-gcc-avr.cmake)

  ##########################################################################
  # name your project
  ##########################################################################
  project(AVR-CPP-EXAMPLE)

  ##########################################################################
  # status messages
  ##########################################################################
  message(STATUS "Current uploadtool is: ${AVR_UPLOADTOOL}")
  message(STATUS "Current programmer is: ${AVR_PROGRAMMER}")
  message(STATUS "Current upload port is: ${AVR_UPLOADTOOL_PORT}")
  message(STATUS "Current uploadtool options are: ${AVR_UPLOADTOOL_OPTIONS}")
  message(STATUS "Current MCU is set to: ${AVR_MCU}")
  message(STATUS "Current H_FUSE is set to: ${AVR_H_FUSE}")
  message(STATUS "Current L_FUSE is set to: ${AVR_L_FUSE}")

  ##########################################################################
  # set build type
  ##########################################################################
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
  endif(NOT CMAKE_BUILD_TYPE)

  ##########################################################################
  # needs to be defined for AVR toolchain
  ##########################################################################
  set(MCU_SPEED "16000000UL")

  ##########################################################################
  # some cmake cross-compile necessities
  ##########################################################################

  if(DEFINED ENV{AVR_FIND_ROOT_PATH})
      set(CMAKE_FIND_ROOT_PATH $ENV{AVR_FIND_ROOT_PATH})
  else(DEFINED ENV{AVR_FIND_ROOT_PATH})
      if(EXISTS "/opt/local/avr")
        set(CMAKE_FIND_ROOT_PATH "/opt/local/avr")
      elseif(EXISTS "/usr/avr")
        set(CMAKE_FIND_ROOT_PATH "/usr/avr")
      elseif(EXISTS "/usr/lib/avr")
        set(CMAKE_FIND_ROOT_PATH "/usr/lib/avr")
      elseif(EXISTS "/usr/local/CrossPack-AVR")
        set(CMAKE_FIND_ROOT_PATH "/usr/local/CrossPack-AVR")
      else(EXISTS "/opt/local/avr")
        message(FATAL_ERROR "Please set AVR_FIND_ROOT_PATH in your environment.")
      endif(EXISTS "/opt/local/avr")
  endif(DEFINED ENV{AVR_FIND_ROOT_PATH})
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
  # not added automatically, since CMAKE_SYSTEM_NAME is "generic"
  set(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
  set(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")

  ##########################################################################
  # status messages for generating
  ##########################################################################
  message(STATUS "Set CMAKE_FIND_ROOT_PATH to ${CMAKE_FIND_ROOT_PATH}")
  message(STATUS "Set CMAKE_SYSTEM_INCLUDE_PATH to ${CMAKE_SYSTEM_INCLUDE_PATH}")
  message(STATUS "Set CMAKE_SYSTEM_LIBRARY_PATH to ${CMAKE_SYSTEM_LIBRARY_PATH}")

  ##########################################################################
  # compiler options for all build types
  ##########################################################################
  
  add_definitions("-fpack-struct")
  add_definitions("-fshort-enums")
  add_definitions("-mmcu=${AVR_MCU}")
  add_definitions("-Wall")
  add_definitions("-pedantic")
  add_definitions("-pedantic-errors")
  add_definitions("-funsigned-char")
  add_definitions("-funsigned-bitfields")
  add_definitions("-ffunction-sections")
  add_definitions("-Os")
  set(CMAKE_C_COMPILER "avr-gcc")
  set(CMAKE_CXX_COMPILER "avr-g++")
  add_definitions("-std=c++11")

  add_definitions(-DTARGET=1)

  ##########################################################################
  # include search paths
  ##########################################################################
  include_directories(freertos_distro/FreeRTOS_avr)
    include_directories(freertos_distro/FreeRTOS_avr/include)
    include_directories(freertos_distro/FreeRTOS_avr/source/portable)
    include_directories(freertos_distro/FreeRTOS_avr/source)

    add_subdirectory(freertos_distro/FreeRTOS_tasks)

    add_subdirectory(component_framework)
    add_subdirectory(freertos_distro/FreeRTOS_avr)
    add_subdirectory(${PRJ_NAME}/application_code)
    add_subdirectory(${PRJ_NAME}/target)



  elseif(BUILD_TYPE STREQUAL "PC")
    project(pc-example)
    add_definitions(-DBUILD=1 )
    add_definitions("-Os")
    add_definitions("-std=c++17")
    add_definitions("-fpermissive")
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    add_definitions(-DPC=1)
    add_definitions("-std=c++17")
    
    include_directories(freertos_distro/FreeRTOS_Linux)
    include_directories(freertos_distro/FreeRTOS_Linux/include)
    include_directories(freertos_distro/FreeRTOS_Linux/source/portable)
    include_directories(freertos_distro/FreeRTOS_Linux/source)

    add_subdirectory(component_framework)
    add_subdirectory(freertos_distro/FreeRTOS_Linux)
    add_subdirectory(freertos_distro/FreeRTOS_tasks)
    add_subdirectory(${PRJ_NAME}/simulation/quadcopter_model)
    add_subdirectory(${PRJ_NAME}/application_code)
    add_subdirectory(${PRJ_NAME}/simulation)


  elseif(BUILD_TYPE STREQUAL "UNITTEST")
    project(unittest)
    add_definitions(-DPC=1)
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    add_definitions("-std=c++17")
    add_definitions("-fpermissive")
    include_directories(freertos_distro/FreeRTOS_Linux)
    include_directories(freertos_distro/FreeRTOS_Linux/include)
    include_directories(freertos_distro/FreeRTOS_Linux/source/portable)
    include_directories(freertos_distro/FreeRTOS_Linux/source)

    add_subdirectory(component_framework)
    add_subdirectory(freertos_distro/FreeRTOS_Linux)
    add_subdirectory(freertos_distro/FreeRTOS_tasks)
    add_subdirectory(${PRJ_NAME}/simulation/quadcopter_model)
    add_subdirectory(${PRJ_NAME}/application_code)
    add_subdirectory(${PRJ_NAME}/simulation)


endif()

##########################################################################
# building library and application in their subdirectories
##########################################################################



