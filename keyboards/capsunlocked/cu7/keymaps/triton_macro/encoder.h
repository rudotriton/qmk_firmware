#ifndef ENCODER_H
#define ENCODER_H

#include QMK_KEYBOARD_H

extern int rgb_flag;
extern int ltwo_flag;

void vim_encoder(bool clockwise);
void rgb_encoder(bool clockwise);

#endif
