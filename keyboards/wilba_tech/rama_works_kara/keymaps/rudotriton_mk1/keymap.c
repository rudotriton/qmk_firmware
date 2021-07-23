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
  FN_MO24 = SAFE_RANGE,
  FN_MO34
};

#define _COLEMAK 0
#define _QWERTY 1
#define _SYMBOLS 5
#define _NUMPAD 6

// 0 - colemak
// 1 - qwerty
// 2 - media layer and various such as arrows
// 3 - other controls
// 4 - layer toggles and lighting
// 5 - left index layer
// 6 - right index layer
// 7 - numpar

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default layer
  [_COLEMAK] = LAYOUT_60_hhkb(
    KC_ESC,        KC_1,         KC_2,              KC_3,         KC_4,         KC_5, KC_6, KC_7,         KC_8,         KC_9,              KC_0,         KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,        KC_Q,         LCTL_T(KC_W),      LCTL_T(KC_F), KC_P,         KC_G, KC_J, KC_L,         RCTL_T(KC_U), RCTL_T(KC_Y),      KC_SCLN,      KC_LBRC, KC_RBRC, KC_BSPC,
    CTL_T(KC_ESC), LSFT_T(KC_A), LT(_NUMPAD, KC_R), LALT_T(KC_S), LT(5, KC_T),  KC_D, KC_H, LT(6, KC_N),  RALT_T(KC_E), LT(_NUMPAD, KC_I), RSFT_T(KC_O), KC_QUOT, KC_ENT,
    KC_LSFT,       KC_Z,         KC_X,              KC_C,         LCMD_T(KC_V), KC_B, KC_K, RCMD_T(KC_M), KC_COMM,      KC_DOT,            KC_SLSH,      KC_RSFT, FN_MO24,
        KC_LALT, KC_LCMD,                                          KC_SPC,                             KC_RCMD, FN_MO34),

  [_QWERTY] = LAYOUT_60_hhkb(
    KC_ESC,        KC_1,         KC_2,              KC_3,         KC_4,         KC_5, KC_6, KC_7,         KC_8,         KC_9,              KC_0,            KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,        KC_Q,         LCTL_T(KC_W),      LCTL_T(KC_E), KC_R,         KC_T, KC_Y, KC_U,         RCTL_T(KC_I), RCTL_T(KC_O),      KC_P,            KC_LBRC, KC_RBRC, KC_BSPC,
    CTL_T(KC_ESC), LSFT_T(KC_A), LT(_NUMPAD, KC_S), LALT_T(KC_D), LT(5, KC_F),  KC_G, KC_H, LT(6, KC_J),  RALT_T(KC_K), LT(_NUMPAD, KC_L), RSFT_T(KC_SCLN), KC_QUOT, KC_ENT,
    KC_LSFT,       KC_Z,         KC_X,              KC_C,         LCMD_T(KC_V), KC_B, KC_K, RCMD_T(KC_M), KC_COMM,      KC_DOT,            KC_SLSH,         KC_RSFT, FN_MO24,
        KC_LALT, KC_LCMD,                                          KC_SPC,                             KC_RCMD, FN_MO34),

  // Fn2 Layer
  [2] = LAYOUT_60_hhkb(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  XXXXXXX,
    KC_CAPS, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   XXXXXXX, KC_DEL,
    XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, XXXXXXX, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, XXXXXXX, KC_TRNS,
        XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, KC_TRNS),

  // Fn3 Layer
  [3] = LAYOUT_60_hhkb(
    XXXXXXX, TG(_QWERTY), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, EF_DEC,      EF_INC,  H1_DEC,  H1_INC,  H2_DEC,  H2_INC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BR_DEC,  BR_INC,  XXXXXXX,
    XXXXXXX, KC_SLCK,     KC_PAUS, S1_DEC,  S1_INC,  S2_DEC,  S2_INC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ES_DEC,  ES_INC,
    XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
        XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, KC_TRNS),

  // Fn5 Layer - both fn keys
  [4] = LAYOUT_60_hhkb(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
        XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, KC_TRNS),

  [_SYMBOLS] = LAYOUT_60_hhkb(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_ESC,  KC_HASH, KC_LPRN, KC_RPRN, KC_PIPE, KC_CIRC, KC_MINS, KC_EQL,  KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_EXLM, KC_GRV,  KC_LBRC, KC_RBRC, KC_AT,   KC_BSLS, KC_UNDS, KC_PERC, KC_DLR,  KC_QUES, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_TILD, KC_LCBR, KC_RCBR, KC_ENT,  KC_AMPR, KC_PLUS, KC_QUOT, KC_DQUO, XXXXXXX, XXXXXXX, KC_TRNS,
      XXXXXXX, XXXXXXX,                            KC_ENT,                            XXXXXXX, KC_TRNS),

  // numpad and arrow layer
  [_NUMPAD] = LAYOUT_60_hhkb(
  XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX,       XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, LCTL_T(KC_HOME), KC_UP,         KC_END,          XXXXXXX, XXXXXXX, KC_7,         RCTL_T(KC_8), RCTL_T(KC_9), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_LEFT,         KC_DOWN,       KC_RIGHT,        KC_ESC,  KC_BSPC, KC_4,         KC_5,         KC_6,         XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, LCTL(KC_LEFT),   LCTL(KC_RGHT), LCMD_T(XXXXXXX), XXXXXXX, KC_0,    RCMD_T(KC_1), KC_2,         KC_3,         XXXXXXX, XXXXXXX, KC_TRNS,
      XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, KC_TRNS),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FN_MO24:
      if (record->event.pressed) {
        layer_on(2);
        update_tri_layer(2, 3, 4);
      } else {
        layer_off(2);
        update_tri_layer(2, 3, 4);
      }
      return false; // Skip all further processing of this key
      break;
    case FN_MO34:
      if (record->event.pressed) {
        layer_on(3);
        update_tri_layer(2, 3, 4);
      } else {
        layer_off(3);
        update_tri_layer(2, 3, 4);
      }
      return false;
      break;
    default:
      return true; // Process all other keycodes normally
  }
  return true;
}
