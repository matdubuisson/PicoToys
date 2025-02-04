#include "pico/stdlib.h"

#include "servo_api.h"

int main(void) {
    Servo s1;
    ServoInit(&s1, 20, false);
    ServoOn(&s1);

    while (true) {
        ServoPosition(&s1, 0);
        sleep_ms(500);
        ServoPosition(&s1, 100);
        sleep_ms(500);
    }

    return 0;
}

