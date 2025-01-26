cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(la_wifit C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(la_wifit
    la_wifit.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(la_wifit pico_stdlib)
target_link_libraries(la_wifit pico_cyw43_arch_none)
target_link_libraries(la_wifit pico_cyw43_arch_lwip_threadsafe_background)

target_include_directories(la_wifit PRIVATE ${CMAKE_CURRENT_LIST_DIR} )

# enable usb output, disable uart output
pico_enable_stdio_usb(la_wifit 1)
pico_enable_stdio_uart(la_wifit 1)

# create map/bin/hex/uf2 file in addition to ELF
pico_add_extra_outputs(la_wifit)