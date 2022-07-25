#ifndef LAYER_ACTIONS_H
#define LAYER_ACTIONS_H

#include QMK_KEYBOARD_H
#include "keymap.h"

extern bool to_move_win;
extern bool is_cmd_tab_active;
extern int rgb_flag;
extern int ltwo_flag;
extern bool l_eight_lock;

void default_actions(int key_idx, bool release);
void layer_one_actions(int key_idx, bool release);
void layer_two_actions(int key_idx, bool release);
void layer_three_actions(int key_idx, bool release);
void layer_four_actions(int key_idx, bool release);
void layer_five_actions(int key_idx, bool release);
void layer_six_actions(int key_idx, bool release);
void layer_seven_actions(int key_idx, bool release);
void layer_eight_actions(int key_idx, bool release);

void (*layer_actions[9]) (int, bool);

#endif
