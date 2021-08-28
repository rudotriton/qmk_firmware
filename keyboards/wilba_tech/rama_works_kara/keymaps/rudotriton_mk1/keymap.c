/* Copyright 2021 Jason Williams (Wilba)
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
// Default layout for RAMA WORKS KARA
#include QMK_KEYBOARD_H

enum my_keycodes {
  FN_MO46 = SAFE_RANGE,
  FN_MO56,
  RM_TOG,
  RM_LCL,
  RM_MOD,
  RM_RMOD,
  RM_HDE,
  RM_HIN,
  RM_SDE,
  RM_SIN,
  RM_VDE,
  RM_VIN,
  RM_SPD,
  RM_SPI,
  TEST_NEXT_LED,
  TEST_PREV_LED,
  LED_DEBUG_TOG
};

#define _COLEMAKM 0
#define _QWERTYM 1
#define _COLEMAK 2
#define _QWERTY 3
#define _FNONE 4
#define _FNTWO 5
#define _FNBOTH 6
#define _SYMBOLS 7
#define _NUMPAD 8
#define _MOUSE 9

// 0 - colemak with homerow mods
// 1 - qwerty with homerow mods
// 2 - colemak clean
// 3 - qwerty clean
// 4 - function one media layer and various such as arrows
// 5 - function two keyboard colors
// 6 - function both
// 7 - symbols
// 8 - numpad

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default layer
  [_COLEMAKM] = LAYOUT_60_hhkb(
  KC_ESC,        KC_1,         KC_2,              KC_3,         KC_4,                KC_5, KC_6, KC_7,                KC_8,         KC_9,              KC_0,         KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,        KC_Q,         LCTL_T(KC_W),      LCTL_T(KC_F), KC_P,                KC_G, KC_J, KC_L,                RCTL_T(KC_U), RCTL_T(KC_Y), LT(_MOUSE, KC_SCLN), KC_LBRC, KC_RBRC, KC_BSPC,
  CTL_T(KC_ESC), LSFT_T(KC_A), LT(_NUMPAD, KC_R), LALT_T(KC_S), LT(_SYMBOLS, KC_T),  KC_D, KC_H, LT(_SYMBOLS, KC_N),  RALT_T(KC_E), LT(_NUMPAD, KC_I), RSFT_T(KC_O), KC_QUOT, KC_ENT,
  KC_LSFT,       KC_Z,         KC_X,              KC_C,         LCMD_T(KC_V),        KC_B, KC_K, RCMD_T(KC_M),        KC_COMM,      KC_DOT,            KC_SLSH,      KC_RSFT, FN_MO46,
  KC_LALT, KC_LCMD,                                          KC_SPC,                             KC_RCMD, FN_MO56),

  [_QWERTYM] = LAYOUT_60_hhkb(
  KC_ESC,        KC_1,         KC_2,              KC_3,         KC_4,                KC_5, KC_6, KC_7,                KC_8,         KC_9,              KC_0,            KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,        KC_Q,         LCTL_T(KC_W),      LCTL_T(KC_E), KC_R,                KC_T, KC_Y, KC_U,                RCTL_T(KC_I), RCTL_T(KC_O),     LT(_MOUSE, KC_P), KC_LBRC, KC_RBRC, KC_BSPC,
  CTL_T(KC_ESC), LSFT_T(KC_A), LT(_NUMPAD, KC_S), LALT_T(KC_D), LT(_SYMBOLS, KC_F),  KC_G, KC_H, LT(_SYMBOLS, KC_J),  RALT_T(KC_K), LT(_NUMPAD, KC_L), RSFT_T(KC_SCLN), KC_QUOT, KC_ENT,
  KC_LSFT,       KC_Z,         KC_X,              KC_C,         LCMD_T(KC_V),        KC_B, KC_K, RCMD_T(KC_M),        KC_COMM,      KC_DOT,            KC_SLSH,         KC_RSFT, FN_MO46,
  KC_LALT, KC_LCMD,                                          KC_SPC,                             KC_RCMD, FN_MO56),

  [_COLEMAK] = LAYOUT_60_hhkb(
  KC_ESC,         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,         KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
  CTL_T(KC_BSPC), KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E,    KC_I,   KC_O,    KC_QUOT, KC_ENT,
  KC_LSFT,        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, FN_MO46,
  KC_LALT, KC_LCMD,                 KC_SPC,               KC_RCMD, FN_MO56),

  [_QWERTY] = LAYOUT_60_hhkb(
  KC_ESC,   KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
  KC_LCTL,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, FN_MO46,
  KC_LALT, KC_LCMD,                 KC_SPC,               KC_RCMD, FN_MO56),

  [_FNONE] = LAYOUT_60_hhkb(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  XXXXXXX,
  XXXXXXX, TEST_PREV_LED, TEST_NEXT_LED, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   XXXXXXX, KC_DEL,
  KC_CAPS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, XXXXXXX, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, XXXXXXX,
  KC_TRNS, XXXXXXX, XXXXXXX, KC_MRWD, KC_MFFD, XXXXXXX, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, KC_RSFT, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),

  [_FNTWO] = LAYOUT_60_hhkb(
  TO(_COLEMAKM), TO(_QWERTYM), TO(_COLEMAK), TO(_QWERTY), TO(_FNONE), TO(_FNTWO), TO(_FNBOTH), TO(_SYMBOLS), TO(_NUMPAD), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,       RM_MOD,       RM_RMOD,      RM_HDE,      RM_HIN,     RM_SPD,     RM_SPI,      RM_TOG,       RM_LCL,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,       KC_SLCK,      KC_PAUS,      RM_SDE,      RM_SIN,     XXXXXXX,    XXXXXXX,     XXXXXXX,      XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TRNS,       KC_BRIU,      KC_BRID,      RM_VDE,      RM_VIN,     XXXXXXX,    XXXXXXX,     XXXXXXX,      XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),

  [_FNBOTH] = LAYOUT_60_hhkb(
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
  XXXXXXX, LED_DEBUG_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),

  [_SYMBOLS] = LAYOUT_60_hhkb(
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_ESC,  KC_HASH, KC_LPRN, KC_RPRN, KC_PIPE, KC_CIRC, KC_MINS, KC_EQL,  KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_CAPS, KC_EXLM, KC_GRV,  KC_LBRC, KC_RBRC, KC_AT,   KC_BSLS, KC_UNDS, KC_PERC, KC_DLR,  KC_QUES, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, KC_TILD, KC_LCBR, KC_RCBR, KC_ENT,  KC_AMPR, KC_PLUS, KC_QUOT, KC_DQUO, XXXXXXX, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_ENT,                            KC_TRNS, KC_TRNS),

  // numpad and arrow layer
  [_NUMPAD] = LAYOUT_60_hhkb(
  KC_TRNS, XXXXXXX, XXXXXXX,         XXXXXXX,       XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, LCTL_T(KC_HOME), KC_UP,         KC_END,          XXXXXXX, XXXXXXX, KC_7,         RCTL_T(KC_8), RCTL_T(KC_9), XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_TAB,  KC_LEFT,         KC_DOWN,       KC_RIGHT,        KC_ESC,  KC_BSPC, KC_4,         KC_5,         KC_6,         RSFT_T(XXXXXXX), XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, LCTL(KC_LEFT),   LCTL(KC_RGHT), LCMD_T(XXXXXXX), XXXXXXX, KC_0,    RCMD_T(KC_1), KC_2,         KC_3,         XXXXXXX,         KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),

  [_MOUSE] = LAYOUT_60_hhkb(
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
  XXXXXXX, XXXXXXX, KC_WH_U, KC_MS_U, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),
};

static int test_led_index, test_color;
bool LED_DEBUG = false;

void rgb_matrix_indicators_user(void) {
    if (LED_DEBUG) {
        rgb_matrix_set_color(test_led_index, (test_color == 0) * 255, (test_color == 1) * 255, (test_color == 2) * 255);
    }
}

uint8_t last_mode = RGB_MATRIX_SOLID_COLOR;
int     hue, saturation, value;
bool    color_layers = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TEST_NEXT_LED:
            if (record->event.pressed && LED_DEBUG) {
                if (++test_color > 2) {
                    test_color = 0;
                    if (++test_led_index >= DRIVER_LED_TOTAL) {
                        test_led_index = 0;
                    }
                }
            }
            break;
        case TEST_PREV_LED:
            if (record->event.pressed && LED_DEBUG) {
                if (--test_color < 0) {
                    test_color = 2;
                    if (--test_led_index < 0) {
                        test_led_index = DRIVER_LED_TOTAL - 1;
                    }
                }
            }
            break;
        case LED_DEBUG_TOG:
            if (record->event.pressed) {
              LED_DEBUG = LED_DEBUG ? false : true;
        }
            break;
        case FN_MO46:
            if (record->event.pressed) {
                layer_on(_FNONE);
                update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
            } else {
                layer_off(_FNONE);
                update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
            }
            return false;  // Skip all further processing of this key
            break;
        case FN_MO56:
            if (record->event.pressed) {
                layer_on(_FNTWO);
                update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
            } else {
                layer_off(_FNTWO);
                update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
            }
            return false;
            break;
        case RM_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle_noeeprom();
                if (rgb_matrix_is_enabled()) {
                    rgb_matrix_mode_noeeprom(last_mode);
                }
            }
            return false;  // Skip all further processing of this key
            break;
        case RM_LCL:
            if (record->event.pressed) {
                if (color_layers) {
                    color_layers = false;
                } else {
                    color_layers = true;
                }
            }
            return false;
            break;
        case RM_MOD:
            if (record->event.pressed) {
                rgb_matrix_mode_noeeprom(last_mode);
                rgb_matrix_step_noeeprom();
                last_mode = rgb_matrix_get_mode();
            }
            return false;
            break;
        case RM_RMOD:
            if (record->event.pressed) {
                rgb_matrix_mode_noeeprom(last_mode);
                rgb_matrix_step_reverse_noeeprom();
                last_mode = rgb_matrix_get_mode();
            }
            return false;
            break;
        case RM_HDE:
            if (record->event.pressed) {
                rgb_matrix_decrease_hue_noeeprom();
                hue = rgb_matrix_get_hue();
            }
            return false;
            break;
        case RM_HIN:
            if (record->event.pressed) {
                rgb_matrix_increase_hue_noeeprom();
                hue = rgb_matrix_get_hue();
            }
            return false;
            break;
        case RM_SDE:
            if (record->event.pressed) {
                rgb_matrix_decrease_sat_noeeprom();
            }
            return false;
            break;
        case RM_SIN:
            if (record->event.pressed) {
                rgb_matrix_increase_sat_noeeprom();
            }
            return false;
            break;
        case RM_VDE:
            if (record->event.pressed) {
                rgb_matrix_decrease_val_noeeprom();
            }
            return false;
            break;
        case RM_VIN:
            if (record->event.pressed) {
                rgb_matrix_increase_val_noeeprom();
            }
            return false;
            break;
        case RM_SPD:
            if (record->event.pressed) {
                rgb_matrix_decrease_speed_noeeprom();
            }
            return false;
            break;
        case RM_SPI:
            if (record->event.pressed) {
                rgb_matrix_increase_speed_noeeprom();
            }
            return false;
            break;
        default:
            return true;  // Process all other keycodes normally
    }
    return true;
}

// keys that can be double tapped without them repeting on the second tap
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_NUMPAD, KC_R):
            return true;
        case LT(_NUMPAD, KC_S):
            return true;
        case LT(_SYMBOLS, KC_T):
            return true;
        case LT(_SYMBOLS, KC_N):
            return true;
        default:
            return false;
    }
}

// color caps lock green when caps is on
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        // rgb_matrix_set_color(8, RGB_GREEN);
        int led_seq[] = {17, 16, 15, 14, 13, 12, 11, 10, 9, 18, 19, 20, 21, 22, 23, 30, 29, 28, 27, 26, 25, 24, 0, 1, 2, 3, 4, 5, 6, 7, 8, 45, 44, 43, 42, 41, 40, 47, 48, 49, 50, 51, 52, 55, 54, 53, 59, 58, 57, 56, 32, 33, 34, 35, 36, 46, 39, 38, 37, 31, 60, 61, 62};
        rgb_matrix_enable_noeeprom();  // enables Rgb, without saving settings
        for (int i = 0; i < DRIVER_LED_TOTAL; ++i) {
            rgb_matrix_set_color(led_seq[i], RGB_RED);
        }
    }
}

void keyboard_post_init_user(void) {
    hue           = 180;
    saturation    = 255;
    value         = 200;
    int led_seq[] = {17, 16, 15, 14, 13, 12, 11, 10, 9, 18, 19, 20, 21, 22, 32, 31, 30, 29, 28, 27, 0, 1, 2, 3, 4, 5, 6, 7, 8, 46, 45, 44, 43, 42, 41, 54, 55, 56, 57, 58, 59, 62, 61, 60, 66, 65, 64, 63, 33, 34, 35, 36, 37, 48, 49, 40, 39, 38, 32, 45, 46, 47, 48, 49};
    rgb_matrix_enable_noeeprom();  // enables Rgb, without saving settings
    for (int i = 0; i < DRIVER_LED_TOTAL; ++i) {
        rgb_matrix_set_color(led_seq[i], RGB_RED);
    }
    // rgb_matrix_sethsv_noeeprom(hue, saturation, value);
    // place for a startup animation?
    // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

// if previous layer was default one -> save it
//   toggle bool to false
bool prev_was_default = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    value = rgb_matrix_get_val();  // the currently used brightness
    if (!color_layers) {
        return state;
    }

    if (prev_was_default) {
        last_mode  = rgb_matrix_get_mode();  // get the current animation
        hue        = rgb_matrix_get_hue();
        saturation = rgb_matrix_get_sat();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        prev_was_default = false;
    }

    switch (get_highest_layer(state)) {
        // case _QWERTYM:
        // rgb_matrix_sethsv_noeeprom(0, 0, value);
        // break;
        // case _COLEMAK:
        // rgb_matrix_sethsv_noeeprom(180, 255, value);
        // break;
        // case _QWERTY:
        // rgb_matrix_sethsv_noeeprom(0, 0, value);
        // break;
        case _FNONE:
            rgb_matrix_sethsv_noeeprom(236, 255, value);
            break;
        case _FNBOTH:
            rgb_matrix_sethsv_noeeprom(185, 220, value);
            break;
        case _SYMBOLS:
            rgb_matrix_sethsv_noeeprom(30, 200, value);
            break;
        case _NUMPAD:
            rgb_matrix_sethsv_noeeprom(0, 150, value);
            break;
        default:  //  for any other layer, or the default layer
            // rgb_matrix_sethsv_noeeprom(180, 255, value);
            rgb_matrix_mode_noeeprom(last_mode);
            rgb_matrix_sethsv_noeeprom(hue, saturation, value);
            prev_was_default = true;
            break;
    }
    return state;
}
