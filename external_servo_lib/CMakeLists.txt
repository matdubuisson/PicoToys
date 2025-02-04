# Source => https://www.i-programmer.info/programming/148-hardware/14849-the-pico-in-c-basic-pwm.html?start=1

add_executable(
    external_servo_lib
    external_servo_lib.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(external_servo_lib pico_stdlib hardware_adc hardware_pwm pico_cyw43_arch_none)

# enable usb output, disable uart output
pico_enable_stdio_usb(external_servo_lib 1)
pico_enable_stdio_uart(external_servo_lib 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(external_servo_lib)
