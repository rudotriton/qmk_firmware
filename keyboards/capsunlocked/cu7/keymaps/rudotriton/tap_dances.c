#include "tap_dances.h"

void tap_key_switch(int key_idx, bool release) {
    (*layer_actions[get_layer()]) (key_idx, release);
}

void hold_key_switch(int key_idx, bool release) {
    (*layer_hold_actions[get_layer()]) (key_idx, release);
}

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

void key_finished(td_tap_t *key_tap_state, qk_tap_dance_state_t *state, int key_idx, int target_layer, void (*setup_layer) (void)) {
    key_tap_state->state = cur_dance(state);
    switch (key_tap_state->state) {
        case TD_SINGLE_HOLD:
            hold_key_switch(key_idx, false);
            break;
        case TD_SINGLE_TAP:
            tap_key_switch(key_idx, false);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(target_layer)) {
                layer_move(_DEFAULT);
            } else {
                layer_move(target_layer);
                if (setup_layer != NULL)
                setup_layer();
            }
            break;
        default:
            break;
    }
}

void key_reset(td_tap_t *key_tap_state, qk_tap_dance_state_t *state, void *user_data, int key_idx) {
    if (key_tap_state->state == TD_SINGLE_HOLD) {
        hold_key_switch(key_idx, true);
    } else if (key_tap_state->state == TD_SINGLE_TAP) {
        tap_key_switch(1, true);
    }
    key_tap_state->state = TD_NONE;
}

static td_tap_t key_one_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void key_one_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_one_tap_state, state, 1, _ONE, NULL);
}

void key_one_reset(qk_tap_dance_state_t *state, void *user_data) {
    key_reset(&key_one_tap_state, state, user_data, 1);
}

static td_tap_t key_two_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void setup_l_two(void) {
    ltwo_flag = 0;
}

// Functions that control what our tap dance key does
void key_two_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_two_tap_state, state, 2, _TWO, setup_l_two);
}

void key_two_reset(qk_tap_dance_state_t *state, void *user_data) {
    key_reset(&key_two_tap_state, state, user_data, 2);
}

static td_tap_t key_three_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void key_three_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_three_tap_state, state, 3, _THREE, NULL);
}

void key_three_reset(qk_tap_dance_state_t *state, void *user_data) {
    key_reset(&key_three_tap_state, state, user_data, 3);
}

static td_tap_t key_four_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void key_four_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_four_tap_state, state, 4, _FOUR, NULL);
}

void key_four_reset(qk_tap_dance_state_t *state, void *user_data) {
    key_reset(&key_four_tap_state, state, user_data, 4);
}

static td_tap_t key_five_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void key_five_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_five_tap_state, state, 5, _FIVE, NULL);
}

void key_five_reset(qk_tap_dance_state_t *state, void *user_data) {
    key_reset(&key_five_tap_state, state, user_data, 5);
}

static td_tap_t key_six_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void setup_l_six(void) {
    rgb_flag = 0;
}

void key_six_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_six_tap_state, state, 6, _META, setup_l_six);
}

void key_six_reset(qk_tap_dance_state_t *state, void *user_data) {
    key_reset(&key_six_tap_state, state, user_data, 6);
}
