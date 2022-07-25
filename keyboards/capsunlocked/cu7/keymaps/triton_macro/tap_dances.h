#ifndef TAP_DANCES_H
#define TAP_DANCES_H

#include "layer_actions.h"
#include "layer_hold_actions.h"
// TAP_DANCE_ENABLE = yes should include it, but it doesn't ¯\_(ツ)_/¯
#include "quantum/process_keycode/process_tap_dance.h"

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

extern void (*layer_hold_actions[9]) (int, bool);
extern void (*layer_actions[9]) (int, bool);

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

#endif
