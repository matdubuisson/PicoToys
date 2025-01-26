#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define GREEN_LED 10
#define YELLOW_LED 11
#define RED_LED 12
#define BLUE_LED 13

#define BUTTON 14

#define TMP_ADC 26
#define LIGHT_ADC 27

int main (void) {
    setup_default_uart();
    stdio_init_all();

    gpio_init(GREEN_LED);
    gpio_init(YELLOW_LED);
    gpio_init(RED_LED);
    gpio_init(BLUE_LED);
    gpio_init(BUTTON);

    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_set_dir(YELLOW_LED, GPIO_OUT);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_set_dir(BUTTON, GPIO_IN);

    adc_init();

    adc_gpio_init(TMP_ADC);
    adc_gpio_init(LIGHT_ADC);

    const float adc_to_voltage_factor = 3.3f / (1 << 12);
    uint16_t adc_value;
    float voltage, temperature, lighting;

    char blue_led_flag = 0;

    while (true) {
        if (gpio_get(BUTTON)) {
            printf("Button clicked !!\n");
            gpio_put(GREEN_LED, 0);
            gpio_put(YELLOW_LED, 0);
            gpio_put(RED_LED, 0);

            gpio_put(GREEN_LED, 1);
            sleep_ms(200);
            gpio_put(GREEN_LED, 0);
            gpio_put(YELLOW_LED, 1);
            sleep_ms(200);
            gpio_put(YELLOW_LED, 0);
            gpio_put(RED_LED, 1);
            sleep_ms(200);
            gpio_put(RED_LED, 0);
        }

        adc_select_input(0); // Well here 0 means ADC 0 so GPIO 26
        adc_value = adc_read();
        voltage = adc_value * adc_to_voltage_factor;
        temperature = (voltage - 0.5f) * 100.0f;
        printf("GPIO26 (ADC0) - Raw: 0x%03x, Voltage: %f V, Temperature: %f C\n", adc_value, voltage, temperature);

        if (temperature > 20.0f) gpio_put(RED_LED, 1);
        else if (temperature < 15.0f) gpio_put(GREEN_LED, 1);
        else gpio_put(YELLOW_LED, 1);

        adc_select_input(1); // Well here 1 means ADC 1 so GPIO 27
        adc_value = adc_read();
        voltage = adc_value * adc_to_voltage_factor;
        #define MAX_VOLTAGE 3.3f
        lighting = voltage / MAX_VOLTAGE;

        printf("GPIO27 (ADC1) - Raw: 0x%03x, Voltage: %f V, Lighting: %.2f\%\n", adc_value, voltage, lighting);

        #define LIGHTING_THRESHOLD 0.3f

        if (!blue_led_flag && lighting <= LIGHTING_THRESHOLD) {
            printf("Turn on lights\n");
            blue_led_flag = 1;
            gpio_put(BLUE_LED, 1);
        } else if (blue_led_flag && lighting > LIGHTING_THRESHOLD) {
            printf("Turn off lights\n");
            blue_led_flag = 0;
            gpio_put(BLUE_LED, 0);
        }

        sleep_ms(250);
        gpio_put(GREEN_LED, 0);
        gpio_put(YELLOW_LED, 0);
        gpio_put(RED_LED, 0);
        sleep_ms(500);
    }

    return 0;
}
