# Source => https://www.i-programmer.info/programming/148-hardware/14849-the-pico-in-c-basic-pwm.html?start=1

message("(test_include_servo_api) Include servo_api from ${SERVO_API_DIRECTORY}")

add_executable(
    test_include_servo_api
    test_include_servo_api.c
    ${SERVO_API_DIRECTORY}/servo_api.c
)

target_include_directories(test_include_servo_api PRIVATE
    ${SERVO_API_DIRECTORY}
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(test_include_servo_api pico_stdlib hardware_pwm)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(test_include_servo_api)
