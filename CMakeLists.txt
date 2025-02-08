# Source => https://github.com/raspberrypi/pico-examples

cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

# Set project name and code specifications
# These three arguments C CXX and ASM are required !!
project(pico_projects C CXX ASM)

# Set gcc versions, these projects are in pure C
# Warning these two lines requires to be defined !!
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.1.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 2.1.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_PROJECTS_PATH ${PROJECT_SOURCE_DIR})

# If you want debug output from USB (pass -DPICO_STDIO_USB=1) this ensures you don't lose any debug output while USB is set up
if (NOT DEFINED PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS)
    set(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS 3000)
endif()

# Initialize the SDK
pico_sdk_init()

function(add_subdirectory_exclude_platforms NAME)
    if (ARGN)
        if (PICO_PLATFORM IN_LIST ARGN)
            message("Skipping ${NAME} example which is unsupported on this platform")
            return()
        endif()
        foreach(PATTERN IN LISTS ARGN)
            string(REGEX MATCH "${PATTERN}" MATCHED "${PICO_PLATFORM}")
            if (MATCHED)
                message("Skipping ${NAME} example which is unsupported on this platform")
                return()
            endif()
        endforeach()
    endif()
    add_subdirectory(${NAME})
endfunction()

add_compile_options(
    -Wall
    -Werror
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

add_subdirectory_exclude_platforms(blink_led)
add_subdirectory_exclude_platforms(hello_world)
add_subdirectory_exclude_platforms(test_servo)
add_subdirectory_exclude_platforms(temperature_and_light_sensors)
add_subdirectory_exclude_platforms(external_servo_lib)

set(ULTRASONIC_API_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ultrasonic_api)
add_subdirectory_exclude_platforms(ultrasonic_api)

set(SERVO_API_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/servo_api)
add_subdirectory_exclude_platforms(servo_api)

add_subdirectory_exclude_platforms(test_include_servo_api)

add_subdirectory_exclude_platforms(dummy)
