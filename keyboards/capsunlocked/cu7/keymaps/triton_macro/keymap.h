#ifndef KEYMAP_H
#define KEYMAP_H

#include QMK_KEYBOARD_H
#include "util.h"
#include "encoder.h"
#include "layer_actions.h"
#include "layer_hold_actions.h"

extern void (*layer_hold_actions[9]) (int, bool);
extern void (*layer_actions[9]) (int, bool);

// layers
#define _DEFAULT 0
#define _ONE 1
#define _TWO 2
#define _THREE 3
#define _FOUR 4
#define _FIVE 5
#define _META 6
#define _RESET 7
#define _MUSIC 8

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

enum {
  TD_L_01,
  TD_L_02,
  TD_L_03,
  TD_L_04,
  TD_L_05,
  TD_L_06
};

bool encoder_update_user(uint8_t index, bool clockwise);

#endif
