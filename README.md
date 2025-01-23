# Setup a project (hello_world example)

0) Make a new directory containing :
    - CMakeLists.txt
        ```bash
        cmake_minimum_required(VERSION 3.13)

        # initialize the SDK based on PICO_SDK_PATH
        # note: this must happen before project()
        include(pico_sdk_import.cmake)

        project(hello_world)

        # initialize the Raspberry Pi Pico SDK
        pico_sdk_init()

        add_executable(hello_world
            hello_world.c
        )

        # Add pico_stdlib library which aggregates commonly used features
        target_link_libraries(hello_world pico_stdlib)
        target_link_libraries(hello_world pico_cyw43_arch_none)

        # enable usb output, disable uart output
        pico_enable_stdio_usb(hello_world 1)
        pico_enable_stdio_uart(hello_world 0)

        # create map/bin/hex/uf2 file in addition to ELF.
        pico_add_extra_outputs(hello_world)
        ```
    - file.c
        ```bash
        #include <stdio.h>
        #include "pico/stdlib.h"
        #include "pico/cyw43_arch.h"

        int main() {
            setup_default_uart();
            stdio_init_all();
            if (cyw43_arch_init()) {
                printf("Wi-Fi init failed");
                return -1;
            }

            while (true) {
                printf("Hello, world!\n");
                cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
                sleep_ms(500);
                cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
                sleep_ms(3000);
            }

            return 0;
        }
        ```

1) Create a build directory (for elf and uf2 files and other stuff) :
```bash
mkdir build
cd build/
cmake -DPICO_BOARD=pico_w ..
make hello_world
```

2) Upload UF2 file on rpi

Find it

```bash
lsblk
NAME        MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
....
sdc           8:32   1   128M  0 disk 
└─sdc1        8:33   1   128M  0 part 
....
```

Mount and upload

```bash
sudo mount /dev/sdc1 ~/USB/
sudo cp hello_world.uf2 ~/USB/.
```

3) Find port and connect to it

```bash
ls -l /dev/ | grep -e USB -e ACM
sudo minicom -b 115200 -o -D /dev/ttyACM0
```
