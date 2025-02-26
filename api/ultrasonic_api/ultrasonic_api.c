#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Inspiration from https://github.com/Thomas-Kleist/Pico-Ultrasonic/blob/main/ultrasonic/ultrasonic.c
// And from https://github.com/ErickSimoes/Ultrasonic/blob/master/src/Ultrasonic.cpp

#include "ultrasonic_api.h"

extern void ultrasonic_init (Ultrasonic *u, uint32_t echo_gpio, uint32_t trig_gpio, uint32_t timeout) {
    u->echo_gpio = echo_gpio;
    u->trig_gpio = trig_gpio;
    u->timeout = timeout;

    gpio_init(echo_gpio);
    gpio_init(trig_gpio);
    gpio_set_dir(echo_gpio, GPIO_IN);
    gpio_set_dir(trig_gpio, GPIO_OUT);

    return;
}

extern uint32_t ultrasonic_get_pulse (Ultrasonic *u) {
    gpio_put(u->trig_gpio, false);
    sleep_us(2);
    gpio_put(u->trig_gpio, true);
    sleep_us(10);
    gpio_put(u->trig_gpio, false);

    uint32_t width;

    for (width = 0; !gpio_get(u->echo_gpio) && width < u->timeout; width++) sleep_us(1);

    if (width == u->timeout) return UINT32_MAX;

    uint64_t start_clock = get_absolute_time(); // In ms
    uint64_t stop_clock;

    for (width = 0; gpio_get(u->echo_gpio) && width < u->timeout; width++) sleep_us(1);

    if (width == u->timeout) return UINT32_MAX;

    stop_clock = get_absolute_time();
    
    return (uint32_t) (stop_clock - start_clock);
}

extern uint32_t ultrasonic_get_meters (Ultrasonic *u) {
    uint32_t µtiming = ultrasonic_get_pulse(u);
    // printf("µtiming = %u\n", µtiming);
    return µtiming == UINT32_MAX ? UINT32_MAX : (340 * µtiming) / 2000000; // MULTIPLICATION BEFORE DIVISION
}

extern uint32_t ultrasonic_get_centimeters (Ultrasonic *u) {
    uint32_t µtiming = ultrasonic_get_pulse(u);
    // printf("µtiming = %u\n", µtiming);
    return µtiming == UINT32_MAX ? UINT32_MAX : (34 * µtiming) / 2000; // MULTIPLICATION BEFORE DIVISION
}

extern uint32_t ultrasonic_get_millimeters (Ultrasonic *u) {
    uint32_t µtiming = ultrasonic_get_pulse(u);
    // printf("µtiming = %u\n", µtiming);
    return µtiming == UINT32_MAX ? UINT32_MAX : (340 * µtiming) / 2000; // MULTIPLICATION BEFORE DIVISION
}
