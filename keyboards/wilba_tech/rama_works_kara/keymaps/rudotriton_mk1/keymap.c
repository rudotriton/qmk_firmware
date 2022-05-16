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
  RM_TOG = SAFE_RANGE,
  RM_LCL,
  RM_ICL,
  RM_MCL,
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
#define _SYMBOLS 4
#define _NUMPAD 5
#define _MOUSE 6
#define _MIDI 7
#define _FNONE 8
#define _FNTWO 9
#define _FNBOTH 10

// 0 - colemak with homerow mods
// 1 - qwerty with homerow mods
// 2 - colemak clean
// 3 - qwerty clean
// 4 - symbols
// 5 - numpad
// 6 - mouse layer
// 7 - midi layer
// 8 - function one media layer
// 9 - function two hsv controls
// 10 - function both

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
  TD_FN_01,
  TD_FN_02
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default layer
  [_COLEMAKM] = LAYOUT_60_hhkb(
  KC_ESC,        KC_1,              KC_2,              KC_3,         KC_4,               KC_5, KC_6, KC_7,                KC_8,         KC_9,              KC_0,                KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,        LT(_MOUSE, KC_Q),  LCTL_T(KC_W),      LCTL_T(KC_F), KC_P,               KC_G, KC_J, KC_L,                RCTL_T(KC_U), RCTL_T(KC_Y),      LT(_MOUSE, KC_SCLN), KC_LBRC, KC_RBRC, KC_BSPC,
  CTL_T(KC_ESC), LSFT_T(KC_A),      LT(_NUMPAD, KC_R), LALT_T(KC_S), LT(_SYMBOLS, KC_T), KC_D, KC_H, LT(_SYMBOLS, KC_N),  RALT_T(KC_E), LT(_NUMPAD, KC_I), RSFT_T(KC_O),        LT(_FNONE, KC_QUOT), KC_ENT,
  KC_LSFT,       LT(_NUMPAD, KC_Z), KC_X,              KC_C,         LCMD_T(KC_V),       KC_B, KC_K, RCMD_T(KC_M),        KC_COMM,      KC_DOT,            KC_SLSH,             KC_RSFT, TD(TD_FN_01),
  KC_LALT, KC_LCMD,                                          KC_SPC,                            KC_RCMD, TD(TD_FN_02)),

  [_QWERTYM] = LAYOUT_60_hhkb(
  KC_ESC,        KC_1,              KC_2,              KC_3,         KC_4,               KC_5, KC_6, KC_7,                KC_8,         KC_9,              KC_0,            KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,        LT(_MOUSE, KC_Q),  LCTL_T(KC_W),      LCTL_T(KC_E), KC_R,               KC_T, KC_Y, KC_U,                RCTL_T(KC_I), RCTL_T(KC_O),      LT(_MOUSE, KC_P), KC_LBRC, KC_RBRC, KC_BSPC,
  CTL_T(KC_ESC), LSFT_T(KC_A),      LT(_NUMPAD, KC_S), LALT_T(KC_D), LT(_SYMBOLS, KC_F), KC_G, KC_H, LT(_SYMBOLS, KC_J),  RALT_T(KC_K), LT(_NUMPAD, KC_L), RSFT_T(KC_SCLN),  LT(_FNONE, KC_QUOT), KC_ENT,
  KC_LSFT,       LT(_NUMPAD, KC_Z), KC_X,              KC_C,         LCMD_T(KC_V),       KC_B, KC_K, RCMD_T(KC_M),        KC_COMM,      KC_DOT,            KC_SLSH,         KC_RSFT, TD(TD_FN_01),
  KC_LALT, KC_LCMD,                                          KC_SPC,                             KC_RCMD, TD(TD_FN_02)),

  [_COLEMAK] = LAYOUT_60_hhkb(
  KC_ESC,         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,         KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
  CTL_T(KC_BSPC), KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E,    KC_I,   KC_O,    KC_QUOT, KC_ENT,
  KC_LSFT,        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, TD(TD_FN_01),
  KC_LALT, KC_LCMD,                 KC_SPC,               KC_RCMD, TD(TD_FN_02)),

  [_QWERTY] = LAYOUT_60_hhkb(
  KC_ESC,   KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
  KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
  KC_LCTL,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, TD(TD_FN_01),
  KC_LALT, KC_LCMD,                 KC_SPC,               KC_RCMD, TD(TD_FN_02)),

  [_SYMBOLS] = LAYOUT_60_hhkb(
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_ESC,  KC_HASH, KC_LPRN, KC_RPRN, KC_PIPE, KC_CIRC, KC_MINS, KC_EQL,  KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_CAPS, KC_EXLM, KC_GRV,  KC_LBRC, KC_RBRC, KC_AT,   KC_BSLS, KC_UNDS, KC_PERC, KC_DLR,  KC_QUES, XXXXXXX, KC_TRNS,
  KC_TRNS, XXXXXXX, KC_TILD, KC_LCBR, KC_RCBR, KC_ENT,  KC_AMPR, KC_PLUS, KC_QUOT, KC_DQUO, XXXXXXX, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_ENT,                            KC_TRNS, KC_TRNS),

  // numpad and arrow layer
  [_NUMPAD] = LAYOUT_60_hhkb(
  KC_TRNS, XXXXXXX,       XXXXXXX,         XXXXXXX,       XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,       LCTL_T(KC_HOME), KC_UP,         KC_END,      KC_WBAK, KC_WFWD, KC_7,         RCTL_T(KC_8), RCTL_T(KC_9), XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_TAB,        KC_LEFT,         KC_DOWN,       KC_RIGHT,    KC_ESC,  KC_BSPC, KC_4,         RALT_T(KC_5), KC_6,         RSFT_T(KC_SCLN), XXXXXXX, KC_TRNS,
  KC_TRNS, LCTL(KC_DOWN), LCTL(KC_LEFT),   LCTL(KC_RGHT), LCTL(KC_UP), KC_F11,  KC_0,    RCMD_T(KC_1), KC_2,         KC_3,         XXXXXXX,         KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_ESC,                            KC_TRNS, KC_TRNS),

  [_MOUSE] = LAYOUT_60_hhkb(
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_WH_U, KC_MS_U, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX, KC_TRNS,
  KC_TRNS, XXXXXXX, KC_WH_L, XXXXXXX, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_SPC,                            KC_TRNS, KC_TRNS),

  [_MIDI] = LAYOUT_60_hhkb(
  KC_TRNS,   MI_VEL_1, MI_VEL_2, MI_VEL_3, MI_VEL_4, MI_VEL_5, MI_VEL_6, MI_VEL_7, MI_VEL_8, MI_VEL_9, MI_VEL_10, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  MI_LEG,    MI_MOD, MI_Cs, MI_Ds, XXXXXXX, MI_Fs, MI_Gs, MI_As, XXXXXXX, MI_Cs_1, MI_Ds_1, XXXXXXX, XXXXXXX, XXXXXXX,
  MI_ALLOFF, MI_C,    MI_D,  MI_E, MI_F, MI_G, MI_A, MI_B, MI_C_1, MI_D_1, MI_E_1, MI_F_1, XXXXXXX,
  MI_SOFT,   MI_PORT, MI_SOST, MI_VELD, MI_OCTD, XXXXXXX, MI_OCTU, MI_VELU, XXXXXXX, XXXXXXX, XXXXXXX, MI_SOFT, KC_TRNS,
  KC_TRNS,   KC_TRNS,                            MI_SUS,                            KC_TRNS, KC_TRNS),

  [_FNONE] = LAYOUT_60_hhkb(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, KC_MFFD, DM_REC1, DM_REC2, XXXXXXX, KC_PGUP, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  KC_CAPS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, DM_PLY1, DM_PLY2, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_ENT,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_RSTP, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, KC_RSFT, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_SPC,                            KC_TRNS, KC_TRNS),

  [_FNTWO] = LAYOUT_60_hhkb(
  TO(_COLEMAKM), TO(_QWERTYM), TO(_COLEMAK), TO(_QWERTY), TO(_SYMBOLS), TO(_NUMPAD), TO(_MOUSE), TO(_MIDI),  TO(_FNONE), TO(_FNTWO), TO(_FNBOTH), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,       RM_MOD,       RM_RMOD,      RM_HDE,      RM_HIN,     RM_SPD,     RM_SPI,      RM_TOG,       RM_ICL,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,       KC_SLCK,      KC_PAUS,      RM_SDE,      RM_SIN,     XXXXXXX,    XXXXXXX,     XXXXXXX,      XXXXXXX,     RM_LCL, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TRNS,       KC_BRIU,      KC_BRID,      RM_VDE,      RM_VIN,     XXXXXXX,    XXXXXXX,     RM_MCL,       XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_SPC,                            KC_TRNS, KC_TRNS),

  [_FNBOTH] = LAYOUT_60_hhkb(
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
  XXXXXXX, LED_DEBUG_TOG, TEST_PREV_LED, TEST_NEXT_LED, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,                            KC_SPC,                            KC_TRNS, KC_TRNS),

};

static int test_led_index, test_color;
bool LED_DEBUG = false;

void rgb_matrix_indicators_user(void) {
    if (LED_DEBUG) {
        rgb_matrix_set_color(test_led_index, (test_color == 0) * 255, (test_color == 1) * 255, (test_color == 2) * 255);
    }
}

uint8_t last_mode = RGB_MATRIX_SOLID_COLOR;
int     hue, saturation, value, speed;
bool    color_layers = true; // should we switch layer colors
bool    color_indicators = true; // highlight layer indicator
bool    color_meta = true; // highlight current pressed meta key

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
        case RM_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle_noeeprom();
                if (rgb_matrix_is_enabled()) {
                    // restore last mode if matrix is now enabled
                    rgb_matrix_mode_noeeprom(last_mode);
                }
            }
            return false;  // Skip all further processing of this key
            break;
        case RM_LCL:
            if (record->event.pressed) {
              color_layers = color_layers ? false : true;
            }
            return false;
            break;
        case RM_ICL:
            if (record->event.pressed) {
              color_indicators = color_indicators ? false : true;
            }
            return false;
            break;
        case RM_MCL:
            if (record->event.pressed) {
              color_meta = color_meta ? false : true;
            }
            return false;
            break;
        case RM_MOD:
            if (record->event.pressed) {
                rgb_matrix_step_noeeprom();
                last_mode = rgb_matrix_get_mode();
            }
            return false;
            break;
        case RM_RMOD:
            if (record->event.pressed) {
                rgb_matrix_step_reverse_noeeprom();
                last_mode = rgb_matrix_get_mode();
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
                speed = rgb_matrix_get_speed();
            }
            return false;
            break;
        case RM_SPI:
            if (record->event.pressed) {
                rgb_matrix_increase_speed_noeeprom();
                speed = rgb_matrix_get_speed();
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
        case LT(_NUMPAD, KC_R): // vim double-tap replace with number
        case LT(_NUMPAD, KC_S): // same, but for qwerty keeb
        case LT(_SYMBOLS, KC_T): // jump to symbol
        case LT(_SYMBOLS, KC_F): // qwerty, jump onto a symbol
        case LT(_SYMBOLS, KC_N): // things ending in n, followed by a symbol
        case LT(_SYMBOLS, KC_J): // qwerty equivalent
            return true;
        default:
            return false;
    }
}

// int led_seq[] = {17, 16, 15, 14, 13, 12, 11, 10, 9, 18, 19, 20, 21, 22, 23, 29, 28, 27, 26, 25, 24, 0, 1, 2, 3, 4, 5, 6, 7, 8, 44, 43, 42, 41, 40, 39, 46, 47, 48, 49, 50, 51, 54, 53, 52, 58, 57, 56, 55, 31, 32, 33, 34, 35, 45, 38, 37, 36, 30, 59, 60, 61};

// color caps lock green when caps is on
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (color_meta) {
      if (host_keyboard_led_state().caps_lock) {
          rgb_matrix_set_color(8, 73, 255, 143);
      }

      if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
          rgb_matrix_set_color(45, 73, 255, 143);
          rgb_matrix_set_color(53, 73, 255, 143);
      }
      if (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL)) {
          rgb_matrix_set_color(36, 73, 255, 143);
          rgb_matrix_set_color(59, 73, 255, 143);
      }

      // cmd key
      if (get_mods() & MOD_BIT(KC_LGUI) || get_mods() & MOD_BIT(KC_RGUI)) {
          rgb_matrix_set_color(37, 73, 255, 143);
          rgb_matrix_set_color(60, 73, 255, 143);
      }

      if (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))
          rgb_matrix_set_color(38, 73, 255, 143);
    }

    // 1-16, 2-15, 3-14, 4-13, 5-12, 6-11, 7-10, 8-9, ,9-18, 10-19
    if (color_layers && color_indicators) {
      if (layer_state_is(_FNBOTH)) {
          rgb_matrix_set_color(19, 255, 73, 173);
      } else if (layer_state_is(_FNONE)) {
          rgb_matrix_set_color(9, 255, 168, 0);
      } else if (layer_state_is(_FNTWO)) {
          rgb_matrix_set_color(18, 255, 168, 0);
      } else if (layer_state_is(_QWERTYM)) {
          rgb_matrix_set_color(16, 255, 168, 0);
      } else if (layer_state_is(_COLEMAK)) {
          rgb_matrix_set_color(15, 255, 168, 0);
      } else if (layer_state_is(_QWERTY)) {
          rgb_matrix_set_color(14, 255, 168, 0);
      } else if (layer_state_is(_SYMBOLS)) {
          rgb_matrix_set_color(13, 255, 168, 0);
      } else if (layer_state_is(_NUMPAD)) {
          rgb_matrix_set_color(12, 255, 168, 0);
      } else if (layer_state_is(_MOUSE)) {
          rgb_matrix_set_color(11, 255, 168, 0);
      } else if (layer_state_is(_MIDI)) {
          rgb_matrix_set_color(10, 255, 168, 0);
      }
    }
}

void keyboard_post_init_user(void) {
    hue           = 180;
    saturation    = 255;
    value         = 200;
    speed         = 25;
    rgb_matrix_enable_noeeprom();  // enables rgb, without saving settings
    // for (int i = 0; i < driver_led_total; ++i) {
        // rgb_matrix_set_color(led_seq[i], rgb_red);
    // }
    rgb_matrix_sethsv_noeeprom(hue, saturation, value);
    rgb_matrix_set_speed_noeeprom(speed);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
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
        // save default layer settings
        last_mode  = rgb_matrix_get_mode();
        hue        = rgb_matrix_get_hue();
        saturation = rgb_matrix_get_sat();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        prev_was_default = false;
    }

    switch (get_highest_layer(state)) {
        case _SYMBOLS:
            rgb_matrix_sethsv_noeeprom(163, 255, value);
            break;
        case _NUMPAD:
            rgb_matrix_sethsv_noeeprom(205, 235, value);
            break;
        case _MOUSE:
            rgb_matrix_sethsv_noeeprom(115, 255, value);
            break;
        case _MIDI:
            rgb_matrix_sethsv_noeeprom(85, 255, value);
            break;
        case _FNONE:
            rgb_matrix_sethsv_noeeprom(236, 255, value);
            break;
        case _FNBOTH:
            rgb_matrix_sethsv_noeeprom(20, 255, value);
            break;
        default:  //  for any other layer, or the default layer we use the last
          // animation instead
            rgb_matrix_mode_noeeprom(last_mode);
            rgb_matrix_sethsv_noeeprom(hue, saturation, value);
            prev_was_default = true;
            break;
    }
    return state;
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

// Initialize tap structure associated with example tap dance key
static td_tap_t fnone_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void fnone_finished(qk_tap_dance_state_t *state, void *user_data) {
    fnone_tap_state.state = cur_dance(state);
    switch (fnone_tap_state.state) {
        case TD_SINGLE_HOLD:
        case TD_SINGLE_TAP:
            if (layer_state_is(_FNONE)) {
                // If already set, then switch it off
                layer_off(_FNONE);
            } else {
                layer_on(_FNONE);
            }
            update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(_FNTWO))
                layer_off(_FNTWO); // fn2 is above so it would always rule

            // Check to see if the layer is already set
            if (layer_state_is(_FNONE)) {
                // If already set, then switch it off
                layer_off(_FNONE);
            } else {
                // If not already set, then switch the layer on
                layer_on(_FNONE);
            }
            update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
            break;
        default:
            break;
    }
}

void fnone_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (fnone_tap_state.state == TD_SINGLE_HOLD || fnone_tap_state.state == TD_SINGLE_TAP) {
        layer_off(_FNONE);
        update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
    }
    fnone_tap_state.state = TD_NONE;
}

// The same thing for the second fn layer key
static td_tap_t fntwo_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void fntwo_finished(qk_tap_dance_state_t *state, void *user_data) {
    fntwo_tap_state.state = cur_dance(state);
    switch (fntwo_tap_state.state) {
        case TD_SINGLE_HOLD:
        case TD_SINGLE_TAP:
            if (layer_state_is(_FNTWO)) {
                // If already set, then switch it off
                layer_off(_FNTWO);
            } else {
                layer_on(_FNTWO);
            }
            update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(_FNONE))
                layer_off(_FNONE);

            // Check to see if the layer is already set
            if (layer_state_is(_FNTWO)) {
                // If already set, then switch it off
                layer_off(_FNTWO);
            } else {
                // If not already set, then switch the layer on
                layer_on(_FNTWO);
            }
            update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
            break;
        default:
            break;
    }
}

void fntwo_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (fntwo_tap_state.state == TD_SINGLE_HOLD || fntwo_tap_state.state == TD_SINGLE_TAP) {
        layer_off(_FNTWO);
        update_tri_layer(_FNONE, _FNTWO, _FNBOTH);
    }
    fntwo_tap_state.state = TD_NONE;
}
// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_FN_01] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fnone_finished, fnone_reset),
    [TD_FN_02] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fntwo_finished, fntwo_reset)
};
