#ifndef LAYER_HOLD_ACTIONS_H
#define LAYER_HOLD_ACTIONS_H

#include QMK_KEYBOARD_H
#include "layer_actions.h"
#include "keymap.h"

void default_hold_actions(int key_idx, bool release);
void layer_one_hold_actions(int key_idx, bool release);
void layer_three_hold_actions(int key_idx, bool release);
void layer_eight_hold_actions(int key_idx, bool release);

void (*layer_hold_actions[9]) (int, bool);

#endif
