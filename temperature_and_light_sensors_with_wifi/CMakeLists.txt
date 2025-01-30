cmake_minimum_required(VERSION 3.13)

# Initialize the SDK based on PICO_SDK_PATH
# Note: this must happen before project()
include(pico_sdk_import.cmake)

project(temperature_and_light_sensors)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(temperature_and_light_sensors
    temperature_and_light_sensors.c
)

# Link to current directory and previous parent one (from build/ it's direct directory) to find .h files
target_include_directories(temperature_and_light_sensors PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
        )

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(temperature_and_light_sensors
	pico_cyw43_arch_lwip_threadsafe_background
	pico_stdlib
	hardware_adc
	pico_lwip
	)

# Enable usb output, disable uart output
pico_enable_stdio_usb(temperature_and_light_sensors 1)
pico_enable_stdio_uart(temperature_and_light_sensors 1)

# Create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(temperature_and_light_sensors)
