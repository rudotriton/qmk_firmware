/*
Copyright 2021 CapsUnlocked

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
#include QMK_KEYBOARD_H

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
    TO(_DEFAULT), KC_NO, RESET,
    KC_NO,        KC_NO, KC_NO),

    [_MUSIC] = double_taps,
};

int get_layer(void) {
    for (int i = _DEFAULT; i <= _MUSIC; i++) {
        if (layer_state_is(i)) return i;
    }
    return -1;
}

// variables for cmd tabbing
bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

// rgb_flag
// 0 - screen brightness
// 1 - hue
// 2 - saturation
// 3 - value
// 4 - mode
// 5 - speed
int rgb_flag = 0;

void rgb_encoder(bool clockwise) {
    switch (rgb_flag) {
        case 1:
            if (clockwise) { // hue
                rgb_matrix_increase_hue_noeeprom();
            } else {
                rgb_matrix_decrease_hue_noeeprom();
            }
            break;
        case 2:
            if (clockwise) { // sat
                rgb_matrix_increase_sat_noeeprom();
            } else {
                rgb_matrix_decrease_sat_noeeprom();
            }
            break;
        case 3:
            if (clockwise) { // val
                rgb_matrix_increase_val_noeeprom();
            } else {
                rgb_matrix_decrease_val_noeeprom();
            }
            break;
        case 4:
            if (clockwise) { // mode
                rgb_matrix_step_noeeprom();
            } else {
                rgb_matrix_step_reverse_noeeprom();
            }
            break;
        case 5:
            if (clockwise) { // speed
                rgb_matrix_increase_speed_noeeprom();
            } else {
                rgb_matrix_decrease_speed_noeeprom();
            }
            break;
        default:
            if (clockwise) { // brightness
                tap_code(KC_BRIU);
            } else {
                tap_code(KC_BRID);
            }
            break;
    }
}

// ltwo_flag
// 0 - mouse scroll wheel
// 1 - vim jumplist
// 2 - vim search targets n/N
// 3 - vim undo/redo
int ltwo_flag = 0;

void vim_encoder(bool clockwise) {
    switch (ltwo_flag) {
        case 0:
            if (clockwise) {
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
            }
            break;
        case 1:
            if (clockwise) {
                tap_code16(C(KC_I));
            } else {
                tap_code16(C(KC_O));
            }
            break;
        case 2:
            if (clockwise) {
                tap_code(KC_N);
            } else {
                tap_code16(S(KC_N));
            }
            break;
        case 3:
            if (clockwise) {
                  tap_code16(C(KC_R));
              } else {
                  tap_code(KC_U);
            }
            break;
        case 4:
            if (clockwise) {
                  tap_code(KC_WH_R);
              } else {
                  tap_code(KC_WH_L);
            }
            break;
    }
}

// Volume up/down on the encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_layer()) {
        case _DEFAULT:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case _ONE:
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
        case _THREE:
            break;
        case _FOUR:
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

int led_indices[] = { 2, 1, 0, 3, 4, 5 };

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    int layer = get_layer();
    switch (layer) {
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

// NOTE: Layer actions
bool l_eight_lock = false;

void default_actions(int key_idx, bool release) {
    if (release) return;
    switch (key_idx) {
        case 1:
            tap_code(KC_MPRV);
            break;
        case 2:
            tap_code(KC_MPLY);
            break;
        case 3:
            tap_code(KC_MNXT);
            break;
        case 4:
            // Switch to Kitty and hide other windows
            tap_code(KC_ESC);
            tap_code16(G(C(KC_M)));
            tap_code16(G(A(KC_H)));
            break;
        case 5:
            tap_code(KC_MUTE);
            break;
        case 6:
            l_eight_lock = false;
            layer_move(_MUSIC);
            break;
    }
}

void layer_one_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 1:
            if (!release)
            tap_code16(C(KC_LEFT));
            break;
        case 2:
            if (is_cmd_tab_active && !release) {
                tap_code(KC_ENT); // allow bypassing the timeout
            } else if (release) {
                unregister_code16(C(KC_UP));
            } else {
                register_code16(C(KC_UP));
            }
            break;
        case 3:
            if (!release)
            tap_code16(C(KC_RGHT));
            break;
        case 4:
            if (!release)
            tap_code16(G(A(KC_V)));
            break;
        case 5:
            if (release)
            unregister_code16(C(KC_DOWN));
            else
            register_code16(C(KC_DOWN));
            break;
        case 6:
            if (release)
            unregister_code16(KC_F11);
            else
            register_code16(KC_F11);
            break;

    }
}

void layer_two_actions(int key_idx, bool release) {
    if (release) return;
        switch (key_idx) {
            case 1:
            case 2:
            case 3:
            case 4:
                ltwo_flag = ltwo_flag == key_idx ? 0 : key_idx;
                break;
        }
}

// NOTE: Room for activities
// NOTE: right now it seems to be set for youtube
void layer_three_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 1:
            if (!release) {
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
            }
            break;
        case 2:
            if (!release) {
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
            }
            break;
        case 3:
            if (!release) {
                register_code(KC_RGHT);
            } else {
                unregister_code(KC_RGHT);
            }
            break;
        case 4:
            if (!release) {
                register_code16(S(KC_COMM));
            } else {
                unregister_code16(S(KC_COMM));
            }
            break;
        case 5:
            if (!release) {
            } else {
            }
            break;
        case 6:
            if (!release) {
                register_code16(S(KC_DOT));
            } else {
                unregister_code16(S(KC_DOT));
            }
            break;
    }
}

void layer_four_actions(int key_idx, bool release) {
    if (release) return;

    switch (key_idx) {
        case 1:
            tap_code16(C(S(KC_TAB))); // previous tab
            break;
        case 2:
            tap_code16(G(KC_W)); // close tab
            break;
        case 3:
            tap_code16(C(KC_TAB)); // next tab
            break;
        case 4:
            tap_code16(G(KC_R)); // refresh
            break;
        case 5:
            tap_code16(G(S(KC_T))); // reopen last closed tab
            break;
        case 6:
            // copy, open new tab, paste, enter
            tap_code16(G(KC_C));
            tap_code16(G(A(KC_J))); // launch ff w/ BTT
            tap_code16(G(KC_T));
            tap_code16(G(KC_V));
            tap_code(KC_ENT);
            break;
    }
}

void layer_five_actions(int key_idx, bool release) {
    if (release) return;

    switch (key_idx) {
        case 1:
            tap_code16(G(S(KC_DEL))); // hammerspoon: rotate monitor
            break;
        case 2:
            tap_code16(G(A(KC_RBRC))); // toggle system theme
            break;
        case 3:
            tap_code16(G(C(KC_Q))); // lock screen
            break;
        case 4:
            tap_code16(G(S(KC_BSLS))); // hammerspoon: fix monitors
            break;
        case 5:
            break;
        case 6:
            break;
    }
}

void layer_six_actions(int key_idx, bool release) {
    if (release) return;

    switch (key_idx) {
        case 6:
            layer_move(_RESET);
            break;
        default:
            rgb_flag = rgb_flag == key_idx ? 0 : key_idx;
            break;
    }
}

void layer_seven_actions(int key_idx, bool release) {
    if (key_idx == 6 && release)
        layer_move(_META);
}

// some spotify actions
void layer_eight_actions(int key_idx, bool release) {
    if (key_idx == 6 && release && !l_eight_lock)
        layer_move(_DEFAULT);
    if (release) return;

    switch (key_idx) {
        case 1:
            tap_code16(G(KC_S)); // shuffle
            break;
        case 2:
            tap_code16(G(KC_R)); // repeat
            break;
        case 3:
            l_eight_lock = true;
            layer_move(_MUSIC);
            break;
        case 4:
            tap_code16(G(S(KC_RBRC))); // open spotify w/ BTT
            break;
        case 5:
            tap_code(KC_BSPC); // delete for removing a song from the playlist
            break;
        case 6:
            layer_move(_DEFAULT);
            break;
    }
}

void (*layer_actions[9]) (int, bool) = {
    default_actions,
    layer_one_actions,
    layer_two_actions,
    layer_three_actions,
    layer_four_actions,
    layer_five_actions,
    layer_six_actions,
    layer_seven_actions,
    layer_eight_actions
};

void key_switch(int key_idx, bool release) {
    (*layer_actions[get_layer()]) (key_idx, release);
}

// NOTE: START OF TAPDANCES

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
        case TD_SINGLE_TAP:
            key_switch(key_idx, false);
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
    if (key_one_tap_state.state == TD_SINGLE_HOLD || key_one_tap_state.state == TD_SINGLE_TAP) {
        key_switch(1, true);
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
    if (key_two_tap_state.state == TD_SINGLE_HOLD || key_two_tap_state.state == TD_SINGLE_TAP) {
        key_switch(2, true);
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
    if (key_three_tap_state.state == TD_SINGLE_HOLD || key_three_tap_state.state == TD_SINGLE_TAP) {
        key_switch(3, true);
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
    if (key_four_tap_state.state == TD_SINGLE_HOLD || key_four_tap_state.state == TD_SINGLE_TAP) {
        key_switch(4, true);
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
    if (key_five_tap_state.state == TD_SINGLE_HOLD || key_five_tap_state.state == TD_SINGLE_TAP) {
        key_switch(5, true);
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
    if (key_six_tap_state.state == TD_SINGLE_HOLD || key_six_tap_state.state == TD_SINGLE_TAP) {
        key_switch(6, true);
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
