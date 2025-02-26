message("(test_ultrasonic_api) Current path => ${CMAKE_CURRENT_SOURCE_DIR}")
message("(test_ultrasonic_api) Lib path => ${ULTRASONIC_API_DIRECTORY}")

add_executable(
    test_ultrasonic_api
    test_ultrasonic_api.c
    ${ULTRASONIC_API_DIRECTORY}/ultrasonic_api.c
)

include_directories(test_ultrasonic_api PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ULTRASONIC_API_DIRECTORY}
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(
    test_ultrasonic_api
    pico_stdlib
    hardware_gpio
)

# enable usb output, disable uart output
pico_enable_stdio_usb(test_ultrasonic_api 1)
pico_enable_stdio_uart(test_ultrasonic_api 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(test_ultrasonic_api)
