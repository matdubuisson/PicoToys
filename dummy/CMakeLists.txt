# Source => https://www.i-programmer.info/programming/148-hardware/14849-the-pico-in-c-basic-pwm.html?start=1

message("(dummy) Include servo_api from ${SERVO_API_DIRECTORY}")

add_executable(
    dummy
    dummy.c
    ${ULTRASONIC_API_DIRECTORY}/ultrasonic_api.c
    ${SERVO_API_DIRECTORY}/servo_api.c
    ${LN298_MOTOR_DRIVER_API_DIRECTORY}/ln298_motor_driver_api.c
)

target_include_directories(dummy PRIVATE
    ${ULTRASONIC_API_DIRECTORY}
    ${SERVO_API_DIRECTORY}
    ${LN298_MOTOR_DRIVER_API_DIRECTORY}
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(dummy
    pico_stdlib
    hardware_gpio
    hardware_pwm
    pico_cyw43_arch_none
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(dummy 1)
pico_enable_stdio_uart(dummy 1)

# Create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(dummy)
