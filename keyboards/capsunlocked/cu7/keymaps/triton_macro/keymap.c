/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "keymap.h"

bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;
bool to_move_win = false;
int rgb_flag = 0;
int ltwo_flag = 0;
bool l_eight_lock = false;
int led_indices[] = { 2, 1, 0, 3, 4, 5 };

#define double_taps LAYOUT( KC_TRNS, TD(TD_L_01), TD(TD_L_02), TD(TD_L_03), TD(TD_L_04), TD(TD_L_05), TD(TD_L_06))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = double_taps,
    [_ONE] = double_taps,
    [_TWO] = double_taps,
    [_THREE] = double_taps,
    [_FOUR] = double_taps,
    [_FIVE] = double_taps,
    [_META] = double_taps,

    [_RESET] = LAYOUT(
                  KC_TRNS,
    TO(_DEFAULT), KC_NO,   RESET,
    KC_NO,        KC_NO,   KC_NO),

    [_MUSIC] = double_taps,
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_layer()) {
        case _DEFAULT: // volume up/down
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case _ONE: // cycle applications
            if (!is_cmd_tab_active) {
                is_cmd_tab_active = true;
                register_code(KC_RCMD);
            }
            cmd_tab_timer = timer_read();
            if (clockwise) {
                tap_code16(KC_TAB);
            } else {
                tap_code16(S(KC_TAB));
            }
            break;
        case _TWO:
            vim_encoder(clockwise);
            break;
        case _FOUR: // cycle browser tabs
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(C(S(KC_TAB)));
            }
            break;
        case _META:
            rgb_encoder(clockwise);
            break;
        case _MUSIC:
            if (clockwise) {
                  tap_code16(S(KC_RGHT));
              } else {
                  tap_code16(S(KC_LEFT));
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 1250) {
            unregister_code(KC_RCMD);
            is_cmd_tab_active = false;
        }
    }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    int layer = get_layer();
    switch (layer) {
        case _ONE:
            if (to_move_win) {
                for (int i = led_min; i < led_max; i++) {
                    rgb_matrix_set_color(i, 0, 108, 255);
                }
            }
            rgb_matrix_set_color(2, 255, 168, 0);
            break;
        case _TWO:
            rgb_matrix_set_color(1, 255, 168, 0);
            if (ltwo_flag) {
                rgb_matrix_set_color(led_indices[ltwo_flag - 1], 0, 108, 255);
            }
            break;
        case _META:
            rgb_matrix_set_color(5, 255, 168, 0);
            if (rgb_flag) {
                rgb_matrix_set_color(led_indices[rgb_flag - 1], 0, 108, 255);
            }
            break;
        case _RESET:
            rgb_matrix_set_color(2, 36, 255, 99);// green
            rgb_matrix_set_color(0, 255, 0, 152); // red
            break;
        case _MUSIC:
            rgb_matrix_set_color(2, 255, 168, 0);
            rgb_matrix_set_color(5, 255, 168, 0);
            break;
        default:
            rgb_matrix_set_color(led_indices[layer-1], 255, 168, 0);
            break;
    }
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();  // enables rgb, without saving settings
    rgb_matrix_sethsv_noeeprom(180, 255, 200);
    rgb_matrix_set_speed_noeeprom(25);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

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

// NOTE: ONE
static td_tap_t key_one_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void key_one_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_one_tap_state, state, 1, _ONE, NULL);
}

void key_one_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (key_one_tap_state.state == TD_SINGLE_HOLD) {
        hold_key_switch(1, true);
    } else if (key_one_tap_state.state == TD_SINGLE_TAP) {
        tap_key_switch(1, true);
    }
    key_one_tap_state.state = TD_NONE;
}

// NOTE: TWO
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
    if (key_two_tap_state.state == TD_SINGLE_HOLD) {
        hold_key_switch(2, true);
    } else if (key_two_tap_state.state == TD_SINGLE_TAP) {
        tap_key_switch(2, true);
    }
    key_two_tap_state.state = TD_NONE;
}

// NOTE: THREE
static td_tap_t key_three_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void key_three_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_three_tap_state, state, 3, _THREE, NULL);
}

void key_three_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (key_three_tap_state.state == TD_SINGLE_HOLD) {
        hold_key_switch(3, true);
    } else if (key_three_tap_state.state == TD_SINGLE_TAP) {
        tap_key_switch(3, true);
    }
    key_three_tap_state.state = TD_NONE;
}

// NOTE: FOUR
static td_tap_t key_four_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void key_four_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_four_tap_state, state, 4, _FOUR, NULL);
}

void key_four_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (key_four_tap_state.state == TD_SINGLE_HOLD) {
        hold_key_switch(4, true);
    } else if (key_four_tap_state.state == TD_SINGLE_TAP) {
        tap_key_switch(4, true);
    }
    key_four_tap_state.state = TD_NONE;
}

// NOTE: FIVE
static td_tap_t key_five_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void key_five_finished(qk_tap_dance_state_t *state, void *user_data) {
    key_finished(&key_five_tap_state, state, 5, _FIVE, NULL);
}

void key_five_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (key_five_tap_state.state == TD_SINGLE_HOLD) {
        hold_key_switch(5, true);
    } else if (key_five_tap_state.state == TD_SINGLE_TAP) {
        tap_key_switch(5, true);
    }
    key_five_tap_state.state = TD_NONE;
}

// NOTE: SIX
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
    if (key_six_tap_state.state == TD_SINGLE_HOLD) {
        hold_key_switch(6, true);
    } else if (key_six_tap_state.state == TD_SINGLE_TAP) {
        tap_key_switch(6, true);
    }
    key_six_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_L_01] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_one_finished, key_one_reset),
    [TD_L_02] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_two_finished, key_two_reset),
    [TD_L_03] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_three_finished, key_three_reset),
    [TD_L_04] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_four_finished, key_four_reset),
    [TD_L_05] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_five_finished, key_five_reset),
    [TD_L_06] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_six_finished, key_six_reset),
};
