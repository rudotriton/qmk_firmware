/* Copyright 2022 @rudotriton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keymap.h"

bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;
bool is_shift_opt_active = false; // small increment volume controls
uint16_t shift_opt_timer = 0;
bool timer_morse_mode = false;
bool morse_evaluated = true;
uint16_t morse_timer = 0;
uint16_t morse_hold_timer = 0;
bool morse_held = false;
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
    [_FIVE] = LAYOUT( KC_TRNS,
                     TD(TD_L_01), TD(TD_L_02), MORSE_KEY,
                     TD(TD_L_04), TD(TD_L_05), TD(TD_L_06)
    ),
    [_META] = double_taps,

    [_RESET] = LAYOUT(
                  KC_TRNS,
    TO(_DEFAULT), KC_NO,   RESET,
    KC_NO,        KC_NO,   KC_NO),

    [_MUSIC] = double_taps,
};

void matrix_scan_user(void) {
    if (is_cmd_tab_active) {
        if (timer_elapsed(cmd_tab_timer) > 1250) {
            unregister_code(KC_RCMD);
            is_cmd_tab_active = false;
        }
    }
    if (is_shift_opt_active) {
        if (timer_elapsed(shift_opt_timer) > 1000) {
            unregister_mods(MOD_MASK_SA);
            is_shift_opt_active = false;
        }
    }
    if (timer_morse_mode && !morse_evaluated && !morse_held) {
        if (timer_elapsed(morse_timer) > 250) {
            eval_morse();
        }
    }

}

int morse_map[] = {
    KC_SPC, // 0
    KC_NO, // 1
    KC_E, // 2
    KC_T, // 3
    KC_I, // 4
    KC_A, // 5
    KC_N, // 6
    KC_M, // 7
    KC_S, // 8
    KC_U, // 9
    KC_R, // 10
    KC_W, // 11
    KC_D, // 12
    KC_K, // 13
    KC_G, // 14
    KC_O, // 15
    KC_H, // 16
    KC_V, // 17
    KC_F, // 18
    KC_NO, // 19
    KC_L, // 20
    KC_NO, // 21
    KC_P, // 22
    KC_J, // 23
    KC_B, // 24
    KC_X, // 25
    KC_C, // 26
    KC_Y, // 27
    KC_Z, // 28
    KC_Q, // 29
    KC_NO, // 30
    KC_NO, // 31
    KC_5, // 32
    KC_4, // 33
    KC_NO, // 34
    KC_3, // 35
    KC_NO, // 36
    KC_NO, // 37
    KC_NO, // 38
    KC_2, // 39
    KC_NO, // 40
    KC_NO, // 41
    KC_NO, // 42
    KC_NO, // 43
    KC_NO, // 44
    KC_NO, // 45
    KC_NO, // 46
    KC_1, // 47
    KC_6, // 48
    KC_NO, // 49
    KC_NO, // 50
    KC_NO, // 51
    KC_NO, // 52
    KC_NO, // 53
    KC_NO, // 54
    KC_NO, // 55
    KC_7, // 56
    KC_NO, // 57
    KC_NO, // 58
    KC_NO, // 59
    KC_8, // 60
    KC_NO, // 61
    KC_9, // 62
    KC_0, // 63
};

unsigned code = 0;

void eval_morse(void) {
    tap_code(morse_map[code]);
    morse_evaluated = true;
    code = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MORSE_KEY:
            if (record->event.pressed) {
                morse_timer = timer_read();
                morse_hold_timer = timer_read();
                morse_evaluated = false;
                morse_held = true;
            } else if (!record->event.pressed) {
                morse_timer = timer_read();
                morse_held = false;
                if (timer_elapsed(morse_hold_timer) > 200) {
                    if (code == 0) {
                        code = 3;
                    } else {
                        code = code * 2 + 1;
                    }
                } else {
                    if (code == 0) {
                        code = 2;
                    } else {
                        code *= 2;
                    }
                }
                // NOTE: allows quick eval, if using codes >= 64 then up this
                if (code >= 32)
                    eval_morse();

            }
            return false;
            break;
        default:
            return true;
            break;
    }

    return true;
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
        case _FIVE:
            if (timer_morse_mode) {
                rgb_matrix_set_color(0, 255, 0, 152);
            } else {
                rgb_matrix_set_color(0, 0, 108, 99);
            }
            rgb_matrix_set_color(led_indices[layer-1], 255, 168, 0);
            break;
        case _META:
            rgb_matrix_set_color(5, 255, 168, 0);
            if (rgb_flag) {
                rgb_matrix_set_color(led_indices[rgb_flag - 1], 0, 108, 255);
            }
            break;
        case _RESET:
            rgb_matrix_set_color(2, 0, 108, 255); // blue
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

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_L_01] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_one_finished, key_one_reset),
    [TD_L_02] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_two_finished, key_two_reset),
    [TD_L_03] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_three_finished, key_three_reset),
    [TD_L_04] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_four_finished, key_four_reset),
    [TD_L_05] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_five_finished, key_five_reset),
    [TD_L_06] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_six_finished, key_six_reset),
};

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

void vim_encoder(bool clockwise) {
    switch (ltwo_flag) {
        case 0:
            if (clockwise) {
                tap_code16(KC_DOWN);
            } else {
                tap_code16(KC_UP);
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
                tap_code(KC_WH_L);
            } else {
                tap_code(KC_WH_R);
            }
            break;
        case 5:
            if (clockwise) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_WH_D);
            }
            break;
        case 6:
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
            break;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_layer()) {
        case _DEFAULT: // volume up/down
            if (!is_shift_opt_active) {
                is_shift_opt_active = true;
                register_mods(MOD_MASK_SA);
            }
            shift_opt_timer = timer_read();
            if (clockwise) {
                tap_code_delay(KC_VOLU, 10);
            } else {
                tap_code_delay(KC_VOLD, 10);
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
        case _FIVE:
            if (clockwise) {
                eval_morse();
            } else {
                tap_code16(KC_BSPC);
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
            tap_code16(G(S(KC_RBRC))); // open spotify w/ BTT
            break;
    }
}

void layer_one_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 1:
            if (!release) {
                if (to_move_win) {
                    tap_code16(G(A(KC_L)));
                } else {
                    tap_code16(C(KC_LEFT)); // prev desktop
                }
            }
            break;
        case 2:
            if (release) {
                unregister_code16(C(KC_UP));
            } else {
                if (to_move_win) {
                    tap_code16(G(A(KC_E)));
                } else {
                    register_code16(C(KC_UP));
                }
            }
            break;
        case 3:
            if (!release) {
                if (to_move_win) {
                    tap_code16(G(A(KC_Y)));
                } else {
                    tap_code16(C(KC_RGHT)); // next desktop
                }
            }
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
            if (is_cmd_tab_active && !release) {
                tap_code(KC_ENT); // allow bypassing the timeout
            } else if (release)
                unregister_code16(KC_F11);
            else
                register_code16(KC_F11);
            break;

    }
}

void layer_two_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 6:
            if (!release) {
                ltwo_flag = key_idx; // 6
            } else {
                ltwo_flag = 0;
            }
            break;
        default:
            if (release) return;
            ltwo_flag = ltwo_flag == key_idx ? 0 : key_idx;
            break;
    }
}

void layer_three_actions(int key_idx, bool release) {
    if (release) return;

    switch (key_idx) {
        case 1:
            tap_code16(G(KC_A));
            break;
        case 2:
            tap_code16(G(KC_C));
            break;
        case 3:
            tap_code16(G(KC_V));
            break;
        case 4:
            tap_code16(G(KC_Z));
            break;
        case 5:
            tap_code16(G(KC_S));
            break;
        case 6:
            tap_code16(G(S(KC_Z)));
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
            tap_code16(G(A(KC_J))); // launch firefox w/ betterTouchTool
            tap_code16(G(KC_T));
            tap_code16(G(KC_V));
            tap_code(KC_ENT);
            break;
    }
}

void layer_five_actions(int key_idx, bool release) {
    if (release) return;

    if (timer_morse_mode) {
        switch (key_idx) {
            case 1:
                tap_code(KC_BSPC);
                break;
            case 2:
                tap_code(KC_SPC);
                break;
            case 6:
                tap_code(KC_ENT);
                break;
        }
    } else {
        switch (key_idx) {
            case 1:
                tap_code(KC_BSPC);
                break;
            case 2:
                eval_morse();
            case 3: // morse key
                break;
            case 4:
                // tap_code16(G(S(KC_BSLS))); // hammerspoon rotate monitor
                tap_code16(G(C(KC_Q))); // lock screen
                break;
            case 5:
                tap_code16(G(A(KC_RBRC))); // toggle system theme
                break;
            case 6:
                tap_code16(G(C(KC_H))); // preview, annotet, highlight
                break;
        }
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
    if (release) return; // early return, since we don't use release for other keys

    switch (key_idx) {
        case 1:
            tap_code16(G(KC_S)); // shuffle
            break;
        case 2:
            tap_code(KC_MPLY);
            break;
        case 3:
            tap_code16(G(KC_R)); // repeat
            break;
        case 4:
            if (l_eight_lock) {
                layer_move(_DEFAULT);
            } else {
                l_eight_lock = true;
                layer_move(_MUSIC);
            }
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

void default_hold_actions(int key_idx, bool release) {
    if (release) return;
    switch (key_idx) {
        case 1:
            tap_code16(G(KC_S)); // shuffle
            break;
        case 3:
            tap_code16(G(KC_R)); // repeat
            break;
        case 6:
            l_eight_lock = false;
            layer_move(_MUSIC);
            break;
    }
}

void layer_one_hold_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 6:
            if (!release) {
                to_move_win = true;
            } else {
                to_move_win = false;
            }
            break;
    }
}

void layer_three_hold_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 1:
            if (!release) {
                register_code(KC_LSHIFT);
            } else {
                unregister_code(KC_LSHIFT);
            }
            break;
        case 4:
            if (!release) {
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
            }
            break;
        case 5:
            if (!release) {
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
            }
            break;
        case 6:
            if (!release) {
                register_code(KC_LCMD);
            } else {
                unregister_code(KC_LCMD);
            }
            break;
    }
}

void layer_five_hold_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 1:
            if (!release) {
                timer_morse_mode = !timer_morse_mode;
            }
            break;
    }
}

void layer_eight_hold_actions(int key_idx, bool release) {
    if (release && (key_idx == 6 || key_idx == 4) && !l_eight_lock)
        layer_move(_DEFAULT);
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
        case 5:
            tap_code(KC_MUTE);
            break;
        case 6:
            tap_code16(G(S(KC_RBRC))); // open spotify w/ BTT
            break;
    }
}

void (*layer_hold_actions[9]) (int, bool) = {
    default_hold_actions,
    layer_one_hold_actions,
    layer_two_actions,
    layer_three_hold_actions,
    layer_four_actions,
    layer_five_hold_actions,
    layer_six_actions,
    layer_seven_actions,
    layer_eight_hold_actions
};

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
        tap_key_switch(key_idx, true);
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

int get_layer(void) {
    for (int i = _DEFAULT; i <= _MUSIC; i++) {
        if (layer_state_is(i)) return i;
    }
    return -1;
}
