#ifndef LN298_MOTOR_DRIVER_API
#define LN298_MOTOR_DRIVER_API

/**
 * Source : https://www.i-programmer.info/programming/148-hardware/14849-the-pico-in-c-basic-pwm.html?start=1
 * Source : https://github.com/sirfonzie/INF2004_LAB4/blob/main/l298n.c
 */

typedef struct {
    uint32_t in1; // IN1 LEFT FORWARD
    uint32_t in2; // IN2 LEFT BACKWARD
    uint32_t in3; // IN3 RIGHT BACKWARD
    uint32_t in4; // IN4 RIGHT FORWARD
} LN298MotorDriver;

void init_ln298_motor_driver (LN298MotorDriver *lnmd, uint32_t in1, uint32_t in2, uint32_t in3, uint32_t in4);
void stop_ln298_motor_driver (LN298MotorDriver *lnmd);
void left_ln298_motor_driver (LN298MotorDriver *lnmd);
void right_ln298_motor_driver (LN298MotorDriver *lnmd);
void forward_ln298_motor_driver (LN298MotorDriver *lnmd);
void backward_ln298_motor_driver (LN298MotorDriver *lnmd);

#define PWM_WRAP 0xffff

typedef struct {
    uint32_t frequency;
    uint32_t wrap;

    uint32_t in1; // IN1 LEFT FORWARD
    uint32_t in2; // IN2 LEFT BACKWARD
    uint32_t in3; // IN3 RIGHT BACKWARD
    uint32_t in4; // IN4 RIGHT FORWARD

    uint32_t in1_slice;
    uint32_t in2_slice;
    uint32_t in3_slice;
    uint32_t in4_slice;

    uint32_t in1_channel;
    uint32_t in2_channel;
    uint32_t in3_channel;
    uint32_t in4_channel;
} LN298MotorDriverPWM;

void init_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t in1, uint32_t in2, uint32_t in3, uint32_t in4, uint32_t frequency, uint32_t wrap);
void init_default_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t in1, uint32_t in2, uint32_t in3, uint32_t in4);
void stop_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd);
void left_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t duty);
void right_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t duty);
void forward_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t duty);
void backward_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t duty);

#endif
