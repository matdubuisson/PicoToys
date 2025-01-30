# All other stuff defined in parent directory's CMakeLists.txt

# Define the output executables name
add_executable(
    blink_led
    blink_led.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(blink_led pico_stdlib)
target_link_libraries(blink_led pico_cyw43_arch_none)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(blink_led)

