cmake_minimum_required(VERSION 3.28)

include(pico_sdk_import.cmake)

project(picow_wifi_scan)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(picow_wifi_scan
        picow_wifi_scan.c
        )
target_include_directories(picow_wifi_scan PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )
target_link_libraries(picow_wifi_scan
        pico_cyw43_arch_lwip_threadsafe_background
        pico_stdlib
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(picow_wifi_scan 1)
pico_enable_stdio_uart(picow_wifi_scan 1)

# create map/bin/hex/uf2 file in addition to ELF
pico_add_extra_outputs(picow_wifi_scan)

# add_executable(picow_wifi_scan_poll
#         picow_wifi_scan.c
#         )
# target_include_directories(picow_wifi_scan_poll PRIVATE
#         ${CMAKE_CURRENT_LIST_DIR}
#         ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
#         )
# target_link_libraries(picow_wifi_scan_poll
#         pico_cyw43_arch_lwip_poll
#         pico_stdlib
#         )
# pico_add_extra_outputs(picow_wifi_scan_poll)

