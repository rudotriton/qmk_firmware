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
  TEST_NEXT_LED,
  TEST_PREV_LED,
  RM_TOG,
  RM_MOD,
  RM_RMOD,
  RM_HDE,
  RM_HIN,
  RM_SDE,
  RM_SIN,
  RM_VDE,
  RM_VIN,
  RM_SPD,
  RM_SPI
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

// led indices
#define _LA 0
#define _LB 18
#define _LC 36
#define _LD 54

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
  KC_TAB,        KC_Q,         LCTL_T(KC_W),      LCTL_T(KC_F), KC_P,                KC_G, KC_J, KC_L,                RCTL_T(KC_U), RCTL_T(KC_Y),      KC_SCLN,      KC_LBRC, KC_RBRC, KC_BSPC,
  CTL_T(KC_ESC), LSFT_T(KC_A), LT(_NUMPAD, KC_R), LALT_T(KC_S), LT(_SYMBOLS, KC_T),  KC_D, KC_H, LT(_SYMBOLS, KC_N),  RALT_T(KC_E), LT(_NUMPAD, KC_I), RSFT_T(KC_O), KC_QUOT, KC_ENT,
  KC_LSFT,       KC_Z,         KC_X,              KC_C,         LCMD_T(KC_V),        KC_B, KC_K, RCMD_T(KC_M),        KC_COMM,      KC_DOT,            KC_SLSH,      KC_RSFT, FN_MO46,
  KC_LALT, KC_LCMD,                                          KC_SPC,                             KC_RCMD, FN_MO56),

  [_QWERTYM] = LAYOUT_60_hhkb(
  KC_ESC,        KC_1,         KC_2,              KC_3,         KC_4,                KC_5, KC_6, KC_7,                KC_8,         KC_9,              KC_0,            KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,        KC_Q,         LCTL_T(KC_W),      LCTL_T(KC_E), KC_R,                KC_T, KC_Y, KC_U,                RCTL_T(KC_I), RCTL_T(KC_O),      KC_P,            KC_LBRC, KC_RBRC, KC_BSPC,
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
  KC_CAPS,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, FN_MO46,
  KC_LALT, KC_LCMD,                 KC_SPC,               KC_RCMD, FN_MO56),

  // Fn2 Layer
  [_FNONE] = LAYOUT_60_hhkb(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  XXXXXXX,
  TEST_PREV_LED, TEST_NEXT_LED, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   XXXXXXX, KC_DEL,
  KC_CAPS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, XXXXXXX, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, XXXXXXX,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, KC_RSFT, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),

  // Fn3 Layer
  [_FNTWO] = LAYOUT_60_hhkb(
  XXXXXXX, TO(_COLEMAKM), TO(_QWERTYM), TO(_COLEMAK), TO(_QWERTY), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, RM_MOD,        RM_RMOD,      RM_HDE,       RM_HIN,      RM_SPD,  RM_SPI,  RM_TOG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_SLCK,       KC_PAUS,      RM_SDE,       RM_SIN,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX,       XXXXXXX,      RM_VDE,       RM_VIN,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),

  // Fn5 Layer - both fn keys
  [_FNBOTH] = LAYOUT_60_hhkb(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),

  [_SYMBOLS] = LAYOUT_60_hhkb(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_ESC,  KC_HASH, KC_LPRN, KC_RPRN, KC_PIPE, KC_CIRC, KC_MINS, KC_EQL,  KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_EXLM, KC_GRV,  KC_LBRC, KC_RBRC, KC_AT,   KC_BSLS, KC_UNDS, KC_PERC, KC_DLR,  KC_QUES, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, KC_TILD, KC_LCBR, KC_RCBR, KC_ENT,  KC_AMPR, KC_PLUS, KC_QUOT, KC_DQUO, XXXXXXX, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_ENT,                            KC_TRNS, KC_TRNS),

  // numpad and arrow layer
  [_NUMPAD] = LAYOUT_60_hhkb(
  XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX,       XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, LCTL_T(KC_HOME), KC_UP,         KC_END,          XXXXXXX, XXXXXXX, KC_7,         RCTL_T(KC_8), RCTL_T(KC_9), XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_TAB,  KC_LEFT,         KC_DOWN,       KC_RIGHT,        KC_ESC,  KC_BSPC, KC_4,         KC_5,         KC_6,         RSFT_T(XXXXXXX), XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, LCTL(KC_LEFT),   LCTL(KC_RGHT), LCMD_T(XXXXXXX), XXXXXXX, KC_0,    RCMD_T(KC_1), KC_2,         KC_3,         XXXXXXX,         KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS),
};

static int test_led_index, test_color;

void rgb_matrix_indicators_user(void) {
  rgb_matrix_set_color(test_led_index, (test_color == 0) * 255, (test_color == 1) * 255, (test_color == 2) * 255);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TEST_NEXT_LED:
      if(record->event.pressed) {
        if (++test_color > 2) {
          test_color = 0;
          if (++test_led_index >= DRIVER_LED_TOTAL) {
            test_led_index = 0;
          }
        }
      }
      break;
    case TEST_PREV_LED:
      if(record->event.pressed) {
        if (--test_color < 0) {
          test_color = 2;
          if (--test_led_index < 0) {
            test_led_index = DRIVER_LED_TOTAL - 1;
          }
        }
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
      return false; // Skip all further processing of this key
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
      }
      return false; // Skip all further processing of this key
      break;
    case RM_MOD:
      if (record->event.pressed) {
        rgb_matrix_step_noeeprom();
      }
      return false;
      break;
    case RM_RMOD:
      if (record->event.pressed) {
        rgb_matrix_step_reverse_noeeprom();
      }
      return false;
      break;
    case RM_HDE:
      if (record->event.pressed) {
        rgb_matrix_decrease_hue_noeeprom();
      }
      return false;
      break;
    case RM_HIN:
      if (record->event.pressed) {
        rgb_matrix_increase_hue_noeeprom();
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
      return true; // Process all other keycodes normally
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
    default:
      return false;
  }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color(8, RGB_GREEN);
    // for (uint8_t i = led_min; i <= led_max; i++) {
    // if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
    // rgb_matrix_set_color(i, RGB_GREEN);
    // }
    // }
  }
}

void keyboard_post_init_user(void) {
  // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  // rgb_matrix_sethsv_noeeprom(RGB_WHITE);
  // rgb_matrix_set_color(45, RGB_RED);
  rgb_matrix_enable_noeeprom(); // enables Rgb, without saving settings
  rgb_matrix_sethsv_noeeprom(180, 255, 255);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // int value = rgb_matrix_get_val();
  switch (get_highest_layer(state)) {
    case _QWERTYM:
      // rgb_matrix_sethsv_noeeprom(0, 255, 0);
      break;
    case _COLEMAK:
      // rgb_matrix_sethsv_noeeprom(0, 0, 255);
      break;
    case _QWERTY:
      // rgb_matrix_sethsv_noeeprom(255, 255, 0);
      break;
    case _FNONE:
      rgb_matrix_sethsv_noeeprom(HSV_GOLD);
      break;
    case _FNTWO:
      rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
      break;
    case _FNBOTH:
      rgb_matrix_sethsv_noeeprom(HSV_PINK);
      break;
    case _SYMBOLS:
      rgb_matrix_sethsv_noeeprom(HSV_TURQUOISE);
      break;
    case _NUMPAD:
      rgb_matrix_sethsv_noeeprom(HSV_CORAL);
      break;
    default: //  for any other layers, or the default layer
      rgb_matrix_sethsv_noeeprom(HSV_WHITE);
      break;
  }
  return state;
}

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
#define DRIVER_ADDR_1 0x74
#define DRIVER_ADDR_2 0x76

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
*   driver
*   |  R location
*   |  |      G location
*   |  |      |      B location
*   |  |      |      | */
  {0, C2_1,  C3_1, C4_1},   // LA0 u
  {0, C1_1,  C3_2, C4_2},   // LA1 y
  {0, C1_2,  C2_2, C4_3},   // LA2 t
  {0, C1_3,  C2_3, C3_3},   // LA3 r
  {0, C1_4,  C2_4, C3_4},   // LA4 e
  {0, C1_5,  C2_5, C3_5},   // LA5 w
  {0, C1_6,  C2_6, C3_6},   // LA6 q
  {0, C1_7,  C2_7, C3_7},   // LA7 tab
  {0, C1_8,  C2_8, C3_8},   // LA8 caps
  {0, C9_1,  C8_1, C7_1},   // LA9 8
  {0, C9_2,  C8_2, C7_2},   // LA10 7
  {0, C9_3,  C8_3, C7_3},   // LA11 6
  {0, C9_4,  C8_4, C7_4},   // LA12 5
  {0, C9_5,  C8_5, C7_5},   // LA13 4
  {0, C9_6,  C8_6, C7_6},   // LA14 3
  {0, C9_7,  C8_7, C6_6},   // LA15 2
  {0, C9_8,  C7_7, C6_7},   // LA16 1
  {0, C8_8,  C7_8, C6_8},   // LA17 esc

  {0, C2_9,  C3_9,  C4_9},  // LB0 9
  {0, C1_9,  C3_10, C4_10}, // LB1 0
  {0, C1_10, C2_10, C4_11}, // LB2 -
  {0, C1_11, C2_11, C3_11}, // LB3 +
  {0, C1_12, C2_12, C3_12}, // LB4 |
  {0, C1_13, C2_13, C3_13}, // LB5 delete
  {0, C9_9,  C8_9,  C7_9},  // LB9 i
  {0, C9_10, C8_10, C7_10}, // LB10 o
  {0, C9_11, C8_11, C7_11}, // LB11 p
  {0, C9_12, C8_12, C7_12}, // LB12 [
  {0, C9_13, C8_13, C7_13}, // LB13 ]
  {0, C9_14, C8_14, C7_14}, // LB14 backspace

  {1, C2_1,  C3_1, C4_1}, // LC0 space
  {1, C1_1,  C3_2, C4_2}, // LC1 b
  {1, C1_2,  C2_2, C4_3}, // LC2 v
  {1, C1_3,  C2_3, C3_3}, // LC3 c
  {1, C1_4,  C2_4, C3_4}, // LC4 x
  {1, C1_5,  C2_5, C3_5}, // LC5 z
  {1, C1_6,  C2_6, C3_6}, // LC6 left stab, weird colors
  {1, C1_7,  C2_7, C3_7}, // LC7 left command
  {1, C1_8,  C2_8, C3_8}, // LC8 left option, weird colors
  {1, C9_1,  C8_1, C7_1}, // LC9 h, weird colors
  {1, C9_2,  C8_2, C7_2}, // LC10 g, weird colors
  {1, C9_3,  C8_3, C7_3}, // LC11 f, -..-
  {1, C9_4,  C8_4, C7_4}, // LC12 d
  {1, C9_5,  C8_5, C7_5}, // LC13 s
  {1, C9_6,  C8_6, C7_6}, // LC14 a
  {1, C9_8,  C7_7, C6_7}, // LC16 left shift

  {1, C2_9,  C3_9,  C4_9},  // LD0 j
  {1, C1_9,  C3_10, C4_10}, // LD1 k
  {1, C1_10, C2_10, C4_11}, // LD2 l
  {1, C1_11, C2_11, C3_11}, // LD3 '
  {1, C1_12, C2_12, C3_12}, // LD4 ;, weird colors
  {1, C1_13, C2_13, C3_13}, // LD5 enter
  {1, C1_14, C2_14, C3_14}, // LD6 /
  {1, C1_15, C2_15, C3_15}, // LD7 right shift
  {1, C1_16, C2_16, C3_16}, // LD8 fn1, weird colors
  {1, C9_9,  C8_9,  C7_9},  // LD9 n, all colors off
  {1, C9_10, C8_10, C7_10}, // LD10 m, colors off
  {1, C9_11, C8_11, C7_11}, // LD11 ,
  {1, C9_12, C8_12, C7_12}, // LD12 .
  {1, C9_14, C8_14, C7_14}, // LD14 right stab
  {1, C9_15, C8_15, C6_14}, // LD15 right command
  {1, C9_16, C7_15, C6_15}, // LD16 right opt
};

led_config_t g_led_config = { {
// Note: Left spacebar stab is at 4,3 (LC6)
// Right spacebar stab is at 4,9 (LD13) or 4,10 (LD14)
//
// A17, A16, A15, A14, A13, A12, A11, A10,  A9,  B0,  B1,  B2,  B3,  B4, B5,
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  A0,  B9, B10, B11, B12, B13, B14,
//  A8, C14, C13, C12, C11, C10,  C9,  D0,  D1,  D2,  D3,  D4,  D5,
// C16, C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12,  D6,  D7,  D8,
  // C17,  C8,  C7,  C6, ---, ---, ---,  C0, ---, D13, D14, D15, D16, D17,
 { _LA+17, _LA+16, _LA+15, _LA+14, _LA+13, _LA+12, _LA+11, _LA+10,  _LA+9, _LB+0, _LB+1, _LB+2, _LB+3, _LB+4 },
 { _LA+7, _LA+6, _LA+5, _LA+4, _LA+3, _LA+2,  _LA+1,  _LA+0, _LB+9, _LB+10, _LB+11, _LB+12, _LB+13, _LB+14 },
 { _LA+8, _LC+14, _LC+13, _LC+12, _LC+11, _LC+10, _LC+9, _LD+0, _LD+1, _LD+2, _LD+3, _LD+4, _LD+5 },
 { _LC+16, _LC+5, _LC+4, _LC+3, _LC+2, _LC+1, _LD+9, _LD+10, _LD+11, _LD+12, _LD+6, _LD+7, _LD+8 },
 { _LC+17, _LC+8, _LC+7, _LC+6,  NO_LED,  NO_LED,  NO_LED, _LC+0, NO_LED, _LD+13, _LD+14, _LD+15, _LD+16, _LD+17 }
}, {
  // LA0..LA17
  {120,16}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {4,16}, {4,32},
  {128,0}, {112,0}, {96,0}, {80,0}, {64,0}, {48,0}, {32,0}, {16,0}, {0,0},
  // LB0..
  {144,0}, {160,0}, {176,0}, {192,0}, {216,0}, {224,0},
  // LB09..
  {136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {220,16},
  // LC0..LC17
  {112,64}, {100,48}, {84,48}, {68,48}, {52,48}, {36,48}, {64,64}, {43,64}, {23,64},
  {108,32}, {92,32}, {76,32}, {60,32}, {44,32}, {28,32}, {2,48},
  // LD0..LD17
  {124,32}, {140,32}, {156,32}, {172,32}, {188,32}, {214,32}, {180,48}, {203,48}, {224,48},
  {116,48}, {132,48}, {148,48}, {164,48}, {161,64}, {181,64}, {201,64},
  }, {
  // LA0..LA17
  1, 1, 1, 1, 1, 1, 1, 4, 4,
  1, 1, 1, 1, 1, 1, 1, 1, 4,
  // LB0..LB17
  1, 1, 1, 1, 1, 4,
  1, 1, 1, 1, 1, 4,
  // LC0..LC17
  1, 1, 1, 1, 1, 1, 1, 4, 4,
  1, 1, 1, 1, 1, 1, 4,
  // LD0..LC17
  1, 1, 1, 1, 1, 4, 4, 4, 4,
  1, 1, 1, 1, 1, 4, 4,
} };
