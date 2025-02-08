#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"

#include "ultrasonic_api.h"
#include "servo_api.h"

#define FORWARD_LEFT 10
#define BACKWARD_LEFT 11
#define FORWARD_RIGHT 13
#define BACKWARD_RIGHT 12

#define SERVO 20

static void stop (void) {
    gpio_put(FORWARD_LEFT, false);
    gpio_put(BACKWARD_LEFT, false);
    gpio_put(FORWARD_RIGHT, false);
    gpio_put(BACKWARD_RIGHT, false);
    return;
}

static void left (void) {
    gpio_put(FORWARD_LEFT, false);
    gpio_put(BACKWARD_LEFT, true);
    gpio_put(FORWARD_RIGHT, true);
    gpio_put(BACKWARD_RIGHT, false);
    return;
}

static void right (void) {
    gpio_put(FORWARD_LEFT, true);
    gpio_put(BACKWARD_LEFT, false);
    gpio_put(FORWARD_RIGHT, false);
    gpio_put(BACKWARD_RIGHT, true);
    return;
}

static void forward (void) {
    gpio_put(FORWARD_LEFT, true);
    gpio_put(BACKWARD_LEFT, false);
    gpio_put(FORWARD_RIGHT, true);
    gpio_put(BACKWARD_RIGHT, false);
    return;
}

static void backward (void) {
    gpio_put(FORWARD_LEFT, false);
    gpio_put(BACKWARD_LEFT, true);
    gpio_put(FORWARD_RIGHT, false);
    gpio_put(BACKWARD_RIGHT, true);
    return;
}

static void blink (void) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
    sleep_ms(100);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
    return;
}

int main (void) {
    setup_default_uart();
    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);

    Ultrasonic ultrasonic;
    ultrasonic_init(&ultrasonic, 14, 15, 1000000);

    Servo servo;
    servo_init(&servo, SERVO, false);
    servo_on(&servo);
    servo_percent(&servo, 45);

    gpio_init(FORWARD_LEFT);
    gpio_init(BACKWARD_LEFT);
    gpio_init(FORWARD_RIGHT);
    gpio_init(BACKWARD_RIGHT);

    gpio_set_dir(FORWARD_LEFT, GPIO_OUT);
    gpio_set_dir(BACKWARD_LEFT, GPIO_OUT);
    gpio_set_dir(FORWARD_RIGHT, GPIO_OUT);
    gpio_set_dir(BACKWARD_RIGHT, GPIO_OUT);

    stop();

    blink();

    #define SECURITY_DISTANCE_MM 100
    uint32_t distance, distance2;
    static uint32_t ticks = 0, average_distance = UINT32_MAX;

    // #define STOP 0
    // #define FORWARD 1
    // #define BACKWARD 2
    // #define LEFT 3
    // #define RIGHT 4
    // static uint8_t current_movement;

    while (true) {
        distance = ultrasonic_get_millimeters(&ultrasonic);
        printf("Distance => %u mm\n", distance);

        if (ticks % 128 == 0) {
            average_distance /= 128;

            if (distance - average_distance <= 5) distance = SECURITY_DISTANCE_MM - 1; // Assume dummy stuck
        } else average_distance += distance;

        ticks++;

        if (distance == UINT32_MAX) {
            printf("ERROR\n");
            // current_movement = STOP;
            stop();
            blink();
            continue;
        } else if (distance >= SECURITY_DISTANCE_MM) {
            printf("FORWARD\n");
            // current_movement = FORWARD;
            forward();
        } else {
            stop();

            servo_percent(&servo, 80);
            sleep_ms(500);
            distance = ultrasonic_get_millimeters(&ultrasonic);

            servo_percent(&servo, 10);
            sleep_ms(500);
            distance2 = ultrasonic_get_millimeters(&ultrasonic);

            servo_percent(&servo, 45);

            printf("BACKWARD\n");
            backward();
            sleep_ms(300);

            if (distance <= distance2) right();
            else left();

            sleep_ms(200);
            stop();
        }
    }

    /*
    uint32_t percent;

    while (true) {
        for (percent = 0; percent <= 100; percent += 10) {
            printf("Servo at %u percents\n", percent);
            ServoPosition(&servo, percent);
            sleep_ms(500);
        }

        for (percent = 100; true; percent -= 10) {
            printf("Servo at %u percents\n", percent);
            ServoPosition(&servo, percent);
            sleep_ms(500);

            if (percent == 0) break; // unit => 0 - 10 = MAX - 10
        }
    }
    */

    /*
    while (true) {
        printf("Stop\n");
        stop();
        sleep_ms(1000);
        blink();

        printf("Left\n");
        left();
        sleep_ms(1000);
        blink();

        printf("Right\n");
        right();
        sleep_ms(1000);
        blink();

        printf("Forward\n");
        forward();
        sleep_ms(1000);
        blink();

        printf("Backward\n");
        backward();
        sleep_ms(1000);
        blink();
    }
    */

    return 0;
}
