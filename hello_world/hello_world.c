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