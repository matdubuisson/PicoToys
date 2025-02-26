message("(test_ln298_driver_motor_api) Current path => ${CMAKE_CURRENT_SOURCE_DIR}")
message("(test_ultrasonic_api) Lib path => ${ULTRASONIC_API_DIRECTORY}")

add_executable(
    test_ln298_motor_driver_api
    test_ln298_motor_driver_api.c
    ${LN298_MOTOR_DRIVER_API_DIRECTORY}/ln298_motor_driver_api.c
)

include_directories(test_ultrasonic_api PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LN298_MOTOR_DRIVER_API_DIRECTORY}
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(test_ln298_motor_driver_api pico_stdlib hardware_gpio hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(test_ln298_motor_driver_api 1)
pico_enable_stdio_uart(test_ln298_motor_driver_api 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(test_ln298_motor_driver_api)
