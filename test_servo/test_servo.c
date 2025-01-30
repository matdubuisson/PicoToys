// Source => https://www.i-programmer.info/programming/148-hardware/14849-the-pico-in-c-basic-pwm.html?start=1

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#define TEST_GPIO 14

uint32_t clock = 125000000;

static uint32_t pwm_set_freq_duty(
    uint32_t slice, uint32_t channel,
    uint32_t frequency, uint32_t duty) {
    // https://www.i-programmer.info/programming/148-hardware/14849-the-pico-in-c-basic-pwm.html?start=2

    uint32_t divider16 = clock / frequency / 4096 + (clock % (frequency * 4096) != 0);

    if (divider16 / 16 == 0) divider16 = 16;

    uint32_t wrap = clock * 16 / divider16 / frequency - 1;

    pwm_set_clkdiv_int_frac(slice, divider16 / 16, divider16 & 0xF);
    pwm_set_wrap(slice, wrap);
    pwm_set_chan_level(slice, channel, wrap * duty / 100);

    return wrap;
}

int main(void) {
    setup_default_uart();
    stdio_init_all();
    cyw43_arch_init();

    gpio_init(TEST_GPIO);
    gpio_set_dir(TEST_GPIO, GPIO_OUT);
    gpio_set_function(TEST_GPIO, GPIO_FUNC_PWM);

    uint32_t slice = pwm_gpio_to_slice_num(TEST_GPIO);
    uint32_t channel = pwm_gpio_to_channel(TEST_GPIO); // Macro ex => PWM_CHAN_A

    // See source for these interesting functions
    // pwm_set_wrap
    // pwm_set_phase_correct
    // pwm_set_mask_enabled(uint32) => Manage multiple PWM slices at the same time as 8 first bits
    // pwm_set_chan_level(slice, channel, level);
    // pwm_set_both_levels(uint slice, uint levela, uint levelb)
    // pwm_set_gpio_level(uint gpio, uint level)

    // Non-correct mode :
    // f = fpico / (wrap + 1)
    // level = wrap * duty

    // Correct mode :
    // f = fpico / (2 * (wrap + 1))
    // level = wrap * duty

    pwm_set_phase_correct(slice, false);

    #define SERVO_FREQUENCY 50 // Hz

    uint8_t incrementing = true;
    uint32_t duty_fraction = 10;

    #define TICK 1000
    #define LED_TICK 100

    while (true) {
        printf("Use GPIO: %u, SLICE: %u, CHANNEL: %u, DUTY: %u (\%)\n", TEST_GPIO, slice, channel, duty_fraction);

        pwm_set_enabled(slice, false);
        pwm_set_freq_duty(slice, channel, SERVO_FREQUENCY, duty_fraction);
        pwm_set_enabled(slice, true);

        sleep_ms(TICK - LED_TICK);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);

        if (duty_fraction == 0) incrementing = true;
        else if (duty_fraction == 100) incrementing = false;

        if (incrementing) duty_fraction += 10;
        else duty_fraction -= 10;

        sleep_ms(LED_TICK);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
    }

    return 0;
}
