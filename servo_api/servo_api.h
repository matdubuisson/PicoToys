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

void ServoInit(Servo *s, uint32_t gpio, bool invert);
void ServoOn(Servo *s);
void ServoOff(Servo *s);
void ServoPosition(Servo *s, uint32_t p);

#endif
