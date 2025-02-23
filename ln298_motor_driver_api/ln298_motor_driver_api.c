#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "ln298_motor_driver_api.h"

#define LEFT_FORWARD_IN1_PIN lnmd->in1
#define LEFT_BACKWARD_IN2_PIN lnmd->in2
#define RIGHT_FORWARD_IN4_PIN lnmd->in4
#define RIGHT_BACKWARD_IN3_PIN lnmd->in3

#define LEFT_FORWARD_IN1_SLICE lnmd->in1_slice
#define LEFT_BACKWARD_IN2_SLICE lnmd->in2_slice
#define RIGHT_FORWARD_IN4_SLICE lnmd->in4_slice
#define RIGHT_BACKWARD_IN3_SLICE lnmd->in3_slice

#define LEFT_FORWARD_IN1_CHANNEL lnmd->in1_channel
#define LEFT_BACKWARD_IN2_CHANNEL lnmd->in2_channel
#define RIGHT_FORWARD_IN4_CHANNEL lnmd->in4_channel
#define RIGHT_BACKWARD_IN3_CHANNEL lnmd->in3_channel

extern void init_ln298_motor_driver (LN298MotorDriver *lnmd, uint32_t in1, uint32_t in2, uint32_t in3, uint32_t in4) {
    lnmd->in1 = in1;
    lnmd->in2 = in2;
    lnmd->in3 = in3;
    lnmd->in4 = in4;

    gpio_init(in1);
    gpio_init(in2);
    gpio_init(in3);
    gpio_init(in4);

    gpio_set_dir(in1, GPIO_OUT);
    gpio_set_dir(in2, GPIO_OUT);
    gpio_set_dir(in3, GPIO_OUT);
    gpio_set_dir(in4, GPIO_OUT);

    return;
}

extern void stop_ln298_motor_driver (LN298MotorDriver *lnmd) {
    gpio_put(LEFT_FORWARD_IN1_PIN, false);
    gpio_put(LEFT_BACKWARD_IN2_PIN, false);
    gpio_put(RIGHT_FORWARD_IN4_PIN, false);
    gpio_put(RIGHT_BACKWARD_IN3_PIN, false);
    return;
}

extern void left_ln298_motor_driver (LN298MotorDriver *lnmd) {
    gpio_put(LEFT_FORWARD_IN1_PIN, false);
    gpio_put(LEFT_BACKWARD_IN2_PIN, true);
    gpio_put(RIGHT_FORWARD_IN4_PIN, true);
    gpio_put(RIGHT_BACKWARD_IN3_PIN, false);
    return;
}

extern void right_ln298_motor_driver (LN298MotorDriver *lnmd) {
    gpio_put(LEFT_FORWARD_IN1_PIN, true);
    gpio_put(LEFT_BACKWARD_IN2_PIN, false);
    gpio_put(RIGHT_FORWARD_IN4_PIN, false);
    gpio_put(RIGHT_BACKWARD_IN3_PIN, true);
    return;
}

extern void forward_ln298_motor_driver (LN298MotorDriver *lnmd) {
    gpio_put(LEFT_FORWARD_IN1_PIN, true);
    gpio_put(LEFT_BACKWARD_IN2_PIN, false);
    gpio_put(RIGHT_FORWARD_IN4_PIN, true);
    gpio_put(RIGHT_BACKWARD_IN3_PIN, false);
    return;
}

extern void backward_ln298_motor_driver (LN298MotorDriver *lnmd) {
    gpio_put(LEFT_FORWARD_IN1_PIN, false);
    gpio_put(LEFT_BACKWARD_IN2_PIN, true);
    gpio_put(RIGHT_FORWARD_IN4_PIN, false);
    gpio_put(RIGHT_BACKWARD_IN3_PIN, true);
    return;
}

extern void init_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t in1, uint32_t in2, uint32_t in3, uint32_t in4, uint32_t frequency, uint32_t wrap) {
    lnmd->frequency = frequency;
    lnmd->wrap = wrap;

    lnmd->in1 = in1;
    lnmd->in2 = in2;
    lnmd->in3 = in3;
    lnmd->in4 = in4;

    gpio_set_function(in1, GPIO_FUNC_PWM);
    gpio_set_function(in2, GPIO_FUNC_PWM);
    gpio_set_function(in3, GPIO_FUNC_PWM);
    gpio_set_function(in4, GPIO_FUNC_PWM);

    lnmd->in1_slice = pwm_gpio_to_slice_num(in1);
    lnmd->in2_slice = pwm_gpio_to_slice_num(in2);
    lnmd->in3_slice = pwm_gpio_to_slice_num(in3);
    lnmd->in4_slice = pwm_gpio_to_slice_num(in4);

    lnmd->in1_channel = pwm_gpio_to_channel(in1);
    lnmd->in2_channel = pwm_gpio_to_channel(in2);
    lnmd->in3_channel = pwm_gpio_to_channel(in3);
    lnmd->in4_channel = pwm_gpio_to_channel(in4);

    uint32_t divider = 125e6 / (frequency * wrap);
    pwm_set_clkdiv(lnmd->in1_slice, divider);
    pwm_set_clkdiv(lnmd->in2_slice, divider);
    pwm_set_clkdiv(lnmd->in3_slice, divider);
    pwm_set_clkdiv(lnmd->in4_slice, divider);

    pwm_set_wrap(lnmd->in1_slice, wrap);
    pwm_set_wrap(lnmd->in2_slice, wrap);
    pwm_set_wrap(lnmd->in3_slice, wrap);
    pwm_set_wrap(lnmd->in4_slice, wrap);

    pwm_set_phase_correct(lnmd->in1_slice, false);
    pwm_set_phase_correct(lnmd->in2_slice, false);
    pwm_set_phase_correct(lnmd->in3_slice, false);
    pwm_set_phase_correct(lnmd->in4_slice, false);

    pwm_set_enabled(lnmd->in1_slice, true);
    pwm_set_enabled(lnmd->in2_slice, true);
    pwm_set_enabled(lnmd->in3_slice, true);
    pwm_set_enabled(lnmd->in4_slice, true);

    return;
}

extern void init_default_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t in1, uint32_t in2, uint32_t in3, uint32_t in4) {
    init_pwm_ln298_motor_driver(lnmd, in1, in2, in3, in4, 100, UINT16_MAX);
    return;
}

extern void stop_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd) {
    pwm_set_chan_level(lnmd->in1_slice, lnmd->in1_channel, 0);
    pwm_set_chan_level(lnmd->in2_slice, lnmd->in2_channel, 0);
    pwm_set_chan_level(lnmd->in3_slice, lnmd->in3_channel, 0);
    pwm_set_chan_level(lnmd->in4_slice, lnmd->in4_channel, 0);
    return;
}

extern void left_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t duty) {
    uint32_t level = duty * PWM_WRAP / 100;
    pwm_set_chan_level(LEFT_FORWARD_IN1_SLICE, LEFT_FORWARD_IN1_CHANNEL, 0);
    pwm_set_chan_level(RIGHT_FORWARD_IN4_SLICE, RIGHT_FORWARD_IN4_CHANNEL, level);
    pwm_set_chan_level(LEFT_BACKWARD_IN2_SLICE, LEFT_BACKWARD_IN2_CHANNEL, level);
    pwm_set_chan_level(RIGHT_BACKWARD_IN3_SLICE, RIGHT_BACKWARD_IN3_CHANNEL, 0);
    return;
}

extern void right_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t duty) {
    uint32_t level = duty * PWM_WRAP / 100;
    pwm_set_chan_level(LEFT_FORWARD_IN1_SLICE, LEFT_FORWARD_IN1_CHANNEL, level);
    pwm_set_chan_level(RIGHT_FORWARD_IN4_SLICE, RIGHT_FORWARD_IN4_CHANNEL, 0);
    pwm_set_chan_level(LEFT_BACKWARD_IN2_SLICE, LEFT_BACKWARD_IN2_CHANNEL, 0);
    pwm_set_chan_level(RIGHT_BACKWARD_IN3_SLICE, RIGHT_BACKWARD_IN3_CHANNEL, level);
    return;
}
#include <stdio.h>

extern void forward_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t duty) {
    printf("IN1 => %u, %u, %u\n", lnmd->in1, lnmd->in1_slice, lnmd->in1_channel);
    printf("IN2 => %u, %u, %u\n", lnmd->in2, lnmd->in2_slice, lnmd->in2_channel);
    printf("IN3 => %u, %u, %u\n", lnmd->in3, lnmd->in3_slice, lnmd->in3_channel);
    printf("IN4 => %u, %u, %u\n", lnmd->in4, lnmd->in4_slice, lnmd->in4_channel);
    uint32_t level = duty * PWM_WRAP / 100;
    pwm_set_chan_level(LEFT_FORWARD_IN1_SLICE, LEFT_FORWARD_IN1_CHANNEL, level);
    pwm_set_chan_level(RIGHT_FORWARD_IN4_SLICE, RIGHT_FORWARD_IN4_CHANNEL, level);
    pwm_set_chan_level(LEFT_BACKWARD_IN2_SLICE, LEFT_BACKWARD_IN2_CHANNEL, 0);
    pwm_set_chan_level(RIGHT_BACKWARD_IN3_SLICE, RIGHT_BACKWARD_IN3_CHANNEL, 0);
    return; 
}

extern void backward_pwm_ln298_motor_driver (LN298MotorDriverPWM *lnmd, uint32_t duty) {
    uint32_t level = duty * PWM_WRAP / 100;
    pwm_set_chan_level(LEFT_FORWARD_IN1_SLICE, LEFT_FORWARD_IN1_CHANNEL, 0);
    pwm_set_chan_level(RIGHT_FORWARD_IN4_SLICE, RIGHT_FORWARD_IN4_CHANNEL, 0);
    pwm_set_chan_level(LEFT_BACKWARD_IN2_SLICE, LEFT_BACKWARD_IN2_CHANNEL, level);
    pwm_set_chan_level(RIGHT_BACKWARD_IN3_SLICE, RIGHT_BACKWARD_IN3_CHANNEL, level);
    return;
}