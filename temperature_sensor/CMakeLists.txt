cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(temperature_sensor)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(temperature_sensor
    temperature_sensor.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(temperature_sensor pico_stdlib hardware_adc)

# enable usb output, disable uart output
pico_enable_stdio_usb(temperature_sensor 1)
pico_enable_stdio_uart(temperature_sensor 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(temperature_sensor)
