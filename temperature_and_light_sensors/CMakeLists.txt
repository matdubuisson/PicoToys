add_executable(temperature_and_light_sensors
    temperature_and_light_sensors.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(temperature_and_light_sensors pico_stdlib hardware_adc)

# enable usb output, disable uart output
pico_enable_stdio_usb(temperature_and_light_sensors 1)
pico_enable_stdio_uart(temperature_and_light_sensors 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(temperature_and_light_sensors)
