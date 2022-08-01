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
bool is_shift_opt_active = false;
uint16_t shift_opt_timer = 0;
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

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_L_01] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_one_finished, key_one_reset),
    [TD_L_02] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_two_finished, key_two_reset),
    [TD_L_03] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_three_finished, key_three_reset),
    [TD_L_04] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_four_finished, key_four_reset),
    [TD_L_05] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_five_finished, key_five_reset),
    [TD_L_06] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, key_six_finished, key_six_reset),
};
