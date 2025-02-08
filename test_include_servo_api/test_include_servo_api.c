#include "pico/stdlib.h"

#include "servo_api.h"

int main(void) {
    Servo s1;
    servo_init(&s1, 20, false);
    servo_on(&s1);

    while (true) {
        servo_percent(&s1, 0);
        sleep_ms(500);
        servo_percent(&s1, 100);
        sleep_ms(500);
    }

    return 0;
}

