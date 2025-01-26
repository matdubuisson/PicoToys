#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define WIFI_SSID "WiFi-2.4-6B51"
#define WIFI_PSWD "1DBA04B83F"

static void error(const char *str) {
    while (true) {
        printf("%s\n", str);
        sleep_ms(1000);
    }

    return;
}

int main (void) {
    setup_default_uart();
    stdio_init_all();

    if (cyw43_arch_init()) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        error("Wi-Fi init failed");
        return -1;
    }

    if (cyw43_arch_init_with_country(CYW43_COUNTRY_BELGIUM)) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        error("Error to fit to Belgium policy\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PSWD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        error("Failed to connect wifi\n");
        return 1;
    }

    while (true) {
        printf("Connected\n");
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);
    }

    return 0;
}