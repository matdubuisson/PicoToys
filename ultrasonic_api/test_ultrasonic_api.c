#include <stdio.h>
#include "pico/stdlib.h"

#include "ultrasonic_api.h"

int main (void) {
    setup_default_uart();
    stdio_init_all();

    Ultrasonic u;
    ultrasonic_init(&u, 14, 15, 1000000);

    uint32_t value;

    while (true) {
        value = ultrasonic_get_meters(&u);
        printf("Distance => %u m\n", value);
        sleep_ms(500);
        value = ultrasonic_get_centimeters(&u);
        printf("Distance => %u cm\n", value);
        sleep_ms(500);
        value = ultrasonic_get_millimeters(&u);
        printf("Distance => %u mm\n", value);
        sleep_ms(500);
    }

    return 0;
}
