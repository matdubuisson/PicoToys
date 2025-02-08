#ifndef SERVO_API
#define SERVO_API

typedef struct
{
    uint32_t gpio;
    uint32_t slice;
    uint32_t chan;
    uint32_t speed;
    uint32_t resolution;
    bool on;
    bool invert;
} Servo;

void servo_init(Servo *s, uint32_t gpio, bool invert);
void servo_on(Servo *s);
void servo_off(Servo *s);
void servo_percent(Servo *s, uint32_t p);

#endif
