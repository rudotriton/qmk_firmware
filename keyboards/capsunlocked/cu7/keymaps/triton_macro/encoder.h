#ifndef ENCODER_H
#define ENCODER_H

#include QMK_KEYBOARD_H

extern uint16_t cmd_tab_timer;
extern uint16_t shift_opt_timer;
extern bool is_cmd_tab_active;
extern bool is_shift_opt_active;
extern int rgb_flag;
extern int ltwo_flag;

void vim_encoder(bool clockwise);
void rgb_encoder(bool clockwise);

#endif
