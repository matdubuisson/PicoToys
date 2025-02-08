#ifndef ULTRASONIC_API
#define ULTRASONIC_API

typedef struct
{
    uint32_t echo_gpio;
    uint32_t trig_gpio;
    uint32_t timeout;
} Ultrasonic;

void ultrasonic_init (Ultrasonic *u, uint32_t echo_gpio, uint32_t trig_gpio, uint32_t timeout);
uint32_t ultrasonic_get_pulse (Ultrasonic *u);
uint32_t ultrasonic_get_meters (Ultrasonic *u);
uint32_t ultrasonic_get_centimeters (Ultrasonic *u);
uint32_t ultrasonic_get_millimeters (Ultrasonic *u);

#endif
