# Source => https://www.i-programmer.info/programming/148-hardware/14849-the-pico-in-c-basic-pwm.html?start=1

message("(test_servo_api) Current path => ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(
    test_servo_api
    test_servo_api.c
    ${SERVO_API_DIRECTORY}/servo_api.c
)

include_directories(test_servo_api PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SERVO_API_DIRECTORY}
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(test_servo_api pico_stdlib hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(test_ultrasonic_api 1)
pico_enable_stdio_uart(test_ultrasonic_api 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(test_servo_api)
