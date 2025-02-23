#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "ln298_motor_driver_api.h"

int main (void) {
    setup_default_uart();
    stdio_init_all();

    LN298MotorDriverPWM lnmd;
    init_default_pwm_ln298_motor_driver(&lnmd, 6, 8, 10, 12);

    uint16_t duty = 0;

    while (true) {
        printf("DUTY = %u\n", duty);
        left_pwm_ln298_motor_driver(&lnmd, duty);
        sleep_ms(500);
        right_pwm_ln298_motor_driver(&lnmd, duty);
        sleep_ms(500);
        forward_pwm_ln298_motor_driver(&lnmd, duty);
        sleep_ms(500);
        backward_pwm_ln298_motor_driver(&lnmd, duty);
        sleep_ms(500);
        duty = (duty + 5) % 110;
    }

    // LN298MotorDriver lnmd;
    // init_ln298_motor_driver(&lnmd, 10, 11, 12, 13);

    // uint16_t duty_cycle = 50;
    // #define TEST_GPIO 10
    // #define FREQUENCY 100
    // gpio_set_function(TEST_GPIO, GPIO_FUNC_PWM);
    // uint32_t slice_num = pwm_gpio_to_slice_num(TEST_GPIO);
    // float clock_freq = 125000000.0f;  // Default clock frequency of the Pico in Hz
    // uint32_t divider = clock_freq / (FREQUENCY * 65536);  // Compute clock divider
    // pwm_set_clkdiv(slice_num, divider);
    // pwm_set_wrap(slice_num, 65535);
    // pwm_set_gpio_level(TEST_GPIO, duty_cycle * 65536 / 100);
    // pwm_set_enabled(slice_num, true);

    while (true) {
        // pwm_set_gpio_level(TEST_GPIO, duty_cycle * 65536 / 100);
        // printf("==> %u, %u;\n", duty_cycle, duty_cycle * 65536 / 100);
        // duty_cycle += 10;
        // duty_cycle %= 110;
        // sleep_ms(1000);

        // printf("STOP");
        // stop_ln298_motor_driver(&lnmd);
        // sleep_ms(500);
        // printf("LEFT");
        // left_ln298_motor_driver(&lnmd);
        // sleep_ms(500);
        // printf("RIGHT");
        // right_ln298_motor_driver(&lnmd);
        // sleep_ms(500);
        // printf("FORWARD");
        // forward_ln298_motor_driver(&lnmd);
        // sleep_ms(500);
        // printf("BACKWARD");
        // backward_ln298_motor_driver(&lnmd);
        // sleep_ms(500);
    }

    return 0;
}