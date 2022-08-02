#ifndef KEYMAP_H
#define KEYMAP_H

#include QMK_KEYBOARD_H
// #include "util.h"
// #include "encoder.h"
// #include "tap_dances.h"

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

enum {
  TD_L_01,
  TD_L_02,
  TD_L_03,
  TD_L_04,
  TD_L_05,
  TD_L_06
};

bool encoder_update_user(uint8_t index, bool clockwise);

uint16_t cmd_tab_timer;
uint16_t shift_opt_timer;
bool is_cmd_tab_active;
bool is_shift_opt_active;
int rgb_flag;
int ltwo_flag;

void vim_encoder(bool clockwise);
void rgb_encoder(bool clockwise);

bool to_move_win;
bool is_cmd_tab_active;
int rgb_flag;
int ltwo_flag;
bool l_eight_lock;

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

void default_hold_actions(int key_idx, bool release);
void layer_one_hold_actions(int key_idx, bool release);
void layer_three_hold_actions(int key_idx, bool release);
void layer_eight_hold_actions(int key_idx, bool release);

void (*layer_hold_actions[9]) (int, bool);

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

void (*layer_hold_actions[9]) (int, bool);
void (*layer_actions[9]) (int, bool);

void tap_key_switch(int key_idx, bool release);
void hold_key_switch(int key_idx, bool release);

td_state_t cur_dance(qk_tap_dance_state_t *state);
void key_finished(td_tap_t *key_tap_state, qk_tap_dance_state_t *state, int key_idx, int target_layer, void (*setup_layer) (void));

void key_one_finished(qk_tap_dance_state_t *state, void *user_data);
void key_one_reset(qk_tap_dance_state_t *state, void *user_data);
void key_two_finished(qk_tap_dance_state_t *state, void *user_data);
void key_two_reset(qk_tap_dance_state_t *state, void *user_data);
void key_three_finished(qk_tap_dance_state_t *state, void *user_data);
void key_three_reset(qk_tap_dance_state_t *state, void *user_data);
void key_four_finished(qk_tap_dance_state_t *state, void *user_data);
void key_four_reset(qk_tap_dance_state_t *state, void *user_data);
void key_five_finished(qk_tap_dance_state_t *state, void *user_data);
void key_five_reset(qk_tap_dance_state_t *state, void *user_data);
void key_six_finished(qk_tap_dance_state_t *state, void *user_data);
void key_six_reset(qk_tap_dance_state_t *state, void *user_data);

int get_layer(void);

#endif
