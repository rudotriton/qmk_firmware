#include "encoder.h"

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
